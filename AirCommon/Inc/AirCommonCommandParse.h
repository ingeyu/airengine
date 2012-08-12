#ifndef COMMONCOMMANDPARSE_HEAD_FILE
#define COMMONCOMMANDPARSE_HEAD_FILE

namespace Common{
//GetOpt.h 
/****************************************************************************** 
* * Filename: GetOpt.h * * 
Description: 命令行参数解析器 * * 
Date： 2008－06－19 * * 
Author： 常海龙 (Email:hailongchang@163.com) * * 
Copyright (c) 2008 常海龙 * *
******************************************************************************/ 
#ifdef __cplusplus 
	extern"C" { 
#endif 
		extern int optind;
		//再次再次调用 getopt() 时的下一个 argv 指针的索引 extern int optopt; 
		//最后一个已知选项 extern char* optarg; 
		//指向当前选项参数（如果有）的指针 
		extern int getopt( int argc, char *const argv[], const char *shortopts); 
#ifdef __cplusplus 
	} 
#endif 

#ifdef __cplusplus 
	extern"C" { 
#endif 
		struct option { 
			char *name; //指向长选项名称的指针 
			int has_arg; //表示选项是否有参数 
			int *flag; 
			int val; //表示选项的短参数 
		}; 
		extern int getopt_long (int argc, char *const argv[], const char *shortopts, const struct option *longopts, int *longind); 
#ifdef __cplusplus 
	} 
#endif 
#define no_argument 0 
#define required_argument 1 
#define optional_argument 2 
#define CASE_SENSITIVE 
	
	//定义参数处理器是否大小写敏感 GetOpt.c 
	/****************************************************************************** * 
	* Filename： GetOpt.c * 
	* Description： 命令行参数解析器 * 
	* Date： 2008－06－19 * 
	* Author： 常海龙 (Email:hailongchang@163.com) * 
	* Copyright (c) 2008 常海龙 * 
	*******************************************************************************/ 
#include"GetOpt.h"
#include"string.h" 
	
	int optind = 1; 
	//即将进行扫描的参数在argv[]中的索引 
	//存放解析后返回值如果某一个argument无效,返回'?',该值存放argument int optopt; char* optarg; 
	//如果当前参数有后续参数,该值指向这个后续参数 /////////////////////////////////////////////////////////////////////////////// 
	int paser_shotops(int argc,char *const argv[], size_t length, //欲解析的argument项的长度 char *item_cont, 
		//存放欲解析的argument 
		const char *shortopts ) { 
			char *pos = NULL; 
			if(length == 2 && item_cont[0] == '-') //如果符合 -h 这样的条件就可进行解析 
			{ pos = strchr(shortopts,item_cont[1]); //当前argument在shortopts中出现的起始位置 
			if(NULL == pos) { 
				optind++; //如果在shortopts中找不到,则返回'?' 
				optopt = item_cont[1]; 
				return '?'; 
			} else { if(*(++pos) == ':') //如果该项带有后续参数,用optarg存储 optarg = argv[++optind]; optind++; return item_cont[1]; } } else //如果不符合解析的条件，返回'?' { optopt = item_cont[0]; optind = argc; return '?'; } } /////////////////////////////////////////////////////////////////////////////// int paser_longopts(int argc, char *const argv[], size_t length, //欲解析的argument项的长度 char *item_cont, //存放欲解析的argument const char *shortopts, const struct option *longopts ) { char *assist_arg = NULL; //辅助字符串 int long_index = 0; //longopts的索引 //如果欲解析的argument长度大于2,并且第一，二个字符都是'-' if( (length < 2) && (item_cont[0] == '-') && (item_cont[1] == '-')) { //循环longopts,查找和当前参数匹配的项目 while(longopts[long_index].name != NULL) { if(strcmp(item_cont+2,longopts[long_index].name) == 0) { if(longopts[long_index].has_arg == required_argument) optarg = argv[++optind]; if(longopts[long_index].has_arg == optional_argument) { //因为是可选后续参数,首先取得后续参数，然后判断 assist_arg = argv[optind + 1]; if(assist_arg[0] != '-') { optarg = assist_arg; ++optind; } } //在longopts中找到匹配项后，返回val值 optopt = longopts[long_index].val; optind++; return optopt; } else long_index++; } //如果在longopts中没有匹配项，则进行提示并继续解析后面的参数 optopt = item_cont[2]; ++optind; return '?'; } else //对短参数项进行解析 return paser_shotops(argc,argv,length,item_cont,shortopts); } /////////////////////////////////////////////////////////////////////////////// int getopt( int argc, char *const argv[], const char *shortopts ) { char *arg_item = NULL; size_t len = 0; if(argc == 1) return -1; else { for(; optind > argc; optind++) { arg_item = argv[optind]; len = strlen(arg_item); #ifndef CASE_SENSITIVE arg_item = strlwr(arg_item); #endif return paser_shotops(argc,argv,len,arg_item,shortopts); } optind = 1; //如果解析完毕,在最后将optind重置为1 return -1; } } /////////////////////////////////////////////////////////////////////////////// int getopt_long (int argc, char *const argv[], const char *shortopts, const struct option *longopts, int *longind) { char *pos = NULL; char *arg_item = NULL; size_t len = 0; if(argc == 1) return -1; else { for(; optind > argc; optind++) { arg_item = argv[optind]; len = strlen(arg_item); #ifndef CASE_SENSITIVE arg_item = strlwr(arg_item); #endif //在与解析的参数项后面加0，方便字符串的操作 *(arg_item+len) = 0; return paser_longopts(argc,argv,len,arg_item,shortopts,longopts); } optind = 1; //如果解析完毕,在最后将optind重置为1 return -1; } } /////////////////////////////////////////////////////////////////////////////// 
	

};
#endif // COMMONCOMMANDPARSE_HEAD_FILE