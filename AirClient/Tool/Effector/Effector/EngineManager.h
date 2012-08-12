#ifndef EngineManager_h__
#define EngineManager_h__

#include "AirSingleton.h"

class	EngineManager	:	public	Singleton<EngineManager>{
public:
	EngineManager();

	void	Init(HWND	hWindow);
	void	Release();
	void	ResizeWindow(UINT x,UINT y);
	void	RenderOneFrame();
	Air::Common::Plugin	m_RenderPlugin;
	bool	bInit;
};
#endif // EngineManager_h__
