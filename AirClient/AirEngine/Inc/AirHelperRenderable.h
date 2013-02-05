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
		class	ObjectController;
		class	MoveRenderable	:	public Renderable{
		public:
			MoveRenderable(ObjectController* pControl);
			virtual	~MoveRenderable();
			virtual	Matrix*	GetWorldMatrix();
			ObjectController* m_pControl;
		};
		class	RotateRenderable	:	public Renderable{
		public:
			RotateRenderable(ObjectController* pControl);
			virtual	~RotateRenderable();
			virtual	Matrix*	GetWorldMatrix();
			ObjectController* m_pControl;
		};
		class ENGINE_EXPORT	ObjectController	:	public	MovableObject{
		public:
			ObjectController();
			virtual	~ObjectController();

			virtual	void			ProcessRenderObject(U32	uiPhaseFlag);
			enumMouseControlMode	ChangeMode(enumMouseControlMode mode);
			enumMouseRayCastType	ChangeType(const Float3& vStart,const Float3& vDir);
		protected:
			MoveRenderable*			m_pMove;
			RotateRenderable*		m_pRotate;
			enumMouseControlMode	m_ControlMode;
			enumMouseRayCastType	m_RayCastType;
		};
	}
}