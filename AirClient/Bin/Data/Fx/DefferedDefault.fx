//基本延迟作色 材质效果

float4x4 WorldViewProjection : ViewProjection;
float4x4 World;

float4 fvEyePosition;

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float4 Normal   : NORMAL0;
   float2 Texcoord : TEXCOORD0;
   
};

struct	VS_INPUT_NOR{
	float4 Position : POSITION0;
	float4 Normal   : NORMAL0;
	float2 Texcoord : TEXCOORD0;
	float3 Tan 			: TANGENT;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float3 ViewDirection :   TEXCOORD1;
   float4 WorldNormal   : TEXCOORD2;
   float4	WorldPos			:	TEXCOORD3;
   
};
struct VS_OUTPUT_NOR
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float3 ViewDirection :   TEXCOORD1;
   float4 WorldNormal   : TEXCOORD2;
   float4	WorldPos			:	TEXCOORD3;
   float4	WorldTan			:	TEXCOORD4;
   
};


VS_OUTPUT MainVS( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( Input.Position,WorldViewProjection);
   Output.WorldPos = Output.Position;
   Output.WorldNormal = mul(float4(Input.Normal.xyz,0),World);
   Output.ViewDirection    = fvEyePosition - Output.WorldPos;
   Output.Texcoord = Input.Texcoord;

   return( Output );
   
};
VS_OUTPUT_NOR MainVS_Nor( VS_INPUT_NOR Input )
{
   VS_OUTPUT_NOR Output;

   Output.Position = mul( Input.Position,WorldViewProjection);
   Output.WorldPos = Output.Position;
   Output.WorldNormal = mul(float4(Input.Normal.xyz,0),World);
   Output.WorldTan		=	mul(float4(Input.Tan.xyz,0),World);
   Output.ViewDirection    = fvEyePosition - Output.WorldPos;
   Output.Texcoord = Input.Texcoord;

   return( Output );
   
};




float4 fvSpecular
<
   string UIName = "fvSpecular";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 1, 1, 1, 1.00 );
float4 fvDiffuse
<
   string UIName = "fvDiffuse";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.89, 0.89, 0.89, 1.00 );

struct	PS_OUTPUT{
	float4	WorldPos:			COLOR0;
	float4	WorldNormal:	COLOR1;
	float4	Diffuse:			COLOR2;
};

PS_OUTPUT MainPS( VS_OUTPUT Input ){

	PS_OUTPUT	Out;

	Out.WorldPos						=	float4(Input.WorldPos.z/Input.WorldPos.w,0,0,1);
  Out.WorldNormal         = float4(normalize( Input.WorldNormal.xyz )*0.5f+0.5f,fvSpecular.x);
  Out.Diffuse							=	fvDiffuse;
  return	Out;
   
}

texture	DiffTex;
sampler	DiffMap	=
sampler_state
{
    Texture = <DiffTex>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

PS_OUTPUT MainPS_Diff( VS_OUTPUT Input ){

	PS_OUTPUT	Out;
	
	float4	fvColor					=	tex2D(DiffMap,Input.Texcoord);

	Out.WorldPos						=	float4(Input.WorldPos.z/Input.WorldPos.w,0,0,1);
  Out.WorldNormal         = float4(normalize( Input.WorldNormal.xyz )*0.5f+0.5f,fvSpecular.x);
  Out.Diffuse							=	fvDiffuse*float4(fvColor.xyz,1);
  return	Out;
   
};


texture	SpecTex;
sampler	SpecMap	=
sampler_state
{
    Texture = <SpecTex>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

PS_OUTPUT MainPS_DiffSpec( VS_OUTPUT Input ){

	PS_OUTPUT	Out;
	
	float4	fvColor					=	tex2D(DiffMap,Input.Texcoord);
	float4	fvSpec					=	tex2D(SpecMap,Input.Texcoord);

	Out.WorldPos						=	float4(Input.WorldPos.z/Input.WorldPos.w,0,0,1);
  Out.WorldNormal         = float4(normalize( Input.WorldNormal.xyz )*0.5f+0.5f,fvSpec.x);
  Out.Diffuse							=	fvDiffuse*float4(fvColor.xyz,1);
  return	Out;
   
};

texture	SelfTex;
sampler	SelfMap	=
sampler_state
{
    Texture = <SelfTex>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
PS_OUTPUT MainPS_DiffSpecSelf( VS_OUTPUT Input ){

	PS_OUTPUT	Out;
	
	float4	fvColor					=	tex2D(DiffMap,Input.Texcoord);
	float4	fvSpec					=	tex2D(SpecMap,Input.Texcoord);
	float4	fvSelf					=	tex2D(SelfMap,Input.Texcoord);

	Out.WorldPos						=	float4(Input.WorldPos.z/Input.WorldPos.w,0,0,1);
  Out.WorldNormal         = float4(normalize( Input.WorldNormal.xyz )/2+0.5f,fvSpec.x);
  Out.Diffuse							=	fvDiffuse*float4(fvColor.xyz,fvSelf.x);
  return	Out;
   
};

texture	NormTex;
sampler	NormMap	=
sampler_state
{
    Texture = <NormTex>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};
PS_OUTPUT MainPS_DiffSpecNorm( VS_OUTPUT_NOR Input ){

	PS_OUTPUT	Out;
	
	float4	fvColor					=	tex2D(DiffMap,Input.Texcoord);
	float4	fvSpec					=	tex2D(SpecMap,Input.Texcoord);
	float4	fvNorm					=	tex2D(NormMap,Input.Texcoord);
	
	float3	wNor						=	normalize(Input.WorldNormal.xyz);
	float3	wTan						=	normalize(Input.WorldTan.xyz);
	
	float3	normal					=	(2*fvNorm.xyz)-1;
	
	float3 	BiNorm 		= normalize( cross( wNor, wTan ) );
  float3x3 BTNMatrix = float3x3( wTan, BiNorm, wNor );
  float3	FinalNorm = normalize( mul( normal, BTNMatrix ) ); //world space bump

	Out.WorldPos						=	float4(Input.WorldPos.z/Input.WorldPos.w,0,0,1);
  Out.WorldNormal         = float4(FinalNorm/2+0.5f,fvSpec.x);
  Out.Diffuse							=	fvDiffuse*float4(fvColor.xyz,1);
  return	Out;
   
};

PS_OUTPUT MainPS_DiffSpecSelfNorm( VS_OUTPUT_NOR Input ){

	PS_OUTPUT	Out;
	
	float4	fvColor					=	tex2D(DiffMap,Input.Texcoord);
	float4	fvSpec					=	tex2D(SpecMap,Input.Texcoord);
	float4	fvSelf					=	tex2D(SelfMap,Input.Texcoord);
	float4	fvNorm					=	tex2D(NormMap,Input.Texcoord);
	
	float3	wNor						=	normalize(Input.WorldNormal.xyz);
	float3	wTan						=	normalize(Input.WorldTan.xyz);
	
	float3	normal					=	(2*fvNorm.xyz)-1;
	
	float3 	BiNorm 		= normalize( cross( wNor, wTan ) );
  float3x3 BTNMatrix = float3x3( wTan, BiNorm, wNor );
  float3	FinalNorm = normalize( mul( normal, BTNMatrix ) ); //world space bump

	Out.WorldPos						=	float4(Input.WorldPos.z/Input.WorldPos.w,0,0,1);
  Out.WorldNormal         = float4(FinalNorm/2+0.5f,fvSpec.x);
  Out.Diffuse							=	fvDiffuse*float4(fvColor.xyz,fvSelf.x);
  return	Out;
   
};
texture	ReflTex;
samplerCUBE	ReflMap	=
sampler_state
{
    Texture = <ReflTex>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

PS_OUTPUT MainPS_DiffSpecSelfNormRefl( VS_OUTPUT_NOR Input ){

	PS_OUTPUT	Out;
	
	float4	fvColor					=	tex2D( DiffMap,Input.Texcoord);
	float4	fvSpec					=	tex2D( SpecMap,Input.Texcoord);
	float4	fvNorm					=	tex2D( NormMap,Input.Texcoord);
	float4	fvSelf					=	tex2D( SelfMap,Input.Texcoord);
	
	float3	wNor						=	normalize(Input.WorldNormal.xyz);
	float3	wTan						=	normalize(Input.WorldTan.xyz);
	
	float3	normal					=	(2*fvNorm.xyz)-1;
	
	float3 	BiNorm 		= normalize( cross( wNor, wTan ) );
  float3x3 BTNMatrix = float3x3( wTan, BiNorm, wNor );
  float3	FinalNorm = normalize( mul( normal, BTNMatrix ) ); //world space bump
  
  float3	EyeDir					=	normalize(fvEyePosition.xyz	-	Input.WorldPos.xyz);
  float3	ReflDir					=	2*FinalNorm	-	EyeDir;
  float4	fvRefl					=	texCUBE(	ReflMap,ReflDir);

	Out.WorldPos						=	float4(Input.WorldPos.z/Input.WorldPos.w,0,0,1);
  Out.WorldNormal         = float4(FinalNorm/2+0.5f,fvSpec.x);
  Out.Diffuse							=	fvDiffuse*float4(fvColor.xyz,fvSelf.x);
  return	Out;
   
};

technique NoTexture
{
	pass p0
	{

    CULLMODE				= NONE;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS();
	}
}

technique DiffTexture
{
	pass p0
	{

    CULLMODE				= NONE;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_Diff();
	}
}

technique DiffSpecTexture
{
	pass p0
	{

    CULLMODE				= NONE;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_DiffSpec();
	}
}

technique DiffSpecSelfTexture
{
	pass p0
	{

    CULLMODE				= NONE;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_DiffSpecSelf();
	}
}

technique DiffSpecNorm
{
	pass p0
	{

    CULLMODE				= NONE;
		VertexShader		= compile vs_3_0 MainVS_Nor();
		PixelShader			= compile ps_3_0 MainPS_DiffSpecNorm();
	}
}

technique DSSN
{
	pass p0
	{

    CULLMODE				= NONE;
		VertexShader		= compile vs_3_0 MainVS_Nor();
		PixelShader			= compile ps_3_0 MainPS_DiffSpecSelfNorm();
	}
}

technique DSSNR
{
	pass p0
	{

    CULLMODE				= NONE;
		VertexShader		= compile vs_3_0 MainVS_Nor();
		PixelShader			= compile ps_3_0 MainPS_DiffSpecSelfNormRefl();
	}
}

