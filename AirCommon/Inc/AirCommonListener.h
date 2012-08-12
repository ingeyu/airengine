#ifndef COMMONLISTENER_HEAD_FILE
#define COMMONLISTENER_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonLock.h"

namespace Air{

	namespace	Common{
		/**	\brief	单一监听管理器
		*
		*	单一监听管理器
		*
		***/
		template<typename	T_Listener>
		class	SimpleListenManager{
		public:
			SimpleListenManager(){
				m_pListener	=	NULL;
			};


			/**	\brief	设置监听器
			*   
			*	@remarks 	设置监听器
			*	@see		SimpleListenManager
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			void	SetListener(T_Listener*	pListener){
				m_pListener	=	pListener;
			};
			T_Listener*	m_pListener;		///<	监听器
		};

		/**	\brief	多监听管理器
		*
		*	多监听管理器
		*
		***/
		template<typename T_Listener>
		class	MutilListenerManager{
		public:
			typedef	std::list<T_Listener*>	ListenerList;
			typedef	typename ListenerList::iterator	ListenerListItr;
		public:
			MutilListenerManager(){

			};
			virtual	~MutilListenerManager(){

			};

			/**	\brief	添加管理器
			*   
			*	@remarks 	添加管理器
			*	@see		MutilListenerManager
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			virtual	void	AddListener(T_Listener*	pListener){
				m_lstListener.push_back(pListener);
			};
			/**	\brief	添加管理器
			*   
			*	@remarks 	添加管理器
			*	@see		MutilListenerManager
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			virtual	void	RemoveListener(T_Listener*	pListener){
				m_lstListener.remove(pListener);
			};

			ListenerList	m_lstListener;	///<	监听列表
			
		};
		/**	\brief	多监听管理器(带锁)
		*
		*	多监听管理器(带锁)
		*
		***/
		template<typename T_Listener>
		class	MutilListenerManagerMT
			:	public	MutilListenerManager<T_Listener>{
		public:
			/**	\brief	添加管理器
			*   
			*	@remarks 	添加管理器
			*	@see		MutilListenerManagerMT
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			void	AddListener(T_Listener*	pListener){
				if(pListener==NULL)
					return;
				m_CS.Enter();
				m_lstListener.push_back(pListener);
				m_CS.Leave();
			};
			/**	\brief	移除监听器
			*   
			*	@remarks 	移除监听器
			*	@see		MutilListenerManagerMT
			*	@return   	void
			*	@param		T_Listener * pListener
			*	@note
			*
			**/
			void	RemoveListener(T_Listener*	pListener){
				if(pListener==NULL)
					return;
				m_CS.Enter();
				m_lstListener.remove(pListener);
				m_CS.Leave();
			};
			//CriticalSection	m_CS;	///<	暂时不在这里添加临界区 需要的类自行添加临界区锁
		};
	}
	

};
#endif // COMMONLISTENER_HEAD_FILE