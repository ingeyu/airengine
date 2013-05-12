//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/08
 \version   ver 0.6.0.0
 \filepath  F:\Air\AirClient\AirEngine\Inc
 \filename  EngineCharacterAnimationModel.h
 \note     
       
 \attention:
			动画模型
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINECHARACTERANIMATIONMODEL_HEAD_FILE
#define ENGINECHARACTERANIMATIONMODEL_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirEngineCharacterResource.h"
#include "AirEngineRenderable.h"

class	CalModel;
class	CalHardwareModel;
namespace Air{
	namespace	Common{
		class	Float44;
	}
	
	namespace Engine{
	
		
		namespace	Character{
			class	ModelTemplate;
			/**	\brief	 动画相关
			*
			*	动画相关
			*
			***/
			namespace	Animation{
				typedef	CalModel							CoreAnimation;	
				/**	\brief	动作状态
				*
				*	动作状态
				*
				***/
				enum	enumActionState{
					ACT_STATE_IDLE,
					ACT_STATE_WALK,
					ACT_STATE_RUN,
					ACT_STATE_RIDE_IDLE,
					ACT_STATE_RIDE_WALK,
					ACT_STATE_RIDE_RUN,
					ACT_STATE_FLY_IDLE,
					ACT_STATE_FIY_WALK,
					ACT_STATE_FLY_RUN,
					ACT_STATE_SWIM_IDLE,
					ACT_STATE_SWIM_WALK,
					ACT_STATE_SWIM_RUN,
					ACT_STATE_DIE,
					ACT_STATE_MAX
				};
				class Model;
				/**	\brief	装备
				*
				*	装备
				*
				***/
				class Equipment	:
					public	Renderable{
				public:
					/**	\brief	装备类型
					*
					*	装备类型
					*
					***/
					enum	enType{
						enFace,
						enChest,
						enShoulder,
						enArm,
						enHand,
						enGloves,
						enwaist,
						enLeg,
						enShoe,
						enFoot,
						enMantle,
						enLeftWeapon,
						enRightWeapon,
						enHair,
						enMax
	
					};
					/**	\brief	通过ID获取装备类型名字
					*   
					*	@remarks 	通过ID获取装备类型名字
					*	@see		Equipment
					*	@return   	AString
					*	@param		enType type
					*	@note
					*
					**/
					static	AString	GetTypeNameByID(enType type);
					/**	\brief	通过装备名字获取ID
					*   
					*	@remarks 	通过装备名字获取ID
					*	@see		Equipment
					*	@return   	Client::Character::Animation::Equipment::enType
					*	@param		AString strName
					*	@note
					*
					**/
					static	enType	GetTypeIDByName(AString	strName);
	
					
				public:
					Equipment(CoreAnimation*	pCoreAnimation,enType type,Model*	pParent);
					virtual ~Equipment();
	
					/**	\brief	创建装备
					*   
					*	@remarks 	创建装备
					*	@see		Equipment
					*	@return   	U1
					*	@param		UInt uiMeshID
					*	@param		AString strMeshName
					*	@param		AString strMaterialName
					*	@note
					*
					**/
					U1			Create(	UInt			uiMeshID,
										CAString&		strMeshName,
										CAString&		strMaterialName,
										UInt**			pSubMesh	=	NULL);
					/**	\brief	创建装备
					*   
					*	@remarks 	创建装备
					*	@see		Equipment
					*	@return   	U1
					*	@param		UInt uiMeshID
					*	@param		AString strMeshName
					*	@param		AString strMaterialName
					*	@param		MeshHDBuffer * pHDBuff
					*	@note
					*
					**/
					U1			Create(	UInt			uiMeshID,
										CAString&		strMeshName,
										CAString&		strMaterialName,
										MeshHDBuffer*	pHDBuff		=	NULL);
					/**	\brief	摧毁装备
					*   
					*	@remarks 	摧毁装备
					*	@see		Equipment
					*	@return   	void
					*	@note
					*
					**/
					void		Destroy();
					/**	\brief	获取装备名字
					*   
					*	@remarks 	获取装备名字
					*	@see		Equipment
					*	@return   	AString
					*	@note
					*
					**/
					inline	CAString&		GetEquipmentName()const{return m_strName;};
	
					U1			IsNull();
					SInt		GetMeshID(){return m_uiMeshID;};

					virtual	U32			GetBoneCount();
					virtual	Float44*	GetBoneMatrix();
					virtual	Float44*	GetWorldMatrix();
				protected:
					enType					m_uiEquipmentType;				///<	类型ID
					SInt					m_uiMeshID;						///<	模型ID
	
					CoreAnimation*			m_pCoreAnimation;				///<	动画类指针
					AString					m_strName;						///<	装备名字
					Model*					m_pModel;
				};
				typedef	std::map<UInt,Equipment*>		EquipmentMap;		///<	装备列表
				typedef	EquipmentMap::iterator			EquipmentMapItr;	///<	装备列表迭代器
				typedef	EquipmentMap::value_type		EquipmentMapPair;	///<	装备列表容器
	
				/**	\brief	动作信息
				*
				*	动作信息
				*
				***/
				struct Action{
					AString					m_strName;						///<	动作名字
					UInt					m_uiActionID;					///<	动作ID
				};
	
				typedef	std::map<AString,Action>		ActionMap;			///<	动作列表		
				typedef	ActionMap::iterator				ActionMapItr;		///<	动作列表迭代器
				typedef	ActionMap::value_type			ActionMapPair;		///<	动作列表容器
	
				typedef	stdext::hash_map<UInt*,Equipment*>	EquipmentMeshMap;
				typedef	EquipmentMeshMap::iterator			EquipmentMeshMapItr;
				typedef	EquipmentMeshMap::value_type		EquipmentMeshMapPair;
				/**	\brief	动画模型
				*
				*	动画模型
				*
				***/
				class	ENGINE_EXPORT	Model	:
					public	Common::IProduct,
					public	MovableObject
				{
				public:
					static AString ProductTypeName;
					/**	\brief	创建信息
					*
					*	创建信息
					*
					***/
					struct Info{
						AString	strTemplate;	///<	资源目录
						
					};
				public:
					Model(CAString&	strName,Info* pInfo);
					virtual ~Model();
	
					Real	GetAnimationSpeed();
					void	SetAnimationSpeed(Real	fSpeed	=	1.0f);
					void	SetAnimationSpeedOffset(Real	fSpeedOffset	=	-0.01f);
	
					/**	\brief	添加装备
					*   
					*	@remarks 	如果该部位已有装备  则以前的装备会被换下
					*	@see		Model
					*	@return   	U1
					*	@param		AString strName
					*	@param		AString strMaterial
					*	@param		AString strTypeName
					*	@note
					*
					**/
					virtual U1				AddEquipment(CAString&	strName,CAString& strMaterial,CAString& strTypeName);
					/**	\brief	添加装备
					*   
					*	@remarks 	添加装备
					*	@see		Model
					*	@return   	U1
					*	@param		AString strName
					*	@param		AString strMaterial
					*	@param		Equipment::enType type
					*	@note
					*
					**/
					virtual U1				AddEquipment(CAString&	strName,CAString& strMaterial,Equipment::enType type);
					/**	\brief	移除一件装备
					*   
					*	@remarks 	移除一件装备
					*	@see		Model
					*	@return   	U1
					*	@param		AString strTypeName
					*	@note
					*
					**/
					virtual U1				RemoveEquipment(CAString&	strTypeName);
					/**	\brief	移除一个部位的装备
					*   
					*	@remarks 	移除一个部位的装备
					*	@see		Model
					*	@return   	U1
					*	@param		Equipment::enType type
					*	@note
					*
					**/
					virtual U1				RemoveEquipment(Equipment::enType type);
				
					/**	\brief	播放指定动作（混合到当前状态）
					*   
					*	@remarks 	播放指定动作
					*	@see		Model
					*	@return   	U1
					*	@param		AString strActionName
					*	@param		Real fBlendTime
					*	@note
					*
					**/
					virtual U1				PlayAction(CAString&	strActionName,Real	fBlendTime	=	0.3f);
					//virtual U1				PlayAction(AString	strActionName,Real	fBlendTime	=	0.3f);
					/**	\brief	设置动画状态
					*   
					*	@remarks 	设置动画状态
					*	@see		Model
					*	@return   	U1
					*	@param		AString strCycleActionName
					*	@param		Real fBlendTime
					*	@note
					*
					**/
					virtual U1				SetActionState(CAString&	strCycleActionName,Real	fBlendTime	=	0.3f);
					/**	\brief	同时混合2个循环动画
					*   
					*	@remarks 	同时混合2个循环动画
					*	@see		Model
					*	@return   	U1
					*	@param		AString strState0
					*	@param		AString strState1
					*	@param		Real fWeight0
					*	@param		Real fBlendTime
					*	@note
					*
					**/
					virtual	U1				SetActionState(CAString&	strState0,CAString&	strState1,Real	fWeight0	=	0.5f,Real	fBlendTime	=	0.3f);
					/**	\brief	获取动画状态
					*   
					*	@remarks 	获取动画状态
					*	@see		Model
					*	@return   	AString
					*	@note
					*
					**/
					virtual AString			GetActionState();
	
					/**	\brief	获取细节层次
					*   
					*	@remarks 	获取细节层次
					*	@see		Model
					*	@return   	Real
					*	@note
					*
					**/
					virtual Real			GetLodLevel();
					/**	\brief	设置细节层次
					*   
					*	@remarks 	设置细节层次
					*	@see		Model
					*	@return   	void
					*	@param		Real fLodLevel
					*	@note
					*
					**/
					virtual void			SetLodLevel(Real fLodLevel);
	
					/**	\brief	创建
					*   
					*	@remarks 	创建
					*	@see		Model
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1				Create();
					/**	\brief	摧毁
					*   
					*	@remarks 	摧毁
					*	@see		Model
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1				Destroy();
	
					/**	\brief	更新
					*   
					*	@remarks 	更新
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual void			Update(const FrameTime& frameTime);
					/**	\brief	渲染
					*   
					*	@remarks 	渲染
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual void			Render();
	
					/**	\brief	软件渲染
					*   
					*	@remarks 	软件渲染
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual	void			RenderSoftWare();
					/**	\brief	硬件渲染
					*   
					*	@remarks 	硬件渲染
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual	void			RenderHardWare();
	
	
					/**	\brief	获取骨骼矩阵
					*   
					*	@remarks 	获取骨骼矩阵
					*	@see		Model
					*	@return   	void
					*	@param		UInt uiIndex
					*	@param		Float3 * pPos
					*	@param		Float4 * pQ
					*	@note
					*
					**/
					void					GetBoneMatrix(UInt	uiIndex,Float3*	pPos,Float4*	pQ	=	NULL);
					Float44*				GetBoneMatrix();
					U32						GetBoneCount()const;
					/**	\brief	绑定到骨骼上
					*   
					*	@remarks 	绑定到骨骼上
					*	@see		Model
					*	@return   	U1
					*	@param		AString	strBoneName
					*	@param		MovableObject * pObject
					*	@note
					*
					**/
					U1						AttachObject2Bone(AString	strBoneName,MovableObject*	pObject);
					SceneNode*				GetBoneSceneNode(AString	strBoneName);
					/**	\brief	移除绑定
					*   
					*	@remarks 	移除绑定
					*	@see		Model
					*	@return   	U1
					*	@param		MovableObject * pObject
					*	@note
					*
					**/
					U1						detachObject(MovableObject*	pObject);
					/**	\brief	渲染绑定物体
					*   
					*	@remarks 	渲染绑定物体
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					void					RenderAttachObject();
					/**	\brief	更新绑定物体
					*   
					*	@remarks 	更新绑定物体
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					void					UpdateAttachObject();


					virtual	void			ProcessRenderObject(U32	uiPhaseFlag);
				protected:
					CoreAnimation*			m_pAnimation;
					Resource*				m_pResource;			///<	资源
					Real					m_fLodLevel;			///<	LOD细节层次
					AString					m_strCurrentCycleAction;///<	当前动画状态
	
					EquipmentMap			m_mapEquipment;			///<	装备列表
					ActionMap				m_mapAnimation;			///<	动画列表
					ActionMap				m_mapCycleAnimation;	///<	循环动画列表
	
					EquipmentMeshMap		m_mapEquipmentMesh;		///<	网格与装备的对应关系表
	
					Info					m_Info;
	
					Real					m_fAnimationSpeed;		///<	动画速度
	
	
					typedef	std::map<MovableObject*,SceneNode*>	AttachObjectMap;
	// 				typedef	std::map<UInt,AttachObject>	AttachObjectMap;
	 				typedef	AttachObjectMap::iterator	AttachObjectMapItr;
	 				typedef	AttachObjectMap::value_type	AttachObjectMapPair;
	// 				typedef	std::map<MovableObject*,UInt>	ObjectIndexMap;
	
					typedef	std::map<AString,SceneNode*>			BoneNodeMap;
					typedef	BoneNodeMap::iterator					BoneNodeMapItr;
					typedef	BoneNodeMap::value_type					BoneNodeMapPair;
					
	
					AttachObjectMap			m_mapAttachObjects;
					BoneNodeMap				m_mapBoneNode;
					//ObjectIndexMap			m_mapObjectIndex;
	
					CriticalSection			m_CS;

					Float44*				m_BoneMatrix;
					U32						m_uiBoneCount;
					ModelTemplate*			m_pTemplate;

					Action					m_CycleAnimation[3];
				};

			};
		}
	
	};
};
#endif // ENGINECHARACTERAIMATION_HEAD_FILE