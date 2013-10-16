#include "WinSock2.h"
#include "AirCommonNetSendThread.h"
//#include "AirRandom.h"
namespace Air{
	
	
	
	namespace	Common{
	
	
		NetSendThread::NetSendThread(){
			m_pListener	=	NULL;
			m_bWaiting	=	false;
		}
	
		NetSendThread::~NetSendThread(){
	
		}
	
		U1 NetSendThread::Push( NetPack* pack ){
			//判断数据包的有效性
			if(	pack==NULL	||
				!pack->IsValid()){
				return	false;
			}
	
			//存入列表
			m_CS.Enter();
			//这里是查询别人的帖子 得到的结果 需要定义对齐方式	留下记号 infernalhell 20110229
			//如果NetPack不定义对齐这里会崩溃 原因还没有查明
			m_lstSendPack.push(pack);
			m_CS.Leave();
	
			if(m_bWaiting){
				m_SendEvent.Reset();
			}
			return	true;
		}
	
		U1 NetSendThread::RepetitionRun(){
			NetPack*	p	=	NULL;
	
			m_CS.Enter();
			if(!m_lstSendPack.empty()){
				p	=	m_lstSendPack.front();
				m_lstSendPack.pop();
			}
	
			m_CS.Leave();
	
			if(p==NULL){
				m_bWaiting	=	true;
				//等待1000ms
				m_SendEvent.Wait(1000);
				m_bWaiting	=	false;
			}else{
				if(p->IsValid()){
					int	iRet	=	send(p->uiSocket,p->pData,p->uiSize,0);
					if(iRet	<=	0){
						//发送失败
						if(m_pListener!=NULL)
							m_pListener->OnClose(p->uiSocket);
					}else{
						OutputDebugStringA("发送成功\n");
					}
				}
				//删除数据
				delete	p;
			}
						
	
			return	true;
		}
	
		U1 NetSendThread::Start(NetListener*	pListener){
			m_pListener	=	pListener;
			if(!IsRunning())
				StartThread();
			return	true;
		}
	}
};