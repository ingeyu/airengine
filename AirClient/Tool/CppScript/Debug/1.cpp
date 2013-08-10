/*
	Function
*/
char* str="123123123";
const int i	=	100;
float x		=	1.0f;
unsigned char* pCode = NULL;

struct Vector3 
{
	float	x;
	float	y;
	float	z;
};

namespace	Air{
	void ToLower(char* str){
		int iLen=strlen(str);

		static int iOffset = 'A'-'a';
		for(int i=0;i<iLen;i++){
			if(str[i]>='A' && str[i]<='Z'){
				str[i]-=iOffset;
			}
		}
	}
}
//×¢ÊÍ
int main(){
	int x	=	-5;
	float	f	=	100.0f;
	char str[]	=	"aerIOJIFSDF";
	ToLower(str);
	return -1;
}