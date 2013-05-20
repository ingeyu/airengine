#include "AirSceneLoader.h"
#include "AirEngineMaterialParse.h"
#include "AirMeshEntity.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirCommonParse.h"
#include "AirCSV.h"

namespace	Air{
	namespace	Engine{

		static U32 iCount=0;
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

			AString	strFileName		=	strSceneName;
			Common::Converter::ToLowerCase(strFileName);
			if(Common::EndWith(strFileName,".scene2"))
			{
				return Load2(strSceneName);
			}
			pResSys->Find(strSceneName+".material",data);
			MaterialParse::GetSingleton()->CompileMaterialSet(data.buff,data.size);//uiSize);

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

			

			MeshEntity*	pEnt	=	EngineSystem::GetSingleton()->CreateProduct<MeshEntity>(Common::Converter::ToString(iCount++),&info);

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

		Air::U1 SceneLoader::Save( CAString& strSceneName )
		{
			AString	strContent;
			strContent.resize(256*1024);
			char* p	=	(char*)strContent.c_str();



			int iTotalLength	=	0;
			AChar str[1024];
			strcpy(str,"Type,Name,PosX,PosY,PosZ,QuatX,QuatY,QuatZ,QuatW,ScaleX,ScaleY,ScaleZ,BoundMinX,BoundMinY,BoundMinZ,BoundMaxX,BoundMaxY,BoundMaxZ,Info\n");
			int iLength = strlen(str);
			strcpy(&p[iTotalLength],str);
			iTotalLength	+=	iLength;
			MeshEntityList::iterator	i	=	m_lstEntity.begin();
			for(;i!=m_lstEntity.end();i++){
				float* pBoundingBox	=	(float*)&((*i)->GetWorldBoundingBox().vMin.x);
				float* pPos			=	(float*)&((*i)->GetParentSceneNode()->GetPosition().x);
				float* pQuat		=	(float*)&((*i)->GetParentSceneNode()->GetQuat().x);
				float* pScale		=	(float*)&((*i)->GetParentSceneNode()->GetScale().x);
				sprintf_s(
					str,
					1024,
					"%s,%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%s\n",
					(*i)->GetProductTypeName().c_str(),
					(*i)->GetProductName().c_str(),
					pPos[0],pPos[1],pPos[2],
					pQuat[0],pQuat[1],pQuat[2],pQuat[3],
					pScale[0],pScale[1],pScale[2],
					pBoundingBox[0],pBoundingBox[1],pBoundingBox[2],pBoundingBox[3],pBoundingBox[4],pBoundingBox[5],
					(*i)->GetMesh()->GetProductName().c_str()
					);
				iLength = strlen(str);
				strcpy(&p[iTotalLength],str);
				iTotalLength	+=	iLength;
			}
			Common::File::Save(strSceneName,strContent);
			return false;
		}

		Air::U1 SceneLoader::Load2( CAString& strSceneName )
		{
			Data data;
			ResourceSystem*	pResSys	=	ResourceSystem::GetSingleton();
			pResSys->Find(strSceneName,data);
			if(data.IsNull())
				return false;

			CSV csv;
			csv.Load(data.buff,data.size);
			Transform	trans;
			for(U32 j=1;j<csv.GetLineCount();j++){
				AChar*	strType	=	csv.GetItem(0,j).pStr;
				AChar*	strName	=	csv.GetItem(1,j).pStr;
				trans.pos.x		=	Common::Converter::ToFloat(csv.GetItem(2,j).pStr);
				trans.pos.y		=	Common::Converter::ToFloat(csv.GetItem(3,j).pStr);
				trans.pos.z		=	Common::Converter::ToFloat(csv.GetItem(4,j).pStr);
				trans.rot.x		=	Common::Converter::ToFloat(csv.GetItem(5,j).pStr);
				trans.rot.y		=	Common::Converter::ToFloat(csv.GetItem(6,j).pStr);
				trans.rot.z		=	Common::Converter::ToFloat(csv.GetItem(7,j).pStr);
				trans.rot.w		=	Common::Converter::ToFloat(csv.GetItem(8,j).pStr);
				trans.scale.x		=	Common::Converter::ToFloat(csv.GetItem(9,j).pStr);
				trans.scale.y		=	Common::Converter::ToFloat(csv.GetItem(10,j).pStr);
				trans.scale.z		=	Common::Converter::ToFloat(csv.GetItem(11,j).pStr);
				AChar*	pInfo		=	csv.GetItem(18,j).pStr;
				AddObject(strName,strType,trans,pInfo);
			}

			return true;
		}

		void SceneLoader::AddObject( CAString& strName,CAString& strType,Transform& trans,void* pInfo )
		{
			MeshEntity::Info meinfo;

			if(strType	==	"MeshEntity"){

				MeshEntity* pMesh = AddEntity((AChar*)pInfo,&trans);
			}else{
				IProduct* pProduct	=	EngineSystem::GetSingleton()->CreateProduct(strName,strType,pInfo);
				if(pProduct!=NULL){
					MovableObject* pObject = dynamic_cast<MovableObject*>(pProduct);
					if(pObject!=NULL){
						m_pNode->CreateChildSceneNode(trans.pos,trans.rot,trans.scale)->attachObject(pObject);
					}
				}
			}
		}

	}
}