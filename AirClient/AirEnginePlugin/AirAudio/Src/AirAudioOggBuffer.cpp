// #include "AirAudioOggBuffer.h"
// #include "GlobalSetting.h"
// #include "InterfaceResourceSystem.h"
// 
// namespace	Client{
// 	namespace	Audio{
// 		/**	\brief	内存数据
// 		*
// 		*	内存数据
// 		*
// 		***/
// 		struct	MemeryData{
// 			MemeryData(){
// 				pData		=	NULL;
// 				uiPosition	=	0;
// 			};
// 			Data*	pData;
// 			UInt		uiPosition;
// 		};
// 
// 		/*
// 		** These next four methods are custom accessor functions to allow the Ogg Vorbis
// 		** libraries to be able to stream audio data directly from an Ogre::DataStreamPtr
// 		*/
// 		size_t OggRead(void *ptr, size_t size, size_t nmemb, void *datasource)
// 		{
// 			MemeryData*	p	=	(MemeryData*)datasource;
// 			U8*			pBuff	=	p->pData->GetBuff();
// 			memcpy(ptr,&pBuff[p->uiPosition],size*nmemb);
// 			p->uiPosition	+=	size*nmemb;
// 			return size*nmemb;
// 		}
// 
// 		int OggSeek(void *datasource, ogg_int64_t offset, int whence)
// 		{
// 			MemeryData*	p	=	(MemeryData*)datasource;
// 			switch(whence)
// 			{
// 			case SEEK_SET:
// 				p->uiPosition	=	offset;
// 				break;
// 			case SEEK_END:
// 				p->uiPosition	=	p->pData->GetSize()-1+offset;
// 				// Falling through purposefully here
// 			case SEEK_CUR:
// 				p->uiPosition	+=	offset;
// 				break;
// 			}
// 
// 			return 0;
// 		}
// 
// 		int OggClose(void *datasource)
// 		{
// 			return 0;
// 		}
// 
// 		long OggTell(void *datasource){
// 			MemeryData*	p	=	(MemeryData*)datasource;
// 			return	p->uiPosition;
// 		}
// 
// 		void Swap(short &s1, short &s2)
// 		{
// 			short sTemp = s1;
// 			s1 = s2;
// 			s2 = sTemp;
// 		};
// 
// 		unsigned long DecodeOggVorbis(OggVorbis_File *psOggVorbisFile, char *pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels)
// 		{
// 			int current_section;
// 			long lDecodeSize;
// 			unsigned long ulSamples;
// 			short *pSamples;
// 
// 			unsigned long ulBytesDone = 0;
// 			while (1)
// 			{
// 				lDecodeSize = ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0, 2, 1, &current_section);
// 				if (lDecodeSize > 0)
// 				{
// 					ulBytesDone += lDecodeSize;
// 
// 					if (ulBytesDone >= ulBufferSize)
// 						break;
// 				}
// 				else
// 				{
// 					break;
// 				}
// 			}
// 
// 			// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
// 			// however 6-Channels files need to be re-ordered
// 			if (ulChannels == 6)
// 			{		
// 				pSamples = (short*)pDecodeBuffer;
// 				for (ulSamples = 0; ulSamples < (ulBufferSize>>1); ulSamples+=6)
// 				{
// 					// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
// 					// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
// 					Swap(pSamples[ulSamples+1], pSamples[ulSamples+2]);
// 					Swap(pSamples[ulSamples+3], pSamples[ulSamples+5]);
// 					Swap(pSamples[ulSamples+4], pSamples[ulSamples+5]);
// 				}
// 			}
// 
// 			return ulBytesDone;
// 		}
// 
// 
// 		OggBuffer::OggBuffer( AString& strName ):Buffer(strName){
// 			m_pVorbisInfo	=	NULL;
// 		}
// 
// 		U1 OggBuffer::Create(){
// 			ov_callbacks callbacks;
// 			callbacks.close_func	= OggClose;
// 			callbacks.tell_func		= OggTell;
// 			callbacks.read_func		= OggRead;
// 			callbacks.seek_func		= OggSeek;
// 
// 			MemeryData	mData;
// 			mData.pData	=	ResourceSystem::GetSingleton()->Find(m_strProductName);
// 
// 			if(mData.pData==NULL)
// 				return	false;
// 			//设置回调
// 			int	ret	=	ov_open_callbacks(&mData, &m_OggFile, NULL, 0, callbacks);
// 			//获取音频信息
// 			m_pVorbisInfo = ov_info(&m_OggFile, -1);
// 			unsigned long channels = m_pVorbisInfo->channels;
// 			long	mFreq = m_pVorbisInfo->rate;
// 			int		mChannels = m_pVorbisInfo->channels;
// 			int		mBPS = 16;
// 			//计算音频格式
// 			ComputeFormat(mFreq,mChannels,mBPS);
// 			//申请空间
// 			m_pBuffer = new U8[m_uiSize];
// 			//载入
// 			//LoadBuffer();
// 
// 			DecodeOggVorbis(&m_OggFile,(AChar*)m_pBuffer,m_uiSize,mChannels);
// 
// 			return	true;
// 		}
// 
// 		U1 OggBuffer::Destroy(){
// 			SAF_DA(m_pBuffer);
// 
// 			ov_clear(&m_OggFile);
// 			return	true;
// 		}
// 
// 		U1 OggBuffer::ComputeFormat(long	freq,int channel,int bps){
// 			switch(channel)
// 			{
// 			case 1:
// 				if(bps == 8)
// 				{
// 					m_uiFormat = AL_FORMAT_MONO8;
// 					// Set BufferSize to 250ms (Frequency divided by 4 (quarter of a second))
// 					m_uiSize = freq / 4;
// 				}
// 				else
// 				{
// 					m_uiFormat = AL_FORMAT_MONO16;
// 					// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
// 					m_uiSize = freq >> 1;
// 					// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
// 					m_uiSize -= (m_uiSize % 2);
// 				}
// 				break;
// 			case 2:
// 				if(bps == 8)
// 				{
// 					m_uiFormat = AL_FORMAT_STEREO16;
// 					// Set BufferSize to 250ms (Frequency * 2 (8bit stereo) divided by 4 (quarter of a second))
// 					m_uiSize = freq >> 1;
// 					// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
// 					m_uiSize -= (m_uiSize % 2);
// 				}
// 				else
// 				{
// 					m_uiFormat = AL_FORMAT_STEREO16;
// 					// Set BufferSize to 250ms (Frequency * 4 (16bit stereo) divided by 4 (quarter of a second))
// 					m_uiSize = freq;
// 					// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
// 					m_uiSize -= (m_uiSize % 4);
// 				}
// 				break;
// 			case 4:
// 				m_uiFormat = alGetEnumValue("AL_FORMAT_QUAD16");
// 				// Set BufferSize to 250ms (Frequency * 8 (16bit 4-channel) divided by 4 (quarter of a second))
// 				m_uiSize = freq * 2;
// 				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
// 				m_uiSize -= (m_uiSize % 8);
// 				break;
// 			case 6:
// 				m_uiFormat = alGetEnumValue("AL_FORMAT_51CHN16");
// 				// Set BufferSize to 250ms (Frequency * 12 (16bit 6-channel) divided by 4 (quarter of a second))
// 				m_uiSize = freq * 3;
// 				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
// 				m_uiSize -= (m_uiSize % 12);
// 				break;
// 			case 7:
// 				m_uiFormat = alGetEnumValue("AL_FORMAT_61CHN16");
// 				// Set BufferSize to 250ms (Frequency * 16 (16bit 7-channel) divided by 4 (quarter of a second))
// 				m_uiSize = freq * 4;
// 				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
// 				m_uiSize -= (m_uiSize % 16);
// 				break;
// 			case 8:
// 				m_uiFormat = alGetEnumValue("AL_FORMAT_71CHN16");
// 				// Set BufferSize to 250ms (Frequency * 20 (16bit 8-channel) divided by 4 (quarter of a second))
// 				m_uiSize = freq * 5;
// 				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
// 				m_uiSize -= (m_uiSize % 20);
// 				break;
// 			default:
// 				// Couldn't determine buffer format so log the error and default to mono
// 				//Ogre::LogManager::getSingleton().logMessage("!!WARNING!! Could not determine buffer format!  Defaulting to MONO");
// 
// 				m_uiFormat = AL_FORMAT_MONO16;
// 				// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
// 				m_uiSize = freq >> 1;
// 				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
// 				m_uiSize -= (m_uiSize % 2);
// 				break;
// 			}
// 			return	true;
// 		}
// 
// 		U1 OggBuffer::LoadBuffer(){
// 			int section, sizeRead = 0;
// 			UInt	uiPosition	=	0;
// 			AChar*	pTemp	=	new AChar[m_uiSize];
// 			AChar*	p		=	pTemp;
// 			// Read only what was asked for
// 			while(uiPosition < m_uiSize){
// 				sizeRead = ov_read(&m_OggFile, p, m_uiSize, 0, 2, 1, &section);
// 				if(sizeRead == 0) 
// 					break;
// 				uiPosition+=	sizeRead;
// 				memcpy(&m_pBuffer[uiPosition],p,sizeRead);
// 			}
// 			SAF_DA(pTemp);
// 			return	true;
// 		}
// 		OggBufferFactory::OggBufferFactory(){
// 			m_strTypeName	=	"OggBuffer";
// 		}
// 
// 		IProduct* OggBufferFactory::Create( AString strName,IFactoryParamList* lstParam /* = NULL */ ){
// 			if(strName.empty())
// 				return	NULL;
// 
// 			return	new	OggBuffer(strName);
// 		}
// 	}
// }