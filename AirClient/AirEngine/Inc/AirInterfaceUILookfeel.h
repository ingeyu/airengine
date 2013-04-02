#ifndef INTERFACEUILOOKFEEL_HEAD_FILE
#define INTERFACEUILOOKFEEL_HEAD_FILE

#include "AirInterfaceUIElement.h"
namespace Air{
	
	namespace Engine{
	
		namespace	UI{
			//typedef		std::vector<Common::StringVector>		StateStringMap;
			typedef		std::map<AString,StateArray>		WindowStateMap;
			typedef		WindowStateMap::value_type			WindowStateMapPair;
			/**	\brief	视觉方案类
			*
			*	解析视觉方案类
			*
			***/
			class	ENGINE_EXPORT	Lookfeel	:
				public	IProduct{
			public:
				Lookfeel(CAString&	strName);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Lookfeel
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Lookfeel
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
	
				/**	\brief	获取视觉方案
				*   
				*	@remarks 	获取视觉方案
				*	@see		Lookfeel
				*	@return   	StateArray*
				*	@param		AString & strName
				*	@note
				*
				**/
				StateArray*	GetWindowLookfeel(AString&	strName);
			//protected:
				/**	\brief	解析视觉方案
				*   
				*	@remarks 	解析视觉方案
				*	@see		Lookfeel
				*	@return   	U1
				*	@param		AString & strLookfeelFile
				*	@param		StateArray * pArray
				*	@note
				*
				**/
				static	U1				ParseLookfeel(AString&	strLookfeelFile,StateArray*	pArray);
				/**	\brief	解析状态
				*   
				*	@remarks 	解析状态
				*	@see		Lookfeel
				*	@return   	U1
				*	@param		SortMap * pMap
				*	@param		ElementArray * pArray
				*	@note
				*
				**/
				static	U1				ParseState(SortMap*	pMap,ElementArray*		pArray);
	
				WindowStateMap	m_mapLookfeel;
				AString		m_strLookfeel;
			};
		}
	
	};
};
#endif // INTERFACEUILOOKFEEL_HEAD_FILE