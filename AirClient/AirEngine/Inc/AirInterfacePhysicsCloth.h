#ifndef INTERFACEPHYSICSCLOTH_HEAD_FILE
#define INTERFACEPHYSICSCLOTH_HEAD_FILE

#include "AirInterfacePhysicsCollision.h"

namespace Air{
	
	namespace Client{
	
		namespace	Physics{
			/**	\brief	布料模拟基类
			*
			*	布料模拟基类
			*
			***/
			class	ICloth{
			public:
				/**	\brief	物理布料创建信息
				*
				*	创建信息
				*
				***/
				struct	Info{
					Info(){
						thickness = 0.01f;
						selfCollisionThickness = 0.2f;
						density = 1.0f;
						bendingStiffness = 1.0f;
						stretchingStiffness = 1.0f;
						hardStretchLimitationFactor = 1.0f;
						dampingCoefficient = 0.5f;
						friction = 0.5f;
						pressure = 1.0f;
						tearFactor = 1.5f;
						attachmentTearFactor = 1.5f;
						attachmentResponseCoefficient = 0.2f;
						collisionResponseCoefficient = 0.2f;
						userData	=	NULL;
					};
					Shape	shape;							///<	网格模型
					Real	thickness;						///<	厚度
					Real	selfCollisionThickness;			///<	自身碰撞厚度
					Real	density;						///<	密度
					Real	bendingStiffness;				///<	弯曲度
					Real	stretchingStiffness;			///<	力度
					Real	hardStretchLimitationFactor;
					Real	dampingCoefficient;				///<	阻尼
					Real	friction;						///<	摩擦力
					Real	pressure;						///<	压力
					Real	tearFactor;
					Real	collisionResponseCoefficient;
					Real	attachmentResponseCoefficient;
					Real	attachmentTearFactor;
					void*	userData;
	
				};
	
				virtual	Float3		GetVertexPosition(UInt	uiVertexIdx)	=	NULL;
				virtual	void		SetVertexPosition(UInt	uiVertexIdx,Float3&	vPos)	=	NULL;
				virtual	Float3		GetVertexVelocity(UInt	uiVertexIdx)	=	NULL;
				virtual	void		SetVertexVelocity(UInt	uiVertexIdx,Float3&	vSpeed)	=	NULL;
				virtual	void		AttachToObject(ICollision*	pObject)	=	NULL;
				virtual	void		DetachFromObject(ICollision*	pObject)	=	NULL;
				virtual	void		AddForceAtVertex(UInt	uiVertexIdx,Float3&	vVelocity)	=	NULL;
				virtual	void		AddForceAtPos(Float3&	vPos,Float3&	vVelocity)	=	NULL;
				virtual	const BoundingBox&	GetWorldBoundingBox()	=	NULL;
	
	
				/**	\brief	获取顶点缓冲区
				*   
				*	@remarks 	返回值为顶点数
				*	@see		ICloth
				*	@return   	UInt
				*	@param		SBuff * pBuff
				*	@note
				*
				**/
				virtual	UInt	GetVertexBuff(SBuff*	pBuff)	=	NULL;
				/**	\brief	获取索引缓冲区
				*   
				*	@remarks 	返回值为索引数量
				*	@see		ICloth
				*	@return   	UInt
				*	@param		UInt * pBuff
				*	@note
				*
				**/
				virtual	UInt	GetIndexBuff(UInt*				pBuff)	=	NULL;
			};
		}
	
	};
};
#endif // INTERFACEPHYSXCLOTH_HEAD_FILE