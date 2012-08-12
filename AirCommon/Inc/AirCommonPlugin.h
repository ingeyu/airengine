#ifndef COMMONPLUGINMANAGER_HEAD_FILE
#define COMMONPLUGINMANAGER_HEAD_FILE
#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
namespace Air{
	
	namespace Common{
		typedef		U1(*Func)(void*);
	
		/**	\brief	基本插件接口类
		*
		*	基本插件接口类
		*
		***/
		class	IPlugin{
		public:
			virtual	~IPlugin(){};
			/**	\brief	初始化
			*   
			*	@remarks 	初始化
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Initialization(){return	true;};
			/**	\brief	开始
			*   
			*	@remarks 	开始
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Start(){return	true;};
			/**	\brief	停止
			*   
			*	@remarks 	停止
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Stop(){return	true;};
			/**	\brief	释放
			*   
			*	@remarks 	释放
			*	@see		IPlugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Release(){return	true;};
		};
		/**	\brief	插件管理
		*
		*	插件管理
		*
		***/
		class	COMMON_EXPORT	Plugin	:	public	IProduct{
		public:
			/**	\brief	插件函数类型
			*
			*	插件函数类型
			*
			***/
			enum	enumFuncType{
				enInit,
				enStart,
				enStop,
				enRelease,
				enMax
			};
		public:
			Plugin(CAString& strName,void*	pParam);
			virtual ~Plugin();
	
			/**	\brief	创建插件
			*   
			*	@remarks 	创建插件
			*	@see		Plugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Create();
	
			/**	\brief	摧毁插件
			*   
			*	@remarks 	摧毁插件
			*	@see		Plugin
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Destroy();
	
			/**	\brief	执行插件函数
			*   
			*	@remarks 	执行函数
			*	@see		Plugin
			*	@return   	U1
			*	@param		enumFuncType funcType
			*	@note
			*
			**/
			virtual	U1	Excute(enumFuncType	funcType);
	
			/**	\brief	获取函数
			*   
			*	@remarks 	获取函数
			*	@see		Plugin
			*	@return   	Common::Func
			*	@param		AString strName
			*	@note
			*
			**/
			virtual	Func	GetFunction(AString	strName);
		public:
			void*		m_pParam;
			Func		m_Func[enMax];
		};
		class	COMMON_EXPORT	PluginFactory	:
			public	IFactory{
		public:
			PluginFactory();
	
			/**	\brief	创建插件
			*   
			*	@remarks 	创建插件
			*	@see		PluginFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam = NULL);
	
		};
		
	
	};
};
#endif // COMMONPLUGINMANAGER_HEAD_FILE