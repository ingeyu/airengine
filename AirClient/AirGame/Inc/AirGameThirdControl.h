#ifndef GAMETHIRDCONTROL_HEAD_FILE
#define GAMETHIRDCONTROL_HEAD_FILE

#include "AirGameHeader.h"
#include "AirGameFPSControl.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Game{
			class	ThirdControl	:
				public	FPSControl{
			public:
				ThirdControl(AString	strName,Info*	pInfo);
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		FPSControl
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		FPSControl
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	鼠标移动事件
				*   
				*	@remarks 	鼠标移动事件
				*	@see		Control
				*	@return   	bool
				*	@param		const Input::MouseEvent & arg
				*	@note
				*
				**/
				virtual bool	mouseMoved( const OIS::MouseEvent &arg );
	
				/**	\brief	每帧更新
				*   
				*	@remarks 	每帧更新
				*	@see		ThirdControl
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		OnFrameMove();
	
				virtual	U1		keyReleased( const OIS::KeyEvent &arg );
	
				Real			m_fMinCameraDis;
				Real			m_fMaxCameraDis;
				Real			m_fCurrentDis;
				Real			m_fTargetDis;
	
				Float3			m_vTargetPosition;	///<	目标位置
				Real			m_fMoveSensitivity;	///<	移动灵敏度
			};
	
		}
	
	};
};
#endif // GAMETHIRDCONTROL_HEAD_FILE