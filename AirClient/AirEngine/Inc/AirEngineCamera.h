#ifndef ENGINECAMERA_HEAD_FILE
#define ENGINECAMERA_HEAD_FILE

#include "AirRenderCommon.h"
#include "AirEngineFrustum.h"
namespace Air{
	
	
	namespace Engine{
		class	Scene;
		class	MovableObject;

		enum	enumCameraType{
			enCT_UNKNOWN,
			enCT_MAIN,
			enCT_REFLECT,
			enCT_SHADOW,
			enCT_MAX
		};
	
		/**	\brief	摄像机类
		*
		*	摄像机类
		*
		***/
		class	ENGINE_EXPORT	Camera	:
			public	TProduct<Camera>,
			public	Frustum
		{
		public:
			Camera(CAString&	strName);
	
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		Camera
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		Camera
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
	

	
			/**	\brief	渲染
			*   
			*	@remarks 	渲染
			*	@see		Camera
			*	@return   	void
			*	@note
			*
			**/
			void				Render2D(SInt uiWidth	=	-1,SInt uiHeight	=	-1);
	
			/**	\brief	获取包围盒纹理的6个面的视野矩阵
			*   
			*	@remarks 	
			*	@see		Camera
			*	@return   	void
			*	@param		DWORD dwFace
			*	@note
			*
			**/
			void				RenderCubeMap( DWORD dwFace,SInt uiWidth	=	-1,SInt uiHeight	=	-1);

	
			Float3		GetRealDirection();
			Float3		GetRealPosition();
			Float3		GetRealRightDirection();
			Float3		GetRealUpDirection();
	
			/**	\brief	是否为反射摄像机
			*   
			*	@remarks 	是否为反射摄像机
			*	@see		Camera
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		IsReflect(){
				return	m_bReflect;
			}
			/**	\brief	设置是否启用反射
			*   
			*	@remarks 	设置是否启用反射
			*	@see		Camera
			*	@return   	void
			*	@param		U1 bEnable
			*	@note
			*
			**/
			inline	void	SetReflectEnable(U1	bEnable){
				m_bReflect	=	bEnable;
			};
			/**	\brief	设置反射平面
			*   
			*	@remarks 	设置反射平面
			*	@see		Camera
			*	@return   	void
			*	@param		Float3 normal
			*	@param		Real fDistance
			*	@note
			*
			**/
			void		SetReflectPlane(Float3 normal,Real	fDistance);


			enumCameraType			GetType(){
				return	m_Type;
			}
			void					SetType(enumCameraType	type){
				m_Type	=	type;
			};

			void			FindMovableObject(Scene*	pScene	=	NULL,Camera*	pMainCamera	=	NULL);
			void			ProcessShadowObject();
			void			AddMovableObject(MovableObject*	pObj);

			void			SetPhaseFlag(U32	flag);
			void			AddPhaseFlag(U32	flag);
			void			RemovePhaseFlag(U32	flag);
			void			ClearPhaseFlag();
			
		protected:
			Buffer*				m_pConstantBuffer;	///<	摄像机的ConstantBuffer
	
			U1					m_bReflect;			///<	是否为反射摄像机
			Plane				m_ReflectPlane;		///<	反射参照板
	
			TVector<MovableObject*>	m_vecReflectMovable;
			TVector<MovableObject*>	m_vecShadowMovable;
			enumCameraType			m_Type;
			U32						m_PhaseFlag;
		};
	};
};
#endif // ENGINECAMERA_HEAD_FILE