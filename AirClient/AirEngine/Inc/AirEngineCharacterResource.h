//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/08
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  EngineCharacterResource.h
 \note     
       
 \attention:
			模型资源
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINECHARACTERRESOURCE_HEAD_FILE
#define ENGINECHARACTERRESOURCE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderBuffer.h"


class	CalCoreModel;
class	CalCoreMesh;
namespace Air{
	
	namespace Engine{
	
		namespace	Character{
			typedef	CalCoreModel	CoreMesh;
	
	
			struct	MeshHDBuffer{
				MeshHDBuffer(){
					pVertexBuff		=	NULL;
					pIndexBuff		=	NULL;
					pVertexDeclare	=	NULL;
				};
				/**	\brief	清空指针
				*   
				*	@remarks 	清空指针
				*	@see		MeshHDBuffer
				*	@return   	void
				*	@note
				*
				**/
				void	Clear(){
					pVertexBuff		=	NULL;
					pIndexBuff		=	NULL;
					pVertexDeclare	=	NULL;
				};
				Render::Buffer*		pVertexBuff;
				Render::Buffer*		pIndexBuff;
				Render::Vertex::IDeclare*	pVertexDeclare;
			};
			/**	\brief	模型动画资源
			*
			*	模型动画资源
			*
			***/
			class	ENGINE_EXPORT	Resource	:
				public	IProduct{
			public:
				/**	\brief	模型和动画文件引用信息
				*
				*	模型和动画文件引用信息
				*
				***/
				struct Info{
					Info(AString	name,UInt id	=	-1){
						strcpy_s(strName,MAX_NAME,name.c_str());
						uiID		=	id;
						uiRefCount	=	0;
						pUserData	=	NULL;
					};
					/**	\brief	判断是否为空
					*   
					*	@remarks 	判断是否为空
					*	@see		Info
					*	@return   	U1
					*	@note
					*
					**/
					U1	IsNull(){
						return (uiRefCount <=0 || uiID	== -1);
					}
					AChar	strName[MAX_NAME];		///<	名字
					UInt	uiID;					///<	id
					UInt	uiRefCount;				///<	引用计数
					void*	pUserData;				///<	自定义数据
				};
				typedef	stdext::hash_map<AString,Info>	InfoMap;
				typedef	InfoMap::iterator				InfoMapItr;
				typedef	InfoMap::value_type				InfoMapPair;
			public:
				Resource(CAString&	strName,AString*	strSkeleton);
				virtual ~Resource();
	
				/**	\brief	载入模型资源
				*   
				*	@remarks 	载入模型资源
				*	@see		Resource
				*	@return   	UInt
				*	@param		AString strName
				*	@param		MeshHDBuffer* pOutMeshBuff
				*	@note
				*
				**/
				SInt	LoadMesh(CAString&	strName,MeshHDBuffer*	pOutMeshBuff	=	NULL);
				/**	\brief	卸载模型资源
				*   
				*	@remarks 	卸载模型资源
				*	@see		Resource
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				U1		UnLoadMesh(CAString&	strName);
				/**	\brief	载入动画资源
				*   
				*	@remarks 	载入动画资源
				*	@see		Resource
				*	@return   	UInt
				*	@param		AString strName
				*	@note
				*
				**/
				SInt	LoadAnimation(CAString&	strName);
				/**	\brief	卸载动画资源
				*   
				*	@remarks 	卸载动画资源
				*	@see		Resource
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				U1		UnLoadAnimation(CAString&	strName);
	
				SInt	GetAnimationID(CAString&	strName);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Resource
				*	@return   	U1
				*	@note
				*
				**/
				virtual U1	Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Resource
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();

			protected:
				U1			ParseConfig(CAString&	strConfig);
	
				/**	\brief	创建硬件缓冲
				*   
				*	@remarks 	创建硬件缓冲
				*	@see		Resource
				*	@return   	U1
				*	@param		MeshHDBuffer * pOutBuff
				*	@param		CalCoreMesh * pInMesh
				*	@note
				*
				**/
				U1			CreateHardwareBuff(MeshHDBuffer*	pOutBuff,CalCoreMesh*	pInMesh);
				/**	\brief	摧毁硬件缓冲
				*   
				*	@remarks 	摧毁硬件缓冲
				*	@see		Resource
				*	@return   	U1
				*	@param		MeshHDBuffer * pInBuff
				*	@note
				*
				**/
				U1			DestroyHardwareBuff(MeshHDBuffer*	pInBuff);
	
			public:
			protected:
				InfoMap		m_mapMeshInfo;				///<	模型信息列表
				InfoMap		m_mapAnimationInfo;			///<	动画列表
				AString		m_strSkeleton;				///<	骨骼
			};

		}
	
	};
};
#endif // ENGINECHARACTERMESH_HEAD_FILE