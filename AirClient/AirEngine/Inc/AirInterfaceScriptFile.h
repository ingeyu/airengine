/*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.


 \author    InfernalHell	Xinhe
 \date      2009/11/01
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  InterfaceScriptFile.h
 \note     
       
 \attention:
			脚本文件类
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef INTERFACESCRIPTFILE_HEAD_FILE
#define INTERFACESCRIPTFILE_HEAD_FILE

//#include "Define.h"
#include "AirInterfaceScriptVariable.h"
namespace Air{
	
	namespace Client{
	
		
		namespace Script{
			class	IFunction;
			class	IVariable;
			/**	\brief	脚本文件
			*
			*	脚本文件
			*
			***/
			class IFile{
			public:
		
				/**	\brief	获取脚本文件名
				*   
				*	@remarks 	获取脚本文件名
				*	@see		IFile
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual AString		GetFileName(){return "";};
	
				/**	\brief	获取文件全局变量数
				*   
				*	@remarks 	获取文件全局变量数
				*	@see		IFile
				*	@return   	int
				*	@note
				*
				**/
				virtual SInt			GetVariableCount(){return 0;};
				/**	\brief	获取全局变量名字
				*   
				*	@remarks 	获取全局变量名字
				*	@see		IFile
				*	@return   	Client::String
				*	@note
				*
				**/
				virtual AString		GetVariableName(){return "";};
				/**	\brief	获取变量
				*   
				*	@remarks 	变量
				*	@see		IFile
				*	@return   	IVariable*
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual IVariable	GetVariable(SInt iIndex){return IVariable();};
				/**	\brief	获取变量
				*   
				*	@remarks 	获取变量
				*	@see		IFile
				*	@return   	IVariable*
				*	@param		String strName
				*	@note
				*
				**/
				virtual IVariable	GetVariable(AString strName){return IVariable();};
		
				/**	\brief	获取函数数量
				*   
				*	@remarks 	获取函数数量
				*	@see		IFile
				*	@return   	int
				*	@note
				*
				**/
				virtual SInt			GetFunctionCount(){return 0;};
				/**	\brief	获取函数名
				*   
				*	@remarks 	获取函数名
				*	@see		IFile
				*	@return   	Client::String
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual AString		GetFunctionName(SInt iIndex){return "";};
				/**	\brief	获取函数全名
				*   
				*	@remarks 	获取函数全名
				*	@see		IFile
				*	@return   	Client::String
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual AString		GetFunctionString(SInt iIndex){return  "";};
				/**	\brief	获取函数
				*   
				*	@remarks 	获取函数
				*	@see		IFile
				*	@return   	IFunction*
				*	@param		int iIndex
				*	@note
				*
				**/
				virtual IFunction*	GetFunction(SInt iIndex){return NULL;};
				/**	\brief	获取函数
				*   
				*	@remarks 	
				*	@see		IFile
				*	@return   	IFunction*
				*	@param		String strName
				*	@note
				*
				**/
				virtual IFunction*	GetFunction(AString strName){return NULL;};
				/**	\brief	获取函数通过函数全名
				*   
				*	@remarks 	获取函数通过函数全名
				*	@see		IFile
				*	@return   	IFunction*
				*	@param		String strFullName
				*	@note
				*
				**/
				virtual IFunction*	GetFunctionByFullName(AString strFullName){return NULL;};
	
				/**	\brief	编译
				*   
				*	@remarks 	编译
				*	@see		IFile
				*	@return   	void
				*	@note
				*
				**/
				virtual U1		Compile(){return true;};
				/**	\brief	是否编译
				*   
				*	@remarks 	是否编译
				*	@see		IFile
				*	@return   	bool
				*	@note
				*
				**/
				virtual U1		HasCompile(){return true;};
	
	
				/**	\brief	读取二进制
				*   
				*	@remarks 	读取二进制
				*	@see		IFile
				*	@return   	bool
				*	@note
				*
				**/
				virtual U1		ReadBinary(){return true;};
				/**	\brief	写入二进制
				*   
				*	@remarks 	
				*	@see		IFile
				*	@return   	bool
				*	@note
				*
				**/
				virtual U1		WriteBinary(){return true;};
		
			};
		}
	};
};

#endif // INTERFACESCRIPTFILE_HEAD_FILE