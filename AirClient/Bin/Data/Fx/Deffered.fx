//延迟作色的FX文件

struct	VS_INPUT{
	float4 Position	:	POSITION0;
};

struct	VS_OUTPUT{
	float4 Position	:	POSITION0;
	float2 UV				:	TEXCOORD0;
};

VS_OUTPUT	MainVS(VS_INPUT Input){
	VS_OUTPUT	Output;
	Output.Position	=	float4(Input.Position.xy,0.0f,1.0f);
	float2 uv   	= sign( Input.Position.xy);
	Output.UV 	= (float2(uv.x, -uv.y) + 1.0f)/2.0f;
	return	Output;
};


texture	PositionTex;	//位置
texture	NormalTex;		//法线XYZ		高光强度W
texture	DiffuseTex;		//漫反射XYZ	自发光W	

sampler2D PositionMap = sampler_state
{
   Texture = (PositionTex);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   MinFilter = Linear;
   MagFilter = Linear;
   MipFilter = Linear;
};
sampler2D NormalMap = sampler_state
{
   Texture = (NormalTex);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   MinFilter = Linear;
   MagFilter = Linear;
   MipFilter = Linear;
};
sampler2D DiffuseMap = sampler_state
{
   Texture = (DiffuseTex);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   MinFilter = Linear;
   MagFilter = Linear;
   MipFilter = Linear;
};

//灯光位置	
float4	LightPosArray[50];
//灯光漫反射
float4	LightDiffArray[50];
//眼睛位置
float4	EyePosition;
//灯光数量
int			iNumLight	=	2;	
//环境光
float4	Ambient		=	float4(0.2,0.2,0.2,1);
//视野投影逆矩阵
float4x4	ViewProjInv;

//计算所有灯光颜色
float4	ComputeLight(	float3	Pos,
											float3	Nor,
											float3	Diff,
											float		Self,
											float		Spec,
											float		fSpecularPower){

	float3	fDiff	=	float3(0,0,0);
	float3	fSpec	=	float3(0,0,0);
	
	for(int i=0;i<iNumLight;i++){
		float3	LightDir;
		float4	LightPos	=	LightPosArray[i];
		float4	LightDiff	=	LightDiffArray[i];
		float		fAttenuation	=	1;
		
		if(LightPos.w	<=	0){
			LightDir			=	normalize(LightPos.xyz);
		}else{
			float	fDis		=	distance(LightPos.xyz,Pos);
			fAttenuation	=	max(1	-	fDis/LightPos.w,0);
			LightDir			=	normalize(LightPos.xyz	-	Pos);
		}
		
		float3	EyeDir	=	normalize(EyePosition.xyz	-	Pos);
		float		fNDotL	=	max(dot(Nor,LightDir),0);
		//return	float4(fNDotL,fNDotL,fNDotL,1);
		
		float3	fvReflection		= 	normalize( ( ( 2.0f * Nor ) * ( fNDotL ) ) - LightDir ); 
		
		fDiff						+=	fNDotL*LightDiff.xyz*fAttenuation;
		fSpec           +=	pow( max( 0.0f, dot( fvReflection, EyeDir ) ),fSpecularPower )*LightDiff.xyz*LightDiff.w;
   
	}
	
	float4	Color	=	float4(Ambient.xyz*Diff	+	Diff*(fDiff+Self)	+	fSpec*Spec,1);
	return	Color;
}

float4	MainPS(VS_OUTPUT	Input):COLOR0{

	float4	Position	=	tex2D( PositionMap, Input.UV );
	float4	Normal		=	tex2D( NormalMap, 	Input.UV );
	float4	Diffuse		=	tex2D( DiffuseMap, 	Input.UV );

	
	
	//return	float4(Diffuse.xyz,1);
	
	float		Spec			=	Normal.w;
	float		Self			=	Diffuse.w;
	float		SpecPower	=	32;
	
	float2	xy		=	Input.UV*float2(2,-2)+float2(-1,1);
	
	float4	pos	=	float4(xy,Position.x,1);
	float4	WPos	=	mul(pos,ViewProjInv);
	WPos.xyz	=	WPos.xyz/WPos.www;

	
	
	float4	Color			=	float4(0,0,0,0);

	float3 normal  	= Normal.xyz*2-1;
	
	//return	float4(WPos.xyz,1);

	
		//计算漫反射 高光
		float4 Light		= ComputeLight(WPos.xyz,normal.xyz,Diffuse.xyz,Self,Spec,SpecPower);
		//计算环境光和反射
		Color = float4(Diffuse.xyz,1)	+	Light;

	return	float4(Light.xyz,1);
	return	float4(Color.xyz,1);
};

technique VeryHighTechnique
{
   pass Pass_0
   {
			CULLMODE = NONE;
	    ZWRITEENABLE = FALSE;
      //ZENABLE = FALSE;
      VertexShader = compile vs_3_0 MainVS();
      PixelShader = compile ps_3_0 MainPS();
   }

}