#ifndef ENGINECHARACTER_HEAD_FILE
#define ENGINECHARACTER_HEAD_FILE

class	CalCoreModel;
class	CalModel;
class	CalHardwareModel;

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirInterfaceRenderVertexBuff.h"
#include "AirEngineSceneNode.h"
namespace	Air{
	namespace Client{
		/**	\brief	角色
		*
		*	角色
		*
		***/
		namespace	Character{
			typedef	CalModel			AnimationMesh;		///<	动画控制器
			typedef	CalCoreModel		Mesh;				///<	模型管理器
			typedef	CalHardwareModel	HarewareMesh;		///<	硬件动画
		
			typedef	std::vector<SInt>	IDVector;			///<	ID列表
			typedef	IDVector			IDVectorItr;		///<	ID列表迭代器
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
			/**	\brief	装备
			*
			*	装备
			*
			***/
			namespace Equipment{
				enum	enType{
					enHair,
					enFace,
					enChest,
					enLeftShoulder,
					enRightShoulder,
					enLeftArm,
					enRightArm,
					enLeftHand,
					enRightHand,
					enLeftGloves,
					enRightGloves,
					enLeftWeapon,
					enRightWeapon,
					enwaist,
					enLeg,
					enPants,
					enShoe,
					enFoot,
					enMantle,
					enMax
					
				};
				AString	GetTypeNameByID(enType type);
				enType	GetTypeIDByName(AString	strName);

				struct Info{
					AChar	strName[MAX_NAME];			///<	资源名
					AChar	strTypeName[MAX_NAME];		///<	类型名
					AChar	strMaterial[MAX_NAME];		///<	材质名
					enType	type;						///<	类型ID
					UInt	id;							///<	模型ID
					void*	material;					///<	材质指针
				};
				typedef	std::map<AString,Info>	InfoMap;
				typedef	InfoMap::iterator		InfoMapItr;
				typedef	InfoMap::value_type		InfoMapPair;
			};

			class	SoftwareModel	:
				public	MovableObject{
			public:
				SoftwareModel(AString	strName,void*	pInfo);
				virtual ~SoftwareModel();

				virtual	U1			SetAction(enumActionState actState,Real	fBlendTime	=	0.3f);

				Real				GetLodLevel();
				void				SetLodLevel(Real fLodLevel);

				void				SetState(enumActionState state, Real fBlendTime	=	0.3f);
				enumActionState		GetState();

				U1					AddEquipment(AString strEquipmentName,Equipment::enType type);
				U1					AddEquipment(AString strEquipmentName,AString strTypeName);

				U1					SetMaterial(AString	strMaterialName,Equipment::enType type);
				U1					SetMaterial(AString	strMaterialName,AString strTypeName);

				virtual	U1		Create();
				virtual	U1		Destroy();
				virtual	void	Render();
				virtual	void	Updata();

			private:

				
			protected:
				enumActionState		m_CurrentActionState;		///<	当前动画状态
				AnimationMesh*		m_pAnimation;
				Mesh*				m_pMesh;
				
				IDVector			m_vectorAnimation;
				IDVector			m_vectorMesh;
				//IDVector			m_vectorAnimation;

				Real				m_fRenderScale;
				float				m_fLodLevel;
				AString				m_strName;
			private:
				Equipment::InfoMap	m_mapEquipmentInfp;			///<	装备信息

			};
	// 		class	HarewareModel	:	public	SoftwareModel{
	// 		public:
	// 			HarewareModel(){};
	// 			virtual ~HarewareModel(){};
	// 		};
		}

	};
}
#endif // ENGINECHARACTER_HEAD_FILE