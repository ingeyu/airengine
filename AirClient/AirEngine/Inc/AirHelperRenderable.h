#pragma once
#include "AirEngineRenderable.h"
#include "AirEngineMovableObject.h"

namespace	Air{
	namespace	Client{
		enum enumMouseRayCastType{
			eMRCT_None,
			eMRCT_X,
			eMRCT_Y,
			eMRCT_Z,
		};
		enum enumMouseControlMode{
			eMCM_Select,
			eMCM_Move,
			eMCM_Rotate,
			eMCM_Scale
		};
		class	MoveRenderable	:	public Renderable{
		public:
			MoveRenderable();
			virtual	~MoveRenderable();
			virtual	Matrix*	GetWorldMatrix(){return	&m_WorldMatrix;};
			Matrix	m_WorldMatrix;
		};
		class	RotateRenderable	:	public Renderable{
		public:
			RotateRenderable();
			virtual	~RotateRenderable();
			virtual	Matrix*	GetWorldMatrix(){return	&m_WorldMatrix;};
			Matrix	m_WorldMatrix;
		};
		class ENGINE_EXPORT	ObjectController	:	public	MovableObject{
		public:
			ObjectController();
			virtual	~ObjectController();

			virtual	void	ProcessRenderObject(U32	uiPhaseFlag);
		protected:
			MoveRenderable*			m_pMove;
			RotateRenderable*		m_pRotate;
			enumMouseControlMode	m_ControlMode;
			enumMouseRayCastType	m_RayCastType;
		};
	}
}