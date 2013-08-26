int testcall(){
	return 123456789;
}
char* GlobalString = "Hello World!";
__declspec(dllimport) void Print(const char* str);
int iGolbal = 123456789;
__declspec(dllexport)	int main(int iCount,int iStart){
	Print(GlobalString);
	int iTotal	=	iGolbal;//testcall();
	for(int i=iStart;i<iCount;i++){
		iTotal-=i;
	}
	return iTotal;
}