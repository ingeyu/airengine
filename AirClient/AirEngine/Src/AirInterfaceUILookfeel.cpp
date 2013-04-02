#include "AirInterfaceUILookfeel.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceUISystem.h"
namespace Air{
	
	namespace	Engine{
		namespace	UI{
	
	
			Lookfeel::Lookfeel( CAString& strName):IProduct(strName){
				//m_strLookfeel	=	*strLookfeel;
			}
	
			U1 Lookfeel::Create(){
				File	file(m_strProductName);
				if(!file.Open())
					return	false;
				IniFile	cfg;
				cfg.LoadFileFromMemory(file.GetData());
	
				SortMap*	pMap	=	cfg.GetSort("Lookfeel");
				if(pMap==NULL)
					return	false;
				
				SortMap&	m	=	*pMap;
				SortMap::iterator	i	=	m.begin();
				for(;i!=m.end();i++){
					StringVector&	lst	=	i->second;
					if(lst.empty())
						continue;
					AString	strName		=	i->first;
					AString&	strFileName	=	lst[0];
					StateArray	sArray;
					if(ParseLookfeel(strFileName,&sArray)){
						m_mapLookfeel.insert(WindowStateMapPair(strName.c_str(),sArray));
					}
				}
	
				return	true;
			}
	
			U1 Lookfeel::Destroy(){
				m_mapLookfeel.clear();
				return	true;
			}
	
			StateArray* Lookfeel::GetWindowLookfeel( AString& strName ){
			
				WindowStateMap::iterator	i	=	m_mapLookfeel.find(strName.c_str());
				if(i!=m_mapLookfeel.end()){
					return	(StateArray*)&(i->second);
				}else{
					return	NULL;
				}
			}
	
			U1 Lookfeel::ParseLookfeel( AString& strLookfeelFile,StateArray*	pArray ){
				File	file(strLookfeelFile);
				if(!file.Open())
					return	false;
				IniFile	cfg;
				cfg.LoadFileFromMemory(file.GetData());
	
				StringVector*	pLst	=	cfg.GetStringList("State",cfg.GetSort("Lookfeel"));
				if(pLst==NULL)
					return	false;
	
				StringVector&	lst	=	*pLst;
	
				UInt	uiSize	=	lst.size();
				
				StateArray&	sArray	=	*pArray;
				sArray.resize(uiSize);
	
				for(UInt i=0;i<uiSize;i++){
					AString&	strState	=	lst[i];
					SortMap*	pMap	=	cfg.GetSort((AChar*)strState.c_str());
					ElementArray	eArray;
					if(ParseState(pMap,&eArray)){
						sArray[i]	=	eArray;
					}
					
				}
	
				return	true;
			}
	
			U1 Lookfeel::ParseState(SortMap*	pMap,ElementArray* pArray ){
				SortMap&	m	=	*pMap;
				StringVector&	pLstSize	=	m["Size"];
				StringVector&	pLstUV		=	m["UV"];
				StringVector&	pLstColor	=	m["Color"];
				StringVector&	pLstCustom	=	m["Custom"];
	
				UInt	uiSize	=	pLstSize.size();
				ElementArray&	eArray	=	*pArray;
				eArray.resize(uiSize);
				for(UInt	i=0;i<uiSize;i++){
					IElement	e;
// 					e.m_vPositionSize	=	GlobalSetting::ParseFloat4(pLstSize[i]);
// 					e.m_vUV				=	GetGlobalSetting().m_pUISystem->GetImage(pLstUV[i]);//GlobalSetting::ParseFloat4(pLstUV[i]);
// 					e.m_vColor			=	GlobalSetting::ParseFloat4(pLstColor[i]);
// 					e.m_vCustom			=	GlobalSetting::ParseFloat4(pLstCustom[i]);
					eArray[i]			=	e;
				}
	
				return	true;
			}
		}
	}
};