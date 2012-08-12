#include "AirAudioBuffer.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceResourceSystem.h"
namespace Air{
	
	namespace	Client{
		namespace	Audio{
			
	
			Buffer::Buffer( CAString& strName ):IProduct(strName){
				m_pBuffer		=	NULL;
				m_uiSize		=	0;
				m_uiFormat		=	0;
				m_uiFreqBuffer	=	0;
			}
	
			U1 Buffer::Create(){
				OutputDebugStringA("Create	WAV	Buffer(");
				OutputDebugStringA(m_strProductName.c_str());
				OutputDebugStringA(")\n");
				S8	Loop	=	0;
	
	 			Data*	pData	=	NULL;//GetGlobalSetting().m_pResourceSystem->Find(m_strProductName);
				if(pData==NULL)
					return	false;
	
				if(!LoadWAVFromMemory(pData))
					return	false;
			
	// 			alutLoadWAVMemory((S8*)pData->GetBuff(),&m_uiFormat, (void **) &m_pBuffer,(ALsizei*)&m_uiSize, &m_uiFreqBuffer, &Loop);
	
	//			alutLoadWAVFile((ALbyte*)m_strProductName.c_str(),&m_uiFormat, (void **) &m_pBuffer,(ALsizei*)&m_uiSize, &m_uiFreqBuffer, &Loop);
				if(m_pBuffer==NULL)
					return false;
				U1	bError	=	alGetError();
				m_pObject	=	(UInt*)m_pBuffer;
				return true;
			}
	
			U1 Buffer::Destroy(){
				if(m_pBuffer!=NULL){
	 			//alutUnloadWAV(m_uiFormat,m_pBuffer,m_uiSize,m_uiFreqBuffer);
					delete[]		m_pBuffer;
					m_pBuffer		=	NULL;
					m_uiSize		=	0;
					m_uiFormat		=	0;
					m_uiFreqBuffer	=	0;
				}
				m_pObject	=	NULL;
				OutputDebugStringA("Destroy	WAV	Buffer(");
				OutputDebugStringA(m_strProductName.c_str());
				OutputDebugStringA(")\n");
				return true;
			}
	
			U1 Buffer::LoadWAVFromMemory( Data* pData ){
	
				WAV::RIFFHeader riff;
				WAV::SubChunk1	chunk1;
				WAV::SubChunk2	chunk2;
	
				U8*		p		=	pData->GetBuff();
				UInt	uiPos	=	0;
	
				// read the sub chunk data
				memcpy(&riff,	&p[uiPos],sizeof(WAV::RIFFHeader));uiPos+=sizeof(WAV::RIFFHeader);
				memcpy(&chunk1, &p[uiPos],sizeof(WAV::SubChunk1));uiPos+=sizeof(WAV::SubChunk1);
				memcpy(&chunk2, &p[uiPos],sizeof(WAV::SubChunk2));uiPos+=sizeof(WAV::SubChunk2);
	
				AChar	str[256];
				ZeroMemory(str,256);
				// check chunk identifiers
				if(	riff.riff[0] != 'R' || 
					riff.riff[1] != 'I' || 
					riff.riff[2] != 'F' || 
					riff.riff[3] != 'F')
				{
					sprintf(str,"LoadWAV(%s): invalid 'RIFF' header\n", m_strProductName.c_str());
					OutputDebugStringA(str);
					return false;
				}
				if(	riff.wave[0] != 'W' || 
					riff.wave[1] != 'A' || 
					riff.wave[2] != 'V' || 
					riff.wave[3] != 'E')
				{
					sprintf(str,"LoadWAV(%s): invalid 'WAVE' header\n",  m_strProductName.c_str());
					OutputDebugStringA(str);
					return false;
				}
				if(	chunk1.subChunkId[0] != 'f' || 
					chunk1.subChunkId[1] != 'm' || 
					chunk1.subChunkId[2] != 't' || 
					chunk1.subChunkId[3] != ' ')
				{
					sprintf(str,"LoadWAV(%s): invalid 'fmt ' header\n",  m_strProductName.c_str());
					OutputDebugStringA(str);
					return false;
				}
				if(	chunk2.subChunkId[0] != 'd' || 
					chunk2.subChunkId[1] != 'a' || 
					chunk2.subChunkId[2] != 't' || 
					chunk2.subChunkId[3] != 'a')
				{
					sprintf(str,"LoadWAV(%s): invalid 'data' header\n",  m_strProductName.c_str());
					OutputDebugStringA(str);
					return false;
				}
	
				m_uiSize		=	chunk2.subChunkSize;
				m_uiFreqBuffer	=	chunk1.sampleRate;
	
				//set the data
				if(chunk1.numChannels == 1)
				{
					if(chunk1.bitsPerSample == 8)
						m_uiFormat = AL_FORMAT_MONO8;
					if(chunk1.bitsPerSample == 16)
						m_uiFormat = AL_FORMAT_MONO16;
				}
				if(chunk1.numChannels == 2)
				{
					if(chunk1.bitsPerSample == 8)
						m_uiFormat = AL_FORMAT_STEREO8;
					if(chunk1.bitsPerSample == 16)
						m_uiFormat = AL_FORMAT_STEREO16;
				}
	
				m_pBuffer	=	new	U8[m_uiSize];
				memcpy(m_pBuffer,&p[uiPos],m_uiSize);
	
				return	true;
			}
			BufferFactory::BufferFactory(){
				m_strTypeName	=	"Buffer";
			}
	
			IProduct* BufferFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /* = NULL */ ){
				if(strName.empty())
					return	NULL;
				Buffer*	pBuff	=	new	Buffer(strName);
				return	pBuff;
			}
		}
	} 
};