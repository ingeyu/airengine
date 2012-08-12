#include "AirEngineShaderShareParam.h"
//#include "asm_math.h"
namespace Air{
	
	namespace	Client{
	
	
		ShaderShareParam::ShaderShareParam(){
			m_bLeftHand			=	true;
			m_bUpDirY			=	true;
			m_bRenderShadow		=	false;
	
	
			m_vBoundMin			=	Float3(0,0,0);
			m_vBoundMax			=	Float3(0,0,0);
			m_vBoundSphere		=	Float4(0,0,0,0);
			m_vCursorPosition	=	Float4(0,0,0,0);
			m_vCursorMove		=	Float4(0,0,0,0);
	
			m_iScreenWidth		=	1024;
			m_iScreenHeight		=	768;
	
			m_fTotalTime		=	0;
			m_fTimeDelta		=	0;
			m_fEngineTimeDelta	=	0;
			m_fEngineTotalTime	=	0;
	
// 			m_matView			=	XMMATRIX::IDENTITY;
// 			m_matProj			=	Float44::IDENTITY;
// 			m_matViewProj		=	Float44::IDENTITY;
// 			for(int i=0;i<MAX_LIGHT;i++)
// 				m_matShadow[i]	=	Float44::IDENTITY;
// 			m_matWorld			=	Float44::IDENTITY;
// 			m_matWorldView		=	Float44::IDENTITY;
// 			m_matWorldViewProj	=	Float44::IDENTITY;
// 			m_matViewProjI		=	Float44::IDENTITY;
	
	
			//摄像机角度
			m_fFOV				=	3.14159265f/4.0f;
			//纵横比
			m_fASpect			=	(Real)m_iScreenWidth/m_iScreenHeight;
			//最近裁剪距离 不要设定得太小 否则会导致 模型与模型 面与面 跳动得厉害
			//一般设定1左右就可以了 0.01的时候比较闪
			m_fNearCullDistance	=	3.0f;
			m_fFarCullDistance	=	5000.0f;
	
			m_vCurrentLookAt	=	Float3(0,0,0);
			m_vCurrentPosition	=	Float3(300,10,10);
			if(m_bUpDirY)
				m_vCurrentUpDirection	=	Float3(0,1,0);
			else
				m_vCurrentUpDirection	=	Float3(0,0,1);
			m_vCurrentRightDirection	=	Float3(1,0,0);
	
	
			m_AmibentColor		=	Float4(1.0f,1.0f,1.0f,1.0f);
	
			m_LightPosition.resize(50);
			m_LightDiffuse.resize(50);
			for(UInt i=0;i<50;i++){
				UpdataLight(i,Float4(100,100,100,100.0f),Float4(0,0,0,0));
				//edit	by	infernalhell	FUCK	U
	// 			m_pShadowTexture[i]				=	NULL;
	// 			m_pShadowTextureCube[i]			=	NULL;
			}
	
			m_uiNumBone		=	60;
			m_BoneMatrixArray.resize(m_uiNumBone);
	
			m_pBoneTexture	=	NULL;
	
		}
	
		void ShaderShareParam::UpdataBound( BoundBox& box ){
	
// 			m_vBoundMin	=	box.Center	-	box.Extents;
// 			m_vBoundMax	=	box.m_vMax;
// 			Float3 vCenter	=	box.GetCenter();
// 			m_vBoundSphere	=	Float4(vCenter.x,vCenter.y,vCenter.z,box.GetHalfSize().length());
	
		}
	
		void ShaderShareParam::UpdataLight( UInt uiLightID,Float4 pos,Float4 diff /*= Float4(1,1,1,1)*/ ){
			if(uiLightID < 0)
				return;
			m_LightPosition[uiLightID]	=	pos;
			m_LightDiffuse[uiLightID]	=	diff;
		}
		void ShaderShareParam::UpdataWorldMatrix(Float44* pMatrix ){
			m_matWorld	=	*pMatrix;
			//这个地方2个矩阵相乘可能会有问题 留下记号
// 			m_matWorldView		=	m_matWorld		*	m_matView;
// 			m_matWorldViewProj	=	m_matWorldView	*	m_matProj;
	//  		AString	str	=	AString("\nW")	+Converter::toString(m_matWorld)	+	
	//  						AString("\nV")	+Converter::toString(m_matView)	+
	//  						AString("\nP")	+Converter::toString(m_matProj);
	//  		OutputDebugStringA(str.c_str());
	//  		OutputDebugStringA("\n");
		}
	
	}
};