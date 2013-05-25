#ifndef AirPhysicsObject_h__
#define AirPhysicsObject_h__

#include "AirPhysicsShape.h"

namespace	Air{
	namespace	Physics{
		class	ENGINE_EXPORT	Object	:	public	Common::IProduct{
		public:
			struct Info{
				void	RelativeToAbs(){
					for(U32 i=0;i<uiShapeCount;i++){
#ifdef _X86_
						pShapeArray[i]	=	(PointShape*)((U32)this + (U32)pShapeArray[i]);
#else
						pShapeArray[i]	=	(PointShape*)((U64)this + (U64)pShapeArray[i]);
#endif
					}
				};
				void	AbsToRelative(){
					for(U32 i=0;i<uiShapeCount;i++){
#ifdef _X86_
						pShapeArray[i]	=	(PointShape*)((U32)pShapeArray[i]-(U32)this);
#else
						pShapeArray[i]	=	(PointShape*)((U64)pShapeArray[i]-(U64)this);
#endif
					}
				}
				U32				uiBufferSize;
				float			fMass;
				U32				uiShapeCount;
				PointShape*		pShapeArray[4];
			};
			static AString	ProductTypeName;
			Object(CAString& strName,Info* pInfo);


			virtual	U1	Create();
			virtual	U1	Destroy();
			U1			CollosionDetect(const Float3& p,Float3& v,U32 uiMask);
		public:
			inline	U32			GetShapeCount(){
				return m_pInfo->uiShapeCount;
			};
			inline	PointShape*	GetShape(U32 uiIndex){
				return m_pInfo->pShapeArray[uiIndex];
			};
			inline	float		GetMass(){
				return m_pInfo->fMass;
			};
			inline	void		SetMask(U32 uiMask){
				m_uiMask	=	uiMask;
			}
			inline	U32			GetMask(){
				return m_uiMask;
			}
		public:
			Info*		m_pInfo; 
			U32			m_uiMask;
		};
	}
}
#endif // AirPhysicsObject_h__
