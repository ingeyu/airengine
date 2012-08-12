#ifndef INTERFACERENDERMATERIAL_HEAD_FILE
#define INTERFACERENDERMATERIAL_HEAD_FILE


//#include "AirEngine.h"
#include "AirEngineHeader.h"
#include "AirInterfaceRenderCommon.h"
#include "AirCommonIniFile.h"
#include "AirInterfaceRenderEffect.h"
namespace Air{
	
	namespace Client{
	
		namespace	Render{
	
	
			/**	\brief	接收阴影
			*
			*	接收阴影
			*
			***/
			class	IReceiveShadowable{
			public:
				IReceiveShadowable():m_bRecevieShadow(false){};
				virtual	~IReceiveShadowable(){};
				/**	\brief	设置是否接受阴影
				*   
				*	@remarks 	设置是否接受阴影
				*	@see		ICastShadowable
				*	@return   	void
				*	@param		U1 bCastShadow
				*	@note
				*
				**/
				inline	void			SetReceiveShadow(U1	bReceiveShadow){m_bRecevieShadow	= bReceiveShadow;};
				/**	\brief	是否接受阴影
				*   
				*	@remarks 	是否接受阴影
				*	@see		ICastShadowable
				*	@return   	U1
				*	@note
				*
				**/
				inline	U1				IsReceiveShadow(){return m_bRecevieShadow;};
			protected:
	
				U1						m_bRecevieShadow;			///<	是否投射阴影
			};
	
	
	
	
	
			/**	\brief	材质接口
			*
			*	材质接口
			*
			***/
			class	IMaterial	:	public	IReceiveShadowable{
			public:
				/**	\brief	渲染技术类型
				*
				*	渲染技术类型
				*
				***/
				enum	enumTechinqueType{
					enTECH_VERYHIGH,		///<	最高效果
					enTECH_HIGH,			///<	较高效果
					enTECH_NORMAL,			///<	普通效果
					enTECH_LOW,				///<	最低效果
					enTECH_CASTSHADOW,		///<	投射阴影
					enTECH_DEFEREDSHADE,	///<	延迟作色
					enTECH_MAX				///<	max
				};
	
	
				typedef		SortMap			TechniqueInfo;
				typedef		StringVector	TechniqueParamList;
	
				typedef	stdext::hash_map<AString,enumParamType>	ParamTypeMap;
				typedef	ParamTypeMap::iterator					ParamTypeMapItr;
				typedef	ParamTypeMap::value_type				ParamTypeMapPair;
	
				/**	\brief	技术
				*
				*	技术
				*
				***/
				class	ENGINE_EXPORT	Technique{
				public:
					/**	\brief	参数
					*
					*	参数
					*
					***/
					struct	Param{
						AString					strName;			///<	参数名
						IEffect::ParamHandle	pHandle;			///<	参数句柄
						enumParamType			uiType;				///<	参数类型
						union{
							void*					pValue;			///<	指针类型
							U1						bValue;			///<	布尔类型
							SInt					iValue;			///<	整形
							Real					fValue;			///<	浮点
						};
					};
					typedef	std::vector<Param>			ParamArray;		///<	参数数组
					typedef	ParamArray::iterator		ParamArrayItr;	///<	参数迭代器
	
					typedef	std::map<AString,Param*>		ParamMap;
					typedef	ParamMap::iterator				ParamMapItr;
					typedef	ParamMap::value_type			ParamMapPair;
	
					/**	\brief	创建信息
					*
					*	创建信息
					*
					***/
					struct	Info{
						IEffect*				pEffect;				///<	默认效果
						TechniqueInfo*			strConfigInfo;			///<	材质文件中的配置信息
					};
	
				public:
					Technique(AString	strName,Info*	pInfo);
	
					/**	\brief	创建
					*   
					*	@remarks 	创建
					*	@see		Technique
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1		Create();
					/**	\brief	摧毁
					*   
					*	@remarks 	摧毁
					*	@see		Technique
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1		Destroy();
	
					/**	\brief	设置布尔参数
					*   
					*	@remarks 	设置布尔参数
					*	@see		Technique
					*	@return   	U1
					*	@param		ParamHandle pParam
					*	@param		U1 bValue
					*	@note
					*
					**/
					virtual U1			SetParam(AString	strName,	U1		bValue);
					/**	\brief	设置整形参数
					*   
					*	@remarks 	设置整形参数
					*	@see		Technique
					*	@return   	U1
					*	@param		ParamHandle pParam
					*	@param		SInt iValue
					*	@note
					*
					**/
					virtual U1			SetParam(AString	strName,	SInt	iValue);
					/**	\brief	设置浮点参数
					*   
					*	@remarks 	设置浮点参数
					*	@see		Technique
					*	@return   	U1
					*	@param		ParamHandle pParam
					*	@param		Real fValue
					*	@note
					*
					**/
					virtual U1			SetParam(AString	strName,	Real	fValue);
					/**	\brief	设置参数
					*   
					*	@remarks 	设置参数（向量）
					*	@see		Technique
					*	@return   	U1
					*	@param		ParamHandle pParam
					*	@param		Float4 * pVector
					*	@note
					*
					**/
					virtual U1			SetParam(AString	strName,	void*	pVector,UInt uiSize);
	
					/**	\brief	设置四维向量
					*   
					*	@remarks 	设置四维向量
					*	@see		Technique
					*	@return   	U1
					*	@param		AString strName
					*	@param		Float4 v
					*	@note
					*
					**/
					virtual	U1			SetParam(AString strName,		Float4& v);
	
					/**	\brief	设置矩阵
					*   
					*	@remarks 	设置矩阵
					*	@see		Technique
					*	@return   	U1
					*	@param		AString strName
					*	@param		Float44 & pMatrix
					*	@note
					*
					**/
					virtual	U1			SetParam(AString strName,		Float44& pMatrix);
					/**	\brief	设置纹理
					*
					*
					*	@remarks 	设置参数（纹理）
					*	@see		Technique
					*	@param		ParamHandle pParam
					*	@param		ITexture* pTexture
					*
					***/
					virtual	U1			SetParam(AString	strName,	ITexture*	pTexture);
	
					/**	\brief	获取参数
					*   
					*	@remarks 	获取参数
					*	@see		Technique
					*	@return   	void*
					*	@note
					*
					**/
					virtual	void*		GetParam(AString	strName);
	
	
					/**	\brief	初始化参数类型表
					*   
					*	@remarks 	初始化参数类型表
					*	@see		Technique
					*	@return   	void
					*	@note
					*
					**/
					static	void	InitParamTypeMap();
					/**	\brief	获取参数类型
					*   
					*	@remarks 	获取参数类型
					*	@see		Technique
					*	@return   	UInt
					*	@param		AString strName
					*	@note
					*
					**/
					static	enumParamType	GetParamTypeByName(AString strName);
	
					static	ParamTypeMap					m_mapParamType;
	
					/**	\brief	使用该技术来渲染
					*   
					*	@remarks 	使用该技术来渲染
					*	@see		Technique
					*	@return   	void
					*	@param		Draw::Buff drawBuff
					*	@note
					*
					**/
					void	Render(Draw::Buff drawBuff);
				protected:
					/**	\brief	获取参数的值
					*   
					*	@remarks 	获取参数的值
					*	@see		Technique
					*	@return   	U1
					*	@param		Param & p
					*	@param		AChar * strValue
					*	@note
					*
					**/
					U1	GetParamValue(Param&	p,AChar*	strValue);
	
					/**	\brief	清理参数列表
					*   
					*	@remarks 	清理参数列表
					*	@see		Technique
					*	@return   	U1
					*	@note
					*
					**/
					U1	ClearParamArray();
	
					/**	\brief	设置参数
					*   
					*	@remarks 	设置参数
					*	@see		Technique
					*	@return   	U1
					*	@param		Param & param
					*	@note
					*
					**/
					U1	SetFXParam( Param& param );
	
	
				protected:
					Info					m_Info;			///<	技术信息
					AString					m_strName;		///<	技术名
					ParamArray				m_ParamArray;	///<	参数列表
					IEffect::ParamHandle	m_pHandle;		///<	技术指针
					ParamMap				m_mapParam;		///<	参数索引
	// 				U8*						pIAInputSignature;
	// 				UInt					IAInputSignatureSize;
	
				};
			public:
				virtual ~IMaterial(){};
	
				/**	\brief	渲染
				*   
				*	@remarks 	渲染
				*	@see		IMaterial
				*	@return   	void
				*	@param		Draw::Buff buff
				*	@note
				*
				**/
				virtual	void	Render(Draw::Buff	buff)		=	NULL;
	
				/**	\brief	获取一个技术
				*   
				*	@remarks 	获取一个技术
				*	@see		IMaterial
				*	@return   	Technique*
				*	@param		UInt uiIndex
				*	@note
				*
				**/
				virtual Technique*	GetTechnique(enumTechinqueType type 	=	enTECH_VERYHIGH)	=	NULL;
				/**	\brief	设置一个技术
				*   
				*	@remarks 	设置一个技术
				*	@see		IMaterial
				*	@return   	void
				*	@param		UInt uiIndex
				*	@note
				*
				**/
				virtual void		SetTechnique(enumTechinqueType type 	=	enTECH_VERYHIGH)	=	NULL;
				/**	\brief	获取当前技术
				*   
				*	@remarks 	获取当前技术
				*	@see		IMaterial
				*	@return   	Technique*
				*	@note
				*
				**/
				virtual	Technique*	GetCurrentTechnique()	=	NULL;
	
				/**	\brief	是否使用Aplha混合
				*   
				*	@remarks 	是否使用Alpha混合
				*	@see		IMaterial
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			IsAlphaBlend()			=	NULL;
			};
	
			typedef	Common::RefPtr<IMaterial*>	IMaterialPtr;
	
		}
	
	};
};
#endif // INTERFACERENDERMATERIAL_HEAD_FILE