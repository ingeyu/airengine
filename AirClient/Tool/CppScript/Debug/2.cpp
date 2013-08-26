int testcall(){
	return 10000;
}
__declspec(dllexport)	int main(int iCount,int iStart){
	int iTotal	=	testcall();
	for(int i=iStart;i<iCount;i++){
		iTotal-=i;
	}
	return iTotal;
}