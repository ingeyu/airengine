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

Vector3 tempVector;
Vector3	vec[100];

struct Vector4 
{
	float	f[4];
};

__declspec(dllimport) int strlen(const char* str);

namespace	Air{
	void ToLower(char* str){
		int iLen=strlen(str);
		for(int i=0;i<iLen;i++){
			if((str[i]>=65) && (str[i]<=90)){
				str[i]+=32;
			}
		}
	}
}
//×¢ÊÍ
int main(){
	int x	=	-5;
	float	f	=	100.0f;
	char str2[100]	=	"aerIOJIFSDF";
	Air::ToLower(str);
	return -1;
}