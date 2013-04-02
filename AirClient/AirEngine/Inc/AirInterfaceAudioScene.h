#ifndef INTERFACEAUDIOSCENE_HEAD_FILE
#define INTERFACEAUDIOSCENE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceAudioSound.h"
namespace Air{
	
	namespace Engine{
		class	Camera;
	
		namespace	Audio{
			class	IScene	:
				public	IFactoryManager,
				public	IProperty{
			public:
				/**	\brief	初始化
				*   
				*	@remarks 	初始化
				*	@see		Scene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Initialization()	=	NULL;
				/**	\brief	释放
				*   
				*	@remarks 	释放
				*	@see		Scene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Release()	=	NULL;
				/**	\brief	设置摄像机
				*   
				*	@remarks 	设置摄像机
				*	@see		IScene
				*	@return   	void
				*	@param		Camera * pCamera
				*	@note
				*
				**/
				virtual	void	SetCamera(Camera*	pCamera)	=	NULL;
				/**	\brief	更新
				*   
				*	@remarks 	更新
				*	@see		Scene
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Updata()	=	NULL;
	
				/**	\brief	播放
				*   
				*	@remarks 	播放
				*	@see		Scene
				*	@return   	void
				*	@param		ISound::Info & info
				*	@note
				*
				**/
				virtual	ISound*	Play(ISound::Info*	pInfo)	=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEAUDIOSCENE_HEAD_FILE