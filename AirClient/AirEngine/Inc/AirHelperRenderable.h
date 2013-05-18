#pragma once
#include "AirEngineRenderable.h"
#include "AirEngineMovableObject.h"

namespace	Air{
	namespace	Engine{
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
		class BoxRenderable;
		class	ObjectController;
		class	MoveRenderable	:	public Renderable{
		public:
			MoveRenderable(ObjectController* pControl);
			virtual	~MoveRenderable();
			virtual	void BeforeRender( Material* pMaterial );
			virtual	Matrix*	GetWorldMatrix();
			ObjectController* m_pControl;
		};
		class	RotateRenderable	:	public Renderable{
		public:
			RotateRenderable(ObjectController* pControl);
			virtual	~RotateRenderable();
			virtual	void BeforeRender( Material* pMaterial );
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
			inline enumMouseRayCastType	GetType()const{
				return m_RayCastType;
			};
			void					SetPosition(const Float3& vPos,float fScale);
			void					SetSelectObjectBoundingBox(const BoundingBox& bound);
			void					SetRayCastObjectBoundingBox(const BoundingBox& bound);
		protected:
			MoveRenderable*			m_pMove;
			RotateRenderable*		m_pRotate;
			BoxRenderable*			m_pSelectBox;
			BoxRenderable*			m_pRayCastBox;
			enumMouseControlMode	m_ControlMode;
			enumMouseRayCastType	m_RayCastType;
		};
	}
}