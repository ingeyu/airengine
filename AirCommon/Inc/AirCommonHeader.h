//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


\author    InfernalHell	Xinhe
\date      2010/03/27
\version   ver 0.6.0.0
\filepath  f:\Air\AirCommon\Inc
\filename  EngineCommonHeader.h
\note     

\attention:

\remarks    created by InfernalHell version 0.6.0.0 
\History:
<author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINECOMMONHEADER_HEAD_FILE
#define ENGINECOMMONHEADER_HEAD_FILE


#if 1
//def DEBUG_MEMORY_ALLOC
#define CRTDBG_MAP_ALLOC #include <crtdbg.h>   #ifdef _DEBUG  #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)  #define new DEBUG_NEW  #endif  
#include <stdlib.h>
#include <crtdbg.h>
#endif

//STL模板库头文件
#include <map>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <set>
#include <hash_map>
#include <iostream>
#include <sstream>
#include <hash_map>
#include <hash_set>


#include <tchar.h>
#include <Windows.h>
#include <assert.h>

#include "math.h"

#include "AirCommonRefPtr.h"
#include "AirCommonMemory.h"
#include "AirCommonFunction.h"

//数学库部分
#include "xnamath.h"
#include "AirCommonVector2.h"
#include "AirCommonVector3.h"
#include "AirCommonQuaternion.h"
#include "AirCommonMatrix.h"
#include "AirCommonPlane.h"

#include "AirCommonInt2.h"
#include "AirCommonInt3.h"
#include "AirCommonInt4.h"

#include "AirSingleton.h"


#ifndef	STD_MACRO
#define STD_MACRO

#define STD_MAP			std::map
#define STD_VECTOR		std::vector
#define STD_LIST		std::list
#define STD_QUEUE		std::queue
#define STD_HASHMAP		stdext::hash_map
#define STD_SET			std::set
#define STD_HASHSET		stdext::hash_set

#endif



//浮点精度
#ifndef		FLOAT_BIT
#define 	FLOAT_BIT						32
#endif
//删除指针
#ifndef		SAFE_DELETE
#define		SAFE_DELETE(p)					if(p!=0){delete p;p=0;}
#endif
#define		SAF_D							SAFE_DELETE
//删除指针数组
#ifndef		SAFE_DELETE_ARRAY
#define		SAFE_DELETE_ARRAY(p)			if(p!=0){delete[] p;p=0;}
#endif
#define		SAF_DA							SAFE_DELETE_ARRAY
//安全释放
#ifndef		SAFE_RELEASE
#define		SAFE_RELEASE(p)					if(p!=0){p->Release();p=0;}
#endif
#define		SAF_R							SAFE_RELEASE	

//安全释放
#ifndef		SAFE_RELEASE_REF
#define		SAFE_RELEASE_REF(p)					if(p!=0){p->ReleaseRef();p=0;}
#endif

//安全执行
#ifndef		SAFE_IMPLEMENT
#define		SAFE_IMPLEMENT(p,Function)		if(p!=0){p->Function;}
#endif
#define		SAF_I							SAFE_IMPLEMENT
//输出到调试窗口
#ifndef		OUTPUT_TO_DEBUG
#define		OUTPUT_TO_DEBUG(strInfo)		OutputDebugString(strInfo)
#endif
//输出到消息窗口
#ifndef		OUTPUT_TO_MESSAGEBOX
#define		OUTPUT_TO_MESSAGEBOX(strTitle,strContext)	MessageBox(0,strContext,strTitle,0)
#endif
//输出错误信息到消息窗口
#ifndef		OUTPUT_ERROR_TO_MESSAGEBOX
#define		OUTPUT_ERROR_TO_MESSAGEBOX(strContext)		OUTPUT_TO_MESSAGEBOX("错误",strContext)
#endif


#ifndef		RETURN_FALSE
#define		RETURN_FALSE(p)								if(!p)return false;
#endif
#define		R_FALSE										RETURN_FALSE

#ifndef		RETURN_TRUE
#define		RETURN_TRUE(p)								if(p)return false;
#endif
#define		R_TURE										RETURN_TRUE


#ifndef		_ZERO
#define		_ZERO(p)									(p)=0
#endif


#ifndef		MAX_NAME
#define		MAX_NAME									256
#endif


#ifndef		KBIT										
#define		KBIT										1024
#endif

#ifndef		min
#define		min(a,b)									((a)<(b)?(a):(b))
#endif


#ifndef		max
#define		max(a,b)									((a)>(b)?(a):(b))
#endif




#ifdef	UNICODE
#define tstrcat		wcscat
#define tsscanf		wsscanf
#define tstrcpy		wcscpy
#define tsprintf	wsprintf
#else
#define	tstrcat		strcat
#define tsscanf		sscanf
#define tstrcpy		strcpy
#define tsprintf	sprintf
#endif





namespace Air{
	template<typename	T>
	void	MemoryZero(T& t){
		memset(&t,0,sizeof(t));
	};
	
		typedef	std::string			AString;
		typedef	const	AString		CAString;
		typedef	std::wstring		WString;
	
	#ifdef UNICODE
		typedef	std::wstring		String;
	#else
		typedef	std::string			String;
	#endif
	
	
		typedef	char				AChar;
		typedef	wchar_t				WChar;
		typedef	bool				U1;
		typedef	unsigned char		U8;
		typedef	unsigned short		U16;
		typedef	unsigned long		U32;
		typedef	unsigned __int64	U64;
		typedef	unsigned int		UInt;
	#if 1
		//(FLOAT_BIT == 32)
		typedef	float				Real;
	#else
		typedef	double				Real;
	#endif

		typedef	float				FLOAT;

		typedef	double				DReal;
		typedef	char				S8;
		typedef	short				S16;
		typedef	long				S32;
		typedef	__int64				S64;
		typedef	int					SInt;
	
	
		typedef	void*				Handle;

		//typedef	std::vector<AString>		StringVector;
		typedef	std::list<AString>				StringList;
		typedef	std::map<AString,AString>		StringMap;
		typedef	std::vector<AString>			StringVector;
		typedef	std::map<AString,StringVector>	SortMap;
		typedef std::map<AString,SortMap>		SortList;

		//typedef	std::vector<IFunction*>			FunctionVector;	
	
		/**	\brief	对比2个实体内容是否一致
		*   
		*	@remarks 	对比2个实体内容是否一致
		*	@see		
		*	@return   	bool
		*	@param		T1 & t1
		*	@param		T2 & t2
		*	@note
		*
		**/
		template<typename T1,typename T2>
		bool Compare(T1& t1,T2& t2){
			UInt size1 = sizeof(t1);
			UInt size2 = sizeof(t2);
			if(size1 != size2)
				return false;
			char* data1 = new char[size1];
			memcpy(data1,&t1,size1);
			char* data2 = new char[size2];
			memcpy(data2,&t2,size2);
	
			for(UInt i=0;i<size1;i++){
				if(data1[i] != data2[i]){
					delete data1;
					delete data2;
					return false;
				}
			}
			delete[] data1;
			delete[] data2;
	
			return true;
		};
};



	#include "AirUnion.h"


namespace	Air{
// 	typedef XMVECTOR	Vector2;		///<	这里的Vector是4维向量
// 	typedef	XMVECTOR	Vector3;		///<	这里的Vector是4维向量
// 	typedef	XMVECTOR	Vector4;
// 	typedef	XMVECTOR	Quaternion;
// 	typedef	XMFLOAT3X3	Matrix3;
// 	typedef	XMMATRIX	Matrix4;

	typedef	Common::Vector2		Float2;
	typedef	Common::Vector3		Float3;
	typedef	Common::DVector3	DFloat3;
	typedef	Common::Quaternion	Float4;
	typedef	XMFLOAT3X3			Float33;
	typedef	Common::Matrix		Float44;

	typedef	XMCOLOR		COLOR;

	

	//主要这个VECTOR不会调用析构函数 所以不要放入复杂对象 
	//可以存放 指针 整形 浮点 2维 3维向量之类
	template<typename	T>
	class	TVector{
	public:
		typedef	T*		iterator;
		TVector(){
			m_pData		=	NULL;
			m_uiSize	=	0;
			m_uiMaxSize	=	0;
		};
		~TVector(){
			if(m_pData!=NULL){
				delete[]	m_pData;
				m_pData	=	NULL;
			}
		};

		void	resize(U32	uiSize){
			if(uiSize	<=	m_uiMaxSize){
				m_uiSize	=	uiSize;
			}else{
				T*	p	=	new	T[uiSize];
				if(m_pData!=NULL){
					delete[]	m_pData;
				}
				m_pData		=	p;
				m_uiSize	=	uiSize;
				m_uiMaxSize	=	uiSize;
			}
		};
		U32		size(){
			return	m_uiSize;
		};
		U32		length(){
			return	m_uiSize;
		};

		void	clear(){
			m_uiSize	=	0;
		}
		void	push_back(T&	t){
			if(m_uiSize<m_uiMaxSize){
				m_pData[m_uiSize]	=	t;
				m_uiSize++;
			}else{
				if(m_uiMaxSize	==	0){
					m_uiMaxSize	=	2;
					m_uiSize	=	0;
					m_pData	=	new	T[m_uiMaxSize];
					m_pData[m_uiSize]	=	t;
					m_uiSize++;
				}else{
					m_uiMaxSize	=	m_uiMaxSize<<1;
					T*	p	=	new	T[m_uiMaxSize];
					if(m_pData!=NULL){
						memcpy(p,m_pData,m_uiSize*sizeof(T));
						delete[]	m_pData;
					}
					m_pData	=	p;
					m_pData[m_uiSize]	=	t;
					m_uiSize++;
				}
			}
		}

		iterator	begin(){
			return	m_pData;
		};
		iterator	end(){
			return	&m_pData[m_uiSize];
		};
		T&			operator[](U32	index){
			return	m_pData[index];
		};


		T*	m_pData;
		U32	m_uiSize;
		U32	m_uiMaxSize;
	};
}




	//不显示一些已知无关紧要的警告 具体参见每个警告的注释

	//warning C4244: “参数”: 从“double”转换到“const Real”，可能丢失数据
#pragma warning(disable:4244)
	//warning C4305: “参数”: 从“double”到“Real”截断
#pragma warning(disable:4305)
	//warning C4275: 非 dll 接口 class“Common::IPlugin”用作 dll 接口 class“Client::Render::ISystem”的基
#pragma warning(disable:4275)
	//warning C4251: “Common::INode::m_lstChild”: class“std::list<_Ty>”需要有 dll 接口由 class“Common::INode”的客户端使用 
#pragma warning(disable:4251)
	//warning C4267: “初始化”: 从“size_t”转换到“UInt”，可能丢失数据
#pragma warning(disable:4267)
	//warning C4311: “类型转换”: 从“void *”到“UInt”的指针截断
#pragma warning(disable:4311)


#endif // ENGINECOMMONHEADER_HEAD_FILE