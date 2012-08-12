
#include "AirMesh.h"
#include "IGame.h"
#include "AirCommonHeader.h"
namespace	Air{
	FILE*	OpenFileBinary(const AString&	strName){
		return	fopen(strName.c_str(),"wb");
	};
	FILE*	OpenFileAscii(const AString&	strName){
		return	fopen(strName.c_str(),"w");
	};
	template<typename	T>
	void	Write(FILE*	pFile,const T& t){
		fwrite(&t,sizeof(t),1,pFile);
	}
	void	Write(FILE* pFile,const void*	pData,unsigned int uiSize){
		fwrite(&uiSize,sizeof(int),1,pFile);
		fwrite(pData,uiSize,1,pFile);
	}
	void	Write(FILE*	pFile,CAString&	str){
		fprintf(pFile,"%s",str.c_str());
	};

	IGameScene*	pScene	=	NULL;
	AString		strFullPath;
	AString		strPath;
	AString		strMaterialPath;
	AString		strMaterialContent;
	AString		strSceneContent;
	struct Vertex{
		Point3	position;
		Point3	normal;
		Point2	uv;
		Point3	tangent;
		bool	operator == (const Vertex&	v){
			if(	position.x	!=	v.position.x||
				position.y	!=	v.position.y||
				position.z	!=	v.position.z||
				normal.x	!=	v.normal.x	||
				normal.y	!=	v.normal.y	||
				normal.z	!=	v.normal.z	||
				position.x	!=	v.position.x||
				uv.x		!=	v.uv.x		||
				uv.y		!=	v.uv.y		||
				tangent.x	!=	v.tangent.x	||
				tangent.y	!=	v.tangent.y	||
				tangent.z	!=	v.tangent.z)
			{
				return	false;
			}
			return	true;
		};
	};
	typedef	std::vector<Vertex>	VertexVector;
	typedef	std::vector<unsigned int>	UIntVector;
	unsigned int	PushVertex(VertexVector&	vec,const	Vertex&	v){
		unsigned	int	uiSize	=	vec.size();
		for(unsigned int i=0;i<uiSize;i++){
			if(vec[i]	==	v){
				return	i;
			}
		}
		vec.push_back(v);
		return	vec.size()-1;
	};


	bool	ExportMesh(IGameNode*	pNode,bool bExportScene){
		FILE*	pFile	=	NULL;

		AString	strFileName	=	AString(pNode->GetName())+AString(".ame");

		strSceneContent	+=	"Mesh="+strFileName+"\n";
		
		if(!bExportScene)
			pFile	=	OpenFileBinary(strFullPath);
		else
			pFile	=	OpenFileBinary(strFileName.c_str());

		Interface * ip = GetCOREInterface();



		IGameMesh*	pMesh			=	(IGameMesh*)pNode->GetIGameObject();
		IGameMaterial*	pMat	=	pNode->GetNodeMaterial();
		AString		strMaterialName;
		if(pMat!=NULL)
			strMaterialName	=	pMat->GetMaterialName();
		else
			strMaterialName	=	"NoMaterial";
		Box3 boundingbox;
		pMesh->GetBoundingBox(boundingbox);
		unsigned int version	=	'0EMA';
		Write(pFile,version);
		Write(pFile,boundingbox.pmin);
		Write(pFile,boundingbox.pmax);
		Write(pFile,strMaterialName.c_str(),strMaterialName.size());

		pMesh->SetCreateOptimizedNormalList();

		int iLastPercent	=	0;
		if(pMesh->InitializeData())
		{
			bool	bIsSkin	=	pMesh->IsObjectSkinned();
			


			VertexVector	vec;
			UIntVector		vecIdx;
			int numFaces = pMesh->GetNumberOfFaces();
			for(int n=0;n<numFaces;n++)
			{
				Vertex	v;

				FaceEx* f = pMesh->GetFace(n);

				DWORD		iUV[3];

				DWORD		index;
				
				pMesh->GetMapFaceIndex(1,n,iUV);
				for(int i=0;i<3;i++){
					pMesh->GetVertex(f->vert[i],v.position);
					pMesh->GetNormal(f->norm[i],v.normal);
					pMesh->GetTexVertex(f->texCoord[i], v.uv);
					int iTanIdx	=	pMesh->GetFaceVertexTangentBinormal(n,i);
					pMesh->GetTangent(iTanIdx,v.tangent);

					index	=	PushVertex(vec,v);
					vecIdx.push_back(index);
				}
				int iPercent	=	(n*100/numFaces);
				if(iPercent	!=	iLastPercent){
					iLastPercent	=	iPercent;
					char s[32];
					itoa(n,s,10);
					AString	strTitle	=	strFullPath+"("+s+"/numFaces)";
					ip->ProgressUpdate(iLastPercent,1,(char*)strTitle.c_str());
				}
			}

			Tab<int> matidTab = pMesh->GetActiveMatIDs();
			unsigned int	uiMaterialCount	=	matidTab.Count();
			for(int i=0;i<uiMaterialCount;i++){
				int	id	=	matidTab[i];
				//pScene->getroo
				//pMesh->get
			}

// 			// 得到skin信息
// 			if( pGameMesh->IsObjectSkinned() )
// 			{
// 				IGameSkin *pGameSkin = NULL;
// 				pGameSkin = pGameMesh->GetIGameSkin();
// 				int iBoneID;
// 				float fWeight;
// 				int type = pGameSkin->GetVertexType(vertexId);
// 				if(type==IGameSkin::IGAME_RIGID)
// 				{
// 					iBoneID = pGameSkin->GetBoneID(vertexId,0);
// 					IGameNode *pBoneNode = g_Exporter.GetIGameScene()->GetIGameNode(ULONG(iBoneID));
// 					TCHAR *chBoneName = pBoneNode->GetName();
// 					fWeight = 1.f;
// 					pVertexData->AddInfluence(iBoneID, fWeight);
// 				}
// 				else //blended
// 				{
// 					for(int b=0;b<pGameSkin->GetNumberOfBones(vertexId);++b)
// 					{
// 						iBoneID = pGameSkin->GetBoneID(vertexId,b);
// 						IGameNode *pBoneNode = g_Exporter.GetIGameScene()->GetIGameNode(ULONG(iBoneID));
// 						TCHAR *chBoneName = pBoneNode->GetName();
// 						fWeight = pGameSkin->GetWeight(vertexId,b);
// 						pVertexData->AddInfluence(iBoneID, fWeight);
// 					}
// 				}
// 			}
			Write(pFile,&vec[0],sizeof(Vertex)*vec.size());
			Write(pFile,&vecIdx[0],sizeof(int)*vecIdx.size());
		}
		fclose(pFile);
		return	true;
	};
	AString	GetPropertyInfo(IGameProperty*	pProperty){
		if(!pProperty)	//fix me NH...
			return	"";

		AString	prop	=	pProperty->GetName();
		prop+="=";
		switch(pProperty->GetType()){
		case IGAME_POINT3_PROP:{
			Point3 p; 
			pProperty->GetPropertyValue(p);
			char s[128];
			sprintf(s,"%f %f %f\n",p.x,p.y,p.z);
			prop+=s;
			break;}
		case IGAME_POINT4_PROP:{
			Point4 p; 
			pProperty->GetPropertyValue(p);
			char s[128];
			sprintf(s,"%f %f %f %f\n",p.x,p.y,p.z,p.w);
			prop+=s;
			break;}
		case IGAME_FLOAT_PROP:{
			float p; 
			pProperty->GetPropertyValue(p);
			char s[128];
			sprintf(s,"%f\n",p);
			prop+=s;
			break;}
		case IGAME_STRING_PROP:{			
			char s1[512];
			const char*	p	=s1;
			pProperty->GetPropertyValue(p);
			prop+=p;
			prop+="\n";
			break;}
		case IGAME_INT_PROP:{
			int p; 
			pProperty->GetPropertyValue(p);
			char s[128];
			sprintf(s,"%d\n",p);
			prop+=s;
			break;}
		default:{
			break;}

		}
		return	prop;
	}
	bool	ExportMaterial(IGameMaterial*	pMaterial){
		if(pMaterial==NULL)
			return	false;
		AString	strFullMaterialName	=	strMaterialPath;
		

		AString	strMaterialName	=	pMaterial->GetMaterialName();
		AString	strMaterialInfo	=	AString("[")+pMaterial->GetMaterialName()+"]\n";//AString("[Material]\n");
		AString	strMaterialInfo2	=	strMaterialInfo;

// 		strMaterialInfo	+=	"Name=";
// 		strMaterialInfo	+=	pMaterial->GetMaterialName();
// 		strMaterialInfo	+=	"\n";
		strMaterialInfo	+=	GetPropertyInfo(pMaterial->GetDiffuseData());
		strMaterialInfo	+=	GetPropertyInfo(pMaterial->GetAmbientData());
		strMaterialInfo	+=	GetPropertyInfo(pMaterial->GetSpecularData());
		strMaterialInfo	+=	GetPropertyInfo(pMaterial->GetGlossinessData());
		strMaterialInfo	+=	GetPropertyInfo(pMaterial->GetOpacityData());
		strMaterialInfo	+=	GetPropertyInfo(pMaterial->GetSpecularLevelData());
		strMaterialInfo	+=	GetPropertyInfo(pMaterial->GetEmissiveData());
		int	iTexture	=	pMaterial->GetNumberOfTextureMaps();
// #define ID_AM 0   //!< Ambient 
// #define ID_DI 1   //!< Diffuse
// #define ID_SP 2   //!< Specular
// #define ID_SH 3   //!< Glossiness (Shininess in 3ds Max release 2.0 and earlier)
// #define ID_SS 4   //!< Specular Level (Shininess strength in 3ds Max release 2.0 and earlier)
// #define ID_SI 5   //!< Self-illumination
// #define ID_OP 6   //!< Opacity
// #define ID_FI 7   //!< Filter color
// #define ID_BU 8   //!< Bump 
// #define ID_RL 9   //!< Reflection
// #define ID_RR 10  //!< Refraction 
// #define ID_DP 11  //!< Displacement 
		static	AString	strSlotName[]={
			"AmbientTex",
			"DiffuseTex",
			"SpecularTex",
			"GlossinessTex",
			"SpecularLevelTex",
			"SelfIlluminationTex",
			"OpacityTex",
			"FiltercolorTex",
			"BumpTex",
			"ReflectionTex",
			"RefractionTex",
			"DisplacementTex"
		};
		for(int i=0;i<iTexture;i++){
			
			IGameTextureMap*	pMap	=	pMaterial->GetIGameTextureMap(i);

			//纹理不支持导出
			if(!pMap->IsEntitySupported()){
				continue;
			}

			int	slot	=	pMap->GetStdMapSlot();

			if(slot == -1)
				continue;
			AString	strTexName	=	pMap->GetBitmapFileName();
			AString	strTexName2	=	pMap->GetTextureName();
			//strPath	
			MSTR pPath;
			MSTR pName;
			SplitPathFile(strTexName.c_str(),&pPath,&pName);
			AString	strNewName	=	strPath+pName.data();
			CopyFileA(strTexName.c_str(),strNewName.c_str(),FALSE);
			
			
			strMaterialInfo	+=	strSlotName[slot];//pMap->GetTextureName();
			strMaterialInfo	+=	"=";
			strMaterialInfo	+=	pName.data();
			strMaterialInfo	+=	"\n";

			
		}
		if(strMaterialInfo.size()	>	strMaterialInfo2.size()){
			//FILE*	pFile	=	OpenFileAscii(strFullMaterialName);
			//Write(pFile,strMaterialInfo);
			//fclose(pFile);

			strMaterialContent+=strMaterialInfo;
		}

		return	true;
	};
	bool	ExportNode(IGameNode*	pNode,bool bExportScene){

		Interface * ip = GetCOREInterface();

		AString	strName	=	pNode->GetName();

		Matrix3	mWorld	=	pNode->GetWorldTM(0).ExtractMatrix3();

		IGameObject * obj = pNode->GetIGameObject();
		IGameObject::ObjectTypes T = obj->GetIGameType();
		switch(T){
			case IGameObject::IGAME_XREF:{
			break;}
			case IGameObject::IGAME_BONE:{
				break;}
			case IGameObject::IGAME_HELPER:{
				break;}
			case IGameObject::IGAME_CAMERA:{
				break;}
			case IGameObject::IGAME_MESH:{
				IGameMesh * gM = (IGameMesh*)obj;
				ExportMesh(pNode,bExportScene);
				IGameMaterial*	pMaterial	=	pNode->GetNodeMaterial();
				ExportMaterial(pMaterial);
				break;}
			case IGameObject::IGAME_SPLINE:{
				break;}
			case IGameObject::IGAME_IKCHAIN:{
				break;}
			case IGameObject::IGAME_LIGHT:{
				break;}
		}
		int iChildCount	=	pNode->GetChildCount();
		for(int i=0;i<iChildCount;i++){
			ExportNode(pNode->GetNodeChild(i),bExportScene);
		}
		return	true;
	}

	void SetFullPath( const char* pFullName )
	{
		strFullPath		=	pFullName;
		strMaterialPath	=	strFullPath + ".Scene.material";
	}

	void SetPath( const char* pPath )
	{
		strPath	=	AString(pPath)+"\\";
	}

}

DWORD WINAPI fn2(LPVOID arg)
{
	return(0);
}

int GetExportCount(IGameNode*	pNode){
	if(pNode==NULL)
		return 0;
	int iCount	=	0;
	IGameObject * obj = pNode->GetIGameObject();
	IGameObject::ObjectTypes T = obj->GetIGameType();
	if(T==IGameObject::IGAME_MESH){
		iCount++;
	}
		
	int iChildCount	=	pNode->GetChildCount();
	for(int i=0;i<iChildCount;i++){
		iCount	+=	GetExportCount(pNode->GetNodeChild(i));
	}

	return	iCount;
}

bool Air::Export(bool bExportSelect)
{
	Interface * ip = GetCOREInterface();


	//MyErrorProc pErrorProc;

	UserCoord Whacky = {
		1,	//Right Handed
		1,	//X axis goes right
		3,	//Y Axis goes down
		4,	//Z Axis goes in.
		1,	//U Tex axis is right
		1,  //V Tex axis is Down
	};	

	ip->ProgressStart("Export Scene To AirMesh......",true,fn2,NULL);


	bool	exportSelected	= bExportSelect;
	float	igameVersion	= GetIGameVersion();

	IGameScene*	pIGameScene	=	GetIGameInterface();

	pScene		=	pIGameScene;
	IGameConversionManager * cm = GetConversionManager();
	//	cm->SetUserCoordSystem(Whacky);
	cm->SetCoordSystem((IGameConversionManager::IGAME_D3D));
	//	pIgame->SetPropertyFile(_T("hello world"));
	pIGameScene->InitialiseIGame(exportSelected);
	pIGameScene->SetStaticFrame(0);

	int iExportCount	=	0;//pIGameScene->GetTopLevelNodeCount();

	for(int loop = 0; loop <pIGameScene->GetTopLevelNodeCount();loop++)
	{
		IGameNode * pGameNode = pIGameScene->GetTopLevelNode(loop);

		iExportCount+=	GetExportCount(pGameNode);
	}

	bool bExportScene	=	iExportCount	>	1;

	FILE* pSceneFile	=	NULL;
	if(bExportScene){
		strSceneContent+="[Scene]\n";
	}

	for(int loop = 0; loop <pIGameScene->GetTopLevelNodeCount();loop++)
	{
		IGameNode * pGameNode = pIGameScene->GetTopLevelNode(loop);
		//check for selected state - we deal with targets in the light/camera section

		if(pGameNode->IsTarget())
			continue;
		

		ExportNode(pGameNode,bExportScene);


	}

	pIGameScene->ReleaseIGame();

	//保存材质
	FILE*	pFile	=	OpenFileAscii(strMaterialPath);
	Write(pFile,strMaterialContent);
	fclose(pFile);

	//保存场景
	if(bExportScene){
		pFile	=	OpenFileAscii(strFullPath+".Scene");
		Write(pFile,strSceneContent);
		fclose(pFile);
	}

	strMaterialContent.clear();
	strSceneContent.clear();
	ip->ProgressEnd();
	return	true;
}
