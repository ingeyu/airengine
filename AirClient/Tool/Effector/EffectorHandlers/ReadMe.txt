========================================================================
    活动模板库：EffectorHandlers 项目概述
========================================================================

应用程序向导已为您创建了此 EffectorHandlers 
项目。您可以在此基础上，编写自己的动态链接库 (DLL)。

此文件是项目所含每个文件的内容摘要。

EffectorHandlers.vcxproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，
    它包含有关生成该文件时所用 Visual C++ 版本的信息，
    以及有关使用应用程序向导选择的平台、配置和项目功能
    的信息。

EffectorHandlers.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。 
    它包含有关项目文件与筛选器之间的关联信息。 
    IDE 中使用这种关联来显示文件的分组， 将具有类似
    扩展名的文件显示在专用节点下。例如，“.cpp”文件与
    “源文件”筛选器关联在一起。

EffectorHandlers.idl
    此文件包含项目中定义的类型库、接口和 coclass 的 IDL 定义。
    此文件将由 MIDL 编译器处理，用于生成：
        C++ 接口定义和 GUID 声明 (EffectorHandlers.h)
        GUID 定义 (EffectorHandlers_i.c)
        类型库 (EffectorHandlers.tlb)
        封送处理代码 (EffectorHandlers_p.c 和 dlldata.c)

EffectorHandlers.h
    此文件包含 EffectorHandlers.idl 中所定义项的 C++ 接口定义
    和 GUID 声明。 它将在编译过程中由 MIDL 重新生成。

EffectorHandlers.cpp
    此文件包含对象映射和 DLL 导出的实现。

EffectorHandlers.rc
    这是程序使用的所有 Microsoft Windows 资源
    的列表。

EffectorHandlers.def
    此模块定义文件为链接器提供有关 DLL 所要求的
    导出的信息。 它包含用于以下内容的导出：
        DllGetClassObject
        DllCanUnloadNow
        DllRegisterServer
        DllUnregisterServer
        DllInstall

/////////////////////////////////////////////////////////////////////////////
其他标准文件:

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 EffectorHandlers.pch 的预编译头 (PCH) 文件
    和名为 StdAfx.obj 的预编译类型文件。

Resource.h
    这是用于定义资源 ID 的标准头文件。

/////////////////////////////////////////////////////////////////////////////
其他注释:

	“MFC 支持”选项可用于将 Microsoft 基础类库构建到您的主干应用程序中，
	从而让您能够使用 MFC 类、对象和函数。
/////////////////////////////////////////////////////////////////////////////