#include "AirCommonStringHandle.h"
#include "AirCommonLock.h"
namespace	Air{
	namespace	Common{
		AChar					g_GlobalChar	=	0x0;
	
		StringHandle::StringHandle( const AString& str ){
			m_pValue	=	StringHashTable::GetSingleton()->Hash(str);

		}

		StringHandle::StringHandle( const AChar* str ){
			m_pValue	=	StringHashTable::GetSingleton()->Hash(str);
		}

		StringHandle::StringHandle( const StringHandle& handle ){
			m_pValue	=	handle.m_pValue;
		}

		StringHandle::StringHandle( const AString* pStr ){
			m_pValue	=	(AString*)pStr;
		}

		StringHandle::StringHandle(){

		}

		StringHandle& StringHandle::operator=( const AChar* str ){
			m_pValue	=	StringHashTable::GetSingleton()->Hash(str);
			return	*this;
		}

		StringHandle& StringHandle::operator=( const AString& str ){
			m_pValue	=	StringHashTable::GetSingleton()->Hash(str);
			return	*this;
		}

		StringHandle& StringHandle::operator=( const StringHandle& handle ){
			m_pValue	=	handle.m_pValue;
			return	*this;
		}

		StringHandle& StringHandle::operator=( const AString* pStr ){
			m_pValue	=	(AString*)pStr;
			return	*this;
		}
		bool StringHandle::operator==( const StringHandle& handle ){
			return	m_pValue	==	handle.m_pValue;
		}

		bool StringHandle::operator!=( const StringHandle& handle ){
			return	m_pValue	!=	handle.m_pValue;
		}

		bool StringHandle::operator>( const StringHandle& handle ){
			return	m_pValue	>	handle.m_pValue;
		}

		bool StringHandle::operator<( const StringHandle& handle ){
			return	m_pValue	<	handle.m_pValue;
		}

		bool StringHandle::operator<=( const StringHandle& handle ){
			return	m_pValue	<=	handle.m_pValue;
		}

		bool StringHandle::operator>=( const StringHandle& handle ){
			return	m_pValue	>=	handle.m_pValue;
		}

		const AChar* StringHandle::c_str()const {
			if(m_pValue!=NULL){
				return	m_pValue->c_str();
			}else{
				return	NULL;
			}
		}

		AChar& StringHandle::operator[]( const U32 index ){
			if(m_pValue==NULL)
				return	g_GlobalChar;
			else	if(m_pValue->empty()){
				return	g_GlobalChar;
			}else{
				return	(*m_pValue)[index];
			}
		}

		AString* StringHashTable::HashString( const AString& str ){
			AString* p = NULL;
			m_CS.Enter();
			p	=	Hash(str);
			m_CS.Leave();
			return	p;
		}

		AString* StringHashTable::HashString( const AChar* str ){
			if(str==NULL)
				return	NULL;
			AString* p = NULL;
			m_CS.Enter();
			p	=	Hash(AString(str));
			m_CS.Leave();
			return	p;
		}
	}
}