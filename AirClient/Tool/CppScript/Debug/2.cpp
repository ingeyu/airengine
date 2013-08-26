int testcall(){
	return 123456789;
}
int iGolbal = 123456789;
__declspec(dllexport)	int main(int iCount,int iStart){
	int iTotal	=	iGolbal;//testcall();
	for(int i=iStart;i<iCount;i++){
		iTotal-=i;
	}
	return iTotal;
}