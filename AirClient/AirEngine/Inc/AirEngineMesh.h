//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/05/31
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  EngineMesh.h
 \note     
       
 \attention:
			模型加载类
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINEMESH_HEAD_FILE
#define ENGINEMESH_HEAD_FILE

#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirCommonFile.h"

#include "AirRenderBuffer.h"


namespace Air{
	
	
	namespace Client{
	
		typedef		std::vector<Float3>		Vec3Array;
		typedef		std::vector<U32>		IndexArray;
	
		/**	\brief	模型解析接口来
		*
		*	模型解析接口类
		*
		***/
		class	ENGINE_EXPORT	Mesh	:
			public	IProduct{
		public:
			/**	\brief	顶点
			*
			*	顶点
			*
			***/
	
			typedef	Render::PNTT	Vertex;
	
			/**	\brief	 16位索引
			*
			*	16为索引
			*
			***/
			struct	Face16{
				Face16():f0(0),f1(0),f2(0){
				}
				Face16(UInt v0,UInt v1,UInt v2):f0(v0),f1(v1),f2(v2){
				}
				U16		f0,f1,f2;
			};
			/**	\brief	32位索引
			*
			*	32位索引
			*
			***/
			struct	Face32{
				Face32():f0(0),f1(0),f2(0){
				}
				Face32(Face16&	f16):f0(f16.f0),f1(f16.f1),f2(f16.f2){
				}
				Face32(UInt v0,UInt v1,UInt v2):f0(v0),f1(v1),f2(v2){
				}
				UInt	f0,f1,f2;
			};
			/**	\brief	模型解析回调
			*
			*	模型解析回调
			*
			***/
			class	IParseCallBack{
			public:
	// 			IParseCallBack(){
	// 				Mesh::SetParseCallBack(this);
	// 			}
				/**	\brief	解析接口
				*   
				*	@remarks 	解析接口
				*	@see		IParseCallBack
				*	@return   	U1
				*	@param		Common::File::Data * pData
				*	@param		std::vector<Vertex> & lstVertex
				*	@param		std::vector<Face32> & lstFace32
				*	@param		std::vector<Face16> & lstFace16
				*	@param		U1 & bUseNormal
				*	@param		U1 & bUseTexCoord
				*	@param		U1 & bUseTangent
				*	@note
				*
				**/
				virtual	U1	Parse(	Data*					pData,
									std::vector<Vertex>&	lstVertex,
									std::vector<Face32>&	lstFace32,
									std::vector<Face16>&	lstFace16,
									U1&						bUseNormal,
									U1&						bUseTexCoord,
									U1&						bUseTangent)	=	NULL;
				/**	\brief	获取解析后缀名
				*   
				*	@remarks 	获取解析后缀名
				*	@see		IParseCallBack
				*	@return   	AString
				*	@note
				*
				**/
				virtual	AString	GetPostfixName()	=	NULL;
			};
	
		public:
			Mesh(CAString&	strName);
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		Mesh
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		Mesh
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	
	
			/**	\brief	计算法线和切线
			*   
			*	@remarks 	计算法线和切线
			*	@see		Mesh
			*	@return   	U1
			*	@param		U1 bTangent
			*	@note
			*
			**/
			U1	ComputeNormalTangent(U1	bTangent	=	false);
	
			/**	\brief	设置回调
			*   
			*	@remarks 	设置回调
			*	@see		Mesh
			*	@return   	void
			*	@param		IParseCallBack * pCallBack
			*	@note
			*
			**/
			static	void	SetParseCallBack(IParseCallBack*	pCallBack);
	
			/**	\brief	获取回调函数
			*   
			*	@remarks 	获取回调函数
			*	@see		Mesh
			*	@return   	IParseCallBack*
			*	@param		AString strName
			*	@note
			*
			**/
			static	IParseCallBack*	GetParseCallBack(AString	strName);
	
			UInt					GetVertexCount();
			UInt					GetFaceCount();
			Vertex*					GetVertexArray();
			Face16*					GetFace16Array();
			Face32*					GetFace32Array();
			U1						IsFace16();
	
			U1						GetPositionArray(Vec3Array&	posArray,Float3	vScale	=	Float3(1,1,1));
			U1						GetIndexArray(IndexArray&	indexArray);
	
			
	
	
		//protected:
			std::vector<Vertex>		m_lstVertex;		///<	顶点列表
			std::vector<Face32>		m_lstFace32;		///<	面列表
			std::vector<Face16>		m_lstFace16;		///<	面列表
	
			U1						m_bUseNormal;		///<	是否有法线
			U1						m_bUseTexCoord;		///<	是否有纹理坐标
			U1						m_bUseTangent;		///<	是否有切线
	
			static	std::map<AString,IParseCallBack*>		m_mapParseFunction;		///<	解析回调列表
		};
	
		class	MeshFactory	:
			public	IFactory{
		public:
			MeshFactory();
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		BuffFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
		};
	
	};
};
#endif // ENGINEMESH_HEAD_FILE