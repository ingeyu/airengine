#ifndef ENGINESHADERSHAREPARAM_HEAD_FILE
#define ENGINESHADERSHAREPARAM_HEAD_FILE

#include "AirEngineHeader.h"
namespace Air{
	
	namespace Engine{
	
	#ifndef MAX_LIGHT
	#define MAX_LIGHT	9
	#endif
	
		class						Material;
	
		class	ShaderShareParam{
		public:
			ShaderShareParam();
	
			void UpdataBound( BoundBox& box );
			/**	\brief	更新灯光信息
			*   
			*	@remarks 	更新灯光信息
			*	@see		GlobalSetting
			*	@return   	void
			*	@param		UInt uiLightID
			*	@param		Float4 pos
			*	@param		U1 bPointLight
			*	@param		Float4 diff
			*	@note
			*
			**/
			void	UpdataLight(UInt uiLightID,Float4 pos,Float4 diff);
	
			/**	\brief	渲染物体之前调用此函数 将自己的世界矩阵进行更新
			*   
			*	@remarks 	在材质中才可以自动绑定
			*	@see		GlobalSetting
			*	@return   	void
			*	@param		Float44 * pMatrix
			*	@note
			*
			**/
			void	UpdataWorldMatrix(Float44*	pMatrix);
	
			//摄像机位置朝向
			Float3				m_vCurrentPosition;
			Float3				m_vCurrentLookAt;
			Float3				m_vCurrentUpDirection;
			Float3				m_vCurrentDirection;
			Float3				m_vCurrentRightDirection;
			//矩阵
			Float44				m_matView;
			Float44				m_matProj;
			Float44				m_matViewProj;
			Float44				m_matShadow[MAX_LIGHT];
			Float44				m_matWorld;
			Float44				m_matWorldView;
			Float44				m_matWorldViewProj;
			Float44				m_matViewProjI;
	
			//环境光
			Float4				m_AmibentColor;
			//灯光
			VectorArray			m_LightPosition;
			VectorArray			m_LightDiffuse;
	
			//屏幕
			Real				m_iScreenWidth;
			Real				m_iScreenHeight;
	
			//摄像机
			Real				m_fFOV;
			Real				m_fASpect;
			Real				m_fNearCullDistance;
			Real				m_fFarCullDistance;
	
			//时间
			Real				m_fTimeDelta;
			Real				m_fTotalTime;
	
			Real				m_fEngineTimeDelta;
			Real				m_fEngineTotalTime;
	
			Float3						m_vBoundMin;			///<	包围盒最小值
			Float3						m_vBoundMax;			///<	包围盒最大值
			Float4						m_vBoundSphere;			///<	包围球
	
			Float4						m_vCursorPosition;		///<	鼠标位置
			Float4						m_vCursorMove;			///<	鼠标移动量
	
			Texture*			m_pShadowTexture[MAX_LIGHT];		///<	平行光和聚光灯的
			Texture*			m_pShadowTextureCube[MAX_LIGHT];	///<	点光源的阴影深度
	
		protected:
			U1							m_bLeftHand;			///<	是否使用左手坐标系
			U1							m_bUpDirY;				///<	顶方向
		public:
			U1	IsLeftHand(){
				return	m_bLeftHand;
			};
			U1	IsUpDirY(){
				return	m_bUpDirY;
			};
			U1							m_bRenderShadow;		///<	是否在渲染阴影
	
	
			U1							m_bPostComposer;				///<	是否为后期效果处理
			Texture*					m_pLastPostComposerResult;		///<	上一个后期效果处理结果纹理
			Material*					m_pCurrentPostComposerMaterial;	///<	当前后期效果材质
			Texture*					m_pBoneTexture;
	
	
			MatrixArray					m_BoneMatrixArray;				///<	骨骼矩阵
			UInt						m_uiNumBone;					///<	骨骼数量
	
		};
	
	};
};
#endif // ENGINESHADERSHAREPARAM_HEAD_FILE