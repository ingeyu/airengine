__declspec(dllimport)	void Print(const char* str);
__declspec(dllimport)	void*	malloc(int	uiSize);
__declspec(dllimport)	void	free(void*	p);
__declspec(dllimport)	char*	strcpy(char* pDst,char* src);
struct Vector3{
	float x;
	float y;
	short z;
	Vector3(){
		x	=	0;
		y	=	0;
		z	=	0;
	}
	~Vector3(){
		Print("Vector3::~Vector3");
	};
	virtual	void	Add(){
		Print("Vector3::Add");
	};
};

struct Vector4	:	public	Vector3
{
	Vector4(){
	};
	~Vector4(){
		Print("Vector4::~Vector4");
	};
	virtual	void	Add(){
		Print("Vector4::Add");
	};
};

struct MyClass{
	Vector4* pVec4;
	MyClass(){
		pVec4	=	new Vector4();
	};
	~MyClass(){
		if(pVec4!=NULL){
			delete pVec4;
			pVec4=NULL;
		}
	};

	void	Call(){
		pVec4->Add();
	};

};


__declspec(dllexport)	int main(int iCount,int iStart){
	Vector3 v;
	v.Add();
	MyClass* pV =	NULL;
	pV	=	new MyClass();
	pV->Call();
	delete pV;

	int v2[100];
	v2[iStart]=11;
	v2[2]=12;

	char* s = malloc(512);
	strcpy(s,"1234567890");
	char* s2 = (s + 5);
	strcpy(s2,"abcdefg");
	Print(s);
	free(s);

	return 123;
}
