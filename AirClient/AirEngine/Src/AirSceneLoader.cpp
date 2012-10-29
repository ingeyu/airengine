#include "AirSceneLoader.h"
#include "AirEngineMaterialParse.h"
#include "AirMeshEntity.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"

namespace	Air{
	namespace	Client{


		SceneLoader::SceneLoader()
		{
			m_pParentNode	=	NULL;
		}

		Air::U1 SceneLoader::Load( CAString& strSceneName )
		{
			Unload();

			//U8*	pData=NULL;
			//U32	uiSize=0;
			//Common::File::Load(strSceneName+".material",pData,uiSize);
			Data data;
			Resource::ISystem*	pResSys	=	GetGlobalSetting().m_pResourceSystem;
			pResSys->Find(strSceneName+".material",data);
			MaterialParse::GetSingleton()->CompileMaterialSet(data.buff,data.size);//uiSize);
			pResSys->Find(strSceneName,data);

			IniFile	file;
			file.LoadFileFromMemory(&data);

			StringVector&	pVec	=	*file.GetStringList("Mesh","Scene");

			AString	strPath;
			AString	strScene;
			Common::Converter::SplitFilePath(strSceneName,&strPath,&strScene);


			Material::Info	minfo;
			minfo.strTemplate	=	"MT_Object";
			minfo.bUseSkin		=	false;
			minfo.vecFloatParam.resize(4);
			minfo.vecTextureName.resize(1);

			minfo.vecFloatParam[0]	=	Float4(1,1,1,1);
			minfo.vecFloatParam[1]	=	Float4(0.5,0.5,0.5,0);
			minfo.vecFloatParam[2]	=	Float4(0.1,0.1,0.1,0.1);
			minfo.vecFloatParam[3]	=	Float4(0,0,0,0);

			

			//m_pParentNode->SetScale(Float3(0.01,0.01,0.01));

			U32	uiMeshCount	=	pVec.size();
			for(U32 i=0;i<uiMeshCount;i++){

				MeshEntity::Info	info;
				info.strMeshName	=	strPath+pVec[i];
				info.strMaterial	=	"NoMaterial";

				MeshEntity*	pEnt	=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity*>(pVec[i]+Common::Converter::ToString(i),"MeshEntity",&info);

				AString	strMSName	=	pEnt->GetMesh()->GetMaterialName();

				MaterialSetInfo*	pInfo	=	MaterialParse::GetSingleton()->GetMaterialSetInfo(strMSName);
				if(pInfo!=NULL){

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
					if(minfo.vecTextureName[0].empty()){
						minfo.vecTextureName[0]	=	"Texture/1x1white.png";
					}

					Material*	p	=	EngineSystem::GetSingleton()->CreateProduct<Material*>(strMSName+"MRT","Material",&minfo);
					pEnt->SetMaterial(p);
					p->ReleaseRef();

					p	=	EngineSystem::GetSingleton()->CreateProduct<Material*>(strMSName+"ShadowDepth","Material",&mdepthinfo);
					pEnt->SetMaterial(p);
					p->ReleaseRef();

				}

				m_pParentNode->attachObject(pEnt);
				
				m_vecEntity.push_back(pEnt);
			}

			return	true;
		}

		Air::U1 SceneLoader::Unload()
		{
			std::vector<MeshEntity*>::iterator	i	=	m_vecEntity.begin();
			for(;i!=m_vecEntity.end();i++){
				(*i)->ReleaseRef();
			}
			m_vecEntity.clear();
			return	true;
		}

		void SceneLoader::SetNode( SceneNode* pParent )
		{
			m_pParentNode	=	pParent->CreateChildSceneNode();
			m_pParentNode->SetScale(Float3(0.1,0.1,0.1));
		}

	}
}