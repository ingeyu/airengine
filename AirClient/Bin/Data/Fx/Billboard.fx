struct	VS_INPUT{
	float4	Position	:	POSITION;
};

struct	VS_OUTPUT{
	float4	Position	:	POSITION;
	float2	UV				:	TEXCOORD0;
};

float4	UpDirection;
float4	RightDirection;

float4x4	WorldViewProj;

VS_OUTPUT	MainVS(VS_INPUT	Input){
	VS_OUTPUT	Output;
	
	float3	vPos		=	Input.Position.x*RightDirection.xyz	+	Input.Position.y*UpDirection.xyz;
	
	Output.UV				=	Input.Position.xy*float2(0.5f,-0.5f)	+	float2(0.5f,0.5f);
	
	Output.Position	=	mul(float4(vPos,1),WorldViewProj);
	
	return	Output;
};

float4	PositionArray[100];

VS_OUTPUT	MainVS_Set(VS_INPUT	Input){
	VS_OUTPUT	Output;
	
	float3	vPos		=	Input.Position.x*RightDirection.xyz	+	Input.Position.y*UpDirection.xyz;
	int			iIdx		=	Input.Position.z*100;
	float4	wPos		=	PositionArray[iIdx];
	
	Output.UV				=	Input.Position.xy*float2(0.5f,-0.5f)	+	float2(0.5f,0.5f);
	
	Output.Position	=	mul(float4(vPos+wPos.xyz,1),WorldViewProj);
	
	return	Output;
};

float4x4	TransformArray[5];

float4	Trans(float3	v){
	float	f		=	v.x*4;
	float3	vOldPos	=	v.zyz;
	float4	vPos	=	float4(0,0,0,0);
	if(f<1){
		vPos	+=	mul(float4(vOldPos,1),TransformArray[1])*f;
		vPos	+=	mul(float4(vOldPos,1),TransformArray[0])*(1	-	f);
	}else	if(f	<	2	){
		vPos	+=	mul(float4(vOldPos,1),TransformArray[2])*(f	-	1);
		vPos	+=	mul(float4(vOldPos,1),TransformArray[1])*(2	-	f);
	}else	if(f	<	3){
		vPos	+=	mul(float4(vOldPos,1),TransformArray[3])*(f	-	2);
		vPos	+=	mul(float4(vOldPos,1),TransformArray[2])*(3	-	f);
	}else{
		vPos	+=	mul(float4(vOldPos,1),TransformArray[4])*(f	-	3);
		vPos	+=	mul(float4(vOldPos,1),TransformArray[3])*(4	-	f);
	}
	return	vPos;
};
VS_OUTPUT	MainVS_Strip(VS_INPUT	Input){
	VS_OUTPUT	Output;
	
	float3	vPos		=	Trans(Input.Position.xyz).xyz;
	
	Output.UV				=	Input.Position.xy*float2(1,-1)+float2(0,1);
	
	Output.Position	=	mul(float4(vPos,1),WorldViewProj);
	
	return	Output;
};


texture	DiffTex;
sampler	DiffMap	=
sampler_state
{
    Texture = <DiffTex>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
};

float4	MainPS(VS_OUTPUT	Input)	:	COLOR{

	float4	vColor	=	tex2D(DiffMap,Input.UV);
	
	return	vColor;
}

technique Base
{
   pass Pass_0
   {
			CULLMODE = NONE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS();
   }
}

technique Base_Blend
{
   pass Pass_0
   {
			ALPHATESTENABLE	= FALSE;
			ALPHABLENDENABLE	= TRUE;
    	DESTBLEND					= INVSRCALPHA;
    	SRCBLEND					= SRCALPHA;
    	CULLMODE					= NONE;
    	ZWRITEENABLE 			= FALSE;
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS();
   }
}



technique BaseSet
{
   pass Pass_0
   {
			CULLMODE = NONE;
      VertexShader = compile vs_2_0 MainVS_Set();
      PixelShader = compile ps_2_0 MainPS();
   }
}

technique BaseSet_Blend
{
   pass Pass_0
   {
			ALPHATESTENABLE	= FALSE;
			ALPHABLENDENABLE	= TRUE;
    	DESTBLEND					= INVSRCALPHA;
    	SRCBLEND					= SRCALPHA;
    	CULLMODE					= NONE;
      ZWRITEENABLE 			= FALSE;
      VertexShader = compile vs_2_0 MainVS_Set();
      PixelShader = compile ps_2_0 MainPS();
   }
}


technique BaseStrip
{
   pass Pass_0
   {
			CULLMODE = NONE;
      VertexShader = compile vs_2_0 MainVS_Strip();
      PixelShader = compile ps_2_0 MainPS();
   }
}

technique BaseStrip_Blend
{
   pass Pass_0
   {
			ALPHATESTENABLE	= FALSE;
			ALPHABLENDENABLE	= TRUE;
    	DESTBLEND					= INVSRCALPHA;
    	SRCBLEND					= SRCALPHA;
    	CULLMODE					= NONE;
    	ZWRITEENABLE 			= FALSE;
      VertexShader = compile vs_2_0 MainVS_Strip();
      PixelShader = compile ps_2_0 MainPS();
   }
}
