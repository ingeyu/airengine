//最终渲染到屏幕的FX文件

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
	float2 uv   	= sign( Input.Position);
	Output.UV 	= (float2(uv.x, -uv.y) + 1.0f)/2.0f;
	return	Output;
};

texture InputTexture
<
   string ResourceName = "InputTexture.tga";
>;
sampler2D DiffMap = sampler_state
{
   Texture = (InputTexture);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   MinFilter = Linear;
   MagFilter = Linear;
   MipFilter = Linear;
};

float4	MainPS(VS_OUTPUT	Input):COLOR0{
	//return float4(1,0,1,1);
	return	tex2D( DiffMap, Input.UV );
};

float 	fTotalTime		=	0;
float4	vPositionSize	=	float4(0,0,1,1);
float4	vPercent			=	float4(0,0,0,0);

VS_OUTPUT	MainVS_Loading(VS_INPUT Input){
	VS_OUTPUT	Output;
	Output.Position	=	float4(Input.Position.xy*vPositionSize.zw+vPositionSize.xy,0.0f,1.0f);
	float2 uv   	= sign( Input.Position);
	Output.UV 	= (float2(uv.x, -uv.y) + 1.0f)/2.0f;
	return	Output;
};

float4	MainPS_Loading(VS_OUTPUT	Input): COLOR0{
	float	f	=	sin(-fTotalTime+Input.UV.x*40)/8+1.0f;
	float4	vColor	=	tex2D( DiffMap, Input.UV )*f;
	if(Input.UV.x	>	vPercent.x){
		return	float4(vColor.xxx,vColor.w/2);
	}else{
		return	vColor;
	}
};

technique VeryHighTechnique
{
   pass Pass_0
   {
	CULLMODE = NONE;
	
      VertexShader = compile vs_2_0 MainVS();
      PixelShader = compile ps_2_0 MainPS();
   }

}

technique Alpha
{
	pass
	{
		ALPHABLENDENABLE = TRUE;
    DESTBLEND = INVSRCALPHA;
    SRCBLEND = SRCALPHA;
		VertexShader = compile vs_2_0 MainVS();
		PixelShader = compile ps_2_0 MainPS();
	}
}

technique Loading
{
	pass
	{
		ALPHABLENDENABLE = TRUE;
    DESTBLEND = INVSRCALPHA;
    SRCBLEND = SRCALPHA;
		VertexShader = compile vs_2_0 MainVS_Loading();
		PixelShader = compile ps_2_0 MainPS_Loading();
	}
}


