#ifndef COMMONLOCK_HEAD_FILE
#define COMMONLOCK_HEAD_FILE

#include "MCommon.h"
namespace Air{
	
	namespace Common{
		/**	\brief	临界区对象
		*
		*	临界区对象
		*
		***/
		class	CriticalSection{
		public:
			inline	CriticalSection(){
				InitializeCriticalSection(&m_CriticalSection);
			};
	
			~CriticalSection(){
				DeleteCriticalSection(&m_CriticalSection);
			};
	
			inline	U32		TryEnter(){
				return TryEnterCriticalSection(&m_CriticalSection); 
			};
			inline	void	Enter(){
				EnterCriticalSection(&m_CriticalSection); 
			};
			inline	void	Leave(){
				LeaveCriticalSection(&m_CriticalSection); 
			};
	
			CRITICAL_SECTION	m_CriticalSection;//临界区引用计数
		};
	
		/**	\brief	互斥对象
		*
		*	互斥对象
		*
		***/
		class	Mutex{
		public:
			Mutex(AString	strName	=	""){
				m_hMutex	=	CreateMutexA(NULL,FALSE,strName.c_str());
			};
			~Mutex(){
				CloseHandle(m_hMutex);
			}
	
			/**	\brief	等待互斥对象
			*   
			*	@remarks 	等待互斥对象
			*	@see		Mutex
			*	@return   	void
			*	@param		U32 uiTime
			*	@note
			*
			**/
			inline	void	Enter(U32	uiTime	=	INFINITE){
				WaitForSingleObject(m_hMutex,uiTime);
			};
	
			/**	\brief	释放互斥对象
			*   
			*	@remarks 	释放互斥对象
			*	@see		Mutex
			*	@return   	void
			*	@note
			*
			**/
			inline	void	Leave(){
				ReleaseMutex(m_hMutex);
	
			};
	
			HANDLE	m_hMutex;	///<	互斥对象句柄
		};
		
		/**	\brief	事件
		*
		*	事件
		*
		***/
		class	Event{
		public:
			Event(const AChar*	strName=NULL){
				if(strName==NULL){
					m_hEvent	=	CreateEventA(NULL,FALSE,FALSE,"");
				}else{
					m_hEvent	=	CreateEventA(NULL,FALSE,FALSE,strName);
				}
				
			};
			~Event(){
				CloseHandle(m_hEvent);
			}

			/**	\brief	设置事件
			*   
			*	@remarks 	设置事件
			*	@see		Event
			*	@return   	void
			*	@note
			*
			**/
			void	Reset(){
				SetEvent(m_hEvent);
			}
			/**	\brief	等待事件
			*   
			*	@remarks 	等待事件
			*	@see		Event
			*	@return   	void
			*	@param		U32		uiTime
			*	@note
			*
			**/
			void	Wait(U32	uiTime	=	INFINITE){
				WaitForSingleObject(m_hEvent,uiTime);
			}
			HANDLE	m_hEvent;
		};
#ifndef	LOCK_ADD
#define LOCK_ADD(x,val)	InterlockedAdd(&x,val)
#endif
#ifndef	LOCK_ADD_1
#define LOCK_ADD_1(x)	InterlockedIncrement(&x)
#endif
#ifndef	LOCK_SUB_1
#define LOCK_SUB_1(x)	InterlockedDecrement(&x)
#endif
	};
};
#endif // COMMONLOCK_HEAD_FILE