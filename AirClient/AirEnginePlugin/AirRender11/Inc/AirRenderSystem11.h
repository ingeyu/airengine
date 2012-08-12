#ifndef RENDERSYSTEM_HEAD_FILE
#define RENDERSYSTEM_HEAD_FILE

#include "AirRenderHeader11.h"
#include "AirRenderStateManager11.h"

namespace Air{
	
	
	
	namespace Client{
		class ISceneNode;
	
		namespace	Render{
			class System	:	
				public	ISystem,
				public	StateManager{
			public:
				System();
				virtual ~System();
	
				/**	\brief	初始化
				*   
				*	@remarks 	初始化
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Initialization();
	
				/**	\brief	开始
				*   
				*	@remarks 	开始
				*	@see		System
				*	@return   	bool
				*	@note
				*
				**/
				virtual bool Start();
	
	
				/**	\brief	停止渲染
				*   
				*	@remarks 	停止渲染
				*	@see		System
				*	@return   	bool
				*	@note
				*
				**/
				virtual	bool Stop();
	
				/**	\brief	释放
				*   
				*	@remarks 	释放
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Release();
				/**	\brief	重置设备
				*   
				*	@remarks 	重置设备
				*	@see		IEngine
				*	@return   	long
				*	@param		void * pd3dDevice
				*	@param		const void * pBackBufferSurfaceDesc
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual void		OnD3DResetDevice(	void* pd3dDevice, const void* pBackBufferSurfaceDesc,void* pUserContext,void*	pSwapChain	= NULL );
				/**	\brief	设备丢失
				*   
				*	@remarks 	设备丢失
				*	@see		IEngine
				*	@return   	void
				*	@param		void * pUserContext
				*	@note
				*
				**/
				virtual void		OnD3DLostDevice(	void* pUserContext );	
				/**	\brief	设置为Instance技术顶点缓冲
				*   
				*	@remarks 	设置为Instance技术顶点缓冲
				*	@see		ISystem
				*	@return   	void
				*	@param		Vertex::IBuff * pBuff
				*	@param		Vertex::IBuff * pInstanceBuff
				*	@param		UInt uiInstanceCount
				*	@note
				*
				**/
				virtual	void		SetVertexInstance(Vertex::IBuff* pBuff,Vertex::IBuff* pInstanceBuff,UInt uiInstanceCount );
				/**	\brief	保存屏幕纹理到本地文件
				*   
				*	@remarks 	保存屏幕纹理到本地文件
				*	@see		System
				*	@return   	void
				*	@param		AString strName
				*	@note
				*
				**/
				virtual	U1		SaveScreenToFile(CAString&	strName);
				/**	\brief	设置全屏状态
				*   
				*	@remarks 	设置全屏状态
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		SetFullScreen();
				/**	\brief	更新表面
				*   
				*	@remarks 	更新表面
				*	@see		ISystem
				*	@return   	U1
				*	@param		ITexture * pSrcTexture
				*	@param		RECT * rect
				*	@param		ITexture * pDstTexture
				*	@param		POINT & p
				*	@note
				*
				**/
				virtual	U1			UpdataSurface(ITexture*	pSrcTexture,RECT*	rect,ITexture*	pDstTexture,POINT& p);
	
				/**	\brief	子类需要重写的循环调用函数
				*   
				*	@remarks 	线程自身的执行函数
				*	@see		Thread
				*	@return   	bool
				*	@note
				*
				**/
				virtual bool RepetitionRun();
				/**	\brief	窗口尺寸变化
				*   
				*	@remarks 	窗口尺寸变化
				*	@see		ISystem
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			ChangeSize();
				/**	\brief	是否需要重置
				*   
				*	@remarks 	是否需要重置
				*	@see		ISystem
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			IsNeedReset();
	
				/**	\brief	重置设备
				*   
				*	@remarks 	重置设备
				*	@see		ISystem
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			Reset();
	
				/**	\brief	由RenderDevice调用
				*   
				*	@remarks 	设备丢失的时候  需要由主线程执行设备重置
				*	@see		System
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		SetNeedReset();

				//IDirect3D9*			GetD3D();
				
				/**	\brief	设置顶点声明
				*   
				*	@remarks 	设置顶点声明
				*	@see		IDirectXCallback
				*	@return   	U1
				*	@param		Vertex::IBuff * pBuff
				*	@note
				*
				**/
				virtual U1		SetVertexDeclare(VertexDeclare*	pDeclare);
				/**	\brief	设置顶点缓冲
				*   
				*	@remarks 	设置顶点缓冲
				*	@see		IDirectXCallback
				*	@return   	U1
				*	@param		Vertex::IDeclare * pDeclare
				*	@note
				*
				**/
				virtual U1		SetVertexBuffer(VertexBuffer*	pBuffer);
				/**	\brief	设置索引缓冲
				*   
				*	@remarks 	设置索引缓冲
				*	@see		IDirectXCallback
				*	@return   	U1
				*	@param		Index::IBuffer * pBuffer
				*	@note
				*
				**/
				virtual U1		SetIndexBuffer(IndexBuffer*		pBuffer);

				/**	\brief	设置纹理
				*   
				*	@remarks 	设置纹理
				*	@see		ISystem
				*	@return   	U1
				*	@param		enumShaderType type
				*	@param		U32 uiRegister
				*	@param		ITexture * pTexture
				*	@note
				*
				**/
				virtual	U1		SetTexture(enumShaderType	type,U32	uiRegister,ITexture*	pTexture);
				/**	\brief	设置shader
				*   
				*	@remarks 	设置shader
				*	@see		ISystem
				*	@return   	U1
				*	@param		Render::enumShaderType	type
				*	@param		IShader * pShader
				*	@note
				*
				**/
				virtual	U1		SetShader(Render::enumShaderType	type,IShader*	pShader);
				/**	\brief	设置光栅化状态
				*   
				*	@remarks 	设置光栅化状态
				*	@see		ISystem
				*	@return   	U1
				*	@param		IRasterizerState * pState
				*	@note
				*
				**/
				virtual	U1		SetRasterizerState(IRasterizerState*	pState);
				/**	\brief	设置深度模板状态
				*   
				*	@remarks 	设置深度模板状态
				*	@see		ISystem
				*	@return   	U1
				*	@param		IDepthStencilState * pState
				*	@note
				*
				**/
				virtual	U1		SetDepthStencilState(IDepthStencilState*	pState);
				/**	\brief	设置混合状态
				*   
				*	@remarks 	设置混合状态
				*	@see		ISystem
				*	@return   	U1
				*	@param		IBlendState * pState
				*	@note
				*
				**/
				virtual	U1		SetBlendState(IBlendState*	pState);
				virtual	U1		DrawOpt(const DrawOption&	opt);

				virtual	U1		SetConstantBuffer(enumShaderType	type,IConstantBuffer*	pBuffer);
				virtual	U1		SetConstantBuffer(IConstantBuffer*	pBuffer);
			private:
				ISceneNode*			m_pSceneNode;
	
				U1					m_bNeedReset;
				//IDirect3D9*			m_pD3D;
			};
		};
	};
};
#endif // RENDERSYSTEM_HEAD_FILE