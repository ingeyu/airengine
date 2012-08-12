#ifndef ENGINESHARESHADEROBJECTPARAM_HEAD_FILE
#define ENGINESHARESHADEROBJECTPARAM_HEAD_FILE

namespace Client{

	class	ObjectParam{
	public:
		ObjectParam(){

		};
		Float44				m_matWorld;
		Float44				m_matWorldView;
		Float44				m_matWorldViewProj;

		Render::ITexture*			m_pBoneTexture;
		MatrixArray					m_BoneMatrixArray;				///<	¹Ç÷À¾ØÕó
		UInt						m_uiNumBone;					///<	¹Ç÷ÀÊýÁ¿
	};

};
#endif // ENGINESHARESHADEROBJECTPARAM_HEAD_FILE