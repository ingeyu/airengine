#include "AirCommonXml.h"
#include "tinyxml.h"
namespace Air{
	
	namespace	Common{
		
	
		Xml::Node::Node(TiXmlElement*	pNode){
			m_pNode	=	pNode;
		}
	
		Xml::Node::~Node(){
			//SAF_D(m_pHandle);
		}
	
		U1 Xml::Node::GetAttribute( AString strName ,int*	p){
	
			if(m_pNode!=NULL){
				m_pNode->Attribute(strName.c_str(),p);
				return	true;
			}
			return	false;
		}
	
		U1 Xml::Node::GetAttribute( AString strName,Real* p ){
	
			if(m_pNode!=NULL){
				double	d;
				m_pNode->Attribute(strName.c_str(),&d);
				if(p!=NULL)
					*p	=	d;
				return	true;
			}
			return	false;
		}
	
		AString Xml::Node::GetAttribute( AString strName ){
	
				if(m_pNode!=NULL){
					return	m_pNode->Attribute(strName.c_str());
				}
			return	"";
		}
		void Xml::Node::SetAttribute( AString strName,AString strValue ){
			if(m_pNode!=NULL){
				m_pNode->SetAttribute(strName.c_str(),strValue.c_str());
			}
		}
	
		AString Xml::Node::GetValue(){
			if(m_pNode!=NULL){
				return	m_pNode->GetText();
			}
			return	"";
		}
	
	
	
		Xml::Node Xml::Node::Find( AString strChildNode ){
			Node	n;
			if(m_pNode!=NULL){
				if(!m_pNode->NoChildren()){
					n.m_pNode	=	m_pNode->FirstChildElement(strChildNode.c_str());
					return	n;
				}
			}
			return	n;
		}
	
		Xml::Node Xml::Node::FindPath( AString strPath ){
	
			return	NULL;
		}
	
		Xml::Node::NodeVector Xml::Node::FindNodeVector( AString strChildNode ){
	
			return	NodeVector();
		}
	
		Xml::Node::NodeVector Xml::Node::FindNodeVectorPath( AString strPath ){
	
			return	NodeVector();
		}
	
		AString Xml::GetAttribute( AString strName ,AString	strAttrubute){
			return	GetRootNode().Find(strName).GetAttribute(strAttrubute);
		}
	
		UInt Xml::Node::GetNodeCount(){
			//m_pDocument->
			return	0;
		}
	
	
	
		Common::Xml::Node Xml::Node::Next(){
			Node	n;
			if(m_pNode!=NULL){
				//if(!m_pNode->NoChildren()){
					n.m_pNode	=	m_pNode->NextSiblingElement();
	#ifdef	_DEBUG
	
	// 				if(n.m_pNode!=NULL){
	// 					OutputDebugStringA(n.m_pNode->GetText());
	// 					OutputDebugStringA(n.m_pNode->Value());
	// 					OutputDebugStringA("\n");
	// 				}
	#endif
					return	n;
				//}
			}
			return	n;
		}
	
		AString Xml::Node::GetName(){
			if(m_pNode!=NULL){
				return	m_pNode->Value();
			}
			return	"";
		}
		Xml::Xml(){
			m_pDocument	=	NULL;
		}
		Xml::~Xml(){
			SAF_D(m_pDocument);
		}
	
		U1 Xml::LoadFromFile( AString strName ){
			m_pDocument	=	new	TiXmlDocument(strName.c_str());
			if(m_pDocument!=NULL){
				return	m_pDocument->LoadFile();
			}
			return	false;
		}
	
		U1 Xml::LoadFromMemory( U8* pData,UInt uiSize ){
			m_pDocument	=	new	TiXmlDocument();
			if(m_pDocument!=NULL){
				m_pDocument->Parse((AChar*)pData);
			}
			return	true;
		}
	
		U1 Xml::Save(){
			if(m_pDocument!=NULL){
				m_pDocument->SaveFile("Temp.xml");
			}
			return	true;
		}
	
		U1 Xml::SaveAs( AString strAnotherName ){
			if(m_pDocument!=NULL){
				m_pDocument->SaveFile(strAnotherName.c_str());
			}
			return	true;
		}
		Common::Xml::Node Xml::GetRootNode(){
			if(m_pDocument!=NULL){
	#ifdef	_DEBUG
				TiXmlElement*	p	=	m_pDocument->RootElement();
				if(p!=NULL){
					OutputDebugStringA(p->GetText());
					OutputDebugStringA(p->Value());
					OutputDebugStringA("\n");
				}
	#endif
				return	Node(m_pDocument->RootElement());
			}
			return	Node();
		}
	}
};