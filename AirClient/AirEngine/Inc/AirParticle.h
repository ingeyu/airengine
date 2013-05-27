#ifndef AirParticle_h__
#define AirParticle_h__

#include "AirEngineMovableObject.h"
#include "AirParticleElement.h"

namespace	Air{


	namespace	Engine{
		
		class Particle;
		class ParticleTemplate;
		enum	enumElementHitHandle{
			enEHH_None			=	0,
			enEHH_MarkDead		=	1,
			enEHH_BornElement	=	1<<1,
			enEHH_BornParticle	=	1<<2,
		};
		typedef	U32	(__stdcall	*ElementHitCallback)(
			void*					pThis,
			const ParticleElement&	element,
			U32						hitMask,
			PhysicsObject*			pObject
			);
		struct ParticleCB{
			ParticleCB(){
				pObject	=	NULL;
				pCB		=	NULL;
			};
			void*					pObject;
			ElementHitCallback		pCB;

		};
		class ENGINE_EXPORT	Particle	:	
			public	IProduct,
			public	MovableObject,
			public	Renderable{
		public:
			static AString ProductTypeName;
			struct Info{
				Info(){
					strTemplate=NULL;
					strMaterial=NULL;
				}
				AChar* strTemplate;
				AChar* strMaterial;
			};

			Particle(CAString& str,Info* pInfo);

			virtual	U1					Create();
			virtual	U1					Destroy();
			virtual	void				Update(const FrameTime& frameTime);
			virtual	void				ProcessRenderObject(U32	uiPhaseFlag);

			virtual	Matrix*				GetWorldMatrix();
			virtual	void				OnRender(Render::Device* pDevice);
			virtual	void				AddElement(const Float3& vPos,const Float3& vVelocity,float fSize);
			virtual	void				AddElement(ParticleElement* pElement);
			virtual	void				AddElement();
			void						EnableEmitter(U1	bEnable);
			U1							IsEmitterEnable();
		public:
			inline	U32					GetElementCount()const	{return m_lstElement.size();};
			inline	PElementList&		GetElementList()		{return m_lstElement;};
			inline	ParticleTemplate*	GetTemplate()			{return m_pTemplate;};
			inline	void				SetCallback(const ParticleCB& cb){m_CB=cb;};
			inline	const ParticleCB&	GetCallback()const		{return m_CB;};
			inline	U32					GetCollisionMask(){return m_uiCollisionMask;};
			inline	void				SetCollisionMask(U32 uiMask){m_uiCollisionMask	=	uiMask;}
		protected:
			float							m_fBornTime;
			PElementList					m_lstElement;
			ParticleTemplate*				m_pTemplate;
			Info*							m_pInfo;
			ParticleCB						m_CB;
			U32								m_uiCollisionMask;
			U1								m_bEnableEmitter;
		};

		typedef void*	(*ParticleScriptParser)(StringVector&	vecScript,U32& i);

		class ENGINE_EXPORT	ParticleSystem	:	
			public	IFactoryManager,
			public Singleton<ParticleSystem>
		{
		public:
			ParticleSystem();

			virtual	U1	Initialization();
			virtual	U1	Release();

			void		Update(const FrameTime& frameTime);

			U1		Compile(CAString&	strScript);
			U1		Compile(Data&		data);
			U1		Compile(U8*	pData,U32 uiSize);
			void*	GetTemplateInfo(CAString&	strName);

			U1						AddScriptParser(CAString& strName,ParticleScriptParser pParser);
			template<typename T>
			U1						AddScriptParser(){
				return AddScriptParser(T::ProductTypeName,T::ScriptParser);
			};
			ParticleScriptParser	GetScriptParser(CAString& strName);
		public:
			void*	PTAlloc(U32 uiSize);
			void*	PTAlloc(const void* pData,U32 uiSize);
		protected:
			STD_HASHMAP<AString,void*>					m_mapTemplateInfo;
			Data										m_TemplateData;
			U32											m_uiDataUsed;
			STD_HASHMAP<AString,ParticleScriptParser>	m_mapParser;
			
		};
	}
}
#endif // AirParticle_h__