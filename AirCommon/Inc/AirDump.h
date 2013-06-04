#ifndef AirDump_h__
#define AirDump_h__

#include "AirCommon.h"
namespace	Air{
	enum enumDumpLevel{
		enDL_Tiny,
		enDL_Mini,
		enDL_Normal,
		enDL_Full
	};

	COMMON_EXPORT	void	Dump_Init(enumDumpLevel level	=	enDL_Normal);
	COMMON_EXPORT	void	GenDump(enumDumpLevel level	=	enDL_Normal);
}
#endif // AirDump_h__
