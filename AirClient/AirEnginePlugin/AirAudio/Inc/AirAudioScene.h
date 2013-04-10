#ifndef AUDIOSCENE_HEAD_FILE
#define AUDIOSCENE_HEAD_FILE

#include "AirAudioHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			class	Scene	:
				public	IScene{
			public:
				Scene(AString	strName);
	
				/**	\brief	初始化
				*   
				*	@remarks 	初始化
				*	@see		Scene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Initialization();
				/**	\brief	释放
				*   
				*	@remarks 	释放
				*	@see		Scene
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Release();
	
				/**	\brief	更新
				*   
				*	@remarks 	更新
				*	@see		Scene
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Update();
				/**	\brief	设置摄像机
				*   
				*	@remarks 	设置摄像机
				*	@see		IScene
				*	@return   	void
				*	@param		Camera * pCamera
				*	@note
				*
				**/
				virtual	void	SetCamera(Camera*	pCamera);
	
				/**	\brief	播放
				*   
				*	@remarks 	播放
				*	@see		Scene
				*	@return   	void
				*	@param		ISound::Info & info
				*	@note
				*
				**/
				virtual	ISound*	Play(ISound::Info*	pInfo);
	
				/**	\brief	停止所有声音
				*   
				*	@remarks 	停止所有声音
				*	@see		Scene
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	StopAllSound();
				/**	\brief	摧毁所有
				*   
				*	@remarks 	摧毁所有
				*	@see		Scene
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	DestroyAllSound();
	
				
	
				typedef		std::list<ISound*>	SoundList;
				typedef		SoundList::iterator	SoundListItr;
	
			protected:
				virtual	void	UpdateListener(Camera*	pCamera);
			protected:
				AString		m_strName;
				Camera*		m_pCamera;
			};
		}
	
	};
};
#endif // AUDIOSCENE_HEAD_FILE