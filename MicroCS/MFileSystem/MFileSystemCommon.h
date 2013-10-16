#ifndef MFileSystemCommon_h__
#define MFileSystemCommon_h__

#ifndef MFILESYSTEM_EXPORT
#ifdef MFILESYSTEM_IMPORT
#define MFILESYSTEM_EXPORT __declspec(dllexport)
#else
#define MFILESYSTEM_EXPORT __declspec(dllimport)
#endif
#endif


#include "MCommon.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
#include "AirFileMapping.h"
#include "AirCommonNetClient.h"
#include "AirCommonNetServer.h"

#include "MNetData.h"


#endif // MFileSystemCommon_h__
