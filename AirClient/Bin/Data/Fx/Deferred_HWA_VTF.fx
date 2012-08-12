//延迟着色下的 骨骼动画 效果文件
	
float4	vDiffuse	=	float4(1,1,1,1);
float4	vSpecular	=	float4(1,1,1,64);

	float4x4 viewProjectionMatrix;
	float4x4 World;
	

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
	oWPosition	=	oPosition;
	
	
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

struct	PS_OUTPUT{
	float4	Depth		:	COLOR0;
	float4	Normal	:	COLOR1;
	float4	Diffuse	:	COLOR2;
};

PS_OUTPUT MainPS(	float3 oNormal		:	NORMAL,
									float3 oTan				:	TANGENT,
									float2 oUV				: TEXCOORD0,
									float4 oWPosition	:	TEXCOORD1)
{
	PS_OUTPUT	Out;
	
	float4	DiffColor	=	tex2D(DiffMap,oUV);
	
	
	Out.Depth		=	float4(oWPosition.z/oWPosition.w,0,0,DiffColor.w);
	Out.Normal	=	float4(oNormal/2+0.5f,vSpecular.x);
	Out.Diffuse	=	vDiffuse*float4(DiffColor.xyz,1);
	
	return	Out;
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

PS_OUTPUT MainPS_Normal(	float3 oNormal		:	NORMAL,
											float3 oTan				:	TANGENT,
											float2 oUV				: TEXCOORD0,
											float4 oWPosition	:	TEXCOORD1)
{
	
	float4	NorColor	=	tex2D(NormMap,oUV);
	NorColor					=	NorColor*2	-	1;
	
	float3 	BiNorm 		= normalize( cross( oNormal, oTan ) );
  float3x3 BTNMatrix = float3x3( BiNorm, oTan, oNormal );
  float3	FinalNorm = normalize( mul( NorColor, BTNMatrix ) ); //world space bump
	
	PS_OUTPUT	Out;
	
	float4	DiffColor	=	tex2D(DiffMap,oUV);
	
	
	Out.Depth		=	float4(oWPosition.z/oWPosition.w,0,0,DiffColor.w);
	Out.Normal	=	float4(FinalNorm/2+0.5f,vSpecular.x);
	Out.Diffuse	=	vDiffuse*float4(DiffColor.xyz,1);
	
	return	Out;
	
};

technique AT
{
	pass p1
	{
		ALPHABLENDENABLE	= FALSE;
		ALPHATESTENABLE		= TRUE;
		CULLMODE					= NONE;
		ZWRITEENABLE		= TRUE;
		ALPHAREF				= 0x10;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS();
	}
}

technique ANT
{
	pass p1
	{
		ALPHABLENDENABLE	= FALSE;
		ALPHAFUNC					= GREATER;
		ALPHATESTENABLE		= TRUE;
		CULLMODE					= NONE;
		ZWRITEENABLE		= TRUE;
		ALPHAREF				= 0x10;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_Normal();
	}
}

technique ANTB
{
	pass p1
	{
		ALPHABLENDENABLE	= FALSE;
		ALPHAFUNC					= GREATER;
		ALPHATESTENABLE		= TRUE;
		CULLMODE					= CW;
		ZWRITEENABLE		= TRUE;
		ALPHAREF				= 0x10;
		VertexShader		= compile vs_3_0 MainVS();
		PixelShader			= compile ps_3_0 MainPS_Normal();
	}
}


