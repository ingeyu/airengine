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
			class	Sound	:
				public	ISound{
			public:
				Sound(CAString&	strName,Info*	pInfo);
	
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
				/**	\brief	获取声音类型
				*   
				*	@remarks 	获取声音类型
				*	@see		ISound
				*	@return   	Client::Audio::ISound::enumType
				*	@note
				*
				**/
				virtual	enumType	GetType();
				/**	\brief	声音文件不需要渲染
				*   
				*	@remarks 	声音文件不需要渲染
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Render();
				/**	\brief	更新
				*   
				*	@remarks 	更新
				*	@see		Sound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		Updata();
				/**	\brief	获取当前状态
				*   
				*	@remarks 	获取当前状态
				*	@see		ISound
				*	@return   	Client::Audio::ISound::enumState
				*	@note
				*
				**/
				virtual	enumState	GetState();
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
				/**	\brief	获取剩余次数
				*   
				*	@remarks 	获取剩余次数
				*	@see		ISound
				*	@return   	UInt
				*	@note
				*
				**/
				virtual	SInt		GetRepeatCount();
				/**	\brief	更新声音
				*   
				*	@remarks 	更新位置信息
				*	@see		ISound
				*	@return   	void
				*	@note
				*
				**/
				virtual	void		UpdataSound();
			protected:
				UInt		m_uiSource;
				UInt		m_uiSampleSet;
				Info		m_Info;
				Buffer*		m_pBuffer;
				Float3		m_vLastPosition;
			};	
	
			class	SoundFactory	:
				public	IFactory{
			public:
				SoundFactory();
	
				/**	\brief	创建声音
				*   
				*	@remarks 	创建声音
				*	@see		SoundFactory
				*	@return   	IProduct*
				*	@param		AString strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
			};
		}
	
	};
};
#endif // AUIDOSOUND_HEAD_FILE