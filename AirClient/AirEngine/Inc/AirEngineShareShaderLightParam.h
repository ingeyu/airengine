#ifndef ENGINESHARESHADERLIGHTPARAM_HEAD_FILE
#define ENGINESHARESHADERLIGHTPARAM_HEAD_FILE

namespace Client{

#ifndef		LIGHT_COUNT
#define		LIGHT_COUNT	50
#endif

	/**	\brief	灯光参数
	*
	*	灯光参数
	*
	***/
	class	LightParam{
	public:
		LightParam(){
			m_AmibentColor	=	Float4(0.5,0.5,0.5,1);
			m_LightPosition.resize(LIGHT_COUNT);
			m_LightDiffuse.resize(LIGHT_COUNT);

			for(UInt i=0;i<LIGHT_COUNT;i++){
				m_pShadowTexture[i]		=	NULL;
				m_pShadowTextureCube[i]	=	NULL;
				m_LightPosition[i]		=	Float4(100,100,100,100);
				m_LightDiffuse[i]		=	Float4(0,0,0,0);

			}
		};

		//环境光
		Float4						m_AmibentColor;
		//灯光
		VectorArray					m_LightPosition;
		VectorArray					m_LightDiffuse;

		Float44						m_matShadow[LIGHT_COUNT];
		//阴影纹理
		Render::ITexture*			m_pShadowTexture[LIGHT_COUNT];		///<	平行光和聚光灯的
		Render::ITexture*			m_pShadowTextureCube[LIGHT_COUNT];	///<	点光源的阴影深度
	};

};
#endif // ENGINESHARESHADERLIGHTPARAM_HEAD_FILE