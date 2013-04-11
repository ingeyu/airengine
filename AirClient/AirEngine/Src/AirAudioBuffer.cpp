#include "AirAudioBuffer.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceResourceSystem.h"


namespace	WAV{

	struct RIFFHeader{
		char riff[4];
		long size;
		char wave[4];

		void Print()
		{
			printf("RIFFHeader::Print()\n");
			printf("riff: %c%c%c%c\n", riff[0], riff[1], riff[2], riff[3]);
			printf("size: %i\n", size);
			printf("wave: %c%c%c%c\n", wave[0], wave[1], wave[2], wave[3]);
			printf("\n");
		}
	};


	struct SubChunk1
	{
		char subChunkId[4];
		long subChunkSize;
		short format;
		short numChannels;
		long sampleRate;
		long byteRate;
		short blockAlign;
		short bitsPerSample;

		void Print()
		{
			printf("WAVSubChunk1::Print()\n");
			printf("subChunkId: %c%c%c%c\n", subChunkId[0], subChunkId[1], subChunkId[2], subChunkId[3]);
			printf("subChunkSize: %i\n", subChunkSize);
			printf("format: %i\n", format);
			printf("numChannels: %i\n", numChannels);
			printf("sampleRate: %i\n", sampleRate);
			printf("byteRate: %i\n", byteRate);
			printf("blockAlgin: %i\n", blockAlign);
			printf("bitsPerSample: %i\n", bitsPerSample);
			printf("\n");
		}
	};


	struct SubChunk2
	{
		char subChunkId[4];
		long subChunkSize;

		void Print()
		{
			printf("WAVSubChunk2::Print()\n");
			printf("subChunkId: %c%c%c%c\n", subChunkId[0], subChunkId[1], subChunkId[2], subChunkId[3]);
			printf("subChunkSize: %i\n", subChunkSize);
			printf("\n");
		}
	};
}

namespace Air{
	
	namespace	Engine{
		namespace	Audio{
			
			AString	Buffer::ProductTypeName="Buffer";
			Buffer::Buffer( CAString& strName ):IProduct(strName){
				m_pBuffer		=	NULL;
				m_uiSize		=	0;
				m_uiFormat		=	enF_MONO8;
				m_uiFreqBuffer	=	0;
			}
	
			U1 Buffer::Create(){

				S8	Loop	=	0;
	
	 			Data	data;
				GetGlobalSetting().m_pResourceSystem->Find(m_strProductName,data);
				if(data.IsNull())
					return	false;
	
				if(!LoadWAVFromMemory(&data))
					return	false;

				if(m_pBuffer==NULL)
					return false;

				m_pObject	=	(UInt*)m_pBuffer;
				return true;
			}
	
			U1 Buffer::Destroy(){
				if(m_pBuffer!=NULL){
					delete[]		m_pBuffer;
					m_pBuffer		=	NULL;
					m_uiSize		=	0;
					m_uiFormat		=	(enumFormat)0;
					m_uiFreqBuffer	=	0;
				}
				m_pObject	=	NULL;
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
						m_uiFormat = enF_MONO8;
					if(chunk1.bitsPerSample == 16)
						m_uiFormat = enF_MONO16;
				}
				if(chunk1.numChannels == 2)
				{
					if(chunk1.bitsPerSample == 8)
						m_uiFormat = enF_STEREO8;
					if(chunk1.bitsPerSample == 16)
						m_uiFormat = enF_STEREO16;
				}
	
				m_pBuffer	=	new	U8[m_uiSize];
				memcpy(m_pBuffer,&p[uiPos],m_uiSize);
	
				return	true;
			}
		}
	} 
};