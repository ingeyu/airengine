#include "AirEngineCharacterResource.h"
#include "..\..\AirCharacter\cal3d.h"
#include "AirCommonFile.h"
#include "AirCommonIniFile.h"
#include "AirSlkReader.h"
#include "AirRenderSystem.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceResourceSystem.h"
namespace Air{
	
	namespace	Client{
		namespace	Character{
	
	
			Resource::Resource( CAString& strName,AString*	strSkeleton ):IProduct(strName){
				m_strSkeleton	=	*strSkeleton;
			}
	
			Resource::~Resource(){
			}
	
			SInt Resource::LoadMesh( CAString& strName ,MeshHDBuffer*	pOutMeshBuff){
				if(IsNull())
					return -1;
				AString strFullName	=	m_strProductName	+	strName;
				CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
				//查找已有列表
				InfoMapItr	i	=	m_mapMeshInfo.find(strFullName.c_str());
				if(i!=m_mapMeshInfo.end()){
					Info&	oldInfo	=	i->second;
					//判断是否为空 不为空则增加引用计数然后返回
					if(!oldInfo.IsNull()){
						oldInfo.uiRefCount++;
					}else{
						Data	pData;
						GetGlobalSetting().m_pResourceSystem->Find(m_strProductName + strName,pData);
						if(!pData.IsNull())
							return	-1;
						//如果不在列表中 则新建载入
						//oldInfo.uiID	=	pCoreMesh->loadCoreMesh(m_strProductName + strName,strName);
						oldInfo.uiID	=	pCoreMesh->loadCoreMesh(pData.buff,strName);
						//如果载入成功 则增加引用计数
						if(oldInfo.uiID != -1){
							oldInfo.uiRefCount++;
						}
					}
					return oldInfo.uiID;
				}
				Data	pData;
				GetGlobalSetting().m_pResourceSystem->Find(m_strProductName + strName,pData);
				if(pData.IsNull())
					return	-1;
				//如果不在列表中 则新建载入
				//SInt	uiID	=	pCoreMesh->loadCoreMesh(m_strProductName + strName,strName);
				SInt	uiID	=	pCoreMesh->loadCoreMesh(pData.buff,strName);
				//失败则返回-1
				if(uiID<0){
					return -1;
				}
				
				MeshHDBuffer*	pMeshBuff	=	NULL;
	
				CalCoreMesh*	pTempMesh	=	pCoreMesh->getCoreMesh(uiID);
				pMeshBuff	=	new	MeshHDBuffer;
				//创建硬件缓冲
				CreateHardwareBuff(pMeshBuff,pTempMesh);
	
				if(pOutMeshBuff!=NULL){
					*pOutMeshBuff	=	*pMeshBuff;
				}
	
				//新建一个 增加引用计数
				Info	info(strFullName,uiID);
				info.uiRefCount++;
				info.pUserData	=	pMeshBuff;
				//插入列表中
				m_mapMeshInfo.insert(InfoMapPair(strFullName.c_str(),info));
				//返回
				return uiID;
			}
	
			U1 Resource::UnLoadMesh( CAString& strName ){
				//判断是否为空 是则直接返回失败
				if(IsNull()	||	strName.empty())
					return false;
				AString strFullName	=	m_strProductName	+	strName;
				//从列表中查找
				InfoMapItr	i	=	m_mapMeshInfo.find(strFullName.c_str());
				//如果没有找到 返回
				if(i==m_mapMeshInfo.end()){
					return true;
				}
				Info& info	=	i->second;
				//找到之后 判断是否为空
				if(info.IsNull()){
					m_mapMeshInfo.erase(i);
					return true;
				}
				//减少引用
				info.uiRefCount--;
				//检查是否没有人引用此资源 
				if(info.uiRefCount<=0){
					//卸载
					CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
					pCoreMesh->unloadCoreMesh(info.uiID);
					info.uiID	=	-1;
	
						MeshHDBuffer*	pMeshBuff	=	(MeshHDBuffer*)info.pUserData;
						//摧毁硬件缓冲
						DestroyHardwareBuff(pMeshBuff);
				}
				m_mapMeshInfo.erase(i);
				return true;
			}
	
			SInt Resource::LoadAnimation( CAString& strName ){
				if(IsNull())
					return -1;
				CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
				//查找已有列表
				InfoMapItr	i	=	m_mapAnimationInfo.find(strName.c_str());
				if(i!=m_mapAnimationInfo.end()){
					Info&	oldInfo	=	i->second;
					//判断是否为空 不为空则增加引用计数然后返回
					if(!oldInfo.IsNull()){
						oldInfo.uiRefCount++;
					}else{
						//如果为空 则载入 
						oldInfo.uiID	=	pCoreMesh->loadCoreAnimation(m_strProductName+strName,strName);
						//如果载入成功 则增加引用计数
						if(oldInfo.uiID != -1){
							oldInfo.uiRefCount++;
						}
					}
					return oldInfo.uiID;
				}
				Data	pData;
				GetGlobalSetting().m_pResourceSystem->Find(m_strProductName + strName,pData);
				if(pData.IsNull())
					return	-1;
				//如果不在列表中 则新建载入
				//SInt	uiID	=	pCoreMesh->loadCoreAnimation(m_strProductName + strName,strName);
				SInt	uiID	=	pCoreMesh->loadCoreAnimation(pData.buff,strName);
				//失败则返回-1
				if(uiID<0){
					return -1;
				}
				//新建一个 增加引用计数
				Info	info(strName,uiID);
				info.uiRefCount++;
				//插入列表中
				m_mapAnimationInfo.insert(InfoMapPair(strName.c_str(),info));
				//返回
				return uiID;
			}
	
			U1 Resource::UnLoadAnimation( CAString& strName ){
				if(IsNull())
					return false;
				InfoMapItr	i	=	m_mapAnimationInfo.find(strName.c_str());
				if(i==m_mapAnimationInfo.end()){
					return true;
				}
				Info& info	=	i->second;
				if(info.IsNull()){
					return true;
				}
				info.uiRefCount--;
				if(info.uiRefCount<=0){
					CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
					pCoreMesh->unloadCoreAnimation(info.uiID);
					info.uiID	=	-1;
				}
				return true;
			}
	
			U1 Resource::Create(){
				AString	strConfigFileName	=	m_strProductName + "Animation.slk";
	
				if(!ParseConfig(strConfigFileName)){
					return false;
				}
				return true;
			}
	
			U1 Resource::Destroy(){
				m_mapAnimationInfo.clear();
				m_mapMeshInfo.clear();
				CoreMesh*	pCoreMesh	=	GetObjectT<CoreMesh*>();
				SAF_D(pCoreMesh);
				m_pObject	=	NULL;
				return true;
			}
	
			U1 Resource::ParseConfig(CAString&	strConfig){
	
	
				CoreMesh*	pCoreMesh	=	new	CoreMesh(m_strProductName.c_str());
				m_pObject				=	(UInt*)pCoreMesh;
	
				Data	pData;
				
				GetGlobalSetting().m_pResourceSystem->Find(m_strProductName + m_strSkeleton,pData);
				if(pData.IsNull())
					return	false;
	
				if(!pCoreMesh->loadCoreSkeleton(pData.buff)){
					SAF_D(pCoreMesh);
					return false;
				}
	
				StringVector	lstAnimation;
	
				CSlkReader r;
				GetGlobalSetting().m_pResourceSystem->Find(strConfig,pData);
				if(pData.IsNull())
					return	false;
	
				if( !r.ReadFromString((char*)pData.buff,pData.size ) ){
					return FALSE;
				}
	
				int nLine = 2;
				int iRet;
	
				while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
				{
					if( CSlkReader::ret_nothisline == iRet )
						continue;
	
					CSlkReader::SField* field;
		
					field = r.GetFieldOfLine( 5 );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					AString	strAnimationName	=	field->data.szValue;
	
	
					lstAnimation.push_back(strAnimationName);
				}	
	
				if(lstAnimation.empty()){
					SAF_D(pCoreMesh);
					return false;
				}
	
				for(U32	i=0;i<lstAnimation.size();i++){
					LoadAnimation(lstAnimation[i]);
				}
	
				
				return true;
			}
	
			SInt Resource::GetAnimationID( CAString& strName ){
				InfoMapItr	i	=	m_mapAnimationInfo.find(strName.c_str());
				if(i==m_mapAnimationInfo.end()){
					return -1;
				}
				Info& info	=	i->second;
				return info.uiID;
			}
	
			U1 Resource::CreateHardwareBuff( MeshHDBuffer* pOutBuff,CalCoreMesh* pInMesh ){
				std::vector<ABuff>	vertexData;
				std::vector<UInt>								indexData;
	
				SInt	iMeshCount	=	pInMesh->getCoreSubmeshCount();
				SInt	iVertexCount	=	0;
				SInt	iIndexCount		=	0;
				//首先计算顶点数 和 索引数
				for(SInt i=0;i<iMeshCount;i++){
					CalCoreSubmesh*	pSubMesh	=	pInMesh->getCoreSubmesh(i);
					iVertexCount	+=	pSubMesh->getVectorVertex().size();
					iIndexCount		+=	pSubMesh->getFaceCount()*3;
				}
				if(	iVertexCount	==	0	||
					iIndexCount		==	0)
				{
					return	false;
				}
				//分配空间
				vertexData.resize(iVertexCount);
				indexData.resize(iIndexCount);
	
				SInt	iV	=	0;
				SInt	iI	=	0;
	
				
				for(SInt i=0;i<iMeshCount;i++){
					CalCoreSubmesh*	pSubMesh							=	pInMesh->getCoreSubmesh(i);
					//计算切线
					pSubMesh->enableTangents(0,true);
	
					std::vector<CalCoreSubmesh::Vertex>&							lstVector	=	pSubMesh->getVectorVertex();
					std::vector<std::vector<CalCoreSubmesh::TangentSpace> >&		lstTangent	=	pSubMesh->getVectorVectorTangentSpace();
					std::vector<std::vector<CalCoreSubmesh::TextureCoordinate> >&	lstTexcoord	=	pSubMesh->getVectorVectorTextureCoordinate();
					std::vector<CalCoreSubmesh::Face>&								lstFace		=	pSubMesh->getVectorFace();
					
					SInt iFaceCount	=	lstFace.size();
					//索引缓冲
					for(SInt	j=0;j<iFaceCount;j++){
						indexData[iI]	=	lstFace[j].vertexId[0]	+	iV;
						indexData[iI+1]	=	lstFace[j].vertexId[1]	+	iV;
						indexData[iI+2]	=	lstFace[j].vertexId[2]	+	iV;
						iI	+=	3;
					}
					
					//顶点缓冲数据
					for(SInt j=0;j<iVertexCount;j++){
						CalCoreSubmesh::Vertex&				ver		=	lstVector[j];
						CalCoreSubmesh::TangentSpace		tang	=	lstTangent[0][j];
						CalCoreSubmesh::TextureCoordinate	uv		=	lstTexcoord[0][j];
		
						//位置
						vertexData[iV].Position		=	Float3(ver.position.x,ver.position.y,ver.position.z);
						//骨骼绑定信息
						vertexData[iV].BoneWeight	=	Float4(0,0,0,0);
						vertexData[iV].BoneIndex	=	Float4(0,0,0,0);
	// 					AChar	str[128];
	// 					sprintf_s(str,"Vertex[%d] ",j);
	// 					OutputDebugStringA(str);
						SInt	iBoneCount	=	ver.vectorInfluence.size();
						for(SInt	k=0;k<iBoneCount;k++){
 							vertexData[iV].BoneWeight[k]	=	ver.vectorInfluence[k].weight;

							//如果只传递自己需要的矩阵 
							//骨骼索引变成0~n
 							vertexData[iV].BoneIndex[k]		=	ver.vectorInfluence[k].boneId;
							
	// 						sprintf_s(str,128,"<%d>%f,%f",k,vertexData[iV].BoneWeight[k],vertexData[iV].BoneIndex[k]);
	// 						OutputDebugStringA(str);
						}
	//					OutputDebugStringA("\n");
						//法线
						vertexData[iV].Normal		=	Float3(ver.normal.x,ver.normal.y,ver.normal.z);
						//UV
						vertexData[iV].UV.x		=	uv.u;
						vertexData[iV].UV.y		=	uv.v;
						//切线
						vertexData[iV].Tangent.x		=	tang.tangent.x;
						vertexData[iV].Tangent.y		=	tang.tangent.y;
						vertexData[iV].Tangent.z		=	tang.tangent.z;
	
	
	
						iV++;
					}
					AString	strName	=	m_strProductName	+	pInMesh->getName();
					Render::Vertex::IDeclare::Info	dInfo;
					dInfo.SetPNTT_Animation();
 					pOutBuff->pVertexDeclare	=	Render::System::GetSingleton()->CreateProduct<Render::Vertex::IDeclare*>("PNTTANIM","Declare",&dInfo);
					Render::Buffer::Info		vInfo;
					vInfo.SetVertexBuffer(iVertexCount,76);
					vInfo.InitData			=	&vertexData[0];
					pOutBuff->pVertexBuff		=	Render::System::GetSingleton()->CreateProduct<Render::Buffer*>(strName+"VB","Buffer",&vInfo);

					vInfo.SetIndexBuffer32(iFaceCount*3);
					vInfo.InitData			=	&indexData[0];
					pOutBuff->pIndexBuff		=	Render::System::GetSingleton()->CreateProduct<Render::Buffer*>(strName+"IB","Buffer",&vInfo);

				}
				return	true;
			}
	
			U1 Resource::DestroyHardwareBuff( MeshHDBuffer* pInBuff ){


				SAFE_RELEASE_REF(pInBuff->pVertexDeclare);
				SAFE_RELEASE_REF(pInBuff->pVertexBuff);
				SAFE_RELEASE_REF(pInBuff->pIndexBuff);
				return	true;
			}
		}
	}
};