
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

		MCOMMON_EXPORT	void GetLocalIP( AString& strIP )
		{
				// 获得本机主机名
				char hostname[MAX_PATH] = {0};
				gethostname(hostname,MAX_PATH);                
				struct hostent FAR* lpHostEnt = gethostbyname(hostname);
				if(lpHostEnt == NULL)
				{
					strIP	=	"127.0.0.1";
				}

				// 取得IP地址列表中的第一个为返回的IP(因为一台主机可能会绑定多个IP)
				LPSTR lpAddr = lpHostEnt->h_addr_list[0];      

				// 将IP地址转化成字符串形式
				struct in_addr inAddr;
				memmove(&inAddr,lpAddr,4);
				strIP = std::string( inet_ntoa(inAddr) );
		}

	}
};