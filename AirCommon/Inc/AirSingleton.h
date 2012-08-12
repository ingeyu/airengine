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


#endif // SINGLETON_HEAD_FILE