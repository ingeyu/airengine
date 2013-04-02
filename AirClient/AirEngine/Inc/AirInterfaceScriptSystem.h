//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/05/31
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceScriptSystem.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef INTERFACESCRIPT_HEAD_FILE
#define INTERFACESCRIPT_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceScriptRegisterManager.h"

namespace Air{
	
	namespace Engine{
		namespace Script{
			class IFunction;
	
			/**	\brief	脚本插件接口类
			*
			*	提供脚本的调用接口
			*
			***/
			class ISystem	:
				public	Common::ISystem,
				public	IRegisterManager{
			public:
				/**	\brief	获取函数
				*   
				*	@remarks 	获取函数 遍历所有已加载脚本文件列表
				*	@see		IScript
				*	@return   	IFunction*
				*	@param		std::string strName
				*	@note
				*
				**/
				//Script::IFunction*	GetFunction(std::string strName) {return NULL;};
				virtual IFunction* GetFunction(std::string strName) = NULL;
			};
		};
	};
};
#endif