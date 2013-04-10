#include "AirInterfaceUIFlashSystem.h"
// #include "..\Dependencies\FlashUI\Include\ASInterface.h"
// #include "..\Dependencies\FlashUI\Include\IFlashDX.h"
namespace Air{
	
	namespace Engine{
	
		namespace	UI{
			namespace	Flash{
				ISystem::ISystem(CAString&	strType):Common::ISystem(strType){
	// 				m_pFlashMgr		=	NULL;
	// 				m_fFlashVersion	=	0;
				}
	
				U1 ISystem::Initialization(){
	// 				m_pFlashMgr		=	GetFlashToDirectXInstance();
	// 				m_fFlashVersion	=	m_pFlashMgr->GetFlashVersion();
					return	true;
				}
	
				U1 ISystem::Release(){
	
					return	true;
				}
	
				void ISystem::Update(){
	
				}
	
				void ISystem::Render(){
	
				}
	
				long ISystem::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,void* pUserContext ){
	
					return	0;
				}
	
				void ISystem::RenderTarget(){
	
				}
	
				void ISystem::OnResetDevice(){
	
				}
			}
		}
	
	}
};