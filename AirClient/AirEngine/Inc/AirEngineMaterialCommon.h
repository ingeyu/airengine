/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/07/30
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EngineMaterialCommon.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINEMATERIALCOMMON_HEAD_FILE
#define ENGINEMATERIALCOMMON_HEAD_FILE

#include "AirRenderBuffer.h"


namespace	Air{
	namespace Engine{
		enum	enumQualityType{
			enQT_VeryHigh,
			enQT_High,
			enQT_Middle,
			enQT_Low,
			enQT_VeryLow,
			enQT_Max
		};
		//材质模板hash
		struct PassHash{
			union{
				struct{
					U32		uiStateHash		:	8;	///<	&(0x00000fff)
					U32		uiStateNumber	:	2;	///<	Max	State	Number	is	3
					U32		uiShaderHash	:	14;	///<	&(0x00000fff)<<15
					U32		uiShaderNumber	:	3;	///<	Max	Shader	Number is	7 
					U32		uiPassNumber	:	2;
					U32		uiPriority 		:	3;	///<	优先级	0~7
				};
				U32			uiHash;
			};
			
			PassHash(){
				uiHash		=	0;
				uiPriority	=	4;
			};
			void	AddShader(void*	p){
				uiStateHash	+=	(U32)p&0x00000fff;
			};
			void	AddState(void*	p){
				uiStateHash	+=	(U32)p&0x00000fff;
			};
		};
		//材质hash
		struct	MaterialHash{
			union{
				struct{
					U32	uiConstantSize		:	8;
					U32	uiTextureHash		:	19;
					U32	uiTextureNumer		:	2;
					U32	uiPriority 			:	3;	///<	优先级	0~7
				};
				U32			uiHash;
			};
			MaterialHash(){
				uiHash		=	0;
				uiPriority	=	4;
			};
			void	AddTexture(void*	p){
				uiTextureHash	+=	(U32)p;
			};
		};
		/**	\brief	纹理信息
		*
		*	纹理信息
		*
		***/
		struct	TextureUnitInfo{
			TextureUnitInfo(U32 uiIdx	=	0,U32	reg	=	0){
				index		=	uiIdx;
				uiRigister	=	reg;
			};
			U32					index;
			U32					uiRigister;
			AString				strSamplerState;
		};
		typedef		std::vector<TextureUnitInfo>	TextureUnitInfoVector;

		/**	\brief	参数绑定类型
		*
		*	参数绑定类型
		*
		***/
		enum	enumParamBindType{
			enPBT_UNKNOWN,
			enPBT_BOOL,
			enPBT_INT,
			enPBT_FLOAT,
			enPBT_INT4,
			enPBT_VECTOR,
			enPBT_INT4ARRAY,
			enPBT_VECTORARRAY,
			enPBT_MATRIX,
			enPBT_MATRIXARRAY,
			enPBT_VECTOR_AUTO,
			enPBT_INT4_AUTO,
			enPBT_INT4ARRAY_AUTO,
			enPBT_VECTORARRAY_AUTO,
			enPBT_MATRIX_AUTO,
			enPBT_MATRIXARRAY_AUTO,
			enPBT_MAX
		};

		/**	\brief	参数绑定信息
		*
		*	参数绑定信息
		*
		***/
		struct	ParamBindInfo{
			ParamBindInfo(){
				uiRegister		=	0;
				bindType		=	enPBT_VECTOR;
				val.m_Int		=	0;
				uiSize			=	0;
			};
			enumParamBindType	bindType;		///<	绑定类型
			UInt				uiRegister;		///<	注册的寄存器位置
			Union4				val;
			UInt				uiSize;			///<	对数组有效 表示数组的大小
		};
		typedef	std::vector<ParamBindInfo*>	ParamBindInfoVector;
		/**	\brief	参数列表
		*
		*	参数列表
		*
		***/
		struct	ShaderParamInfo{
			ShaderParamInfo(AString	str){
				strName		=	str;
			};
			AString					strName;
			TextureUnitInfoVector	m_vecTextureInfo;	///<	纹理信息
		};
		/**	\brief	通道状态信息
		*
		*	通道状态信息
		*
		***/
		typedef	Render::StateInfo	PassStateInfo;

		/**	\brief	通道信息
		*
		*	通道信息
		*
		***/
		struct	PassInfo{
			PassInfo(CAString&	str	=	"UnName"){
				strName	=	str;
				for(UInt i=0;i<6;i++){
					pShaderArray[i]	=	NULL;
				}
			};
			~PassInfo(){
				for(UInt i=0;i<6;i++){
					SAF_D(pShaderArray[i]);
				}
			}
			AString					strName;

			ShaderParamInfo*		pShaderArray[6];	///<	着色语言信息

			AString					strBlendState;
			AString					strDepthStencilState;
			AString					strRasterizerState;
		}; 
		typedef	std::vector<PassInfo*>		PassInfoVector;

		/**	\brief	材质信息
		*
		*	材质信息
		*
		***/
		struct	MaterialTemplateInfo{
			MaterialTemplateInfo(CAString&	str){
				strName	=	str;
				PhaseIndex	=	enPI_MRT;
				uiPriority	=	4;
			}

			~MaterialTemplateInfo(){
				UInt iSize	=	m_vecPassInfo.size();
				for(UInt i=0;i<iSize;i++){
					SAF_D(m_vecPassInfo[i]);
				}
				m_vecPassInfo.clear();
			}

			AString				strName;
			enumPhaseIndex		PhaseIndex;
			PassInfoVector		m_vecPassInfo;
			U32					uiPriority;		///<	0~7
		};
		enum enumMaterialSetParameterType{
			enMSPT_Unknown,
			enMSPT_Diffuse,
			enMSPT_Ambient,
			enMSPT_Specular,
			enMSPT_Glossiness,
			enMSPT_Opacity,
			enMSPT_SpecularLevel,
			enMSPT_SelfIllumColor,
			enMSPT_TexAmbient,
			enMSPT_TexDiffuse,
			enMSPT_TexSpecular,
			enMSPT_TexGlossiness,
			enMSPT_TexSpecularLevel,
			enMSPT_TexSelfillumination,
			enMSPT_TexOpacity,
			enMSPT_TexFiltercolor,
			enMSPT_TexBump,
			enMSPT_TexReflection,
			enMSPT_TexRefraction,
			enMSPT_TexDisplacement
		};
		typedef	std::hash_map<enumMaterialSetParameterType,AString>	MaterialTexteureTypeMap;

		struct MaterialSetInfo{
			MaterialSetInfo(){
				diffuse_opacity				=	Float4(1,1,1,1);
				ambient_alphatest			=	Float4(0.5,0.5,0.5,0.5);
				specular_glossiness			=	Float4(0.1,0.1,0.1,0.1);
				selfIllumColor_fresnel		=	Float4(0,0,0,0);
			};
			Float4	diffuse_opacity;
			Float4	ambient_alphatest;
			Float4	specular_glossiness;
			Float4	selfIllumColor_fresnel;
			MaterialTexteureTypeMap	mapTexture;
		};

		typedef	std::hash_map<AString,MaterialSetInfo>	MaterialSetInfoMap;

		typedef	std::vector<Common::IntVec4>	Int4Vector;
		struct MaterialParameter{
			AString		strName;
			Int4Vector	vecTable;
			Float4		vValue;
			AString		strValue;
		};
		typedef	std::vector<MaterialParameter>	MaterialParameterVector;

	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINEMATERIALCOMMON_HEAD_FILE