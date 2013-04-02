#ifndef AUDIOHEADER_HEAD_FILE
#define AUDIOHEADER_HEAD_FILE

#include "AirAudio.h"
#include "AirEngineHeader.h"
#include "AirInterfaceAudioSystem.h"
#include "AirGlobalSetting.h"
#include "AirEngineSceneNode.h"
#include "AirEngineCamera.h"
#include "AirEngineSystem.h"

#include "al.h"
#include "alc.h"

namespace Air{
	
	namespace Engine{
	
		namespace	Audio{
	
	#define AContext		ALCcontext
	#define ADevice			ALCdevice
	
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
	
		}
	
	};
};
#endif // AUDIOHEADER_HEAD_FILE