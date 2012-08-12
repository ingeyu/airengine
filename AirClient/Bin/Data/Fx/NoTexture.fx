
//--------------------------------------------------------------//
// Textured
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Textured_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 WorldViewProjection : ViewProjection;
float4x4 World;

float3 fvLightPosition
<
   string UIName = "fvLightPosition";
   string UIWidget = "Numeric";
   bool UIVisible =  true;
   float UIMin = -100.00;
   float UIMax = 100.00;
> = float3( 30.00, -30.00, 30.00 );
float3 fvEyePosition
<
   string UIName = "fvEyePosition";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -100.00;
   float UIMax = 100.00;
> = float3( 30.00, -30.00, 30.00 );

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float4 Normal   : NORMAL0;
   float2 Texcoord : TEXCOORD0;
   
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   float4 Normal   : TEXCOORD1;
   float3 ViewDirection :   TEXCOORD2;
   float3 LightDirection :  TEXCOORD3;
   float4 WorldNormal   : TEXCOORD4;
   
};

VS_OUTPUT MainVS( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( Input.Position,WorldViewProjection);
   //Output.Position = mul( WorldViewProjection,Input.Position );
   Output.Normal   = mul( Input.Normal, WorldViewProjection);
   float4 WorldPos = mul(Input.Position,World);
   Output.WorldNormal = mul(float4(Input.Normal.xyz,0),World);
   Output.ViewDirection    = fvEyePosition - WorldPos;
   Output.LightDirection   = fvLightPosition - WorldPos;

   Output.Texcoord = Input.Texcoord;

   return( Output );
   
}

float4 fvAmbient
<
   string UIName = "fvAmbient";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.4, 0.4, 0.4, 1.00 );
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
float fSpecularPower
<
   string UIName = "fSpecularPower";
   string UIWidget = "Numeric";
   bool UIVisible =  true;
   float UIMin = 1.00;
   float UIMax = 100.00;
> = float( 16.00 );



float4 MainPS( VS_OUTPUT Input ) : COLOR0
{
 //  return tex2D( DiffMap, Input.Texcoord );

   float3 fvLightDirection = normalize( Input.LightDirection );
   float3 fvNormal         = normalize( Input.WorldNormal );
   float  fNDotL           = dot( fvNormal, fvLightDirection ); 
   
   float3 fvReflection     = normalize( ( ( 2.0f * fvNormal ) * ( fNDotL ) ) - fvLightDirection ); 
   float3 fvViewDirection  = normalize( Input.ViewDirection );
   float  fRDotV           = max( 0.0f, dot( fvReflection, fvViewDirection ) );
   
   float4 fvBaseColor      = float4(1,1,1,1);//tex2D( DiffMap, Input.Texcoord );
   
   float4 fvTotalAmbient   = fvAmbient * fvBaseColor; 
   float4 fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor; 
   float4 fvTotalSpecular  = fvSpecular * pow( fRDotV, fSpecularPower );
   
   return ( saturate( fvTotalAmbient + fvTotalDiffuse + fvTotalSpecular ) );
   
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


float4 MainPS_Diff( VS_OUTPUT Input ) : SV_Target
{
 //  return tex2D( DiffMap, Input.Texcoord );

   float3 fvLightDirection = normalize( Input.LightDirection );
   float3 fvNormal         = normalize( Input.WorldNormal );
   float  fNDotL           = dot( fvNormal, fvLightDirection ); 
   
   float3 fvReflection     = normalize( ( ( 2.0f * fvNormal ) * ( fNDotL ) ) - fvLightDirection ); 
   float3 fvViewDirection  = normalize( Input.ViewDirection );
   float  fRDotV           = max( 0.0f, dot( fvReflection, fvViewDirection ) );
   
   float4 fvBaseColor      = tex2D( DiffMap, Input.Texcoord );
   
   float4 fvTotalAmbient   = fvAmbient * fvBaseColor; 
   float4 fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor; 
   float4 fvTotalSpecular  = fvSpecular * pow( fRDotV, fSpecularPower );
   
   return ( saturate( fvTotalAmbient + fvTotalDiffuse + fvTotalSpecular ) );
   
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

float4 MainPS_DiffSpec( VS_OUTPUT Input ) : SV_Target
{
 //  return tex2D( DiffMap, Input.Texcoord );

   float3 fvLightDirection = normalize( Input.LightDirection );
   float3 fvNormal         = normalize( Input.WorldNormal );
   float  fNDotL           = dot( fvNormal, fvLightDirection ); 
   
   float3 fvReflection     = normalize( ( ( 2.0f * fvNormal ) * ( fNDotL ) ) - fvLightDirection ); 
   float3 fvViewDirection  = normalize( Input.ViewDirection );
   float  fRDotV           = max( 0.0f, dot( fvReflection, fvViewDirection ) );
   
   float4 fvBaseColor      = tex2D( DiffMap, Input.Texcoord );
   float4	fvSpecColor			 = tex2D( SpecMap, Input.Texcoord );
   
   float4 fvTotalAmbient   = fvAmbient * fvBaseColor; 
   float4 fvTotalDiffuse   = fvDiffuse * fNDotL * fvBaseColor; 
   float4 fvTotalSpecular  = fvSpecular * pow( fRDotV, fSpecularPower )*fvSpecColor.x;
   
   return ( saturate( fvTotalAmbient + fvTotalDiffuse + fvTotalSpecular ) );
   
};



//--------------------------------------------------------------//
// Technique Section for Textured
//--------------------------------------------------------------//
technique VeryHighTechnique
{
   pass Pass_0
   {
			CULLMODE = NONE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS();
   }
}

technique DiffTechnique
{
   pass Pass_0
   {
			CULLMODE = NONE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS_Diff();
   }
}
technique DiffAlphaTestTechnique
{
   pass Pass_0
   {
			CULLMODE = NONE;
			ALPHATESTENABLE	=	TRUE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS_Diff();
   }
}
technique DiffAlphaBlendTechnique
{
   pass Pass_0
   {
			ALPHATESTENABLE	= FALSE;
			ALPHABLENDENABLE	= TRUE;
    	DESTBLEND					= INVSRCALPHA;
    	SRCBLEND					= SRCALPHA;
    	CULLMODE					= NONE;
      VertexShader 			= compile vs_2_0 MainVS();
      PixelShader 			= compile ps_2_0 MainPS_Diff();
   }
}

technique DiffSpecTechnique
{
   pass Pass_0
   {
			CULLMODE = NONE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS_DiffSpec();
   }
}

technique DiffSpecAlphaTestTechnique
{
   pass Pass_0
   {
			CULLMODE = NONE;
			ALPHATESTENABLE	=	TRUE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS_DiffSpec();
   }
}

technique DiffSpecAlphaBlendTechnique
{
   pass Pass_0
   {
			ALPHATESTENABLE	= FALSE;
			ALPHABLENDENABLE	= TRUE;
    	DESTBLEND					= INVSRCALPHA;
    	SRCBLEND					= SRCALPHA;
    	CULLMODE					= NONE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS_DiffSpec();
   }
}



