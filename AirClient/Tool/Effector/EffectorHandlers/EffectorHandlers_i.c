

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue May 01 17:14:16 2012
 */
/* Compiler settings for EffectorHandlers.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IPreview,0x3765BC50,0x337B,0x423B,0xBA,0x2B,0x2A,0x66,0x8F,0x4C,0xAF,0xE3);


MIDL_DEFINE_GUID(IID, IID_IThumbnail,0x4F3D6A47,0xFF5B,0x4D3F,0xA7,0x1F,0x36,0x27,0x50,0x1D,0x5E,0xED);


MIDL_DEFINE_GUID(IID, IID_ISearch,0x0A3CDAA9,0xDFBD,0x4B7C,0x9F,0x17,0x7D,0xC7,0xF7,0x86,0x95,0xB9);


MIDL_DEFINE_GUID(IID, LIBID_EffectorHandlersLib,0x98883DA0,0x9A34,0x4F2A,0xB5,0x89,0x23,0x54,0x63,0xCE,0x67,0x9C);


MIDL_DEFINE_GUID(CLSID, CLSID_Preview,0x9F3B589C,0x7D49,0x4802,0x8A,0xCF,0x24,0x33,0x25,0xAC,0xA4,0xE9);


MIDL_DEFINE_GUID(CLSID, CLSID_Thumbnail,0xF36D5D67,0x40D0,0x4317,0xA7,0x61,0xB6,0x5C,0x9A,0x8D,0x6A,0x4E);


MIDL_DEFINE_GUID(CLSID, CLSID_Search,0x8D34136D,0x3717,0x48CC,0xBB,0x34,0xAD,0x76,0x59,0x31,0xB6,0x4F);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



