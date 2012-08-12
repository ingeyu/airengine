/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/04/10
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  CommonWindow.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONWINDOW_HEAD_FILE
#define COMMONWINDOW_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

namespace	Air{
	namespace Common{
		/**	\brief	默认消息回调
		*   
		*	@remarks 	默认消息回调
		*	@see		
		*	@return   	COMMON_EXPORT	LRESULT
		*	@param		HWND wnd
		*	@param		UINT msg
		*	@param		WPARAM wp
		*	@param		LPARAM lp
		*	@note
		*
		**/
		COMMON_EXPORT	LRESULT	WindowProc(HWND	wnd, UINT	msg, WPARAM	wp, LPARAM lp);
		/**	\brief	新建一个窗口
		*   
		*	@remarks 	新建一个窗口
		*	@see		
		*	@return   	HWND
		*	@param		CAString&	strName
		*	@param		HWND	hParentWnd
		*	@note
		*
		**/
		COMMON_EXPORT	HWND	NewWindow(CAString&	strName,U32 iWidth,U32 iHeight,WNDPROC pWinFunc	=	(WNDPROC)WindowProc,HWND	hParentWnd	=	NULL);
	

	};//end of	namespace	Client
};//end of namespace Air
#endif // COMMONWINDOW_HEAD_FILE