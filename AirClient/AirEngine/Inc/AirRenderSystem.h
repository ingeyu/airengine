//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceRenderSystem.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef INTERFACERENDERSYSTEM_HEAD_FILE
#define INTERFACERENDERSYSTEM_HEAD_FILE


#include "AirEngineHeader.h"
#include "AirRenderCommon.h"
#include "AirRenderBuffer.h"
#include "AirRenderTarget.h"

#include "AirRenderShader.h"
#include "AirRenderState.h"
#include "AirRenderWindow.h"
#include "AirRenderBuffer.h"
#include "AirRenderVertexDeclare.h"
#include "AirRenderDevice.h"

#include "AirCommonThread.h"
#include "AirRenderPhase.h"
namespace Air{
	
	namespace Client{
		class	Renderable;
		class	Viewport;

	
		namespace	Render{


			/**	\brief	渲染系统
			*
			*	渲染系统
			*
			***/
			class ENGINE_EXPORT	System	:
				public	Singleton<System>,
				public	IFactoryManager,
				public	PhaseManager{
			public:
				System();
				virtual ~System();

				virtual	U1	Initialization();
				virtual	U1	Release()		;
				virtual	U1	Start()			;
				virtual	U1	Stop()			;

				Device*				GetDevice();
				U32					GetDeviceCount();
				AString				GetDeviceName();
				void				SelectDevice(U32	uiIndex);
				void				AddDevice(Device*	pDevice);
				Window*				GetMainWindow();

				void				FindActiveCamera(CameraSet&	setCamera);

				void				OnWindowChange(Window* pWindow);
			protected:
				U1						m_bDeviceLost;
				DeviceVector			m_vecDevice;
				Device*					m_pDevice;
				Window*					m_pMainWindow;
			public:
// 				CBFrame					m_CBFrame;
// 				CBCamera				m_CBCamera;
// 				CBObject				m_CBObject;
// 				CBMaterial				m_CBMaterial;
// 				CBBone					m_CBBone;
			};
		}
	
	};
};
#endif // INTERFACERENDERSYSTEM_HEAD_FILE