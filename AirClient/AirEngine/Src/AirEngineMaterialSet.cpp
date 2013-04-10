#include "AirEngineMaterialSet.h"
#include "AirEngineSystem.h"
#include "AirEngineMaterialParse.h"

namespace	Air{
	namespace	Engine{
		MaterialSet::MaterialSet(CAString& strName):TProduct(strName){

		}

		U1	MaterialSet::Create(){

			return	true;
		}
		U1	MaterialSet::Destroy(){
			MaterialMap::iterator	i	=	m_mapMaterial.begin();
			for(;i!=m_mapMaterial.end();i++){
				i->second->ReleaseRef();
			}
			m_mapMaterial.clear();
			return	true;
		}


		Material*	MaterialSet::GetPhaseMaterial(enumPhaseIndex	idx){

			MaterialMap::iterator	i	=	m_mapMaterial.find(idx);
			if(i!=m_mapMaterial.end())
				return	i->second;
			return	NULL;
		}
		void		MaterialSet::RemovePhaseMaterial(enumPhaseIndex	idx){
			MaterialMap::iterator	i	=	m_mapMaterial.find(idx);
			if(i!=m_mapMaterial.end()){
				i->second->ReleaseRef();
				m_mapMaterial.erase(i);
			}

		}
		void		MaterialSet::AddMaterial(Material*	pMaterial){
			//Render::System::GetSingleton()->CreateProduct<Material*>()
			if(pMaterial==NULL)
				return;

			pMaterial->AddRef();

			MaterialMap::iterator	i	=	m_mapMaterial.find(pMaterial->GetPhaseIndex());
			if(i!=m_mapMaterial.end()){
				i->second->ReleaseRef();
				i->second	=	pMaterial;
			}else{
				m_mapMaterial[pMaterial->GetPhaseIndex()]	=	pMaterial;
			}

		}
		void		MaterialSet::AddMaterial(CAString& strMaterialName){
			Material*	pMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material>(strMaterialName);
			if(pMaterial==NULL)
				return;
			AddMaterial(pMaterial);
			pMaterial->ReleaseRef();

		}
		void		MaterialSet::AddRenderObject(Renderable*	pObj,U32	uiPhaseFlag){
			MaterialMap::iterator	i	=	m_mapMaterial.begin();
			Material*	pMaterial	=	NULL;
			for(;i!=m_mapMaterial.end();i++){
				pMaterial	=	i->second;
				enumPhaseIndex	idx	=	pMaterial->GetPhaseIndex();
				if((1<<idx) &uiPhaseFlag){
					pMaterial->AddRenderObject(pObj);
				}
			}
		}

		U1	MSG_Object(MaterialSet* pSet,MaterialSetInfo* pInfo,CAString& strName,U1 bUseSkin){
			AString	strBaseName	=	"Obj_MRT";
			AString	strVS;
			AString	strPS;
			if(bUseSkin)
				strVS	+=	"_Skin";
			else
				strVS	+=	"_NoSkin";

			U32				uiTotalTex	=	1;
			U32				texIndex[4]	=	{0,0,0,0};
			StringVector	vecTextureName;

			MaterialTexteureTypeMap::iterator	itr;
			itr	=	pInfo->mapTexture.find(enMSPT_TexDiffuse);
			if(itr!=pInfo->mapTexture.end()){
				vecTextureName.push_back(itr->second);
			}else{
				vecTextureName.push_back("1x1white.dds");
			}

			itr	=	pInfo->mapTexture.find(enMSPT_TexSpecular);
			if(itr!=pInfo->mapTexture.end()){
				texIndex[1]	=	++uiTotalTex;
				vecTextureName.push_back(itr->second);
				strPS	+=	"_Spec";
			}else{
				strPS	+=	"_NoSpec";
			}

			itr	=	pInfo->mapTexture.find(enMSPT_TexBump);
			if(itr!=pInfo->mapTexture.end()){
				texIndex[2]	=	++uiTotalTex;
				vecTextureName.push_back(itr->second);
				strPS	+=	"_Bump";
			}else{
				strPS	+=	"_NoBump";
			}

			itr	=	pInfo->mapTexture.find(enMSPT_TexSelfillumination);
			if(itr!=pInfo->mapTexture.end()){
				texIndex[3]	=	++uiTotalTex;
				vecTextureName.push_back(itr->second);
				strPS	+=	"_Selfillum";
			}else{
				strPS	+=	"_NoSelfillum";
			}

			AString	strMRT_MT_Name	=	strBaseName+strVS+strPS;
			MaterialTemplateInfo*	pMRT_MT_Info	=	MaterialParse::GetSingleton()->GetMaterialTemplateInfo(strMRT_MT_Name);
			if(pMRT_MT_Info==NULL){
				//构建材质模板
				pMRT_MT_Info	=	new	MaterialTemplateInfo(strMRT_MT_Name);
				pMRT_MT_Info->PhaseIndex	=	enPI_MRT;
				pMRT_MT_Info->uiPriority	=	4;
				pMRT_MT_Info->m_vecPassInfo.resize(1);
				pMRT_MT_Info->m_vecPassInfo[0]	=	new PassInfo("Pass0");

				PassInfo*	pPassInfo	=	pMRT_MT_Info->m_vecPassInfo[0];

				pPassInfo->pShaderArray[enVS]	=	new	ShaderParamInfo(strBaseName	+	strVS);
				pPassInfo->pShaderArray[enPS]	=	new	ShaderParamInfo(strBaseName	+	strPS);

				pPassInfo->pShaderArray[enPS]->m_vecTextureInfo.resize(4);
				for(U32	i=0;i<4;i++){
					TextureUnitInfo&	tuinfo	=	pPassInfo->pShaderArray[enPS]->m_vecTextureInfo[i];
					tuinfo.index			=	texIndex[i];
					tuinfo.uiRigister		=	i;
					tuinfo.strSamplerState	=	"SS_WarpLine2";
				}

				MaterialParse::GetSingleton()->AddInfo(strMRT_MT_Name,pMRT_MT_Info);
			}



			Material::Info	info;
			info.strTemplate	=	strMRT_MT_Name;
			info.bUseSkin		=	bUseSkin;
			info.vecFloatParam.resize(4);
			memcpy(&info.vecFloatParam[0],&pInfo->diffuse_opacity,sizeof(Float4)*4);
			info.vecTextureName	=	vecTextureName;

			
			Material*	pMRT	=	EngineSystem::GetSingleton()->CreateProduct<Material>(strMRT_MT_Name+strName,&info);
			if(pMRT!=NULL){
				pSet->AddMaterial(pMRT);
				pMRT->ReleaseRef();
			}

			
			return	true;
		};

		MaterialSetGenerator::MaterialSetGenerator()
		{

		}

		MaterialSetGenerator::~MaterialSetGenerator()
		{
			m_mapGeneratorFunc.clear();
		}

		void MaterialSetGenerator::AddGenerator( CAString& strTypeName,GeneratorFunc func )
		{
			if(strTypeName.empty())
				return;
			if(func	==	NULL)
				return;

// 			GeneratorFuncMap::iterator	i	=	m_mapGeneratorFunc.find(strTypeName);
// 			if(i!=m_mapGeneratorFunc.end()){
// 				i->second	=	func;
// 			}else{
				m_mapGeneratorFunc[strTypeName]	=	func;
//			}
		}

		MaterialSet* MaterialSetGenerator::GenerateMaterialSet( CAString& strName,CAString& strType,U1 bUseSkin,MaterialSetInfo* pSetInfo /*= NULL*/ )
		{
	

			GeneratorFuncMap::iterator	i	=	m_mapGeneratorFunc.find(strType);
			if(i!=m_mapGeneratorFunc.end()){
				MaterialSetInfo*	pInfo	=	pSetInfo;
				if(pInfo==NULL){
					pInfo	=	MaterialParse::GetSingleton()->GetMaterialSetInfo(strName);
					if(pInfo==NULL){
						//找不到材质 赋予默认材质
						return	NULL;
					}
				}

				GeneratorFunc	func	=	i->second;
				if(func==NULL)
					return	NULL;

				//修改材质集名称
				AString	strMaterialSetName	=	strName;
				if(bUseSkin)
					strMaterialSetName		+=	"Skin";	

				MaterialSet*	pSet	=	EngineSystem::GetSingleton()->GetProduct<MaterialSet>(strMaterialSetName);
				if(pSet!=NULL){
					return	pSet;
				}else{
					pSet				=	EngineSystem::GetSingleton()->CreateProduct<MaterialSet>(strMaterialSetName);
				}

				(*func)(pSet,pSetInfo,strType,bUseSkin);

				return	pSet;
			}

			return	NULL;
		}

	}
}