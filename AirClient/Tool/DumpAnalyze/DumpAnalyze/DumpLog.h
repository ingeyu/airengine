#ifndef DumpLog_h__
#define DumpLog_h__

class DumpLog{
public:
	DumpLog();
	~DumpLog();
	void	Write(const char* str);
	//HANDLE	m_hFile;
	char	strFileName[256];
};
DumpLog& GetLog();
#endif // DumpLog_h__
