#include "AirInterfaceResourceSystem.h"

namespace	Air{
	namespace	Client{
		namespace	Resource{
			

			ISystem::ISystem(CAString&	strType):Common::ISystem(strType){
				m_uiMaxRecycle	=	100*1024*1024;
				m_uiRecycleSize	=	0;

				m_uiLoadIndex	=	0;
				m_uiUnloadLoadIndex	=	0;
			}

			Air::U1 ISystem::Initialization(){
				//Start();

				AddFactory(new	NoParamFactory<IStream>("Stream"));
				return	true;
			}

			Air::U1 ISystem::Release(){
				//停止线程
				Stop();

				//清理队列
// 				m_UnLoadCS.Enter();
// 
// 				m_uiRecycleSize	=	0;
// 				ProductList::iterator	i	=	m_lstUnLoad.begin();
// 				for(;i!=m_lstUnLoad.end();i++){
// 					(*i)->ReleaseRef();
// 				}
// 				m_lstUnLoad.clear();
// 				m_UnLoadCS.Enter();

				m_LoadCS.Enter();

				StreamList::iterator	i	=	m_lstLoad[0].begin();
				for(;i!=m_lstLoad[0].end();i++){
					(*i)->ReleaseRef();
				}
				i	=	m_lstLoad[1].begin();
				for(;i!=m_lstLoad[1].end();i++){
					(*i)->ReleaseRef();
				}

				m_lstLoad[0].clear();
				m_lstLoad[1].clear();
				m_LoadCS.Enter();

				//摧毁所有资源
				DestroyAllProduct();
				DestroyAllFactory();

				return	true;
			}

			Air::U1 ISystem::Start(){
				StartThread();
				return	true;
			}

			Air::U1 ISystem::Stop(){
				StopThreadWaitForExit();
				return	true;
			}

			void ISystem::FindWithPostfix( CAString& strPostfix,IFindFileListener* pListener ){

			}

			Air::U1 ISystem::AddPackage( CAString& strPackageName ){

				return	false;
			}

			bool ISystem::RepetitionRun(){
				IStream*	pFile	=	NULL;

				Sleep(100);

				U32	uiLoadIdx	=	m_uiLoadIndex&1;
				StreamList::iterator	i	=	m_lstLoad[uiLoadIdx].begin();
				if(i!=m_lstLoad[uiLoadIdx].end()){
					if((*i)->GetRefCount()	>	1)
						(*i)->ForceLoad();
					(*i)->ReleaseRef();
				}
				m_lstLoad->clear();
				//优先加载文件
				m_LoadCS.Enter();
				uiLoadIdx++;
				m_LoadCS.Leave();

// 				//如果加载空闲时 卸载文件
// 				if(pFile==NULL){
// 					IProduct*	pProduct	=	NULL;
// 					m_UnLoadCS.Enter();
// 					ProductList::iterator	itr	=	m_lstUnLoad.begin();
// 					if(itr!=m_lstUnLoad.end()){
// 						if(m_uiRecycleSize	>=	m_uiMaxRecycle){
// 							m_uiRecycleSize	-=	pFile->GetSize();
// 							pProduct	=	*itr;
// 							m_lstUnLoad.erase(itr);
// 						}
// 					}
// 					m_UnLoadCS.Leave();
// 					//销毁
// 					if(pProduct!=NULL)
// 						pProduct->ReleaseRef();
// 					return	true;
// 				}
// 
// 				//既没有加载任务 也没有卸载任务 则休息
// 				if(pFile==NULL){
// 					Sleep(10);
// 				}else{
// 					//一种可能性 一个文件进入后台加载队列	但是还没有到加载它的时候 用户手动强制进行了加载	这里就不会二次加载了
// 					if(pFile->GetState()	==	enSS_UnLoad){
// 						//强制加载
// 						pFile->ForceLoad();
// 					}
// 					//减少一个引用计数	
// 					pFile->ReleaseRef();
// 				}
				return	true;
			}

			Air::U1 ISystem::LoadBackground( IStream* pFile ){
				if(pFile==NULL)
					return	false;
				//先添加一个引用计数	防止正在加载的过程中 调用卸载
				pFile->AddRef();
				m_LoadCS.Enter();
				U32	uiLoadIndex	=	(m_uiLoadIndex+1)&1;
				m_lstLoad[uiLoadIndex].push_back(pFile);
				m_LoadCS.Leave();

				return	true;
			}

			Air::U1 ISystem::PushRecycle( IProduct* p ){
				if(p==NULL)
					return	false;
				m_UnLoadCS.Enter();
// 				m_uiRecycleSize	+=	p->GetSize();
// 				m_lstUnLoad.push_back(p);
				m_UnLoadCS.Leave();
				return	true;
			}

			Air::U32 ISystem::Find( CAString& strFileName,Data& outData ){
				return	0;
			}

			Air::U32 ISystem::Find( CAString& strFileName ){
				return	0;
			}

			void ISystem::SetMaxRecycleSize( U32 uiSize ){
				m_uiMaxRecycle	=	uiSize;
			}	

			Air::U32 ISystem::GetMaxRecycleSize(){
				return	m_uiMaxRecycle;
			}
		}
	}
}