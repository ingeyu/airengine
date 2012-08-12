#include "AirCommonStreamIO.h"
#include <fstream>

namespace	Air{
	namespace	Common{
		StreamIO::StreamIO(){
			m_pBegin		=	NULL;
			m_pEnd			=	NULL;
			m_pCurrent		=	NULL;
		}
		StreamIO::~StreamIO(){
			m_pBegin		=	NULL;
			m_pEnd			=	NULL;
			m_pCurrent		=	NULL;
		}
		void StreamIO::Seek( S32 iOffset ){
			m_pCurrent	+=	iOffset;
		}

		Air::U32 StreamIO::Size(){
			return	m_pEnd	-	m_pBegin;
		}

		void StreamIO::SeekBegin(){
			m_pCurrent	=	m_pBegin;
		}

		void StreamIO::SeekEnd(){
			m_pCurrent	=	m_pEnd;
		}

		Air::U1 StreamIO::IsVaild(){
			return	(m_pBegin!=NULL&&m_pEnd!=m_pBegin);
		}
		Air::U1 StreamReader::ReadData( Data&	data ){
			U32	uiSize	=	Read<U32>();

			if(uiSize	>	0){
				data.ReSize(uiSize);
				memcpy(data.GetBuff(),m_pCurrent,uiSize);
				m_pCurrent+=uiSize;
			}
			return	true;
		}

		Air::U1 StreamReader::ReadString( AString& str ){
			U32	uiSize	=	Read<U32>();

			if(uiSize	>	0){
				str.resize(uiSize);
				memcpy(&str[0],m_pCurrent,uiSize);
				m_pCurrent+=uiSize;
			}
			return	true;
		}

		Air::U1 StreamReader::ReadBufferNoSize( void* p,U32 uiSize ){
			if(p==NULL||uiSize==0)
				return	false;
			memcpy(p,m_pCurrent,uiSize);
			m_pCurrent+=uiSize;
			return	true;
		}

		Air::U1 StreamReader::ReadDataNoSize( Data& data ){
			if(data.size	==	0)
				return	false;
			memcpy(data.GetBuff(),m_pCurrent,data.size);
			m_pCurrent+=data.size;
			return	true;
		}	

		StreamReader::StreamReader(){

		}

		StreamReader::StreamReader( const void* pData,U32 uiSize ){
			m_pBegin	=	(U8*)pData;
			m_pEnd		=	m_pBegin	+	uiSize;
			m_pCurrent	=	m_pBegin;
		}
		void StreamWriter::WriteBuffer( const void* val,U32 uiSize ){
			if(val==NULL	&&	uiSize!=0)
				return;
			Write(uiSize);
			if(uiSize>0){
				memcpy(m_pCurrent,val,uiSize);
				m_pCurrent	+=	uiSize;
			}
		}

		void StreamWriter::WriteString( const AString& str ){
			U32	uiSize	=	str.size();
			Write(uiSize);
			if(uiSize	>	0){
				memcpy(m_pCurrent,&str[0],uiSize);
				m_pCurrent+=uiSize;
			}
		}

		void StreamWriter::WriteData( Data& data ){
			U32	uiSize	=	data.size;
			Write(uiSize);
			if(uiSize	>	0){
				memcpy(m_pCurrent,data.buff,uiSize);
				m_pCurrent+=uiSize;
			}
		}

		void StreamWriter::WriteBufferNoSize( const void* val,U32 uiSize ){
			if(val==NULL	||	uiSize==0)
				return;
			if(uiSize>0){
				memcpy(m_pCurrent,val,uiSize);
				m_pCurrent	+=	uiSize;
			}
		}

		void StreamWriter::WriteDataNoSize( Data& data ){
			U32	uiSize	=	data.size;
			if(uiSize	>	0){
				memcpy(m_pCurrent,data.buff,uiSize);
				m_pCurrent+=uiSize;
			}
		}

		FileReader::FileReader( CAString& strName ){
			if(!strName.empty()){
				std::ifstream	i;
				//共享读取 二进制
				i.open(strName.c_str(),_IOSbinary,_SH_DENYRD);
				i.seekg(std::ios::end);
				U32	uiSize	=	i.tellg();
				i.seekg(std::ios::beg);
				if(uiSize>0){
					m_pBegin	=	new	U8[uiSize];
					m_pCurrent	=	m_pBegin;
					m_pEnd		=	m_pBegin+uiSize;

					i.read((char*)m_pBegin,uiSize);
					i.close();
				}
			}
		}

		FileReader::~FileReader(){
			SAFE_DELETE_ARRAY(m_pBegin);
			m_pCurrent	=	NULL;
			m_pEnd		=	NULL;
		}

		MemoryWriter::MemoryWriter( U32 uiSize )
		{
			if(uiSize!=0){
				m_pBegin	=	new U8[uiSize];
				m_pCurrent	=	m_pBegin;
				m_pEnd		=	m_pBegin+uiSize;
			}
		}

		MemoryWriter::~MemoryWriter()
		{
			SAFE_DELETE_ARRAY(m_pBegin);
			m_pEnd		=	NULL;
			m_pCurrent	=	NULL;
		}

		const	void* MemoryWriter::GetDataPtr()
		{
			return	m_pBegin;
		}

		Air::U32 MemoryWriter::GetDataSize()
		{
			return	m_pEnd	-	m_pBegin;
		}

	}
}