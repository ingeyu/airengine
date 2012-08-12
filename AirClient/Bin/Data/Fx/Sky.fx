
float4   vViewPosition;
float4   fvAmibent;
float4x4 matViewProjection;


struct VS_INPUT 
{
   float3 Pos:    POSITION;
};

struct VS_OUTPUT 
{
   float4 Pos:       POSITION;
   float3 TexCoord : TEXCOORD0;
};

VS_OUTPUT MainVS( VS_INPUT In )
{
   VS_OUTPUT Out;
   
   float3 pos = In.Pos*float3(200.0f,200.0f,200.0f)	+	vViewPosition.xyz;
   Out.Pos = mul(float4(pos,1.0),matViewProjection);
   Out.TexCoord = normalize(In.Pos);

   return Out;
};

struct	VS_OUTPUT_DEFFERED{
   float4 Pos:       POSITION;
   float3 TexCoord : TEXCOORD0;
   float4	WorldPos	:TEXCOORD1;
};

VS_OUTPUT_DEFFERED MainVS_Deffered( VS_INPUT In )
{
   VS_OUTPUT_DEFFERED Out;
   
   float3 pos = In.Pos*float3(200.0f,200.0f,200.0f)	+	vViewPosition.xyz;
   Out.Pos = mul(float4(pos,1.0),matViewProjection);
   Out.TexCoord = normalize(In.Pos);
   Out.WorldPos	=	float4(Out.Pos.z/Out.Pos.w,0,0,1);

   return Out;
};

texture diffTex
<
   string ResourceName = "..\\..\\..\\..\\..\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Snow.dds";
>;
samplerCUBE EnvironmentMap = sampler_state
{
   Texture = (diffTex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
   MIPFILTER = LINEAR;
};

struct PS_INPUT 
{
   float3 TexCoord : TEXCOORD0;
};

struct PS_OUTPUT 
{
   float4 Color : COLOR;
};

PS_OUTPUT MainPS( PS_INPUT In )
{
   PS_OUTPUT Out;
   
   Out.Color = texCUBE(EnvironmentMap,In.TexCoord)*fvAmibent;
   
   return Out;
}

struct	PS_OUTPUT_DEFFERED{
	float4	WorldPos:			COLOR0;
	float4	WorldNormal:	COLOR1;
	float4	Diffuse:			COLOR2;

};

PS_OUTPUT_DEFFERED MainPS_Deffered( VS_OUTPUT_DEFFERED In )
{
   PS_OUTPUT_DEFFERED Out;
   float4	color	=	texCUBE(EnvironmentMap,In.TexCoord)*fvAmibent;
   Out.WorldPos	=	In.WorldPos;
   Out.WorldNormal	=	float4(normalize(In.TexCoord),0);
   Out.Diffuse	=	float4(color.xyz,1);

   
   return Out;
}



technique VeryHighTechnique
{
   pass Environment
   {
      CULLMODE = NONE;

      VertexShader = compile vs_3_0 MainVS_Deffered();
      PixelShader = compile ps_3_0 MainPS_Deffered();
   }
}

technique HightTechnique
{
   pass Environment
   {
      CULLMODE = NONE;

      VertexShader = compile vs_3_0 MainVS();
      PixelShader = compile ps_3_0 MainPS();
   }
}