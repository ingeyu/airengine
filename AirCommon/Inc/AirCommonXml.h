#ifndef COMMONXML_HEAD_FILE
#define COMMONXML_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"

class	TiXmlDocument;
class	TiXmlNode;
class	TiXmlElement;
class	TiXmlHandle;
namespace Air{
	
	namespace Common{
	
		/**	\brief	Xml解析类
		*
		*	Xml解析类
		*
		***/
		class	COMMON_EXPORT	Xml{
		public:
			/**	\brief	Xml节点类
			*
			*	节点类
			*
			***/
			class	COMMON_EXPORT	Node{
			public:
				Node(TiXmlElement*	pNode	=	NULL);
				~Node();
	
				typedef		std::vector<Node>		NodeVector;
				typedef		NodeVector::iterator	NodeVectorItr;
	
				/**	\brief	获取属性值
				*   
				*	@remarks 	获取属性值
				*	@see		Node
				*	@return   	U1
				*	@param		AString strName
				*	@param		int * p
				*	@note
				*
				**/
				U1			GetAttribute(AString strName,int*	p);
				/**	\brief	获取属性值
				*   
				*	@remarks 	获取属性值
				*	@see		Node
				*	@return   	U1
				*	@param		AString strName
				*	@param		Real * p
				*	@note
				*
				**/
				U1			GetAttribute(AString strName,Real*	p);
				/**	\brief	获取属性值
				*   
				*	@remarks 	获取属性值
				*	@see		Node
				*	@return   	AString
				*	@param		AString strName
				*	@note
				*
				**/
				AString		GetAttribute(AString strName);
				/**	\brief	设置属性
				*   
				*	@remarks 	设置属性
				*	@see		Node
				*	@return   	void
				*	@param		AString strName
				*	@param		AString strValue
				*	@note
				*
				**/
				void		SetAttribute(AString strName,AString	strValue);
	
				/**	\brief	获取节点的值
				*   
				*	@remarks 	获取节点的值
				*	@see		Node
				*	@return   	AString
				*	@note
				*
				**/
				AString		GetValue();
	
				/**	\brief	获取节点名字
				*   
				*	@remarks 	获取节点名字
				*	@see		Node
				*	@return   	AString
				*	@note
				*
				**/
				AString		GetName();
	
				/**	\brief	是否为空
				*   
				*	@remarks 	是否为空
				*	@see		Node
				*	@return   	U1
				*	@note
				*
				**/
				U1			IsNull(){
					return	m_pNode	==	NULL;
				}
	
	
				/**	\brief	查找节点
				*   
				*	@remarks 	查找节点
				*	@see		Xml
				*	@return   	Common::Xml::Node
				*	@param		AString strChildNode
				*	@note
				*
				**/
				Node	Find(AString	strChildNode);
				Node	FindPath(AString	strPath);
				Node	Next();
				//Node	FirstChild(AString	strChildName);
	
				NodeVector	FindNodeVector(AString	strChildNode);
				NodeVector	FindNodeVectorPath(AString	strPath);
	
				UInt	GetNodeCount();
			
				//TiXmlNode*	m_pNode;
				TiXmlElement*	m_pNode;	///<	节点指针
			};
	
	
			Xml();
			~Xml();
	
			/**	\brief	载入文件
			*   
			*	@remarks 	载入文件
			*	@see		Xml
			*	@return   	U1
			*	@param		AString strName
			*	@note
			*
			**/
			U1	LoadFromFile(AString	strName);
			U1	LoadFromMemory(U8* pData,UInt uiSize);
	
			/**	\brief	保存
			*   
			*	@remarks 	保存
			*	@see		Xml
			*	@return   	U1
			*	@note
			*
			**/
			U1	Save();
			U1	SaveAs(AString	strAnotherName);
	
	
	
			/**	\brief	获取子节点属性
			*   
			*	@remarks 	获取子节点属性
			*	@see		Xml
			*	@return   	AString
			*	@param		AString strName
			*	@param		AString strAttrubute
			*	@note
			*
			**/
			AString			GetAttribute(AString	strName,AString	strAttrubute);
	
			Node	GetRootNode();
	
			TiXmlDocument*	m_pDocument;	///<	文档类指针
		};
	
	};
};
#endif // COMMONXML_HEAD_FILE