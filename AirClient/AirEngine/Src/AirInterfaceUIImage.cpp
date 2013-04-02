#include "AirInterfaceUIImage.h"
#include "AirRenderSystem.h"
#include "AirGlobalSetting.h"
namespace Air{
	
	namespace	Engine{
		namespace	UI{
	
			IImageSet::IImageSet( AString strName ,Info*	pInfo)	:	IProduct(strName){
				if(pInfo!=NULL)
					m_vTextureSize	=	pInfo->vTextureSize;
				else
					m_vTextureSize	=	Float2(1,1);
			}
	
			U1 IImageSet::Create(){
	
				AString	strFix;
				GlobalSetting::ParsePath(m_strProductName,&strFix,NULL,NULL);
				//判断是否为XML文件
				if(	strFix.compare("xml")==0	||
					strFix.compare("Xml")==0	||
					strFix.compare("XML")==0){
					Xml	xml;
					if(!xml.LoadFromFile(m_strProductName))
						return	false;
					Xml::Node	rootNode	=	xml.GetRootNode();
					Xml::Node	node		=	rootNode.Find("Image");
					while(true){
						//Xml::Node	node		=	rootNode.Next("Image");
						if(node.IsNull())
							break;
						AString	strName	=	node.GetAttribute("Name");
						SInt	i[4];
						node.GetAttribute("XPos",&i[0]);
						node.GetAttribute("YPos",&i[1]);
						node.GetAttribute("Width",&i[2]);
						node.GetAttribute("Height",&i[3]);
						Float4	v(i[2],i[3],i[0],i[1]);
						v.x	/=	m_vTextureSize.x;
						v.y	/=	m_vTextureSize.y;
						v.z	/=	m_vTextureSize.x;
						v.w	/=	m_vTextureSize.y;
	
						m_mapImage.insert(ImageMapPair(strName.c_str(),v));
	
						node	=	node.Next();
					}
					return	true;
					//xml.
				}
	
				File file(m_strProductName);
				if(!file.Open())
					return false;
				IniFile	cfgFile;
				cfgFile.LoadFileFromMemory(file.GetData()->buff,file.GetData()->size);
	
				SortMap*	pSort	=	cfgFile.GetSort("ImageSet");
				SortMap&	sortMap	=	*pSort;
	
				SortMap::iterator	i	=	sortMap.begin();
				for(;i!=sortMap.end();i++){
					StringVector&	lst	=	i->second;
					if(lst.empty()){
						continue;
					}
					AString	strName		=	i->first;
					AString	strValue	=	lst[0];
	
// 					Float4	v	=	GlobalSetting::ParseFloat4(strValue);
// 					v.x	/=	m_vTextureSize.x;
// 					v.y	/=	m_vTextureSize.y;
// 					v.z	/=	m_vTextureSize.x;
// 					v.w	/=	m_vTextureSize.y;
					//IImage*	pImg	=	new	IImage(strName,v);
	
					//m_mapImage.insert(ImageMapPair(strName.c_str(),v));
				}
				
				//m_vTextureSize	=	Vector2(m_pTexture->GetInfo().width,m_pTexture->GetInfo().height);
				return true;
			}
	
			U1 IImageSet::Destroy(){
				m_mapImage.clear();
				return true;
			}
	
			Float4 IImageSet::GetImage( AString strName ,Float4*	pVectorInt){
				ImageMapItr	i	=m_mapImage.find(strName.c_str());
				if(i!=m_mapImage.end()){
					Float4	v	=	i->second;
					return	v;
				}else{
					return	Float4(0,0,0,0);
				}
			}
	
			Float2 IImageSet::GetTextureSize(){
				return	m_vTextureSize;
			}
		}
	}
};