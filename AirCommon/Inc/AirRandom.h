//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Random.h
 \note     
       
 \attention:
			随机数
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef RANDOM_HEAD_FILE
#define RANDOM_HEAD_FILE
#include "AirCommon.h"
#include "AirCommonHeader.h"
namespace Air{
	
	namespace Common{
		/**	\brief	数字类
		*
		*	获取随机数和序列数
		*
		***/
		class COMMON_EXPORT Number{
		public:
			/**	\brief	整形随机
			*   
			*	@remarks 	范围默认是0-100
			*	@see		Number
			*	@return   	int
			*	@param		int iMin
			*	@param		int iMax
			*	@note
			*
			**/
			static SInt				RandomI(SInt	 iMin   ,SInt   iMax);
			/**	\brief	浮点随机
			*   
			*	@remarks 	范围默认是0.0f-1.0f
			*	@see		Number
			*	@return   	float
			*	@param		float fMin
			*	@param		float fMax
			*	@note
			*
			**/
			static Real				RandomF();
			/**	\brief	数值自增
			*   
			*	@remarks 	从0开始 每次调用自增1	
			*	@see		Number
			*	@return   	unsigned int
			*	@note
			*
			**/
			static UInt		Increase();
			/**	\brief	字符串自增
			*   
			*	@remarks 	在给定字符串之后加上自增数值，保证创建出来的物体不会重名
			*	@see		Number
			*	@return   	Client::String
			*	@param		char * strName
			*	@note
			*
			**/
			static AString		Increase(const AString& strName);
			/**	\brief	初始化种子
			*   
			*	@remarks 	初始化种子
			*	@see		Number
			*	@return   	void
			*	@note
			*
			**/
			static void InitSrand();
		};
	};
	COMMON_EXPORT	void	RandomF3(Float3& v);
	COMMON_EXPORT	void	RandomF2(Float2& v);
};
#endif