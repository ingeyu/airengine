#include "AirSceneLoader.h"
#include "AirEngineMaterialParse.h"
#include "AirMeshEntity.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"

namespace	Air{
	namespace	Engine{


		SceneLoader::SceneLoader()
		{
			m_pNode	=	NULL;
		}

		Air::U1 SceneLoader::Load( CAString& strSceneName )
		{
			Unload();


			Data data;
			ResourceSystem*	pResSys	=	ResourceSystem::GetSingleton();

			pResSys->Find(strSceneName,data);

			IniFile	file;
			file.LoadFileFromMemory(&data);

			StringVector&	pVec	=	*file.GetStringList("Mesh","Scene");

			AString	strPath;
			AString	strScene;
			Common::Converter::SplitFilePath(strSceneName,&strPath,&strScene);




			

			//m_pParentNode->SetScale(Float3(0.01,0.01,0.01));

			U32	uiMeshCount	=	pVec.size();
			for(U32 i=0;i<uiMeshCount;i++){

	
				MeshEntity*	pEnt = AddEntity(strPath+pVec[i]);
				
				
			}

			return	true;
		}

		Air::U1 SceneLoader::Unload()
		{
			MeshEntityList::iterator	i	=	m_lstEntity.begin();
			for(;i!=m_lstEntity.end();i++){
				(*i)->ReleaseRef();
			}
			m_lstEntity.clear();
			m_pNode->RemoveAllChild(true);
			return	true;
		}

		void SceneLoader::SetNode( SceneNode* pParent )
		{
			m_pNode	=	pParent->CreateChildSceneNode();
			//m_pNode->SetScale(3);
		}

		MeshEntity* SceneLoader::AddEntity( CAString& strName,Transform* ptrans )
		{
			AString	strPath;
			Common::Converter::SplitFilePath(strName,&strPath);

			Material::Info	minfo;
			minfo.strTemplate	=	"MT_Object";
			minfo.bUseSkin		=	false;
			minfo.vecFloatParam.resize(4);
			minfo.vecTextureName.resize(1);

			minfo.vecFloatParam[0]	=	Float4(1,1,1,1);
			minfo.vecFloatParam[1]	=	Float4(1,1,1,0);
			minfo.vecFloatParam[2]	=	Float4(0.1,0.1,0.1,0.1);
			minfo.vecFloatParam[3]	=	Float4(0,0,0,0);

			MeshEntity::Info	info;
			info.strMeshName	=	strName;
			info.strMaterial	=	"NoMaterial";

			static U32 iCount=0;

			MeshEntity*	pEnt	=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity>(strName+Common::Converter::ToString(iCount++),&info);

			AString	strMSName	=	pEnt->GetMesh()->GetMaterialName();

			MaterialSetInfo*	pInfo	=	MaterialParse::GetSingleton()->GetMaterialSetInfo(strMSName);
			if(pInfo!=NULL){

				minfo.vecFloatParam[0]	=	pInfo->diffuse_opacity;
				minfo.vecFloatParam[2]	=	pInfo->specular_glossiness;
				minfo.vecFloatParam[3]	=	pInfo->selfIllumColor_fresnel;
				Material::Info	mdepthinfo;

				if(!pInfo->mapTexture[enMSPT_TexOpacity].empty()){
					minfo.vecFloatParam[1].w	=	0.5;
					mdepthinfo.strTemplate		=	"MT_Object_ShadowDepth_AlphaTest";
					mdepthinfo.vecTextureName.resize(1);
					mdepthinfo.vecTextureName[0]	=	strPath+pInfo->mapTexture[enMSPT_TexDiffuse];
				}else{
					minfo.vecFloatParam[1].w	=	0.0;
					mdepthinfo.strTemplate		=	"MT_Object_ShadowDepth";
				}
				minfo.vecTextureName[0]		=	strPath+pInfo->mapTexture[enMSPT_TexDiffuse];
				if(pInfo->mapTexture[enMSPT_TexDiffuse].empty()){
					minfo.vecTextureName[0]	=	"../Data/Texture/1x1white.png";
				}

				Material*	p	=	EngineSystem::GetSingleton()->CreateProduct<Material>(strMSName+"MRT",&minfo);
				pEnt->SetMaterial(p);
				p->ReleaseRef();

				p	=	EngineSystem::GetSingleton()->CreateProduct<Material>(strMSName+"ShadowDepth",&mdepthinfo);
				pEnt->SetMaterial(p);
				p->ReleaseRef();

			}
			
			SceneNode* pNode	=	NULL;
			if(ptrans!=NULL){
				pNode	=	m_pNode->CreateChildSceneNode(ptrans->pos,ptrans->rot,ptrans->scale);
			}else{
				pNode	=	m_pNode->CreateChildSceneNode();
			}
			pNode->attachObject(pEnt);
			m_lstEntity.push_back(pEnt);
			return pEnt;
		}

		void SceneLoader::RemoveEntity( MeshEntity* pEnt )
		{
			if(pEnt->GetParentSceneNode()!=m_pNode){
				m_pNode->RemoveChild(pEnt->GetParentSceneNode(),true);
			}
			
			m_lstEntity.remove(pEnt);
			SAFE_RELEASE_REF(pEnt);
		}

	}
}