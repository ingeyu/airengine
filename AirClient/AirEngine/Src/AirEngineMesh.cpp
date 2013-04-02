#include "AirEngineMesh.h"
#include "AirGlobalSetting.h"
namespace Air{
	
	
	namespace	Engine{
	
		std::map<AString,Mesh::IParseCallBack*>		Mesh::m_mapParseFunction;
	
		Mesh::Mesh( CAString& strName ):IProduct(strName){
	
		}
	
		U1 Mesh::Create(){
			//打开文件
			File	file(m_strProductName);
			if(!file.Open()){
				return false;
			}
			//解析后缀名
			AString	strPostfix;
			if(!GlobalSetting::ParsePath(m_strProductName,&strPostfix))
				return false;
	
			//判断后缀名是否成功
			if(strPostfix.empty())
				return false;
	
	
			//获取模型解析回调函数
			IParseCallBack*	pCallBack	=	GetParseCallBack(strPostfix);
	
			if(pCallBack==NULL){
				Common::Logger("Engine","Error","不支持的网格类型");
				return false;
			}
	
			//执行解析
			if(!pCallBack->Parse(file.GetData(),m_lstVertex,m_lstFace32,m_lstFace16,m_bUseNormal,m_bUseTexCoord,m_bUseTangent)){
				m_lstFace16.clear();
				m_lstFace32.clear();
				m_lstVertex.clear();
				return false;
			}
	
			
	
			return true;
		}
	
		U1 Mesh::Destroy(){
			m_lstFace16.clear();
			m_lstFace32.clear();
			m_lstVertex.clear();
	
			return	true;
		}
	
		U1 Mesh::ComputeNormalTangent( U1 bTangent /*= false*/ ){
// 			if(m_lstVertex.empty())
// 				return false;
// 	
// 			U1	bUse16Index	=	true;
// 			if(m_lstFace16.empty()){
// 				bUse16Index	=	false;
// 			}
// 			if(m_lstFace32.empty() && !bUse16Index)
// 				return false;
// 	
// 			UInt	uiNumVertex	=	m_lstVertex.size();
// 			UInt	uiNumFace	=	m_lstFace16.size();
// 			if(!bUse16Index){
// 				uiNumFace	=	m_lstFace32.size();
// 			}
// 	
// 			for(UInt	i=0;i<uiNumVertex;i++){
// 	
// 				//存储相关面列表
// 				std::list<Face32>	lstFace;
// 				//找出跟该顶点相关的面
// 				for(UInt	j=0;j<uiNumFace;j++){
// 					Face32 face;
// 					if(bUse16Index){
// 						face	=	Face32(m_lstFace16[j]);
// 					}else{
// 						face	=	m_lstFace32[j];
// 					}
// 					if(	face.f0	==	i||
// 						face.f1	==	i||
// 						face.f2	==	i){
// 							lstFace.push_back(face);
// 					}
// 				}
// 	
// 				//定义一个结构体 存储法线和权重
// 				struct NormalWeight{
// 					Float3	normal;
// 					Real			weight;
// 				};
// 	
// 				//法线权重列表
// 				std::list<NormalWeight>	lstNormal;
// 				//遍历面列表 计算出每个面的发现
// 				std::list<Face32>::iterator	itr	=	lstFace.begin();
// 				for(;itr!=lstFace.end();itr++){
// 					//计算法线
// 					static	Float3	v[5];
// 					static	NormalWeight	vNormal;
// 					Face32	f	=	(Face32)(*itr);
// 					v[0]	=	m_lstVertex[f.f0].Position;
// 					v[1]	=	m_lstVertex[f.f1].Position;
// 					v[2]	=	m_lstVertex[f.f2].Position;
// 	
// 					v[3]	=	v[0]-v[1];//v[3].normalise();
// 					v[4]	=	v[0]-v[2];//v[4].normalise();
// 	
// 					vNormal.normal	=	v[3].crossProduct(v[4]);
// 	
// 					//一定要归一化 否则计算出来的就是不是夹角了
// 					v[3].normalise();
// 					v[4].normalise();
// 					//使用夹角作为权重值
// 					vNormal.weight	=	acos(v[3].dotProduct(v[4]));
// 					vNormal.normal.normalise();
// 	
// 					//vNormal.weight	=	acos(v[3].dotProduct(v[4]));
// 	
// 					lstNormal.push_back(vNormal);
// 				}
// 	
// 				//求出法线的平均值
// 				NormalWeight tempNormal;
// 				tempNormal.normal	=	Float3::ZERO;
// 				tempNormal.weight	=	0.0f;
// 				std::list<NormalWeight>::iterator	it	=	lstNormal.begin();
// 				for(;it!=lstNormal.end();it++){
// 					NormalWeight	vNormal	=	(NormalWeight)(*it);
// 					tempNormal.normal	+=	vNormal.normal*vNormal.weight;
// 					tempNormal.weight	+=	vNormal.weight;
// 				}
// 	
// 				if(tempNormal.weight==0.0f)
// 					tempNormal.weight	=	1.0f;
// 				//存入法线列表中
// 				m_lstVertex[i].Normal	=	tempNormal.normal/tempNormal.weight;
// 				m_lstVertex[i].Normal.normalise();
// 	
// 	
// 	// 			AChar	str[MAX_NAME];
// 	// 			sprintf(str,"%d	=	%f %f %f\n",i,m_lstVertex[i].Normal.x,m_lstVertex[i].Normal.y,m_lstVertex[i].Normal.z);
// 	// 			OutputDebugStringA(str);
// 			}
	
			return true;
		}
	
		void Mesh::SetParseCallBack( IParseCallBack* pCallBack ){
			if(pCallBack==NULL)
				return;
			m_mapParseFunction.insert(std::map<AString,IParseCallBack*>::value_type(pCallBack->GetPostfixName().c_str(),pCallBack));
		}
	
		Mesh::IParseCallBack* Mesh::GetParseCallBack( AString strName ){
			if(strName.empty())
				return	NULL;
	
			std::map<AString,IParseCallBack*>::iterator	i	=	m_mapParseFunction.find(strName.c_str());
			if(i!=m_mapParseFunction.end())
				return i->second;
			else
				return NULL;
		}
	
		UInt Mesh::GetVertexCount(){
			return m_lstVertex.size();
		}
	
		UInt Mesh::GetFaceCount(){
			if(m_lstFace16.empty())
				return	m_lstFace32.size();
			return m_lstFace16.size();
		}
	
		Mesh::Vertex* Mesh::GetVertexArray(){
			if(m_lstVertex.empty())
				return NULL;
			return	&m_lstVertex[0];
		}
	
		Mesh::Face16* Mesh::GetFace16Array(){
			if(m_lstFace16.empty())
				return	NULL;
			return	&m_lstFace16[0];
		}
	
		Mesh::Face32* Mesh::GetFace32Array(){
			if(m_lstFace32.empty())
				return NULL;
			return	&m_lstFace32[0];
		}
	
		U1 Mesh::IsFace16(){
			return !m_lstFace16.empty();
	
		}
	
		U1 Mesh::GetPositionArray( Vec3Array& posArray ,Float3	vScale	/*=	Float3(1,1,1)*/){
			UInt	uiCount	=	m_lstVertex.size();
			posArray.resize(uiCount);
			for(UInt i=0;i<uiCount;i++){
				//posArray[i]	=	m_lstVertex[i].Position*vScale;
			}
			return true;
		}
	
		U1 Mesh::GetIndexArray( IndexArray& indexArray ){
			if(IsFace16()){
				UInt	iFaceCount	=	m_lstFace16.size();
				indexArray.resize(iFaceCount*3);
				for(UInt i=0;i<iFaceCount;i++){
					indexArray[3*i]		=	m_lstFace16[i].f0;
					indexArray[3*i+1]	=	m_lstFace16[i].f1;
					indexArray[3*i+2]	=	m_lstFace16[i].f2;
				}
			}else{
				UInt	iFaceCount	=	m_lstFace32.size()*3;
				indexArray.resize(iFaceCount*3);
				for(UInt i=0;i<iFaceCount;i++){
					indexArray[3*i]		=	m_lstFace32[i].f0;
					indexArray[3*i+1]	=	m_lstFace32[i].f1;
					indexArray[3*i+2]	=	m_lstFace32[i].f2;
				}
			}
			return true;
		}
		MeshFactory::MeshFactory(){
			m_strTypeName	=	"Mesh";
		}
	
		IProduct* MeshFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
			Mesh*	pBuff	=	new	Mesh(strName);
			return	pBuff;
		}
	}
};