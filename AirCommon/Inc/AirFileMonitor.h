#ifndef AirFileMonitor_h__
#define AirFileMonitor_h__

#include "AirCommonThread.h"
#include "AirCommonLock.h"


namespace	Air{

	class COMMON_EXPORT	FileMonitor{
	public:

		FileMonitor();
		FileMonitor(const std::string&	strName);
		virtual	~FileMonitor();
		void	Open(const std::string&	strName);
		bool	IsChanged();

		HANDLE		m_hHandle;
		FILETIME	m_LastModifyTime;
	};

	class COMMON_EXPORT	FileMonitorManager	:	
		public	Air::Common::Thread
	{
	public:
		FileMonitorManager();
		virtual	~FileMonitorManager();
		virtual bool RepetitionRun();
		void	AddFile(const std::string&	strName);
		void	RemoveFile(const std::string&	strName);

		std::map<std::string,FileMonitor>	m_mapFileInfo;
		std::set<std::string>				m_mapAddFileInfo;
		std::set<std::string>				m_mapRemoveFileInfo;
		Common::CriticalSection				m_AddCS;
		Common::CriticalSection				m_RemoveCS;
	};
}
#endif // AirFileMonitor_h__