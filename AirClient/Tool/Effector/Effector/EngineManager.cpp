#include "stdafx.h"
#include "EngineManager.h"
#include "AirGlobalSetting.h"

EngineManager::EngineManager():m_RenderPlugin("AirRender11.dll",NULL)
{
	bInit	=	false;
}

void EngineManager::Init( HWND hWindow )
{
	if(!bInit){
		Air::Client::GetGlobalSetting().m_EngineParam.hWnd	=	hWindow;
		m_RenderPlugin.Create();
		bInit	=	true;
		Air::Client::Render::System::GetSingleton()->Initialization();
	}

	
}

void EngineManager::Release()
{

	Air::Client::Render::System::GetSingleton()->Release();
	m_RenderPlugin.Destroy();
	Air::Client::Render::System::ReleaseSingleton();
	
}

void EngineManager::ResizeWindow( UINT x,UINT y )
{
	Air::Client::RenderWindow*	pMainWnidow	=	Air::Client::Render::System::GetSingleton()->GetMainWindow();
	UINT	w	=	pMainWnidow->GetWidth();
	UINT	h	=	pMainWnidow->GetHeight();
	if(	x	!=	w	||
		y	!=	h)
	{
		pMainWnidow->ReSize(x,y);
	}
}

void EngineManager::RenderOneFrame()
{
	Air::Client::RenderWindow*	pMainWnidow	=	Air::Client::Render::System::GetSingleton()->GetMainWindow();
	if(pMainWnidow!=NULL){
		pMainWnidow->Update();
	}
}
