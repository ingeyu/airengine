
#include "WinSock2.h"
#include "AirCommonNet.h"


//加入win32库
#pragma comment(lib,"wsock32")
namespace Air{
	
	namespace	Common{
		enum	enumNetState{
			enUnKnown,
			enUnInit,
			enInit,
			enMax
		};
	
		static	enumNetState	g_NetState	=	enUnInit;
		
		U1 InitNet(){
			if(g_NetState	==	enUnInit){
				g_NetState	=	enInit;
	
				//Common::Logger("Net","Info","初始化网络");
	
				//初始化与绑定服务器
				WSADATA wsaData;
				if (WSAStartup(MAKEWORD(2,2),&wsaData)){ 
					//Common::Logger("Net","Error","Winsock无法初始化");
					WSACleanup();
					return	false;
				}
			}
			return	true;
		}
	
		U1 ReleaseNet(){
			if(g_NetState	==	enInit){
				g_NetState	=	enUnInit;
	
				//Common::Logger("Net","Info","释放网络");
	
				WSACleanup();
			}
	
			return	true;
		}
	
		AString IP2String( U32 ip ){
			AChar	strTemp[128];
			sprintf_s(strTemp,"%d.%d.%d.%d",ip&0x000000FF,(ip&0x0000FF00)>>8,(ip&0x00FF0000)>>16,ip>>24);
			return	strTemp;
		} 
	
		U32 String2IP( AString strIP ){
			U32	i0=0,i1=0,i2=0,i3=0;
			sscanf_s(strIP.c_str(),"%d.%d.%d.%d",&i0,&i1,&i2,&i3);
			return	i0<<24 | i1<<16 | i2<<8 | i3;
		}
	}
};