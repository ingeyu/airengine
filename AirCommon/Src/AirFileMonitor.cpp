#include "AirFileMonitor.h"
namespace	Air{
	FileMonitor::FileMonitor(){
		m_hHandle	=	NULL;
	};
	FileMonitor::FileMonitor(const std::string&	strName){
		Open(strName);
	}
	FileMonitor::~FileMonitor(){

		CloseHandle(m_hHandle);
	}
	void	FileMonitor::Open(const std::string& strName){
		if(m_hHandle!=NULL){
			CloseHandle(m_hHandle);
			m_hHandle=NULL;
		}
		{
			m_hHandle	=	(HANDLE)CreateFileA((CHAR*)strName.c_str(), (GENERIC_READ ),FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,0,OPEN_EXISTING,FILE_ATTRIBUTE_READONLY,0);
			if((int)m_hHandle	==	-1){
				OFSTRUCT	of;
				memset(&of,0,sizeof(of));
				m_hHandle	=	(HANDLE)CreateFileA((CHAR*)strName.c_str(), (GENERIC_READ ),FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,0,OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS,0);
			}
			GetFileTime(m_hHandle,0,0,&m_LastModifyTime);
		}
	}

	bool	FileMonitor::IsChanged(){
		FILETIME	t;
		GetFileTime(m_hHandle,0,0,&t);

		if(CompareFileTime(&m_LastModifyTime,&t)!=0){
			m_LastModifyTime	=	t;
			return	true;
		}
		return	false;
	}

	FileMonitorManager::FileMonitorManager(){



	};

	FileMonitorManager::~FileMonitorManager(){
		m_RemoveCS.Enter();
		m_mapRemoveFileInfo.clear();
		m_RemoveCS.Leave();
		m_AddCS.Enter();
		m_mapAddFileInfo.clear();
		m_AddCS.Leave();
		m_mapFileInfo.clear();

	};
	bool FileMonitorManager::RepetitionRun(){
		Sleep(1000);

		m_AddCS.Enter();

		std::set<std::string>::iterator	isrc	=	m_mapAddFileInfo.begin();
		for(;isrc!=m_mapAddFileInfo.end();isrc++){
			std::map<std::string,FileMonitor>::iterator	i	=	m_mapFileInfo.find(*isrc);
			if(i==m_mapFileInfo.end()){
				m_mapFileInfo[*isrc].Open(*isrc);
			}
		}
		m_mapAddFileInfo.clear();

		m_AddCS.Leave();

		m_RemoveCS.Enter();
		isrc	=	m_mapRemoveFileInfo.begin();
		for(;isrc!=m_mapRemoveFileInfo.end();isrc++){
			std::map<std::string,FileMonitor>::iterator	i	=	m_mapFileInfo.find(*isrc);
			if(i!=m_mapFileInfo.end()){
				m_mapFileInfo.erase(i);
			}
		}
		m_mapRemoveFileInfo.clear();
		m_RemoveCS.Leave();

		std::map<std::string,FileMonitor>::iterator	i	=	m_mapFileInfo.begin();
		for(;i!=m_mapFileInfo.end();i++){
			if(i->second.IsChanged()){
				printf("%s Changed!\n",i->first.c_str());
			};
		}

		return	true;

	};
	void	FileMonitorManager::AddFile(const std::string&	strName){
		m_AddCS.Enter();
		m_mapAddFileInfo.insert(strName);
		m_AddCS.Leave();
	};
	void	FileMonitorManager::RemoveFile(const std::string&	strName){
		m_RemoveCS.Enter();
		m_mapRemoveFileInfo.erase(m_mapRemoveFileInfo.find(strName));
		m_RemoveCS.Leave();
	}
}