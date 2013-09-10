struct Vector{
	int x;
	int y;
	int z;
}

__declspec(dllexport)	int main(int iCount,int iStart){
	Vector v[100];
	
	v[3].x=100;
	v[1].y	=	v[3].x;
	return -1;
}