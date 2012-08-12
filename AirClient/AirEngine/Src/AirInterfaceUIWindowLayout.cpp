#include "AirInterfaceUIWindowLayout.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceUISystem.h"
namespace Air{
	
	namespace	Client{
		namespace	UI{
			namespace	Window{
	
	
				Layout::Layout( AString strName ,AString*	strLayout,Info*	pInfo):IControl(strName,NULL,pInfo){
					m_strLayout	=	*strLayout;
				}
	
				U1 Layout::Create(){
					if(m_strLayout.empty())
						return false;
					File	file(m_strLayout);
					if(file.Open()){
						IniFile	cfg;
						cfg.LoadFileFromMemory(file.GetData());
	
						StringVector*	pLst	=	cfg.GetStringList("Window",cfg.GetSort("RootWindow"));
						if(pLst==NULL)
							return false;
						StringVector&	lst		=	*pLst;
						UInt	uiSize	=	lst.size();
						for(UInt	i=0;i<uiSize;i++){
							AString	str		=	lst[i];
							AChar	strName[128],strType[128];
							ZeroMemory(strName,128);
							ZeroMemory(strType,128);
							UInt	uiSize	=	str.size();
							for(UInt i=0;i<uiSize;i++){
								if(str[i]	==	':'){
									memcpy(strName,&str[0],i);
									memcpy(strType,&str[i+1],uiSize-i);
									break;
								}
							}
							//sscanf_s(str.c_str(),"%s:%s",strName,strType);
							
							AString	strInfo[8];
							strInfo[0]	=	cfg.Get(strName,"Size");
							strInfo[1]	=	cfg.Get(strName,"Center");
							strInfo[2]	=	cfg.Get(strName,"Color");
							strInfo[3]	=	cfg.Get(strName,"Text");
							strInfo[4]	=	cfg.Get(strName,"TextColor");
							strInfo[5]	=	cfg.Get(strName,"Visiable");
							strInfo[6]	=	cfg.Get(strName,"Enable");
							strInfo[7]	=	cfg.Get(strName,"Key");
	
							Info	info;
// 							info.vPositionSize	=	GlobalSetting::ParseFloat4(strInfo[0]);
// 							Float4	v			=	GlobalSetting::ParseFloat4(strInfo[1]);
// 							info.vCenter		=	Vector2(v.x,v.y);
// 							
// 							info.vColor			=	GlobalSetting::ParseFloat4(strInfo[2]);
// 							info.strText		=	strInfo[3];
// 							info.vTextColor		=	GlobalSetting::ParseFloat4(strInfo[4]);
// 							info.bVisiable		=	Common::Converter::parseBool(strInfo[5]);
// 							info.bEnable		=	Common::Converter::parseBool(strInfo[6]);
							ParseKey(info.key,strInfo[7]);
	
							Window::IControl*	pWindow	=	GetGlobalSetting().m_pUISystem->CreateIWindow(strName,strType,&info);
							if(pWindow!=NULL){
								AddChild(pWindow);
							}
						}
						
					}
	
					//刷新一次窗口树
					Refresh();
					return	true;
				}
	
				U1 Layout::ParseKey( KeyUnion& k,AString& strInfo ){
					if(strInfo.empty())
						return false;
					UInt	uiSize	=	strInfo.size();
					std::vector<AString>	lst;
					UInt	iNumKey	=	0;
					UInt	iLast	=	0;
					for(UInt	i=0;i<uiSize;i++){
						if(strInfo[i]	==	'+'){
							UInt	iChar	=	i	-	iLast;
							AString	s;
							s.resize(iChar);
							memcpy(&s[0],&strInfo[iLast],iChar);
							lst.push_back(s);
							iLast	=	i+1;
							iNumKey++;
						}
					}
					if(iLast!=uiSize){
						UInt	iChar	=	uiSize	-	iLast;
						AString	s;
						s.resize(iChar);
						memcpy(&s[0],&strInfo[iLast],iChar);
						lst.push_back(s);
					}
					if(iNumKey==0){
						k.Key	=	GetKey(strInfo);	
					}else{
						for(UInt	i=0;i<lst.size();i++){
							U8	tempKey	=	GetKey(lst[i]);
							switch(tempKey){
								case	OIS::KC_LCONTROL:
								case	OIS::KC_RCONTROL:{
									k.Ctrl	=	true;
									break;}
								case	OIS::KC_LSHIFT:
								case	OIS::KC_RSHIFT:{
									k.Shift	=	true;
									break;}
								case	OIS::KC_LMENU:
								case	OIS::KC_RMENU:{
									k.Alt	=	true;
									break;}
								default:{
									k.Key	=	tempKey;
									break;}
							}
						}
					}
					return true;
				}
	
				U8 Layout::GetKey( AString& str ){
					return	GetGlobalSetting().GetKey(str);
				}
	
				IControl* Layout::IsMouseInWindow(){
					//永远不要返回 Layout 自身
					IControl*	pActiveWin	=	NULL;
					WindowList::reverse_iterator	i	=	m_lstWindow.rbegin();
					for(;i!=m_lstWindow.rend();i++){
						IControl*	pWindow	=	(IControl*)(*i);
						if(pWindow!=NULL){
							pActiveWin	=	pWindow->IsMouseInWindow();
							if(pActiveWin!=NULL){
								return	pActiveWin;
							}
						}
					}
					return	NULL;
				}
			}
		}
	}
};