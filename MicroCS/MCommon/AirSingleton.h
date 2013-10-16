//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Singleton.h
 \note     
       
 \attention:单件类
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef SINGLETON_HEAD_FILE
#define SINGLETON_HEAD_FILE



#ifndef NULL
#define NULL 0
#endif

/**	\brief	单件类
*
*	单件类
*
***/
template <class T>
class Singleton{
private:
	static T			*m_pInstance;

public:
	Singleton(){
		m_pInstance	= static_cast<T*>(this);
	};
	virtual	~Singleton(){
		m_pInstance	=	NULL;
	}
	static T*	GetSingleton(){
		if(m_pInstance==NULL){
			try{
				m_pInstance = new T();
			}
			catch(...){
				//assert("GetSingleton Error!");
			}
		}
		return m_pInstance;
	};

	static void ReleaseSingleton(){
		if(m_pInstance!=NULL){
			delete m_pInstance;
			m_pInstance=NULL;
		}
	};
};

template <class T>
T* Singleton<T>::m_pInstance				= NULL;

template<typename T>
class RefSingleton{
private:
	static T			*m_pInstance;
	static unsigned int	m_uiRefCount;
public:
	RefSingleton(){
		m_pInstance	= static_cast<T*>(this);
	};
	virtual	~RefSingleton(){
		m_pInstance	=	NULL;
	}
	static T*	AddRef(unsigned int*	pRefCount	=	NULL){
		
		if(m_pInstance==NULL){
			try{
				m_pInstance		= new T();
				InterlockedExchange(&m_uiRefCount,0);
			}
			catch(...){
				//assert("GetSingleton Error!");
			}
		}
		unsigned int	uiRef	=	InterlockedIncrement(&m_uiRefCount);
		if(pRefCount!=NULL){
			*pRefCount=uiRef;
		}
		return m_pInstance;
	};

	static unsigned int ReleaseRef(){
		if(m_pInstance==NULL){
			return 0;
		}
		unsigned int	uiRef	=	InterlockedDecrement(&m_uiRefCount);
		if(m_pInstance!=NULL	&&	uiRef==0){
			delete m_pInstance;
			m_pInstance=NULL;
		}
		return uiRef;
	};
	static	unsigned int	GetRefCount(){
		return m_uiRefCount;
	};
};
template <class T>
T* RefSingleton<T>::m_pInstance				= NULL;
template <class T>
unsigned int RefSingleton<T>::m_uiRefCount			= 0;

#endif // SINGLETON_HEAD_FILE