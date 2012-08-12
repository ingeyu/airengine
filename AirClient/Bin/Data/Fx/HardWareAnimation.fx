#define MAXBONES 60


	// Support up to 24 bones of float3x4
	// vs_1_1 only supports 96 params so more than this is not feasible
float4x4 World;
float4x4 ViewProj;
float4   lightDir	=	float4(1,1,1,1);
float4   lightDiffuseColour	=	float4(1,1,1,1);
float4   ambient	=	float4(0.2,0.2,0.2,1);
float4x4 BoneMatrixArray[MAXBONES];

/*
  Four-weight-per-vertex hardware skinning, 2 lights
  The trouble with vertex programs is they're not general purpose, but
  fixed function hardware skinning is very poorly supported
*/
void MainVS(
	float4 position		: POSITION,
	float4 blendWgt		: BLENDWEIGHT,
	float4 blendIdx		: BLENDINDICES,
	float3 normal		  : NORMAL,
	float2 uv					: TEXCOORD0,

	out float4 oPosition : POSITION,
	out float2 oUv       : TEXCOORD0,
	out float4 colour    : COLOR)
{
	// transform by indexed matrix
	float4 blendPos = float4(0,0,0,0);
	for (int i = 0; i < 4; ++i)
	{
		blendPos += mul(position,BoneMatrixArray[blendIdx[i]]) * blendWgt[i];
	}
	//blendPos.w = 1;
	// view / projection
	float4 tPos	=	mul(blendPos.xzyw,World);
	oPosition 	= mul(tPos,ViewProj);
	// transform normal
	float3 norm = float3(0,0,0);
	for (i = 0; i < 4; ++i)
	{
		norm += mul(normal.xyz,(float3x3)BoneMatrixArray[blendIdx[i]]) * blendWgt[i];
	}
	norm = normalize(norm);
	float3 n	=	mul(norm.xzy,(float3x3)World);


	
	oUv = uv;
	normalize(lightDir);
	normalize(n);
	colour = ambient + (saturate(dot(lightDir, n)) * lightDiffuseColour);
	
};

texture DiffuseTexture
<
    string ResourceName = "Default_color.dds";
    string UIName =  "Âþ·´ÉäÎÆÀí";
    string ResourceType = "2D";
>;
sampler2D DiffMap = sampler_state
{
   Texture = (DiffuseTexture);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   MinFilter = Linear;
   MagFilter = Linear;
   MipFilter = Linear;
};
float4 MainPS(float2 oUv       : TEXCOORD0,
							float4 colour    : COLOR):COLOR0
{
	return	tex2D(DiffMap,oUv);
};

//--------------------------------------------------------------//
// Technique Section for Textured
//--------------------------------------------------------------//
technique VeryHighTechnique
{
   pass p0
   {
			CULLMODE = NONE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS();
   }

}