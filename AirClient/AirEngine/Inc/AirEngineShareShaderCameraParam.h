#ifndef ENGINESHARESHADERCAMERAPARAM_HEAD_FILE
#define ENGINESHARESHADERCAMERAPARAM_HEAD_FILE

namespace Client{

	class	CameraParam{
	public:
		CameraParam(){
			m_bLeftHand			=	true;
			m_bUpDirY			=	true;


			m_matView			=	Float44::IDENTITY;
			m_matProj			=	Float44::IDENTITY;
			m_matViewProj		=	Float44::IDENTITY;
			m_matViewProjI		=	Float44::IDENTITY;

			//摄像机角度
			m_fFOV				=	3.14159265f/4.0f;
			//纵横比
			m_fASpect			=	(Real)m_iScreenWidth/m_iScreenHeight;
			//最近裁剪距离 不要设定得太小 否则会导致 模型与模型 面与面 跳动得厉害
			//一般设定1左右就可以了 0.01的时候比较闪
			m_fNearCullDistance	=	1.0f;
			m_fFarCullDistance	=	5000.0f;

			m_vCurrentLookAt	=	Float3::ZERO;
			m_vCurrentPosition	=	Float3(300,10,10);
			if(m_bUpDirY)
				m_vCurrentUpDirection	=	Float3::UNIT_Y;
			else
				m_vCurrentUpDirection	=	Float3::UNIT_Z;
			m_vCurrentRightDirection	=	Float3::UNIT_X;

			m_iScreenWidth				=	1024;
			m_iScreenHeight				=	768;
		};
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
		Float44				m_matViewProjI;

		//屏幕
		Real				m_iScreenWidth;
		Real				m_iScreenHeight;

		//摄像机
		Real				m_fFOV;
		Real				m_fASpect;
		Real				m_fNearCullDistance;
		Real				m_fFarCullDistance;

		U1					m_bLeftHand;			///<	是否使用左手坐标系
		U1					m_bUpDirY;				///<	顶方向

		PlaneList			m_lstCullPlane;			///<	裁剪板列表
	};

};
#endif // ENGINESHARESHADERCAMERAPARAM_HEAD_FILE