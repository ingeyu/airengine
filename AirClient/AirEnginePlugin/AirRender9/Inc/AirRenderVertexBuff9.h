#ifndef RENDERVERTEXBUFF_HEAD_FILE
#define RENDERVERTEXBUFF_HEAD_FILE

#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"

namespace Air{
	
	namespace Client{
	
		namespace	Render{
	
			namespace Vertex{		
				/**	\brief	创建声明
				*
				*	创建声明
				*
				***/
				class Declare9	:
					public	IDeclare{
				public:
					Declare9(CAString&	strName,Info*	pInfo);
					/**	\brief	获取顶点声明
					*   
					*	@remarks 	这样做是为了渲染的时候才创建
					*	@see		Declare
					*	@return   	IDirect3DVertexDeclaration9*
					*	@note
					*
					**/
					virtual	void*	GetDeclare();
				protected:
					IDirect3DVertexDeclaration9*	m_pDeclare;
				};
				/**	\brief	顶点声明工厂
				*
				*	顶点声明工厂
				*
				***/
				class	Declare9Factory	:
					public	Factory{
				public:
					Declare9Factory();
					/**	\brief	创建
					*   
					*	@remarks 	创建
					*	@see		DeclareFactory
					*	@return   	IProduct*
					*	@param		AString& strName
					*	@param		IFactoryParamList * lstParam
					*	@note
					*
					**/
					virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
	
				};
				/**	\brief	顶点缓冲
				*
				*	顶点缓冲
				*
				***/
				class Buff9	:	
					public	Buffer{
				public:
	
				public:
					Buff9(CAString&	strName,Info*	pInfo);
					/**	\brief	摧毁
					*   
					*	@remarks 	摧毁
					*	@see		Buff
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Destroy( );
	
					virtual	void*	GetBuffer();

					IDirect3DVertexBuffer9*	m_pBuffer;
				};
			};
		}
	
	};
};
#endif // RENDERVERTEXBUFF_HEAD_FILE