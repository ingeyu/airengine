#ifndef AUIDOSOUND_HEAD_FILE
#define AUIDOSOUND_HEAD_FILE

#include "AirAudioHeader.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
			class	Buffer;
			/**	\brief	声音
			*
			*	声音
			*
			***/
			class	ALSound	:
				public	Sound{
			public:
				ALSound(CAString&	strName,Info*	pInfo);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Sound
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Sound
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	设置音量
				*   
				*	@remarks 	设置音量
				*	@see		IProperty
				*	@return   	void
				*	@param		Real f
				*	@note
				*
				**/
				virtual	void	SetVolume(Real	f);
				/**	\brief	设置音调
				*   
				*	@remarks 	设置音调
				*	@see		IProperty
				*	@return   	void
				*	@param		Real f
				*	@note
				*
				**/
				virtual	void	SetPitch(Real	f);

				virtual	enumState	GetState();
				/**	\brief	更新
				*   
				*	@remarks 	更新
				*	@see		Sound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Update();

				/**	\brief	播放
				*   
				*	@remarks 	播放
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Play();
				/**	\brief	暂停
				*   
				*	@remarks 	暂停
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Pause();
				/**	\brief	停止
				*   
				*	@remarks 	停止
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Stop();
				/**	\brief	重新开始播放
				*   
				*	@remarks 	重新开始播放
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		RePlay();

				/**	\brief	更新声音
				*   
				*	@remarks 	更新位置信息
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		UpdateSound();
			protected:
				UInt		m_uiSource;
				UInt		m_uiSampleSet;
				Buffer*		m_pBuffer;
				Float3		m_vLastPosition;
			};	
		}
	
	};
};
#endif // AUIDOSOUND_HEAD_FILE