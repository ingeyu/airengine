#ifndef RENDERDEVICE_HEAD_FILE
#define RENDERDEVICE_HEAD_FILE

#include "AirRenderHeader9.h"
namespace Air{
	
	namespace Client{
	
		namespace	Render{
			/**	\brief	消息回调
			*   
			*	@remarks 	消息回调
			*	@see		
			*	@return   	LRESULT CALLBACK
			*	@param		HWND hwnd
			*	@param		UINT msg
			*	@param		WPARAM wParam
			*	@param		LPARAM lParam
			*	@note
			*
			**/
			LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			/**	\brief	DX9设备类
			*
			*	DX9设备类
			*
			***/
			class	Device9{
			public:
				/**	\brief	设备创建信息
				*
				*	设备创建信息
				*
				***/
				typedef		DisplayParam	Info;
	
				typedef	std::vector<UInt>			MsaaQualityVector;
				typedef	std::vector<D3DDISPLAYMODE>	DisplayModeVector;
				struct	Adapter{
					D3DADAPTER_IDENTIFIER9	identifier;
					HMONITOR				monitor;
					D3DDISPLAYMODE			displayMode;
					MsaaQualityVector		vecMSAAWindow;
					MsaaQualityVector		vecMSAAFull;
					D3DCAPS9				caps;
					DisplayModeVector		vecDisplayMode;
				};
	
	
				typedef	std::vector<Adapter>	AdapterVector;
			public:
				Device9(Info*	pInfo);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
				/**	\brief	设备丢失
				*   
				*	@remarks 	设备丢失
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Lost();
				/**	\brief	重置设备
				*   
				*	@remarks 	重置设备
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Reset();
	
				/**	\brief	渲染一帧
				*   
				*	@remarks 	渲染一帧
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	RenderOneFrame();
				/**	\brief	渲染目标
				*   
				*	@remarks 	渲染目标
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	RenderTarget();
				/**	\brief	渲染最终结果
				*   
				*	@remarks 	渲染最终结果
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	RenderFinal();
				/**	\brief	保存截图
				*   
				*	@remarks 	保存截图
				*	@see		Device9
				*	@return   	U1
				*	@param		AString & strName
				*	@note
				*
				**/
				U1	SetNeedSaveScreen(CAString&	strName);
				/**	\brief	设置全屏
				*   
				*	@remarks 	设置全屏
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	SetNeedFullScreen();
				/**	\brief	检测是否需要更改设备
				*   
				*	@remarks 	检测是否需要更改设备
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	CheckChange();
	
				/**	\brief	全屏
				*   
				*	@remarks 	全屏
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	FullScreen();
				/**	\brief	更改尺寸
				*   
				*	@remarks 	更改尺寸
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	ChangeSize();
				/**	\brief	保存屏幕
				*   
				*	@remarks 	保存屏幕
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	SaveScreen();
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	CreateWin();
				/**	\brief	摧毁窗口
				*   
				*	@remarks 	摧毁窗口
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	DestroyWin();
	
				/**	\brief	创建D3D
				*   
				*	@remarks 	创建D3D
				*	@see		Device9
				*	@return   	U1
				*	@note
				*
				**/
				U1	CreateD3D();
				/**	\brief	创建设备
				*   
				*	@remarks 	创建设备
				*	@see		Device9
				*	@return   	U1
				*	@param		UInt uiAdapter
				*	@note
				*
				**/
				U1	CreateDevice(UInt uiAdapter);
				/**	\brief	摧毁设备
				*   
				*	@remarks 	摧毁设备
				*	@see		Device
				*	@return   	U1
				*	@note
				*
				**/
				U1	DestroyDevice();
	
				/**	\brief	初始化设备状态
				*   
				*	@remarks 	初始化设备状态
				*	@see		Device9
				*	@return   	void
				*	@note
				*
				**/
				void	InitDeviceState();
	
				/**	\brief	设置为设备初识渲染状态
				*   
				*	@remarks 	设置为设备初识渲染状态
				*	@see		Device9
				*	@return   	void
				*	@note
				*
				**/
				inline	void	SetDefaultDeviceState(){
					//m_pDefaultState->Apply();
				};
	
	
				D3DPRESENT_PARAMETERS	m_DeviceParam;				///<	设备创建参数
				Info					m_Info;						///<	创建信息
				AdapterVector			m_vecAdapter;				///<	适配器列表
				IDirect3D9*				m_pD3D;
				IDirect3DDevice9*		m_pDevice;					///<	DX9设备
				IDirect3DStateBlock9*	m_pDefaultState;			///<	默认渲染状态
	
				U1						m_bPause;					///<	是否需要暂停
	
	
				AString					m_strSaveScreenFileName;	///<	保存文件名
				U1						m_bNeedFullScreen;			///<	是否需要全屏切换
			};
		}
	};
};
#endif // RENDERDEVICE_HEAD_FILE