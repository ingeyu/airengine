__declspec(dllimport)	void Print(const char* str);
__declspec(dllimport)	void*	malloc(int	uiSize);
struct Vector3{
	float x;
	float y;
	float z;
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
/*
struct Vector4	:	public	Vector3{
	virtual	~Vector4(){

	};
	virtual	void	Add(){
		Print("Vector4::Add");
	}
};
*/

__declspec(dllexport)	int main(int iCount,int iStart){
	Vector3 v;
	v.Add();
	Vector3* pV =	NULL;
	pV	=	new Vector3();
	pV->Add();
	return 0;
}
