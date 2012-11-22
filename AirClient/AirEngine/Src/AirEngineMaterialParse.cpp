#include "AirEngineMaterialParse.h"
#include "AirCommonParse.h"
#include "AirGlobalSetting.h"

namespace Air{
	
	namespace	Client{

		template<typename T0,typename T1>
		T1	GetElement(const std::map<T0,T1>& m,const T0& key){
			std::map<T0,T1>::const_iterator	i	=	m.find(key);
			if(i!=m.end())
				return	i->second;
			return	(T1)0;
		};

		//namespace	Render{
		using namespace Render;
	
	
	#ifndef	INSERT_PARAM_TYPE
	#define INSERT_PARAM_TYPE(strName,uiParamType)	m_mapParamBindType[strName]	=	uiParamType;
	#endif
			/**	\brief	解析浮点数
			*   
			*	@remarks 	解析浮点数
			*	@see		
			*	@return   	Real
			*	@param		StringVector & vecWord
			*	@param		U32 & i
			*	@note
			*
			**/
			Real	ParseReal(StringVector& vecWord,U32& i){
				Real	f	=	0.0f;
				if(vecWord[i+1]	==	"."){
					f	=	Converter::ToFloat(vecWord[i]	+	vecWord[i+1]	+	vecWord[i+2]);
					i	+=	3;
				}else{
					f	=	Converter::ToFloat(vecWord[i++]);
				}
				return	f;
			};
	
			AString	String2String(const AString&	str){
				AString	strRet;
				strRet.resize(str.size()-2);
				memcpy(&strRet[0],&str[1],str.size()-2);
				return	strRet;
			};
	
	
	
			MaterialParse::MaterialParse(){
				//材质部分枚举
				m_mapParam["Material"]				=	enMaterial;
				m_mapParam["Vector"]				=	enVector;
				m_mapParam["Matrix"]				=	enMatrix;
				m_mapParam["VectorArray"]			=	enVectorArray;
				m_mapParam["MatrixArray"]			=	enMatrixArray;
				m_mapParam["UseSkin"]				=	enUseSkin;

				m_mapParam["MaterialTemplate"]		=	enMaterialTemplate;
				m_mapParam["Phase"]					=	enPhase;
				m_mapParam["Priority"]				=	enPriority;
				m_mapParam["Pass"]					=	enPass;
				m_mapParam["VertexShader"]			=	enVertexShader;
				m_mapParam["Texture"]				=	enTexture;
				m_mapParam["TextureIndex"]			=	enTextureIndex;
				m_mapParam["SamplerState"]			=	enSamplerState;
				m_mapParam["Filter"]				=	enTextureFilter;
				m_mapParam["Address"]				=	enTextureAddress;

				m_mapParam["GeometryShader"]		=	enGeometryShader;
				m_mapParam["PixelShader"]			=	enPixelShader;
				m_mapParam["HullShader"]			=	enHullShader;
				m_mapParam["ComputeShader"]			=	enComputeShader;
				m_mapParam["DomainShader"]			=	enDomainShader;
				m_mapParam["RasterizerState"]		=	enRasterizerState;
				m_mapParam["FillMode"]				=	enFillMode;
				m_mapParam["CullMode"]				=	enCullMode;
				m_mapParam["DepthBias"]				=	enDepthBias;
				m_mapParam["DepthBiasClamp"]		=	enDepthBiasClamp;
				m_mapParam["SlopeScaledDepthBias"]	=	enSlopeScaledDepthBias;
				m_mapParam["DepthClipEnable"]		=	enDepthClipEnable;
				m_mapParam["ScissorEnable"]			=	enScissorEnable;
				m_mapParam["MultiSampleEnable"]		=	enMultisampleEnable;
				m_mapParam["AntialiasedLineEnable"]	=	enAntialiasedLineEnable;
				m_mapParam["BlendState"]			=	enBlendState;
				m_mapParam["AlphaToCoverage"]		=	enAlphaToCoverage;
				m_mapParam["IndepenndentBlend"]		=	enIndependentBlend;
				m_mapParam["RendertargetBlend"]		=	enRenderTargetBlend;
				m_mapParam["BlendEnable"]			=	enBlendEnable;
				m_mapParam["SrcBlend"]				=	enSrcBlend;
				m_mapParam["DestBlend"]				=	enDestBlend;
				m_mapParam["BlendOp"]				=	enBlendOP;
				m_mapParam["SrcBlendAlpha"]			=	enSrcBlendAlpha;
				m_mapParam["DestBlendAlpha"]		=	enDestBlendAlpha;
				m_mapParam["BlendOpAlpha"]			=	enBlendOpAlpha;
				m_mapParam["RenderTargetWriteMask"]	=	enRenderTargetWriteMask;
				m_mapParam["DepthStencilState"]		=	enDepthState;
				m_mapParam["DepthEnable"]			=	enDepthEnable;
				m_mapParam["DepthWriteMask"]		=	enDepthWriteMask;
				m_mapParam["DepthFunc"]				=	enDepthFunc;
				m_mapParam["StencilEnable"]			=	enStencilEnable;
				m_mapParam["StencilReadMask"]		=	enStencilReadMask;
				m_mapParam["StencilWriteMask"]		=	enStencilWriteMask;
				m_mapParam["FrontFace"]				=	enFrontFace;
				m_mapParam["StencilFailOp"]			=	enStencilFailOp;
				m_mapParam["StencilDepthfailOp"]	=	enStencilDepthFailOp;
				m_mapParam["StencilFunc"]			=	enStencilPassOp;
				m_mapParam["StencilFunc"]			=	enStencilFunc;
				m_mapParam["BackFace"]				=	enBackFace;



				m_mapPhaseIndex["Reflect"]		=		enPI_Reflect;
				m_mapPhaseIndex["Shadow"]		=		enPI_Shadow;
				m_mapPhaseIndex["MRT"]			=		enPI_MRT;
				m_mapPhaseIndex["SSAO"]			=		enPI_SSAO;
				m_mapPhaseIndex["GI"]			=		enPI_GI;
				m_mapPhaseIndex["DeferredLight"]=		enPI_DeferredLight;
				m_mapPhaseIndex["Alpha"]		=		enPI_Alpha;
				m_mapPhaseIndex["PostComposer"]	=		enPI_PostComposer;
				m_mapPhaseIndex["Helper"]		=		enPI_Helper;
				m_mapPhaseIndex["UI"]			=		enPI_UI;
				m_mapPhaseIndex["Overlay"]		=		enPI_Overlay;
				m_mapPhaseIndex["HardwareOcc"]	=		enPI_HardwareOcc;
				m_mapPhaseIndex["RayCast"]		=		enPI_RayCast;

	
	
				//enumStencileOP
				m_mapStencileOP["Keep"]					=	enSOP_KEEP;
				m_mapStencileOP["Zero"]					=	enSOP_ZERO;
				m_mapStencileOP["Replace"]				=	enSOP_REPLACE;
				m_mapStencileOP["Incr_Sat"]				=	enSOP_INCR_SAT;
				m_mapStencileOP["Decr_Sat"]				=	enSOP_DECR_SAT;
				m_mapStencileOP["Invert"]				=	enSOP_INVERT;
				m_mapStencileOP["Incr"]					=	enSOP_INCR;
				m_mapStencileOP["Decr"]					=	enSOP_DECR;
	
				//enumBlendOP
				m_mapBlendOP["Add"]						=	enBOP_ADD;
				m_mapBlendOP["Subtract"]				=	enBOP_SUBTRACT;
				m_mapBlendOP["Rev_Subtract"]			=	enBOP_REV_SUBTRACT;
				m_mapBlendOP["Min"]						=	enBOP_MIN;
				m_mapBlendOP["Max"]						=	enBOP_MAX;
	
				//enumBlend
				m_mapBlend["Zero"]						=	enB_ZERO;
				m_mapBlend["One"]						=	enB_ONE;
				m_mapBlend["Src_Color"]					=	enB_SRC_COLOR;
				m_mapBlend["Inv_Src_Color"]				=	enB_INV_SRC_COLOR;
				m_mapBlend["Src_Alpha"]					=	enB_SRC_ALPHA;
				m_mapBlend["Inv_Src_Alpha"]				=	enB_INV_SRC_ALPHA;
				m_mapBlend["Dest_Alpha"]				=	enB_DEST_ALPHA;
				m_mapBlend["Inv_Dest_Alpha"]			=	enB_INV_DEST_ALPHA;
				m_mapBlend["Dest_Color"]				=	enB_DEST_COLOR;
				m_mapBlend["Inv_Dest_Color"]			=	enB_INV_DEST_COLOR;
				m_mapBlend["Src_Alpha_Sat"]				=	enB_SRC_ALPHA_SAT;
				m_mapBlend["Blend_Factor"]				=	enB_BLEND_FACTOR;
				m_mapBlend["Inv_Blend_Factor"]			=	enB_INV_BLEND_FACTOR;
				m_mapBlend["Src1_Color"]				=	enB_SRC1_COLOR;
				m_mapBlend["Inv_Src1_Color"]			=	enB_INV_SRC1_COLOR;
				m_mapBlend["Src1_Alpha"]				=	enB_SRC1_ALPHA;
				m_mapBlend["Inv_Src1_Alpha"]			=	enB_INV_SRC1_ALPHA;
	
				//m_mapTextureAddress
				m_mapTextureAddress["Wrap"]				=	enTA_WRAP;
				m_mapTextureAddress["Mirror"]			=	enTA_MIRROR;
				m_mapTextureAddress["Clamp"]			=	enTA_CLAMP;
				m_mapTextureAddress["Border"]			=	enTA_BORDER;
				m_mapTextureAddress["Mirror_Once"]		=	enTA_MIRROR_ONCE;
	
				//m_mapTextureFilter
				m_mapTextureFilter["Point"]				=	enTF_MIN_MAG_MIP_POINT;
				m_mapTextureFilter["Bilinear"]			=	enTF_MIN_MAG_LINEAR_MIP_POINT;
				m_mapTextureFilter["Trilinear"]			=	enTF_MIN_MAG_MIP_LINEAR;
				


				//m_mapDepthWriteMask
				m_mapDepthWriteMask["Zero"]				=	enDWM_ZERO;
				m_mapDepthWriteMask["All"]				=	enDWM_ALL;
	
				//enumFillMode	
				m_mapFillMode["Point"]					=	enFM_POINT;
				m_mapFillMode["Wireframe"]				=	enFM_WIREFRAME;
				m_mapFillMode["Soild"]					=	enFM_SOILD;
	
				//enumCullMode
				m_mapCullMode["None"]					=	enCM_NONE;
				m_mapCullMode["Cw"]						=	enCM_CW;
				m_mapCullMode["Ccw"]					=	enCM_CCW;
	
				//m_mapFog
				m_mapFog["None"]						=	enF_NONE;
				m_mapFog["Exp"]							=	enF_EXP;
				m_mapFog["Exp2"]						=	enF_EXP2;
				m_mapFog["Line"]						=	enF_LINE;
	
				//enumCompare
				m_mapCompare["Never"]					=	enC_NEVER        ;
				m_mapCompare["Less"]					=	enC_LESS         ;
				m_mapCompare["Equal"]					=	enC_EQUAL        ;
				m_mapCompare["LessEqual"]				=	enC_LESS_EQUAL   ;
				m_mapCompare["Greater"]					=	enC_GREATER      ;
				m_mapCompare["NotEqual"]				=	enC_NOT_EQUAL    ;
				m_mapCompare["GreaterEqual"]			=	enC_GREATER_EQUAL;
				m_mapCompare["Always"]					=	enC_ALWAYS       ;
	
				//enumParamBindType
				INSERT_PARAM_TYPE("Technique",MATERIAL_PARAM_TECHNIQUE);
				INSERT_PARAM_TYPE("Bool",MATERIAL_PARAM_BOOL);
				INSERT_PARAM_TYPE("Int",MATERIAL_PARAM_INT);
				INSERT_PARAM_TYPE("Float",MATERIAL_PARAM_FLOAT);
				INSERT_PARAM_TYPE("Int4",MATERIAL_PARAM_INT4);
				INSERT_PARAM_TYPE("Int4array",MATERIAL_PARAM_INT4ARRAY);
				INSERT_PARAM_TYPE("Vector",MATERIAL_PARAM_VECTOR);
				INSERT_PARAM_TYPE("VectorArray",MATERIAL_PARAM_VECTORARRAY)						///<	向量数组
				INSERT_PARAM_TYPE("Matrix",MATERIAL_PARAM_MATRIX)								///<	矩阵
				INSERT_PARAM_TYPE("MatrixArray",MATERIAL_PARAM_MATRIXARRAY)						///<	矩阵数组
				INSERT_PARAM_TYPE("Texture",MATERIAL_PARAM_TEXTURE)								///<	纹理
				INSERT_PARAM_TYPE("2d",MATERIAL_PARAM_TEXTURE)									///<	2d纹理
				INSERT_PARAM_TYPE("TextureCube",MATERIAL_PARAM_TEXTURE_CUBE)					///<	立方盒纹理
				INSERT_PARAM_TYPE("Cube",MATERIAL_PARAM_TEXTURE_CUBE)							///<	cube纹理
				INSERT_PARAM_TYPE("TextureVolume",MATERIAL_PARAM_TEXTURE_VOLUME)				///<	体积纹理
				INSERT_PARAM_TYPE("Volume",MATERIAL_PARAM_TEXTURE_VOLUME)						///<	3d纹理
				INSERT_PARAM_TYPE("Textureshadow",MATERIAL_PARAM_TEXTURE_SHADOW)				///<	阴影纹理
				INSERT_PARAM_TYPE("Texturesky",MATERIAL_PARAM_TEXTURE_SKY)						///<	天空纹理
				INSERT_PARAM_TYPE("Texturepostcomposer",MATERIAL_PARAM_TEXTURE_LASTPOSTCOMPOSER)///<	上次后期效果处理
				INSERT_PARAM_TYPE("Bonetexture",MATERIAL_PARAM_TEXTURE_BONE)					///<	用于保存骨骼纹理
				INSERT_PARAM_TYPE("Matrixshadow",MATERIAL_PARAM_MATRIX_TEXTURE_SHADOW)			///<	阴影纹理矩阵
				INSERT_PARAM_TYPE("Worldmatrix",MATERIAL_PARAM_MATRIX_WORLD)					///<	世界矩阵
				INSERT_PARAM_TYPE("ViewProjMatrix",MATERIAL_PARAM_MATRIX_VIEWPROJ)				///<	视野投影矩阵
				INSERT_PARAM_TYPE("ViewProjInvMatrix",MATERIAL_PARAM_MATRIX_VIEWPROJ_INV)		///<	视野投影逆矩阵
				INSERT_PARAM_TYPE("WorldViewProjMatrix",MATERIAL_PARAM_MATRIX_WORLDVIEWPROJ)	///<	世界视野投影矩阵
				INSERT_PARAM_TYPE("WorldViewMatrix",MATERIAL_PARAM_MATRIX_WORLDVIEW)			///<	世界视野
				INSERT_PARAM_TYPE("BoneMatrixArray",MATERIAL_PARAM_MATRIX_BONEARRAY)			///<	骨骼矩阵数组
				INSERT_PARAM_TYPE("Amibent",MATERIAL_PARAM_VECTOR_AMIBENT)						///<	环境光
				INSERT_PARAM_TYPE("Lightposition0",MATERIAL_PARAM_VECTOR_LIGHT_POS)				///<	天光位置
				INSERT_PARAM_TYPE("Lightdiffuse0",	MATERIAL_PARAM_VECTOR_LIGHT_DIFF)			///<	天光颜色
				INSERT_PARAM_TYPE("LightPosition1",MATERIAL_PARAM_VECTOR_LIGHT_POS1)			///<	第1盏灯光位置
				INSERT_PARAM_TYPE("Lightdiffuse1",MATERIAL_PARAM_VECTOR_LIGHT_DIFF1)			///<	第1盏灯光颜色
				INSERT_PARAM_TYPE("LightPosition2",MATERIAL_PARAM_VECTOR_LIGHT_POS2)			///<	第2盏灯光位置
				INSERT_PARAM_TYPE("Lightdiffuse2",MATERIAL_PARAM_VECTOR_LIGHT_DIFF2)			///<	第2盏灯光颜色
				INSERT_PARAM_TYPE("Lightposition3",MATERIAL_PARAM_VECTOR_LIGHT_POS3)			///<	第3盏灯光位置
				INSERT_PARAM_TYPE("Lightdiffuse3",MATERIAL_PARAM_VECTOR_LIGHT_DIFF3)			///<	第3盏灯光颜色
				INSERT_PARAM_TYPE("Lightposition4",MATERIAL_PARAM_VECTOR_LIGHT_POS4)			///<	第4盏灯光位置
				INSERT_PARAM_TYPE("Lightdiffuse4",MATERIAL_PARAM_VECTOR_LIGHT_DIFF4)			///<	第4盏灯光颜色
				INSERT_PARAM_TYPE("Lightposition5",MATERIAL_PARAM_VECTOR_LIGHT_POS5)			///<	第5盏灯光位置
				INSERT_PARAM_TYPE("Lightdiffuse5",MATERIAL_PARAM_VECTOR_LIGHT_DIFF5)			///<	第5盏灯光颜色
				INSERT_PARAM_TYPE("Lightposition6",MATERIAL_PARAM_VECTOR_LIGHT_POS6)			///<	第6盏灯光位置
				INSERT_PARAM_TYPE("Lightdiffuse6",MATERIAL_PARAM_VECTOR_LIGHT_DIFF6)			///<	第6盏灯光颜色
				INSERT_PARAM_TYPE("Lightposition7",MATERIAL_PARAM_VECTOR_LIGHT_POS7)			///<	第7盏灯光位置
				INSERT_PARAM_TYPE("Lightdiffuse7",MATERIAL_PARAM_VECTOR_LIGHT_DIFF7)			///<	第7盏灯光颜色
				INSERT_PARAM_TYPE("Lightposition8",MATERIAL_PARAM_VECTOR_LIGHT_POS8)			///<	第8盏灯光位置
				INSERT_PARAM_TYPE("Lightdiffuse8",MATERIAL_PARAM_VECTOR_LIGHT_DIFF8)			///<	第8盏灯光颜色
				INSERT_PARAM_TYPE("Lightpositionarray",MATERIAL_PARAM_VECTOR_LIGHT_POSARRAY)	///<	第8盏灯光颜色
				INSERT_PARAM_TYPE("Lightdiffusearray",MATERIAL_PARAM_VECTOR_LIGHT_DIFFARRAY)	///<	第8盏灯光颜色
				INSERT_PARAM_TYPE("Cameraposition",MATERIAL_PARAM_VECTOR_CAMERA_POSITION)		///<	摄像机位置
				INSERT_PARAM_TYPE("Cameradirection",MATERIAL_PARAM_VECTOR_CAMERA_DIRECTION)		///<	摄像机方向
				INSERT_PARAM_TYPE("Cameraupdirection",MATERIAL_PARAM_VECTOR_CAMERA_UPDIR)		///<	摄像机顶方向
				INSERT_PARAM_TYPE("Camerarightdirection",MATERIAL_PARAM_VECTOR_CAMERA_RIGHTDIR)	///<	摄像机右手方向
				INSERT_PARAM_TYPE("Boundmin",MATERIAL_PARAM_VECTOR_BOUND_MIN)					///<	包围盒最小值
				INSERT_PARAM_TYPE("Boundmax",MATERIAL_PARAM_VECTOR_BOUND_MAX)					///<	包围盒最大值
				INSERT_PARAM_TYPE("Boundsphere",MATERIAL_PARAM_VECTOR_BOUND_SPHERE)				///<	包围球
				INSERT_PARAM_TYPE("Mouseposition",MATERIAL_PARAM_VECTOR_MOUSE_POSITION)			///<	鼠标位置
				INSERT_PARAM_TYPE("MouseMove",MATERIAL_PARAM_VECTOR_MOUSE_MOVE)					///<	鼠标移动便宜量
				INSERT_PARAM_TYPE("Totaltime",MATERIAL_PARAM_FLOAT_TIME_TOTAL)					///<	总时间
				INSERT_PARAM_TYPE("Createtime",MATERIAL_PARAM_FLOAT_TIME_CREATE)				///<	材质创建时间
				INSERT_PARAM_TYPE("Deltatime",MATERIAL_PARAM_FLOAT_TIME_DELTA)					///<	与上一帧的间隔时间
				INSERT_PARAM_TYPE("Screenwidth",MATERIAL_PARAM_FLOAT_SCREEN_WIDTH)				///<	屏幕宽度
				INSERT_PARAM_TYPE("Screenheight",MATERIAL_PARAM_FLOAT_SCREEN_HEIGHT)			///<	屏幕高度
	
				//enumParamBindPos
				m_vecParamBindType.resize(MATERIAL_PARAM_MAX);
				m_vecParamBindType[MATERIAL_PARAM_TECHNIQUE]				=	enPBT_UNKNOWN;
				m_vecParamBindType[MATERIAL_PARAM_BOOL]						=	enPBT_BOOL;
				m_vecParamBindType[MATERIAL_PARAM_INT]						=	enPBT_INT;				///<	整形
				m_vecParamBindType[MATERIAL_PARAM_FLOAT]					=	enPBT_FLOAT;			///<	浮点数
				m_vecParamBindType[MATERIAL_PARAM_INT4]						=	enPBT_INT4;				///<	四维整形向量
				m_vecParamBindType[MATERIAL_PARAM_INT4ARRAY]				=	enPBT_INT4ARRAY;		///<	四维整形向量数组
				m_vecParamBindType[MATERIAL_PARAM_VECTOR]					=	enPBT_VECTOR;			///<	4唯向量
				m_vecParamBindType[MATERIAL_PARAM_VECTORARRAY]				=	enPBT_VECTORARRAY;		///<	向量数组
				m_vecParamBindType[MATERIAL_PARAM_MATRIX]					=	enPBT_MATRIX;			///<	矩阵
				m_vecParamBindType[MATERIAL_PARAM_MATRIXARRAY]				=	enPBT_MATRIXARRAY;		///<	矩阵数组
				m_vecParamBindType[MATERIAL_PARAM_TEXTURE]					=	enPBT_UNKNOWN;			///<	纹理
				m_vecParamBindType[MATERIAL_PARAM_TEXTURE_CUBE]				=	enPBT_UNKNOWN;			///<	立方盒纹理
				m_vecParamBindType[MATERIAL_PARAM_TEXTURE_VOLUME]			=	enPBT_UNKNOWN;			///<	体积纹理
				m_vecParamBindType[MATERIAL_PARAM_TEXTURE_SHADOW]			=	enPBT_UNKNOWN;			///<	阴影纹理
				m_vecParamBindType[MATERIAL_PARAM_TEXTURE_SKY]				=	enPBT_UNKNOWN;			///<	天空纹理
				m_vecParamBindType[MATERIAL_PARAM_TEXTURE_LASTPOSTCOMPOSER]	=	enPBT_UNKNOWN;			///<	上次后期效果处理
				m_vecParamBindType[MATERIAL_PARAM_TEXTURE_BONE]				=	enPBT_UNKNOWN;			///<	存储骨骼动画纹理
				m_vecParamBindType[MATERIAL_PARAM_MATRIX_TEXTURE_SHADOW]	=	enPBT_MATRIX_AUTO;		///<	阴影纹理矩阵
				m_vecParamBindType[MATERIAL_PARAM_MATRIX_WORLD]				=	enPBT_MATRIX_AUTO;		///<	世界矩阵
				m_vecParamBindType[MATERIAL_PARAM_MATRIX_VIEWPROJ]			=	enPBT_MATRIX_AUTO;		///<	视野投影矩阵
				m_vecParamBindType[MATERIAL_PARAM_MATRIX_VIEWPROJ_INV]		=	enPBT_MATRIX_AUTO;		///<	视野投影逆矩阵
				m_vecParamBindType[MATERIAL_PARAM_MATRIX_WORLDVIEWPROJ]		=	enPBT_MATRIX_AUTO;		///<	世界视野投影矩阵
				m_vecParamBindType[MATERIAL_PARAM_MATRIX_WORLDVIEW]			=	enPBT_MATRIX_AUTO;		///<	世界视野
				m_vecParamBindType[MATERIAL_PARAM_MATRIX_BONEARRAY]			=	enPBT_MATRIX_AUTO;		///<	骨骼转换矩阵数组
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_AMIBENT]			=	enPBT_VECTOR_AUTO;				///<	环境光
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS]			=	enPBT_VECTOR_AUTO;			///<	天光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF]		=	enPBT_VECTOR_AUTO;			///<	天光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS1]		=	enPBT_VECTOR_AUTO;			///<	第1盏灯光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF1]		=	enPBT_VECTOR_AUTO;			///<	第1盏灯光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS2]		=	enPBT_VECTOR_AUTO;			///<	第2盏灯光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF2]		=	enPBT_VECTOR_AUTO;			///<	第2盏灯光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS3]		=	enPBT_VECTOR_AUTO;			///<	第3盏灯光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF3]		=	enPBT_VECTOR_AUTO;			///<	第3盏灯光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS4]		=	enPBT_VECTOR_AUTO;			///<	第4盏灯光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF4]		=	enPBT_VECTOR_AUTO;			///<	第4盏灯光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS5]		=	enPBT_VECTOR_AUTO;			///<	第5盏灯光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF5]		=	enPBT_VECTOR_AUTO;			///<	第5盏灯光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS6]		=	enPBT_VECTOR_AUTO;			///<	第6盏灯光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF6]		=	enPBT_VECTOR_AUTO;			///<	第6盏灯光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS7]		=	enPBT_VECTOR_AUTO;			///<	第7盏灯光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF7]		=	enPBT_VECTOR_AUTO;			///<	第7盏灯光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POS8]		=	enPBT_VECTOR_AUTO;			///<	第8盏灯光位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFF8]		=	enPBT_VECTOR_AUTO;			///<	第8盏灯光颜色
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_POSARRAY]	=	enPBT_VECTORARRAY_AUTO;		///<	灯光位置数组
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_LIGHT_DIFFARRAY]	=	enPBT_VECTORARRAY_AUTO;		///<	灯光漫反射数组
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_CAMERA_POSITION]	=	enPBT_VECTOR_AUTO;			///<	摄像机位置
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_CAMERA_DIRECTION]	=	enPBT_VECTOR_AUTO;			///<	摄像机方向
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_CAMERA_UPDIR]		=	enPBT_VECTOR_AUTO;			///<	摄像机顶方向
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_CAMERA_RIGHTDIR]	=	enPBT_VECTOR_AUTO;			///<	摄像机右手方向
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_BOUND_MIN]			=	enPBT_VECTOR_AUTO;			///<	包围盒最小值
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_BOUND_MAX]			=	enPBT_VECTOR_AUTO;			///<	包围盒最大值
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_BOUND_SPHERE]		=	enPBT_VECTOR_AUTO;			///<	包围球
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_MOUSE_POSITION]	=	enPBT_VECTOR_AUTO;
				m_vecParamBindType[MATERIAL_PARAM_VECTOR_MOUSE_MOVE]		=	enPBT_VECTOR_AUTO;
				m_vecParamBindType[MATERIAL_PARAM_FLOAT_TIME_TOTAL]			=	enPBT_VECTOR_AUTO;			///<	总时间
				m_vecParamBindType[MATERIAL_PARAM_FLOAT_TIME_DELTA]			=	enPBT_VECTOR_AUTO;			///<	与上一帧的间隔时间
				m_vecParamBindType[MATERIAL_PARAM_FLOAT_TIME_CREATE]		=	enPBT_VECTOR_AUTO;			///<	创建时间
				m_vecParamBindType[MATERIAL_PARAM_FLOAT_SCREEN_WIDTH]		=	enPBT_VECTOR_AUTO;			///<	屏幕宽度
				m_vecParamBindType[MATERIAL_PARAM_FLOAT_SCREEN_HEIGHT]		=	enPBT_VECTOR_AUTO;			///<	屏幕高度


	
				m_mapMaterialParamType["diffuse"]				=	enMSPT_Diffuse;
				m_mapMaterialParamType["ambient"]				=	enMSPT_Ambient;
				m_mapMaterialParamType["specular"]				=	enMSPT_Specular;
				m_mapMaterialParamType["glossiness"]			=	enMSPT_Glossiness;
				m_mapMaterialParamType["opacity"]				=	enMSPT_Opacity;
				m_mapMaterialParamType["specularlevel"]			=	enMSPT_SpecularLevel;
				m_mapMaterialParamType["selfillumcolor"]		=	enMSPT_SelfIllumColor;
				m_mapMaterialParamType["ambienttex"]			=	enMSPT_TexAmbient;
				m_mapMaterialParamType["diffusetex"]			=	enMSPT_TexDiffuse;
				m_mapMaterialParamType["speculartex"]			=	enMSPT_TexSpecular;
				m_mapMaterialParamType["glossinesstex"]			=	enMSPT_TexGlossiness;
				m_mapMaterialParamType["specularLeveltex"]		=	enMSPT_TexSpecularLevel;
				m_mapMaterialParamType["selfilluminationtex"]	=	enMSPT_TexSelfillumination;
				m_mapMaterialParamType["opacitytex"]			=	enMSPT_TexOpacity;
				m_mapMaterialParamType["filtercolortex"]		=	enMSPT_TexFiltercolor;
				m_mapMaterialParamType["bumptex"]				=	enMSPT_TexBump;
				m_mapMaterialParamType["reflectiontex"]			=	enMSPT_TexReflection;
				m_mapMaterialParamType["refractiontex"]			=	enMSPT_TexRefraction;
				m_mapMaterialParamType["displacementtex"]		=	enMSPT_TexDisplacement;

			}
	
			void MaterialParse::CompileMaterialTemplate(U8*	pData,U32	uiSize ){
				StringVector	vecWord;
				if(!Common::Parse::StringToWord(pData,uiSize,vecWord)){
					return;
				}
				U32 i	=	0;
				MaterialTemplateInfo*	pInfo	=	NULL;
				while(true){
					if(i>=vecWord.size())
						break;
					AString&	str	=	vecWord[i];
					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);

					i++;
					if(m	==	enUnKnown)
						continue;
	
					if(m	==	enMaterialTemplate){
						pInfo	=	new	MaterialTemplateInfo(vecWord[i++]);
						if(!ParseMaterialTemplate(vecWord,i,pInfo)){
							SAF_D(pInfo);
							return;
						}else{
							m_mapMaterialTemplateInfo[pInfo->strName.c_str()]	=	pInfo;
						}
					}
				}
				EngineLogWarnning("材质解析","完毕");
			}
	
			U1 MaterialParse::ParseMaterialTemplate( StringVector& vecWord,U32& i,MaterialTemplateInfo* pInfo ){
				while(true){
					AString&	str	=	vecWord[i];
					if(str	==	"}"){
						i++;
						break;
					}
					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);;
					i++;
					if(m	==	enUnKnown){
						continue;
					}
					PassInfo*	pTInfo	=	NULL;
					switch(m){
						case	enPhase:{
							pInfo->PhaseIndex	=	m_mapPhaseIndex[vecWord[i++]];//(enumPhaseIndex)0;//Common::Converter::ToU32()
							break;}
						case	enPriority:{
							pInfo->uiPriority	=	Common::Converter::ToU32(vecWord[i++]);
							break;}
						case	enPass:
							pTInfo	=	new	PassInfo(vecWord[i]);
							i++;
							if(!ParsePass(vecWord,i,pTInfo)){
								SAF_D(pTInfo);
							}else{
								pInfo->m_vecPassInfo.push_back(pTInfo);
							}
							break;
						default:
							break;
					}
				}
				
				return	true;
			}
	/*
			U1 MaterialParse::ParseMaterialTemplate( StringVector& vecWord,U32& i,MaterialTemplateInfo* pInfo ){
				while(true){
					AString&	str	=	vecWord[i];
					if(str	==	"}"){
						i++;
						break;
					}
					enumMaterial	m	=	(enumMaterial)m_mapParam[str.c_str()];
					i++;
					//如果是无效字符	直接跳过
					if(m	==	enUnKnown){
						continue;
					}
					
					switch(m){

						case	enPass:{
							PassInfo*	pPInfo	=	NULL;
							pPInfo	=	new	PassInfo(vecWord[i++]);
	
							if(!ParsePass(vecWord,i,pPInfo)){
								SAF_D(pPInfo);
							}else{
								pInfo->m_vecPassInfo.push_back(pPInfo);
							}
							break;}
						default:{
							break;}
					}
				}
	
				return	true;
			}
	*/
			U1 MaterialParse::ParsePass( StringVector& vecWord,U32& i,PassInfo* pInfo ){
				while(true){
					AString&	str	=	vecWord[i];
					if(str	==	"}"){
						i++;
						break;
					}
					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);
					i++;
					if(m	==	enUnKnown){
						continue;
					}
	
					switch(m){
						case	enVertexShader:{
							pInfo->pShaderArray[enVS]	=	new	ShaderParamInfo(vecWord[i++]);
							if(!ParseShaderParam(vecWord,i,pInfo->pShaderArray[enVS])){
								SAF_D(pInfo->pShaderArray[enVS]);
							}
							break;}
						case	enGeometryShader:{
							pInfo->pShaderArray[enGS]	=	new	ShaderParamInfo(vecWord[i++]);
							if(!ParseShaderParam(vecWord,i,pInfo->pShaderArray[enGS])){
								SAF_D(pInfo->pShaderArray[enGS]);
							}
							break;}
						case	enPixelShader:{
							pInfo->pShaderArray[enPS]	=	new	ShaderParamInfo(vecWord[i++]);
							if(!ParseShaderParam(vecWord,i,pInfo->pShaderArray[enPS])){
								SAF_D(pInfo->pShaderArray[enPS]);
							}
							break;}
						case	enComputeShader:{
							pInfo->pShaderArray[enCS]	=	new	ShaderParamInfo(vecWord[i++]);
							if(!ParseShaderParam(vecWord,i,pInfo->pShaderArray[enCS])){
								SAF_D(pInfo->pShaderArray[enCS]);
							}
							break;}
						case	enHullShader:{
							pInfo->pShaderArray[enHS]	=	new	ShaderParamInfo(vecWord[i++]);
							if(!ParseShaderParam(vecWord,i,pInfo->pShaderArray[enHS])){
								SAF_D(pInfo->pShaderArray[enHS]);
							}
							break;}
						case	enDomainShader:{
							pInfo->pShaderArray[enDS]	=	new	ShaderParamInfo(vecWord[i++]);
							if(!ParseShaderParam(vecWord,i,pInfo->pShaderArray[enDS])){
								SAF_D(pInfo->pShaderArray[enDS]);
							}
							break;}
						case	enRasterizerState:{
							pInfo->strRasterizerState	=	vecWord[i++];
							break;}	
						case	enDepthState:{
							pInfo->strDepthStencilState	=	vecWord[i++];
							break;}	
						case	enBlendState:{
							pInfo->strBlendState		=	vecWord[i++];
							break;}	
					}
				}
				return	true;
			}
	
			U1 MaterialParse::ParseShaderParam( StringVector& vecWord,U32& i,ShaderParamInfo* pInfo ){
				while(true){
					AString&	str	=	vecWord[i];
					if(str	==	"}"){
						i++;
						break;
					}
					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);
					i++;
					if(m	==	enUnKnown){
						continue;
					}
	
					switch(m){
						case	enTexture:{
							TextureUnitInfo	texUInfo;
							texUInfo.index					=	Converter::ToU32(vecWord[i++]);
							texUInfo.uiRigister				=	Converter::ToU32(vecWord[i++]);
							texUInfo.strSamplerState		=	vecWord[i++];
							pInfo->m_vecTextureInfo.push_back(texUInfo);

							break;}
						default:{
							break;}
					}
					//i++;
				}
	
				return	true;
			}
	
			U1 MaterialParse::ParseTexture( StringVector& vecWord,U32& i,TextureUnitInfo* pInfo ){
				while(true){
					AString&	str	=	vecWord[i];
					if(str	==	"}"){
						i++;
						break;
					}
					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);
					i++;
					if(m	==	enUnKnown){
						continue;
					}
					switch(m){
						case	enTextureIndex:{
							pInfo->index			=	Converter::ToU32(vecWord[i++]);
							break;}
						case	enSamplerState:{
							pInfo->strSamplerState	=	vecWord[i++];
							break;}
						default:{
							break;}
					}
				}
				return	true;
			}
	
			U1 MaterialParse::ParseParam( StringVector& vecWord,U32& i,ParamBindInfo* pInfo ){
// 				switch(pInfo->type){
// 					case	MATERIAL_PARAM_BOOL:{
// 						pInfo->vValue.x	=	Converter::ToU1(vecWord[i++]);	
// 						break;}
// 					case	MATERIAL_PARAM_INT:{
// 						pInfo->vValue.x	=	Converter::ToFloat(vecWord[i++]);
// 						break;}
// 					case	MATERIAL_PARAM_FLOAT:{
// 						pInfo->vValue.x	=	ParseReal(vecWord,i);
// 						break;}
// 					case	MATERIAL_PARAM_VECTOR:{
// 						pInfo->vValue.x	=	ParseReal(vecWord,i);
// 						pInfo->vValue.y	=	ParseReal(vecWord,i);
// 						pInfo->vValue.z	=	ParseReal(vecWord,i);
// 						pInfo->vValue.w	=	ParseReal(vecWord,i);
// 						break;}
// 					default:{
// 						pInfo->strValue	=	vecWord[i++];
// 						break;}
// 				}
				return	true;
			}
	
			void MaterialParse::CompileState( U8*	pData,U32	uiSize ){
				//单词分解	并全部转化为小写
				StringVector	vecWord;
				if(!Common::Parse::StringToWord(pData,uiSize,vecWord)){
					return;
				}
				U32 i	=	0;
	
				while(true){
					//如果超出范围	则跳出循环
					if(i>=vecWord.size()){
						break;
					}
					AString&	str	=	vecWord[i];
					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);;
					i++;
					if(m	==	enUnKnown)
						continue;
	
					switch(m){
						case	enSamplerState:
						case	enRasterizerState:
						case	enDepthState:
						case	enBlendState:{
							AString	strName	=	vecWord[i];
							PassStateInfo*	pState	=	new	PassStateInfo();
							if(m	==	enSamplerState){
								pState->type	=	enRST_SS;
							}else	if(m	==	enDepthState){
								pState->type	=	enRST_DS;
							}else	if(m	==	enBlendState){
								pState->type	=	enRST_BS;
							}else{
								pState->type	=	enRST_RS;
							}
							if(!ParseState(vecWord,i,pState)){
								SAF_D(pState);
							}else{
								m_mapPassState[strName.c_str()]	=	pState;
							}
	
							break;}
					}
				}	
			}
	
			U1 MaterialParse::ParseState( StringVector& vecWord,U32& i,PassStateInfo* pInfo ){
				while(true){
					AString&	str	=	vecWord[i];
					if(str	==	"}"){
						i++;
						break;
					}
					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);
					i++;
					//判断是否存在这个关键字	没有则跳过
					if(m	==	enUnKnown){
						continue;
					}
					i++;
					switch(m){
						//SamplerState
						case	enTextureFilter:{
							pInfo->ss.Filter	=	(enumTextureFilter)m_mapTextureFilter[vecWord[i].c_str()];
							break;}
						case	enTextureAddress:{
							pInfo->ss.AddressU	=	(enumTextureAddress)m_mapTextureAddress[vecWord[i].c_str()];
							pInfo->ss.AddressV	=	pInfo->ss.AddressU;
							pInfo->ss.AddressW	=	pInfo->ss.AddressU;
							break;}
						//Render	State
						case	enFillMode:{
							pInfo->rs.FillMode	=	(enumFillMode)m_mapFillMode[vecWord[i].c_str()];
							break;}
						case	enCullMode:{
							pInfo->rs.CullMode	=	(enumCullMode)m_mapCullMode[vecWord[i].c_str()];
							break;}
						case	enDepthBias:{
							pInfo->rs.DepthBias	=	Converter::ToS32(vecWord[i]);
							break;}
						case	enDepthBiasClamp:{
							pInfo->rs.DepthBiasClamp	=	Converter::ToFloat(vecWord[i]);
							break;}
						case	enSlopeScaledDepthBias:{
							pInfo->rs.SlopeScaledDepthBias	=	Converter::ToFloat(vecWord[i]);
							break;}
						case	enDepthClipEnable:{
							pInfo->rs.DepthClipEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						case	enScissorEnable:{
							pInfo->rs.ScissorEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						case	enMultisampleEnable:{
							pInfo->rs.MultisampleEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						case	enAntialiasedLineEnable:{
							pInfo->rs.AntialiasedLineEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						case	enAlphaToCoverage:{
							pInfo->bs.AlphaToCoverageEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						case	enIndependentBlend:{
							pInfo->bs.IndependentBlendEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						//case	enRenderTargetBlend,
						case	enBlendEnable:{
							pInfo->bs.Blend[0].BlendEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						case	enSrcBlend:{
							pInfo->bs.Blend[0].SrcBlend	=	(enumBlend)m_mapBlend[vecWord[i].c_str()];
							break;}
						case	enDestBlend:{
							pInfo->bs.Blend[0].DestBlend	=	(enumBlend)m_mapBlend[vecWord[i].c_str()];
							break;}
						case	enBlendOP:{
							pInfo->bs.Blend[0].BlendOp	=	(enumBlendOP)m_mapBlendOP[vecWord[i].c_str()];
							break;}
						case	enSrcBlendAlpha:{
							pInfo->bs.Blend[0].SrcBlendAlpha	=	(enumBlend)m_mapBlend[vecWord[i].c_str()];
							break;}
						case	enDestBlendAlpha:{
							pInfo->bs.Blend[0].DestBlendAlpha	=	(enumBlend)m_mapBlend[vecWord[i].c_str()];
							break;}
						case	enBlendOpAlpha:{
							pInfo->bs.Blend[0].BlendOpAlpha	=	(enumBlendOP)m_mapBlendOP[vecWord[i].c_str()];
							break;}
						case	enRenderTargetWriteMask:{
							pInfo->bs.Blend[0].RenderTargetWriteMask	=	Converter::ToS32(vecWord[i]);
							break;}
						//depth	state
						case	enDepthEnable:{
							pInfo->ds.DepthEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						case	enDepthWriteMask:{
							pInfo->ds.DepthWriteMask	=	(enumDepthWriteMask)Converter::ToS32(vecWord[i]);
							break;}
						case	enDepthFunc:{
							pInfo->ds.DepthFunc	=	(enumCompare)m_mapCompare[vecWord[i].c_str()];
							break;}
						case	enStencilEnable:{
							pInfo->ds.StencilEnable	=	Converter::ToU1(vecWord[i]);
							break;}
						case	enStencilReadMask:{
							pInfo->ds.StencilReadMask	=	Converter::ToS32(vecWord[i]);
							break;}
						case	enStencilWriteMask:{
							pInfo->ds.StencilWriteMask	=	Converter::ToS32(vecWord[i]);
							break;}
						default:{
							continue;
						}
					}
					i+=2;
				}
				return	true;
			}
	
			MaterialParse::~MaterialParse(){
				PassStateMap::iterator	i		=	m_mapPassState.begin();
				for(;i!=m_mapPassState.end();i++){
					SAF_D(i->second);
				}
				m_mapPassState.clear();
	
				MaterialTemplateInfoMap::iterator	it	=	m_mapMaterialTemplateInfo.begin();
				for(;it!=m_mapMaterialTemplateInfo.end();it++){
					SAF_D(it->second);
				}
				m_mapMaterialTemplateInfo.clear();
	
				MaterialInfoMap::iterator	itr	=	m_mapMaterialInfo.begin();
				for(;itr!=m_mapMaterialInfo.end();itr++){
					SAF_D(itr->second);
				}
				m_mapMaterialInfo.clear();
			}
	
			MaterialTemplateInfo* MaterialParse::GetMaterialTemplateInfo( CAString& strName ){
				MaterialTemplateInfoMap::iterator	i	=	m_mapMaterialTemplateInfo.find(strName);
				if(i!=m_mapMaterialTemplateInfo.end())
					return	i->second;
				return	NULL;
			}
	
			PassStateInfo* MaterialParse::GetPassStateInfo( CAString& strName ){

				PassStateMap::iterator	i	=	m_mapPassState.find(strName);
				if(i!=m_mapPassState.end())
					return	i->second;
				return	NULL;
			}

			Air::U1 MaterialParse::ParamType2BindType(enumParamType type, ParamBindInfo& info ){
				if(type >=	MATERIAL_PARAM_MAX)
					return	false;

				info.bindType	=	m_vecParamBindType[type];

				if(	info.bindType	==	enPBT_UNKNOWN	||
					info.bindType	>=	enPBT_MAX)
				{
					return	false;
				}
				//着色语言共享参数
				ShaderShareParam&	sParam	=	GetGlobalSetting().m_ShaderParam;

				//计算参数的长度
				switch(info.bindType){
					case	enPBT_BOOL:
					case	enPBT_INT:
					case	enPBT_FLOAT:
					case	enPBT_INT4:
					case	enPBT_VECTOR:
					case	enPBT_INT4_AUTO:
					case	enPBT_VECTOR_AUTO:{
						info.uiSize	=	1;
						break;
										 }
					case	enPBT_MATRIX:
					case	enPBT_MATRIX_AUTO:{
						info.uiSize	=	4;
						break;
										 }
					case	enPBT_INT4ARRAY:
					case	enPBT_VECTORARRAY:
					case	enPBT_MATRIXARRAY:
					case	enPBT_INT4ARRAY_AUTO:
					case	enPBT_VECTORARRAY_AUTO:
					case	enPBT_MATRIXARRAY_AUTO:{
						info.uiSize	=	200;
						break;
												   }
				}

				//获取自动参数的地址
				switch(type){
					case MATERIAL_PARAM_MATRIX_TEXTURE_SHADOW:{
						info.val.m_pVoid		=	&sParam.m_matShadow[0];
						break;}		///<	阴影纹理矩阵
					case MATERIAL_PARAM_MATRIX_WORLD:{
						info.val.m_pVoid		=	&sParam.m_matWorld;
						break;}		///<	世界矩阵
					case MATERIAL_PARAM_MATRIX_VIEWPROJ:{
						info.val.m_pVoid		=	&sParam.m_matViewProj;
						break;}		///<	视野投影矩阵
					case	MATERIAL_PARAM_MATRIX_VIEWPROJ_INV:{
						info.val.m_pVoid		=	&sParam.m_matViewProjI;
						break;}		///<	视野投影逆矩阵
					case MATERIAL_PARAM_MATRIX_WORLDVIEWPROJ:{
						info.val.m_pVoid		=	&sParam.m_matWorldViewProj;
						break;}		///<	世界视野投影矩阵
					case MATERIAL_PARAM_MATRIX_WORLDVIEW:{
						info.val.m_pVoid		=	&sParam.m_matWorldView;
						break;}		///<	世界投影矩阵
					case MATERIAL_PARAM_MATRIX_BONEARRAY:{
						info.val.m_pVoid		=	&sParam.m_BoneMatrixArray;
						break;}
					case MATERIAL_PARAM_VECTOR_AMIBENT:{
						info.val.m_pVoid		=	&sParam.m_AmibentColor;
						break;}		///<	环境光
					case MATERIAL_PARAM_VECTOR_LIGHT_POS:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[0];									 
						break;}		///<	天光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[0];
						break;}		///<	天光颜色
					case MATERIAL_PARAM_VECTOR_LIGHT_POS1:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[1];		
						break;}		///<	第1盏灯光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF1:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[1];
						break;}		///<	第1盏灯光颜色
					case MATERIAL_PARAM_VECTOR_LIGHT_POS2:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[2];		
						break;}		///<	第2盏灯光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF2:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[2];
						break;}		///<	第2盏灯光颜色
					case MATERIAL_PARAM_VECTOR_LIGHT_POS3:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[3];		
						break;}		///<	第3盏灯光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF3:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[3];
						break;}		///<	第3盏灯光颜色
					case MATERIAL_PARAM_VECTOR_LIGHT_POS4:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[4];		
						break;}		///<	第4盏灯光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF4:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[4];
						break;}		///<	第4盏灯光颜色
					case MATERIAL_PARAM_VECTOR_LIGHT_POS5:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[5];		
						break;}		///<	第5盏灯光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF5:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[5];
						break;}		///<	第5盏灯光颜色
					case MATERIAL_PARAM_VECTOR_LIGHT_POS6:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[6];		
						break;}		///<	第6盏灯光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF6:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[6];
						break;}		///<	第6盏灯光颜色
					case MATERIAL_PARAM_VECTOR_LIGHT_POS7:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[7];		
						break;}		///<	第7盏灯光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF7:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[7];
						break;}		///<	第7盏灯光颜色
					case MATERIAL_PARAM_VECTOR_LIGHT_POS8:{
						info.val.m_pVoid		=	&sParam.m_LightPosition[8];		
						break;}		///<	第8盏灯光位置
					case MATERIAL_PARAM_VECTOR_LIGHT_DIFF8:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse[8];
						break;}		///<	第8盏灯光颜色
					case	MATERIAL_PARAM_VECTOR_LIGHT_POSARRAY:{
						info.val.m_pVoid		=	&sParam.m_LightPosition;
						break;}
					case	MATERIAL_PARAM_VECTOR_LIGHT_DIFFARRAY:{
						info.val.m_pVoid		=	&sParam.m_LightDiffuse;
						break;}
					case MATERIAL_PARAM_VECTOR_CAMERA_POSITION:{
						info.val.m_pVoid		=	&sParam.m_vCurrentPosition;
						break;}		///<	摄像机位置
					case MATERIAL_PARAM_VECTOR_CAMERA_DIRECTION:{
						info.val.m_pVoid		=	&sParam.m_vCurrentDirection;
						break;}		///<	摄像机方向
					case MATERIAL_PARAM_VECTOR_CAMERA_UPDIR:{
						info.val.m_pVoid		=	&sParam.m_vCurrentUpDirection;
						break;}		///<	摄像机顶方向
					case MATERIAL_PARAM_VECTOR_CAMERA_RIGHTDIR:{
						info.val.m_pVoid		=	&sParam.m_vCurrentRightDirection;
						break;}		///<	摄像机右手方向
					case MATERIAL_PARAM_VECTOR_BOUND_MIN:{
						info.val.m_pVoid		=	&sParam.m_vBoundMin;
						break;}		///<	包围盒最小值
					case MATERIAL_PARAM_VECTOR_BOUND_MAX:{
						info.val.m_pVoid		=	&sParam.m_vBoundMax;
						break;}		///<	包围盒最大值
					case MATERIAL_PARAM_VECTOR_BOUND_SPHERE:{		
						info.val.m_pVoid		=	&sParam.m_vBoundSphere;
						break;}		///<	包围球
					case MATERIAL_PARAM_VECTOR_MOUSE_POSITION:{
						info.val.m_pVoid		=	&sParam.m_vCursorPosition;
						break;}		///<	鼠标位置	
					case MATERIAL_PARAM_VECTOR_MOUSE_MOVE:{
						info.val.m_pVoid		=	&sParam.m_vCursorMove;
						break;}		///<	鼠标移动偏移量	
					case MATERIAL_PARAM_FLOAT_TIME_TOTAL:{
						info.val.m_pVoid		=	&sParam.m_fTotalTime;
						break;}		///<	总时间
					case MATERIAL_PARAM_FLOAT_TIME_DELTA:{
						info.val.m_pVoid		=	&sParam.m_fTimeDelta;
						break;}		///<	与上一帧的间隔时间
					case MATERIAL_PARAM_FLOAT_TIME_CREATE:{
						info.val.m_pVoid		=	&sParam.m_fTotalTime;
						break;}		///<	创建时间
					case MATERIAL_PARAM_FLOAT_SCREEN_WIDTH:{
						info.val.m_pVoid		=	&sParam.m_iScreenWidth;
						break;}		///<	屏幕宽度
					case MATERIAL_PARAM_FLOAT_SCREEN_HEIGHT:{
						info.val.m_pVoid		=	&sParam.m_iScreenHeight;
						break;}		///<	屏幕高度
					default:{
						return false;
							}	
				}

				return	true;
			}

			void MaterialParse::CompileMaterial( U8*	pData,U32	uiSize ){
				if(pData==NULL)
					return;
				StringVector	vecWord;
				if(!Common::Parse::StringToWordScript(pData,uiSize,vecWord)){
					return;
				}
				U32 i	=	0;
				Material::Info*	pInfo	=	NULL;
				while(true){
					if(i>=vecWord.size())
						break;
					AString&	str	=	vecWord[i];
					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);
					i++;
					if(m	==	enUnKnown)
						continue;

					if(m	==	enMaterial){
						AString	strMaterial		=	vecWord[i];
						i+=2;
						pInfo	=	new	Material::Info();
						pInfo->strTemplate	=	vecWord[i++];
						if(!ParseMaterial(vecWord,i,pInfo)){
							SAF_D(pInfo);
							return;
						}else{
							m_mapMaterialInfo[strMaterial]	=	pInfo;
						}
					}
				}
			}

			Air::U1 MaterialParse::ParseMaterial( StringVector& vecWord,U32& i,Material::Info* pInfo ){
				while(true){
					if(i	>=	vecWord.size()){
						break;
					}
					AString&	str	=	vecWord[i];

					enumMaterial	m	=	(enumMaterial)GetElement(m_mapParam,str);
					if(m	==	enMaterial)
						return	true;
					i++;
					if(m	==	enUnKnown){
						continue;
					}
					
					switch(m){
					case	enVector:{
						Float4	v;
						v.x	=	Common::Converter::ToFloat(vecWord[i++]);
						v.y	=	Common::Converter::ToFloat(vecWord[i++]);
						v.z	=	Common::Converter::ToFloat(vecWord[i++]);
						v.w	=	Common::Converter::ToFloat(vecWord[i++]);
						pInfo->vecFloatParam.push_back(v);
						break;}
					case	enMatrix:{

						U32	uiOldSize	=	pInfo->vecFloatParam.size();
						pInfo->vecFloatParam.resize(uiOldSize+4);
						break;}
					case	enVectorArray:{
						U32	uiArray		=	Common::Converter::ToU32(vecWord[i++]);
						U32	uiOldSize	=	pInfo->vecFloatParam.size();
						pInfo->vecFloatParam.resize(uiOldSize+uiArray);
						break;}
					case	enMatrixArray:{
						U32	uiArray		=	Common::Converter::ToU32(vecWord[i++]);
						U32	uiOldSize	=	pInfo->vecFloatParam.size();
						pInfo->vecFloatParam.resize(uiOldSize+uiArray*4);
						break;}
					case	enPriority:{
						pInfo->uiPriority	=	Common::Converter::ToU32(vecWord[i++]);
						break;}
					case	enTexture:
						pInfo->vecTextureName.push_back(vecWord[i++]);
						break;
					case	enUseSkin:{
						pInfo->bUseSkin		=	Common::Converter::ToU1(vecWord[i++]);
						break;}
					default:
						break;
					}
				}
				return	true;;
			}

			Material::Info* MaterialParse::GetMaterialInfo( CAString& strName ){
				MaterialInfoMap::iterator	i	=	m_mapMaterialInfo.find(strName);
				if(i!=m_mapMaterialInfo.end()){
					return	i->second;
				}
				return	NULL;
			}
			void	MaterialParse::CompileMaterialSet(U8*	pData,U32	uiSize){
				if(pData==NULL	||	uiSize==0)
					return;
				IniFile inifile;

				if(!inifile.LoadFileFromMemory(pData,uiSize))
					return;
				SortList&	sortMap	=	inifile.GetSortMap();

				SortList::iterator	itr	=	sortMap.begin();
				for(;itr!=sortMap.end();itr++){
					SortMap&	sortMapItem	=	itr->second;

					MaterialSetInfo&	info	=	m_mapMaterialSetInfo[itr->first];

					info.mapTexture.clear();

					SortMap::iterator	i	=	sortMapItem.begin();

					AString	strName;
					for(;i!=sortMapItem.end();i++){
						StringVector&	v	=	i->second;
						if(v.empty()){
							continue;
						}
						strName	=	i->first;
						Converter::ToLowerCase(strName);
						enumMaterialSetParameterType	t	=	(enumMaterialSetParameterType)m_mapMaterialParamType[strName];
						switch(t){
							case enMSPT_Diffuse:{
								Converter::ParseString(v[0],(float*)&info.diffuse_opacity,3);
								break;}
							case enMSPT_Ambient:{
								Converter::ParseString(v[0],(float*)&info.ambient_alphatest,3);
								break;}
							case enMSPT_Specular:{
								Converter::ParseString(v[0],(float*)&info.specular_glossiness,3);
								break;}
							case enMSPT_Glossiness:{
								info.specular_glossiness.w	=	Converter::ToFloat(v[0]);
								break;}
							case enMSPT_Opacity:{
								info.diffuse_opacity.w	=	Converter::ToFloat(v[0]);
								break;}
							case enMSPT_SpecularLevel:{

								break;}
							case enMSPT_SelfIllumColor:{
								Converter::ParseString(v[0],(float*)&info.selfIllumColor_fresnel,3);
								break;}
							case enMSPT_TexAmbient:
							case enMSPT_TexDiffuse:
							case enMSPT_TexSpecular:
							case enMSPT_TexGlossiness:
							case enMSPT_TexSpecularLevel:
							case enMSPT_TexSelfillumination:
							case enMSPT_TexOpacity:
							case enMSPT_TexFiltercolor:
							case enMSPT_TexBump:
							case enMSPT_TexReflection:
							case enMSPT_TexRefraction:
							case enMSPT_TexDisplacement:{
								info.mapTexture[t]	=	v[0];
								break;}
						}
					}

				}

			}
			void	MaterialParse::CompileMaterialParameterTable(U8*	pData,U32	uiSize){


			}

			MaterialSetInfo* MaterialParse::GetMaterialSetInfo( CAString& strName )
			{
				MaterialSetInfoMap::iterator	i	=	m_mapMaterialSetInfo.find(strName);
				if(i!=m_mapMaterialSetInfo.end()){
					return	&i->second;
				}
				return	NULL;
			}

			void MaterialParse::AddInfo( CAString& strName,MaterialTemplateInfo* pInfo )
			{
				if(pInfo==NULL||strName.empty())
					return;

				MaterialTemplateInfoMap::iterator	i	=	m_mapMaterialTemplateInfo.find(strName);
				if(i!=m_mapMaterialTemplateInfo.end()){
					//return	i->second;
					delete i->second;
					i->second	=	pInfo;
				}else{
					m_mapMaterialTemplateInfo[strName]	=	pInfo;
				}
			}

	}
};