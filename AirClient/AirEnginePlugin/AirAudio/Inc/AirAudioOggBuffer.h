// #ifndef AUDIOOGGBUFFER_HEAD_FILE
// #define AUDIOOGGBUFFER_HEAD_FILE
// 
// #include "AirAudioBuffer.h"
// #include "ogg\ogg.h"
// #include "vorbis\vorbisfile.h"
// 
// namespace Client{
// 
// 	namespace	Audio{
// 		class	OggBuffer	:
// 			public	Buffer{
// 		public:
// 			OggBuffer(AString&	strName);
// 
// 			virtual	U1	Create();
// 
// 			virtual	U1	Destroy();
// 
// 			U1			ComputeFormat(long	freq,int channel,int bps);
// 
// 			U1			LoadBuffer();
// 
// 			OggVorbis_File		m_OggFile;
// 			vorbis_info*		m_pVorbisInfo;
// 		};
// 
// 		class	OggBufferFactory	:
// 			public	IFactory{
// 		public:	
// 			OggBufferFactory();
// 
// 			virtual	IProduct*	Create(AString strName,IFactoryParamList* lstParam /* = NULL */);
// 
// 		};
// 	}
// 
// };
// #endif // AUDIOOGGBUFFER_HEAD_FILE