#define MAXBONES 80

	// Support up to 24 bones of float3x4
	// vs_1_1 only supports 96 params so more than this is not feasible
	float4x4 viewProjectionMatrix;
	float4x4 World;

	//light
	float4	LightPos	=	float4(400,400,-400,1);
	float4	LightDiff	=	float4(1,1,1,1);
	float4	EyePos		=	float4(100,200,250,1);
	float4	Ambient		=	float4(0.5,0.5,0.5,1);
	
	float4	vDiffuse	=	float4(1,1,1,1);
	float4	vSpecular	=	float4(1,1,1,64);

	texture Bone;
sampler BoneMap =
sampler_state
{
    Texture = <Bone>;
    //MinFilter = Linear;
    //MagFilter = Linear;
    //MipFilter = Linear;
};

float4x4 GetBoneMatrix(int idx){
	float4 v[4];
	v[0]	=	tex2Dlod(BoneMap,float4((idx*4		+0.5f)/1024,0,0,0));
	v[1]	=	tex2Dlod(BoneMap,float4((idx*4 + 1	+0.5f)/1024,0,0,0));
	v[2]	=	tex2Dlod(BoneMap,float4((idx*4 + 2	+0.5f)/1024,0,0,0));
	v[3]	=	tex2Dlod(BoneMap,float4((idx*4 + 3	+0.5f)/1024,0,0,0));
	
	return float4x4(v[0],v[1],v[2],v[3]);
};

/*
  Four-weight-per-vertex hardware skinning, 2 lights
  The trouble with vertex programs is they're not general purpose, but
  fixed function hardware skinning is very poorly supported
*/
void MainVS(
	float4 position		: POSITION,
	float4 blendWgt		: BLENDWEIGHT,
	float4 blendIdx		: BLENDINDICES,
	float3 normal			: NORMAL,
	float2 uv					: TEXCOORD0,
	float3 Tan 				: TANGENT,

	

	out float4 oPosition 	: POSITION,
	out float3 oNormal		:	NORMAL,
	out	float3 oTan				:	TANGENT,
	out float2 oUV				: TEXCOORD0,
	out	float4 oWPosition	:	TEXCOORD1)
{
	float4x4 boneMatrix[4];
	boneMatrix[0]	=	GetBoneMatrix(blendIdx[0]);
	boneMatrix[1]	=	GetBoneMatrix(blendIdx[1]);
	boneMatrix[2]	=	GetBoneMatrix(blendIdx[2]);
	boneMatrix[3]	=	GetBoneMatrix(blendIdx[3]);
	

		float4 blendPos = float4(0,0,0,0);
		blendPos += float4(mul(position,boneMatrix[0]).xyz,1.0f)* blendWgt[0];
 		blendPos += float4(mul(position,boneMatrix[1]).xyz,1.0f)* blendWgt[1];
 		blendPos += float4(mul(position,boneMatrix[2]).xyz,1.0f)* blendWgt[2];
 		blendPos += float4(mul(position,boneMatrix[3]).xyz,1.0f)* blendWgt[3];

		float3 norm = float3(0,0,0);
		norm += mul(normal.xyz,(float3x3)boneMatrix[0]) * blendWgt[0];
		norm += mul(normal.xyz,(float3x3)boneMatrix[1]) * blendWgt[1];
		norm += mul(normal.xyz,(float3x3)boneMatrix[2]) * blendWgt[2];
		norm += mul(normal.xyz,(float3x3)boneMatrix[3]) * blendWgt[3];
		norm = normalize(norm);
		
		float3	tangent	=	float3(0,0,0);
		tangent += mul(Tan.xyz,(float3x3)boneMatrix[0]) * blendWgt[0];
		tangent += mul(Tan.xyz,(float3x3)boneMatrix[1]) * blendWgt[1];
		tangent += mul(Tan.xyz,(float3x3)boneMatrix[2]) * blendWgt[2];
		tangent += mul(Tan.xyz,(float3x3)boneMatrix[3]) * blendWgt[3];
		
	float4 tPos	=	mul(blendPos.xzyw,World);
	oPosition 	= mul(tPos,viewProjectionMatrix);
	oNormal			=	normalize(mul(norm.xzy,(float3x3)World));
	oTan				=	normalize(mul(tangent.xzy,(float3x3)World));
	oUV 				= uv;
	oWPosition	=	tPos;
	
	
};


texture Diff;
sampler DiffMap =
sampler_state
{
    Texture = <Diff>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

float4 MainPS(	float3 oNormal		:	NORMAL,
								float3 oTan				:	TANGENT,
								float2 oUV				: TEXCOORD0,
								float4 oWPosition	:	TEXCOORD1):COLOR0
{
	float4	InputSpec				=	float4(vSpecular.xyz,1);
	float		InputSpecPower	=	vSpecular.w;
	float4	DiffColor	=	tex2D(DiffMap,oUV);

	float3	LightDir	=	normalize(LightPos.xyz	-	oWPosition.xyz);
	float3	EyeDir		=	normalize(EyePos.xyz		-	oWPosition.xyz);
	
	//diffuse lighting
	float4 	Diffuse = saturate( dot( LightDir, oNormal ) )*LightDiff;

  // Calculate specular power
  float3 	halfAngle = normalize( EyeDir + LightDir );
  float4 	spec 			= pow( saturate(dot( halfAngle, oNormal )), InputSpecPower );
  float4	Specular	=	spec*LightDiff*DiffColor.w;
  
  
  // Return combined lighting
  return (Ambient	+	Diffuse*vDiffuse + Specular*InputSpec)*DiffColor;
};



texture	Norm;
sampler NormMap =
sampler_state
{
    Texture = <Norm>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

float4 MainPS_Normal(	float3 oNormal		:	NORMAL,
											float3 oTan				:	TANGENT,
											float2 oUV				: TEXCOORD0,
											float4 oWPosition	:	TEXCOORD1):COLOR0
{
	float4	InputSpec				=	float4(vSpecular.xyz,1);
	float		InputSpecPower	=	vSpecular.w;
	
	float3	LightDir	=	normalize(LightPos.xyz	-	oWPosition.xyz);
	float3	EyeDir		=	normalize(EyePos.xyz		-	oWPosition.xyz);
	
	float4	NorColor	=	tex2D(NormMap,oUV);
	NorColor					=	NorColor*2	-	1;
	
	float3 	BiNorm 		= normalize( cross( oNormal, oTan ) );
  float3x3 BTNMatrix = float3x3( BiNorm, oTan, oNormal );
  float3	FinalNorm = normalize( mul( NorColor, BTNMatrix ) ); //world space bump
	
	//diffuse lighting
	float4 	Diffuse = saturate( dot( LightDir, FinalNorm ) )*LightDiff;

  // Calculate specular power
  float3 	halfAngle = normalize( EyeDir + LightDir );
  float4 	spec 			= pow( saturate(dot( halfAngle, FinalNorm )), InputSpecPower );
  float4	Specular	=	spec*LightDiff;
  
  float4	DiffColor	=	tex2D(DiffMap,oUV);
  // Return combined lighting
  return (Ambient	+	Diffuse*vDiffuse + Specular*InputSpec)*DiffColor;
};

technique AlphaTechnique
{
	pass p0
	{
		ALPHABLENDENABLE	= FALSE;
		ALPHABLENDENABLE	= TRUE;
    DESTBLEND					= INVSRCALPHA;
    SRCBLEND					= SRCALPHA;
    CULLMODE				= NONE;
    ZWRITEENABLE		= FALSE;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS();
	}
	pass p1
	{
		ALPHABLENDENABLE	= FALSE;
		DESTBLEND					= ONE;
    SRCBLEND					= ZERO;
		ALPHAFUNC					= GREATER;
		ALPHATESTENABLE		= TRUE;
		CULLMODE					= NONE;
		ZWRITEENABLE		= TRUE;
		ALPHAREF				= 0xF0;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS();
	}
}

technique AlphaNormalTechnique
{
	pass p0
	{
		ALPHABLENDENABLE	= FALSE;
		ALPHABLENDENABLE	= TRUE;
    DESTBLEND					= INVSRCALPHA;
    SRCBLEND					= SRCALPHA;
    CULLMODE				= NONE;
    ZWRITEENABLE		= FALSE;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_Normal();
	}
	pass p1
	{
		ALPHABLENDENABLE	= FALSE;
		DESTBLEND					= ONE;
    SRCBLEND					= ZERO;
		ALPHAFUNC					= GREATER;
		ALPHATESTENABLE		= TRUE;
		CULLMODE					= NONE;
		ZWRITEENABLE		= TRUE;
		ALPHAREF				= 0xF0;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_Normal();
	}
}

technique AlphaNormalTechnique_CB
{
	pass p0
	{
		ALPHABLENDENABLE	= FALSE;
		ALPHABLENDENABLE	= TRUE;
    DESTBLEND					= INVSRCALPHA;
    SRCBLEND					= SRCALPHA;
    CULLMODE				= CW;
    ZWRITEENABLE		= FALSE;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_Normal();
	}
	pass p1
	{
		ALPHABLENDENABLE	= FALSE;
		DESTBLEND					= ONE;
    SRCBLEND					= ZERO;
		ALPHAFUNC					= GREATER;
		ALPHATESTENABLE		= TRUE;
		CULLMODE					= CW;
		ZWRITEENABLE		= TRUE;
		ALPHAREF				= 0xF0;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_Normal();
	}
}


