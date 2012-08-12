// dllmain.h: 模块类的声明。

class CEffectorHandlersModule : public ATL::CAtlDllModuleT< CEffectorHandlersModule >
{
public :
	DECLARE_LIBID(LIBID_EffectorHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_EFFECTORHANDLERS, "{987CEFEC-96E5-4EDE-89B5-3CA661D3BDA1}")
};

extern class CEffectorHandlersModule _AtlModule;
