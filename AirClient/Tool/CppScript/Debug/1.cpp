/*
	Function
*/
char* str="HELLO WORLD!";


__declspec(dllimport) void Print(const char* str);

namespace	Air{
	void ToLower(char* str){
		int iLen=12;//strlen(str);
		for(int i=0;i<iLen;i++){
			if((str[i]>='A') && (str[i]<=90)){
				str[i]+=32;
			}
		}
	}
}
//×¢ÊÍ
__declspec(dllexport)	int main(int count,int param){

	Print(str);
	Air::ToLower(str);
	Print(str);
	return -1;
}