#ifndef ENGINE_HEAD_FILE
#define ENGINE_HEAD_FILE
	// 下列 ifdef 块是创建使从 DLL 导出更简单的
	// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ENGINE_EXPORTS
	// 符号编译的。在使用此 DLL 的
	// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
	// ENGINE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
	// 符号视为是被导出的。
	#ifndef ENGINE_EXPORT
		#ifdef ENGINE_IMPORT
			#define ENGINE_EXPORT __declspec(dllexport)
		#else
			#define ENGINE_EXPORT __declspec(dllimport)
		#endif
	#endif




namespace Client{

	
	


};
#endif // ENGINE_HEAD_FILE

