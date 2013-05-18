#include "AirCommonIniFile.h"


namespace Air{
	
	
	namespace Common{
	
		IniFile::IniFile(){
		
		}
		IniFile::~IniFile(){
		
		}
		bool IniFile::LoadFile(CAString& strFileName){
			FILE* file = NULL;
			fopen_s(&file,strFileName.c_str(),"rb");
			if(file==NULL)
				return false;
	
			m_strFileName	= strFileName;
			//fsetpos
			fseek(file,0,SEEK_END);
			int size = ftell(file);
			fseek(file,0,SEEK_SET);
			char* str = new char[size+1];
			str[size]='\0';
			fread(str,size,1,file);
	#ifdef _DEBUG
			m_strFileContent = str;
	#endif
			fclose(file);
			if(!Parse(str,size))
				return false;
			delete[] str;
			return true;
	
		}
		bool IniFile::NewFile(AString strFileName){
			FILE* file = NULL;
			fopen_s(&file,strFileName.c_str(),"w+");
			if(file==NULL)
				return false;
			m_strFileName	= strFileName;
			WRITE_LINE("#New Config File!",file);
			fclose(file);
	
			return true;
		}
		bool IniFile::Replace(AString strFileContent){
			m_lstSort.clear();
	#ifdef _DEBUG
			m_strFileContent = strFileContent;
	#endif
			if(!Parse((S8*)strFileContent.c_str(),strFileContent.size()))
				return false;
			return true;
		}
		bool IniFile::AddLine(AString strStringLine){
			FILE* file = NULL;
			fopen_s(&file,m_strFileName.c_str(),"a+");
			R_FALSE(file!=NULL);
	
			fseek(file,0,SEEK_END);
			//AString str = strStringLine + "\n";
			WRITE_LINE(strStringLine,file);
	
			fclose(file);
			return true;
		}
		bool IniFile::Set(const char* strSortName,const char* strName,const char* strValue,int iIndex){
			SortList::iterator itr = m_lstSort.find(strSortName);
			if(itr!=m_lstSort.end()){
				SortMap& map = itr->second;
				SortMap::iterator i = map.find(strName);
				if(i!=map.end()){
					StringVector& lst = i->second;
					lst[iIndex] = AString(strValue);
				}else{
					StringVector lst;
					lst.push_back(AString(strValue));
					map.insert(SortMap::value_type(strName,lst));
				}
			}else{
				SortMap map;
				StringVector lst;
				lst.push_back(AString(strValue));
				map.insert(SortMap::value_type(strName,lst));
				m_lstSort.insert(SortList::value_type(strSortName,map));
			}
			return true;
		}
		bool IniFile::Save(AString strFileName){
			if(!strFileName.empty())
				m_strFileName = strFileName;
	
			FILE* file = NULL;
			fopen_s(&file,m_strFileName.c_str(),"w+");
			R_FALSE(file!=NULL);
	
			SortList::iterator itr = m_lstSort.begin();
			for(;itr!=m_lstSort.end();itr++){
				SortMap& pMap = itr->second;
				WRITE_LINE(itr->first + "\n",file);
				SortMap::iterator i  = pMap.begin();
				for(;i!=pMap.end();i++){
					AString strName = i->first;
					StringVector& lst = i->second;
					int size = lst.size();
					for(int j=0;j<size;j++){
	
						AString str = strName + "=" + lst[j] + "\n";
						WRITE_LINE(str,file);
					}
				}
			}
			fclose(file);		
			return true;
		}
		bool IniFile::Parse(S8*	strContent,UInt uiSize){
			unsigned int size = uiSize;//strContent.size();
			int iStart = 0,iEnd = 0;
	
			for(unsigned int i=0;i<=size;i++,iEnd++){
				char s = strContent[iEnd];
				if(iEnd == size || strContent[iEnd] == 0x0A){
					int iCopyCount = iEnd - iStart - 1;
					if(strContent[iEnd-1]!=0x0D)
						iCopyCount++;
					if(iCopyCount<=0){
						iStart = iEnd + 1;
						continue;				
					}
					
	
					char* tempStr = new char[iCopyCount+1];
	
					char testbuff[128];
					ZeroMemory(testbuff,128);
					//::OutputDebugStringA(itoa(iEnd,testbuff,128));
					memset(tempStr,0,iCopyCount+1);
					memcpy(tempStr,&strContent[iStart],iCopyCount);
					ParseLine(tempStr);
					iStart = iEnd + 1;
					delete tempStr;
				}
			}
	
			return true;
		}
		bool IniFile::ParseLine(CAString& strLine){
			
			if(strLine.empty())
				return false;
			char type= strLine[0];
			if(type == '['){
				strCurrSort = ParseSort(strLine);
			}else if(type == '#'){
				return false;
			}else{
				AString strName;
				AString strValue;
				if(!ParseNameAndValue(strLine,strName,strValue))
					return false;
				SortMap& tempMap = m_lstSort.find(strCurrSort)->second;
				SortMap::iterator itr = tempMap.find(strName.c_str());
				if(itr!=tempMap.end()){
					itr->second.push_back(strValue);
				}else{
					StringVector vecString;
					vecString.push_back(strValue);
					tempMap.insert(SortMap::value_type(strName.c_str(),vecString));
				}
	
			}
			return true;
		}
		AString IniFile::ParseSort(CAString& strSort){
			unsigned int size = strSort.size();
	
			char* str = new char[size - 1];
			str[size -2] = '\0';
			memcpy(str,&strSort[1],size - 2);
	
			std::map<AString,SortMap>::iterator itr = m_lstSort.find(str);
			if(itr==m_lstSort.end()){
				SortMap sortMap;
				m_lstSort.insert(std::map<AString,SortMap>::value_type(str,sortMap));
			}
			AString strReturn(str);
			delete str;
			return strReturn;
		}
		bool IniFile::ParseNameAndValue(AString strSource,AString &strName,AString &strValue){
			unsigned int size = strSource.size();
			int iEqual = 0;
			for(unsigned int i=0;i<size;i++){
				if(strSource[i] == '='){
					iEqual = i;
					strSource[i] = '\0';
					strName.resize(i);
					char strArray[256];
					memset(strArray,0,256);
					memcpy(strArray,strSource.c_str(),i);
					strName	=	strArray;
					strValue = AString(&strSource[i+1]);
					strSource[i] = '=';
					strSource.clear();
					return true;
				}
			}
			return false;
		}
		AString IniFile::Get(const char* strSort,const char* strName,UInt iIndex){
			SortMap* tempMap = GetSort(strSort);
			StringVector* lst = GetStringList(strName,tempMap);
			if(lst == NULL)
				return "";
			StringVector& l = *lst;
			if(iIndex >= l.size() || iIndex < 0)
				return "";
			return l[iIndex];
		}
		int IniFile::GetCount(const char* strSort,const char* strName){
			SortMap* tempMap = GetSort(strSort);
			StringVector* lst = GetStringList(strName,tempMap);
			if(lst == NULL)
				return 0;
			StringVector& l = *lst;
			return l.size();
		}
		SortMap* IniFile::GetSort(const char* strSort){
			SortList::iterator i = m_lstSort.find(strSort);
			if(i == m_lstSort.end()){
				return NULL;
			}
			return &i->second;
		}
		StringVector* IniFile::GetStringList(const char* strName,SortMap* pMap){
			if(pMap==NULL)
				return NULL;
			SortMap::iterator i = pMap->find(strName);
			if(i == pMap->end())
				return NULL;
			return &i->second;
		}

		StringVector* IniFile::GetStringList( const char* strName,const char* strSort ){
			SortList::iterator i = m_lstSort.find(strSort);
			if(i == m_lstSort.end()){
				return NULL;
			}

			SortMap::iterator itr = i->second.find(strName);
			if(itr == i->second.end())
				return NULL;
			return &itr->second;;
		}

		U1 IniFile::LoadFileFromMemory( U8*	pData,U32	uiSize ){
			if(pData==NULL)
				return	false;
			m_strFileName	=	"MemoryFile";
			return	Parse((S8*)pData,uiSize);
		}
	
		U1 IniFile::LoadFileFromString( CAString& str ){
			if(str.empty())
				return	false;
			m_strFileName	=	"MemoryFile";
			return	Parse((S8*)str.c_str(),str.size());
		}
	};
};