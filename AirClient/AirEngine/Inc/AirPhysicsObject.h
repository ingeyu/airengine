#ifndef AirPhysicsObject_h__
#define AirPhysicsObject_h__

#include "AirPhysicsShape.h"
#include "AirEngineMovableObject.h"

namespace	Air{
	namespace	Physics{
		class	ENGINE_EXPORT	Object	:	
			public	Engine::MovableObject{
		public:
			struct Info{
				float			fMass;
				U32				uiShapeCount;
				Shape			pShapeArray[4];
			};
			static AString	ProductTypeName;
			Object(CAString& strName,Info* pInfo);


			virtual	U1	Create();
			virtual	U1	Destroy();
			U1			CollosionDetect(const Float3& p,Float3& v,U32 uiMask);

			virtual	void	Update(const Float44& ParentGlobalWorldMatrix, const Float4& ParentGlobalWorldQuat, const Float3& ParentGlobalWorldScale, U1 bParentDirty);
		public:
			inline	U32			GetShapeCount(){
				return m_Info.uiShapeCount;
			};
			inline	Shape&	GetShape(U32 uiIndex){
				return m_Info.pShapeArray[uiIndex];
			};
			inline	float		GetMass(){
				return m_Info.fMass;
			};
			inline	void		SetMask(U32 uiMask){
				m_uiMask	=	uiMask;
			}
			inline	U32			GetMask(){
				return m_uiMask;
			}
		public:
			Info		m_Info; 
			U32			m_uiMask;
		protected:
			Shape		m_WorldShape[4];
		};
	}
}
#endif // AirPhysicsObject_h__
