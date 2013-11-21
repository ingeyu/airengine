// BigNumberMul.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "process.h"

int iThreadCount	=	1;
int iThreadBlock	=	100*1048576;

struct Buffer{
	unsigned __int64*	iarray;
	unsigned __int64	iCount;
	unsigned __int64	iBegin;
	unsigned __int64	iEnd;
	unsigned __int64	tid;
};

bool Calc(Buffer* pBuffer){
	char str[256];
	sprintf_s(str,"BigNumber.csv",pBuffer->iBegin,pBuffer->iEnd);
	static FILE* pFile = fopen(str,"w");

	unsigned __int64	i	=	pBuffer->iBegin;
	unsigned __int64& iCount	=	pBuffer->iCount;
	unsigned __int64	j	=	2;
	unsigned __int64	k	=	0;	
	static unsigned __int64	iSave	=	0;
	for(;i<pBuffer->iEnd;i++){
		j	=	2;
		k	=	0;
		unsigned __int64 maxValue	=	(i>>1)+1;
		for(;j<iCount;j++){
			unsigned __int64 val = pBuffer->iarray[j];
			if( val>= maxValue){
				break;
			}
			unsigned __int64 valLeft	=	i%val;
			if(valLeft==0){
				k++;
				break;
			}else{
				val	=	(i/val)+val - 1;
				if(maxValue>val){

					maxValue	=	val;
				}
			}
		}
		if(k==0){
			//printf("%lld,\n",i);
			

			if(iCount>=iThreadBlock){
				printf("more than %lld \n",iThreadBlock);
				//if(pBuffer->iCount>0)
				
				return false;
			}
			//if(ival)
			pBuffer->iarray[iCount]	=	i;
			iCount++;
			if((iCount&0xfffff)==0xfffff){

				printf("%lld\n",iCount);
				{
					for(;iSave<iCount;iSave++){
						fprintf(pFile,"%lld,\n",pBuffer->iarray[iSave]);
					}
				}
			}
		}

	}
	return true;

}
void	Function(void* p){

	Buffer buff;
	buff.iarray	=	new unsigned __int64[iThreadBlock];
	buff.iCount	=	0;

	buff.tid	=	(unsigned __int64)p;

	unsigned __int64 iRepeat	=	0xffffffffffffffff/iThreadBlock;
	for(unsigned __int64 i=buff.tid;i<iRepeat;i+=iThreadCount){
		buff.iBegin	=	i*iThreadBlock;
		buff.iEnd	=	(i+1)*iThreadBlock;
		if(!Calc(&buff)){
			return;
		}
		printf("%lld_%lld (%lld)Complated!\n",buff.iBegin,buff.iEnd,buff.iCount);
	}

}



int _tmain(int argc, _TCHAR* argv[])
{
	//for(int i=0;i<iThreadCount;i++){
	//	_beginthread(Function,1048576,(void*)i);
	//}
	Function((void*)0);
	printf("complated\n");
	getchar();

	return 0;
}

