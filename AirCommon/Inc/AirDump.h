#ifndef AirDump_h__
#define AirDump_h__

#include "AirCommon.h"
#include <Guiddef.h>
namespace	Air{
	enum enumDumpLevel{
		enDL_Tiny,
		enDL_Mini,
		enDL_Normal,
		enDL_Full
	};

	COMMON_EXPORT	void	Dump_Init(enumDumpLevel level);
	COMMON_EXPORT	void	GenDump(enumDumpLevel level);

	struct Module{
		unsigned __int64	ModuleBase;
		unsigned	int		ModuleSize;
		unsigned	int	TimeStamp;
		GUID		Guid;
		unsigned	int	Age;
		char		ModuleName[260];
		char		ModulePDBName[260];
	};

	

	class	StackWalker{
	public:
		StackWalker();
		void	AddModule(const char* ModuleName,unsigned long long ModuleBase,unsigned long ModuleSize);
		void	CallStack(void* pContext);
	protected:
		Module			m_vecModule[200];
		unsigned int	m_uiModuleCount;
	};
}
#endif // AirDump_h__
