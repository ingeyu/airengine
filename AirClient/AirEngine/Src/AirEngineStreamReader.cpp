#include "AirEngineStreamReader.h"
namespace	Air{
	namespace	Engine{
		


		ResourceReader::ResourceReader(  Resource::IStream& stream ):m_Stream(stream){
			m_Stream.AddRef();
			if(m_Stream.GetState()	==	Resource::enSS_Loaded){
				m_pBegin	=	(U8*)m_Stream.GetData();
				m_pEnd		=	m_pBegin	+	m_Stream.GetSize();
				m_pCurrent	=	m_pBegin;
			}else{
				m_pBegin	=	NULL;
				m_pEnd		=	NULL;
				m_pCurrent	=	NULL;
			}
		}

		ResourceReader::~ResourceReader(){
			m_Stream.ReleaseRef();
		}

		Air::U1 ResourceReader::IsStreamValid(){
			return	m_Stream.GetState()	==	Resource::enSS_Loaded;
		}

		Air::U1 ResourceReader::ReInit(){
			if(m_Stream.GetState()	==	Resource::enSS_Loaded){
				m_pBegin	=	(U8*)m_Stream.GetData();
				m_pEnd		=	m_pBegin	+	m_Stream.GetSize();
				m_pCurrent	=	m_pBegin;
				return	true;
			}
			return	false;
		}

	}
}