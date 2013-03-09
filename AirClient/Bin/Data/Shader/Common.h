
cbuffer cbPerFrame : register( b0 )
{
	float4	vTime;			///<	x=totaltime t=sin(x) z=cos(x) w= frac(time/(3600*24))
	float4	vAmbient;
	float4	vSunDir;		///<	xyz	=	direction	w	=	lighttype(0,1)
	float4	vSunDiffuse;
	float4	vMainCamPos;
   
}
cbuffer cbPerCamera : register( b1 )
{
    matrix  ViewProjection;
	float4	vCameraDir;
	float4	vCameraPosition;
	float4	vCameraUp;
	float4	vVP_NearFar;
   
}
cbuffer	cbPerObject	:	register(b2)
{
	 matrix  World;
}

cbuffer cbPerSkeleton	:	register(b4)
{
	matrix	BoneMatrix[256];
}