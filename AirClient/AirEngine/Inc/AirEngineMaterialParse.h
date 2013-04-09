#ifndef ENGINEMATERIALPARSE_HEAD_FILE
#define ENGINEMATERIALPARSE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMaterialCommon.h"
#include "AirInterfaceResourceSystem.h"
#include "AirEngineMaterial.h"
namespace Air{
	
	namespace Engine{
	
		//namespace	Render{



			typedef	std::map<AString,U32>						MaterialParamMap;			///<	材质参数	字符串转枚举类
			typedef	std::map<AString,MaterialTemplateInfo*>		MaterialTemplateInfoMap;	///<	材质信息表
			typedef	std::map<AString,Material::Info*>			MaterialInfoMap;
			typedef	std::map<AString,PassStateInfo*>			PassStateMap;				///<	通道状态信息表
			typedef	std::vector<enumParamBindType>				ParamBindTypeMap;
			typedef	std::map<AString,enumPhaseIndex>			PhaseIndexMap;
			/**	\brief	 材质解析
			*
			*	材质解析
			*
			***/
			class	ENGINE_EXPORT	MaterialParse	:
				public	MemoryObject,
				public	Singleton<MaterialParse>{
			public:
				MaterialParse();
				virtual	~MaterialParse();
				/**	\brief	编译材质脚本模板
				*   
				*	@remarks 	编译材质脚本模板
				*	@see		MaterialParse
				*	@return   	void
				*	@param		Data * pData
				*	@note
				*
				**/
				void		CompileMaterialTemplate(U8*	pData,U32	uiSize);
	
				/**	\brief	编译状态
				*   
				*	@remarks 	编译状态
				*	@see		MaterialParse
				*	@return   	void
				*	@param		Data * pData
				*	@note
				*
				**/
				void		CompileState(U8*	pData,U32	uiSize);
				void		CompileMaterial(U8*	pData,U32	uiSize);
				void		CompileMaterialSet(U8*	pData,U32	uiSize);
				void		CompileMaterialParameterTable(U8*	pData,U32	uiSize);
				Material::Info*		GetMaterialInfo(CAString&	strName);
				/**	\brief	获取材质信息
				*   
				*	@remarks 	获取材质信息
				*	@see		MaterialParse
				*	@return   	MaterialTemplateInfo*
				*	@param		CAString& strName
				*	@note
				*
				**/
				MaterialTemplateInfo*	GetMaterialTemplateInfo(CAString&		strName);
	
				/**	\brief	获取材质通道状态信息
				*   
				*	@remarks 	获取材质通道状态信息
				*	@see		MaterialParse
				*	@return   	PassStateInfo*
				*	@param		AString strName
				*	@note
				*
				**/
				PassStateInfo*			GetPassStateInfo(CAString&	strName);

				MaterialSetInfo*		GetMaterialSetInfo(CAString&	strName);

				void					AddInfo(CAString&		strName,MaterialTemplateInfo*	pInfo);
			protected:
				/**	\brief	解析材质部分
				*   
				*	@remarks 	解析材质部分
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		MaterialInfo * pInfo
				*	@note
				*
				**/
				U1	ParseMaterialTemplate(StringVector&	vecWord,U32&	i,MaterialTemplateInfo*	pInfo);
				U1	ParseMaterial(StringVector&	vecWord,U32&	i,Material::Info*	pInfo);
				/**	\brief	解析技术部分
				*   
				*	@remarks 	解析技术部分
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		TechniqueInfo * pInfo
				*	@note
				*
				**/
				//U1	ParseTechnique(StringVector&	vecWord,U32&	i,TechniqueInfo*	pInfo);
				/**	\brief	解析通道部分
				*   
				*	@remarks 	解析通道部分
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		PassInfo * pInfo
				*	@note
				*
				**/
				U1	ParsePass(StringVector&	vecWord,U32&	i,PassInfo*	pInfo);
				/**	\brief	解析材质参数部分
				*   
				*	@remarks 	解析材质参数部分
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		ShaderParamInfo * pInfo
				*	@note
				*
				**/
				U1	ParseShaderParam(StringVector&	vecWord,U32&	i,ShaderParamInfo*	pInfo);
				/**	\brief	解析纹理部分
				*   
				*	@remarks 	解析纹理部分
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		TextureUnitInfo * pInfo
				*	@note
				*
				**/
				U1	ParseTexture(StringVector&	vecWord,U32&	i,TextureUnitInfo*	pInfo);
				/**	\brief	解析参数
				*   
				*	@remarks 	解析参数
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		ParamBindInfo * pInfo
				*	@note
				*
				**/
				U1	ParseParam(StringVector&	vecWord,U32&	i,ParamBindInfo*	pInfo);
	
				/**	\brief	
				*   
				*	@remarks 	
				*	@see		MaterialParse
				*	@return   	U1
				*	@param		StringVector & vecWord
				*	@param		U32 & i
				*	@param		PassStateInfo * pInfo
				*	@note
				*
				**/
				U1	ParseState(StringVector&	vecWord,U32&	i,PassStateInfo*	pInfo);
				/**	\brief	类型转换
				*   
				*	@remarks 	类型转换
				*	@see		
				*	@return   	Air::U1
				*	@param		ParamBindInfo & info
				*	@note
				*
				**/
				U1	ParamType2BindType(Render::enumParamType type,ParamBindInfo& info);
			
				MaterialParamMap	m_mapParam;
				MaterialParamMap	m_mapStencileOP;
				MaterialParamMap	m_mapBlendOP;
				MaterialParamMap	m_mapBlend;
				MaterialParamMap	m_mapTextureAddress;
				MaterialParamMap	m_mapTextureFilter;
				MaterialParamMap	m_mapDepthWriteMask;
				MaterialParamMap	m_mapFillMode;
				MaterialParamMap	m_mapCullMode;
				MaterialParamMap	m_mapFog;
				MaterialParamMap	m_mapCompare;
				MaterialParamMap	m_mapParamBindType;
				MaterialParamMap	m_mapParamBindPos;
				ParamBindTypeMap	m_vecParamBindType;
				MaterialParamMap	m_mapMaterialParamType;
	
				MaterialParamMap	m_mapRS;
			protected:
				PassStateMap				m_mapPassState;					///<	通道状态信息
				MaterialTemplateInfoMap		m_mapMaterialTemplateInfo;		///<	材质信息 这个需要预编译
				MaterialInfoMap				m_mapMaterialInfo;
				PhaseIndexMap				m_mapPhaseIndex;
				MaterialSetInfoMap			m_mapMaterialSetInfo;
			};
		//}
	
	};
};
#endif // INTERFACERENDERMATERIALPARSE_HEAD_FILE