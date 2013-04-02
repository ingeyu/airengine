#ifndef INTERFACEUIFLASHSYSTEM_HEAD_FILE
#define INTERFACEUIFLASHSYSTEM_HEAD_FILE

#include "AirInterfaceUIFlashLayout.h"
namespace Air{
	
	
	namespace Engine{
	
		namespace	UI{
			namespace	Flash{
				class	ENGINE_EXPORT	ISystem	:
					public	Common::ISystem{
				public:
					ISystem(CAString&	strType);
	
					/**	\brief	初始化
					*   
					*	@remarks 	
					*	@see		System
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Initialization();
					/**	\brief	释放
					*   
					*	@remarks 	释放
					*	@see		System
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Release();
					/**	\brief	更新UI
					*   
					*	@remarks 	更新UI 用于处理鼠标消息键盘消息 以便处理是否有窗口被激活
					*	@see		ISystem
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	Updata();
	
					/**	\brief	渲染
					*   
					*	@remarks 	渲染
					*	@see		ISystem
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	Render();
					/**	\brief	渲染窗口目标到缓存
					*   
					*	@remarks 	渲染窗口目标到缓存
					*	@see		Renderer
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	RenderTarget();
					/**	\brief	Windows消息回调
					*   
					*	@remarks 	Windows消息回调
					*	@see		IEngine
					*	@return   	long
					*	@param		HWND hWnd
					*	@param		UINT uMsg
					*	@param		WPARAM wParam
					*	@param		LPARAM lParam
					*	@param		bool * pbNoFurtherProcessing
					*	@param		void * pUserContext
					*	@note
					*
					**/
					virtual long	MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,void* pUserContext );
	
					/**	\brief	设备重置回调
					*   
					*	@remarks 	设备重置回调
					*	@see		IISystem
					*	@return   	void
					*	@note
					*
					**/
					virtual	void	OnResetDevice();
				};
			}
		}
	
	};
};
#endif // INTERFACEUIFLASHSYSTEM_HEAD_FILE