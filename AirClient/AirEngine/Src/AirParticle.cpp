#include "AirParticle.h"
#include "AirParticleTemplate.h"
#include "AirParticleRenderer.h"
#include "AirCommonParse.h"
#include "AirParticleEmitter.h"
#include "AirParticleAffector.h"
#include "AirParticleRenderer.h"
namespace	Air{
	namespace	Engine{
		AString Particle::ProductTypeName="Particle";
		Particle::Particle( CAString& str,Info* pInfo ):IProduct(str)
		{
			m_pTemplate	=	NULL;
			m_pInfo=pInfo;
			m_fBornTime	=	0;
			m_bNeedWorldMatrix	=	true;
			m_BoundingBox.vMin	=	Float3(-100,-100,-100);
			m_BoundingBox.vMax	=	Float3(100,100,100);

		}

		Air::U1 Particle::Create()
		{
			if(m_pInfo==NULL)
			{
				return false;
			}
			m_fBornTime	=	GetTimer().m_FrameTime.fTotalTime;
			m_pTemplate	=	ParticleSystem::GetSingleton()->CreateProduct<ParticleTemplate>(m_pInfo->strTemplate);
			if(m_pTemplate==NULL)
				return false;
			if(m_pInfo->strMaterial!=NULL){
				SetMaterialName(m_pInfo->strMaterial);
			}else{
				SetMaterial(m_pTemplate->GetMaterial());
			}
			return true;
		}

		Air::U1 Particle::Destroy()
		{
			PElementList::iterator i = m_lstElement.end();
			for(;i!=m_lstElement.end();i++){
				delete (*i);
			}
			m_lstElement.clear();
			SAFE_RELEASE_REF(m_pTemplate);
			return true;
		}

		void Particle::Update( const FrameTime& frameTime )
		{
			if(m_pTemplate->GetLife()	>	0){
				if(m_pTemplate->GetLife() + m_fBornTime	<	frameTime.fTotalTime){
					return;
				}
			}
			//当前帧不可见
			if(frameTime.uiFrameIndex	!=	m_uiVisiableFrame){
				return;
			}
			if(m_pTemplate!=NULL){
				m_pTemplate->Update(frameTime,this);
			}
		}

		void Particle::OnRender( Render::Device* pDevice )
		{
			ParticleRenderer* pRenderer	=	m_pTemplate->GetRenderer();
			if(pRenderer!=NULL)
				pRenderer->OnParticleRender(pDevice,this);
		}

		Matrix* Particle::GetWorldMatrix()
		{
			return &m_WorldMatrix;
		}

		void Particle::ProcessRenderObject( U32 uiPhaseFlag )
		{
			AddToRenderQueue(uiPhaseFlag);
		}

		void Particle::AddElement( const Float3& vPos,const Float3& vVelocity,float fSize )
		{
			ParticleElement* pElement	=	new ParticleElement;
			
			pElement->vPos			=	vPos;
			pElement->vVelocity		=	vVelocity;
			pElement->fSize		=	fSize;
			AddElement(pElement);
		}

		void Particle::AddElement( ParticleElement* pElement )
		{
			if(pElement==NULL)
				return;
			pElement->fBornTime	=	GetTimer().m_FrameTime.fTotalTime;
			m_lstElement.push_back(pElement);
		}

		ParticleSystem::ParticleSystem()
		{
			m_uiDataUsed	=	0;
		}

		Air::U1 ParticleSystem::Initialization()
		{
			m_TemplateData.ReSize(4*1048576);

			AddFactory(new ParamFactory<ParticleEmitter>());
			AddFactory(new ParamFactory<BoxEmitter>());
			AddFactory(new ParamFactory<SphereEmitter>());
			AddFactory(new OptionParamFactory<ParticleAffector>());
			AddFactory(new OptionParamFactory<ParticleRenderer>());
			AddFactory(new OptionParamFactory<DirectionRenderer>());
			AddFactory(new NoParamFactory<ParticleTemplate>());
			AddFactory(new ParamFactory<Particle>());

			AddScriptParser<ParticleEmitter>();
			AddScriptParser<BoxEmitter>();
			AddScriptParser<SphereEmitter>();
			AddScriptParser<ParticleTemplate>();
			AddScriptParser<ParticleAffector>();
			AddScriptParser<ParticleRenderer>();
			AddScriptParser<DirectionRenderer>();
			
			return true;
		}

		Air::U1 ParticleSystem::Release()
		{
			m_mapParser.clear();
			m_mapTemplateInfo.clear();
			m_TemplateData.Clear();
			return true;

		}

		void ParticleSystem::Update( const FrameTime& frameTime )
		{
			class UpdateParticle:public Common::TraversalCallback{
			public:
				UpdateParticle(const FrameTime& frameTime):t(frameTime){

				};
				virtual	void	OnTraversal(IProduct* pProduct){
					Particle* p = (Particle*)pProduct;
					p->Update(t);
				}
				const FrameTime& t;
			};

			IFactory* pFactory	=	GetFactory(Particle::ProductTypeName);
			if(pFactory!=NULL){
				UpdateParticle tempUpdate(frameTime);
				pFactory->TraversalProduct(&tempUpdate);
			}
		}

		U1 ParticleSystem::Compile( CAString& strScript )
		{
			return Compile((U8*)strScript.c_str(),strScript.size()+1);
		}

		U1 ParticleSystem::Compile( Data& data )
		{
			return Compile(data.buff,data.size);
		}

		U1 ParticleSystem::Compile( U8*	pData,U32 uiSize )
		{
			{
				if(pData==NULL||uiSize==0)
					return false;
				StringVector	vecWord;
				if(!Common::Parse::StringToWord(pData,uiSize,vecWord)){
					return false;
				}

				
				
				U32 i=0;
				while(i<vecWord.size())
				{
					
					AString& str = vecWord[i++];
					if(str == "ParticleTemplate"){
						AString& strName	=	vecWord[i++];
						ParticleScriptParser pParser = GetScriptParser(str);
						if(pParser!=NULL){
							m_mapTemplateInfo[strName]	=	(*pParser)(vecWord,i);
						}
						
					}
				}

				return true;
			}
		}

		void* ParticleSystem::PTAlloc( U32 uiSize )
		{
			U8*	p	=	&m_TemplateData.buff[m_uiDataUsed];
			m_uiDataUsed+=uiSize;
			return p;
		}

		void* ParticleSystem::PTAlloc( const void* pData,U32 uiSize )
		{
			void*	p	=	PTAlloc(uiSize);
			memcpy(p,pData,uiSize);
			return p;
		}

		void* ParticleSystem::GetTemplateInfo( CAString& strName )
		{
			STD_HASHMAP<AString,void*>::iterator i = m_mapTemplateInfo.find(strName);
			if(i==m_mapTemplateInfo.end())
				return NULL;
			return i->second;
		}

		U1 ParticleSystem::AddScriptParser( CAString& strName,ParticleScriptParser pParser )
		{
			if(pParser==NULL)
				return	false;
			if(strName.empty())
				return false;
			STD_HASHMAP<AString,ParticleScriptParser>::iterator i = m_mapParser.find(strName);
			if(i!=m_mapParser.end()){
				i->second=pParser;
			}else{
				m_mapParser[strName]	=	pParser;
			}
			return true;
		}

		Air::Engine::ParticleScriptParser ParticleSystem::GetScriptParser( CAString& strName )
		{
			STD_HASHMAP<AString,ParticleScriptParser>::iterator i = m_mapParser.find(strName);
			if(i!=m_mapParser.end()){
				return i->second;
			}
			return NULL;
		}

	}
}