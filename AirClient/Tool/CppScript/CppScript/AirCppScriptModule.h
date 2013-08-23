#ifndef AirCppScriptModule_h__
#define AirCppScriptModule_h__

#include "AirCppScriptSyntaxNode.h"
#include "guiddef.h"

namespace	Air{
	namespace	CppScript{
		class	Function;
		enum	enumLoadError{
			enLE_OK,
			enLE_File_Isnt_Exist,
			enLE_File_Size_Less_Than_Module_Header,
			enLE_Unknown_File_Format,
			enLE_Unknown_Version,
			enLE_Cant_Find_Import_Function
		};
		struct	ModuleHeader{
			U32		CppS;
			U32		CompilerVersion;
			U32		Version;
			U32		TimeStamp;
			GUID	Guid;
			U32		Age;
			U32		IATCount;
			union{
				U32		IAT_RA;
				U8*		IAT_A;
			};
			union{
				U32			IAT_Name_RA;
				char**		IAT_Name_A;
			};
			U32		EATCount;
			union{
				U32			EAT_RA;
				U32**		EAT_A;
			};
			union{
				U32			EAT_Name_RA;
				char**		EAT_Name_A;
			};
			union{
				U32		Entry_RA;		//if Entry == 0 its a dll else exe
				U8*		Entry_A;
			};
			U32		ImageSize;		//Include Header
			U8		Code[4];
		};

		class	Module{
		public:
			Module();
			virtual	~Module();
			enumLoadError		Load(const wchar_t* strName);
			enumLoadError		Load(const void* pBuffer,U32 uiSize);
			void				UnLoad();
			
			void*				FindFunction(const char* strFunctionName);
		protected:
			enumLoadError		LoadRelocaltion_VF01();
		protected:
			void*			m_pImageBase;
			U32				m_uiSize;
			ModuleHeader*	m_pHeader;
		};

		void	InitModuleHeader(ModuleHeader& header);
	}
}
#endif // AirCppScriptModule_h__