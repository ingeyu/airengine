#include "AirPhysicsObject.h"
#include "AirPhysicsSystem.h"
namespace	Air{
	namespace	Physics{

		AString	Object::ProductTypeName	=	"PhysicsObject";
		Object::Object( CAString& strName,Info* pInfo ):MovableObject(strName)
		{
			if(pInfo!=NULL){
				m_Info	=	*pInfo;
			}

			m_uiMask	=	enPCM_DynamicObject;
		}

		Air::U1 Object::Create()
		{
			if(m_Info.uiShapeCount==0)
				return false;
			//memcpy(m_)
			return true;
		}

		Air::U1 Object::Destroy()
		{
			return true;
		}

		Air::U1 Object::CollosionDetect( const Float3& p,Float3& v,U32 uiMask )
		{
			if(m_uiMask&uiMask){
				U32 uiShapeCount	=	m_Info.uiShapeCount;
				for(U32 i=0;i<uiShapeCount;i++){
					//use world space shape
					Shape& shape	=	m_WorldShape[i];
					switch(shape.m_Type){
						case 	enPST_Point:	{

												}break;
						case	enPST_Triangle:	{}break;
						case	enPST_Box:		{
							
							BoundingBox	b(shape.m_vPosition-shape.m_vHalfSize,shape.m_vPosition+shape.m_vHalfSize);
							if(b.IsInclude(p)){
								Float3 vNormal	=	p	-	shape.m_vPosition;
								vNormal.Normalize();
								v	+=	vNormal*(-v).Dot(vNormal)*2;
								return true;
							}
												}break;
						case	enPST_Sphere:	{
							Float3 vNormal	=	p	-	shape.m_vPosition;
							
							if(vNormal.Length()	<	shape.m_vHalfSize.x){
								vNormal.Normalize();
								v	+=	vNormal*(-v).Dot(vNormal)*2;
								return true;
							}
												}break;
						case	enPST_Cylinder:	{

							Float3 vNormal	=	p	-	shape.m_vPosition;
							Float3 vTemp	=	vNormal;
							vTemp.y=0;
							float	fLength	=	vTemp.Length();	
							if(	vNormal.y	>	0	&&	
								vNormal.y	<	shape.m_vHalfSize.y	&&
								fLength		<	shape.m_vHalfSize.x)
							{
								v.y = -v.y;
								Float3 vTempV	=	v;
								vTempV.y=0;
								vTemp.Normalize();
								vTempV	+=	vTemp*(-vTempV).Dot(vTemp)*2;
								v.x		=	vTempV.x;
								v.z		=	vTempV.z;
								return true;
							}
												}break;
						case	enPST_Plane:	{

												}break;
					}
				}
			}
			return false;
		}

		void Object::Update( const Float44& ParentGlobalWorldMatrix, const Float4& ParentGlobalWorldQuat, const Float3& ParentGlobalWorldScale, U1 bParentDirty )
		{
			U32 uiShapeCount	=	m_Info.uiShapeCount;
			for(U32 i=0;i<uiShapeCount;i++){
				//local space to world space
				Shape& shape			=	m_Info.pShapeArray[i];
				Shape& worldShape		=	m_WorldShape[i];
				worldShape				=	shape;
				worldShape.m_vPosition	=	ParentGlobalWorldMatrix.GetPosition()+shape.m_vPosition;
				worldShape.m_vHalfSize	=	shape.m_vHalfSize*ParentGlobalWorldScale;
			}
		}

	}
}