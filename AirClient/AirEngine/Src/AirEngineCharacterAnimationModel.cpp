#include "AirEngineCharacterAnimationModel.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "..\..\AirCharacter\cal3d.h"
#include "AirEngineSceneNode.h"
#include "AirRenderSystem.h"
#include "AirEngineMaterial.h"
#include "AirEngineMaterialParse.h"
#include "AirEngineCharacterTemplate.h"
namespace Air{
	
	namespace	Engine{
		namespace	Character{
			namespace	Animation{
			
					static	AString	strTypeArray[]	=	{
						"Face",
						"Chest",
						"Shoulder",
						"Arm",
						"Hand",
						"Gloves",
						"waist",
						"Leg",
						"Shoe",
						"Foot",
						"Mantle",
						"LeftWeapon",
						"RightWeapon",
						"Hair",
						"Max"
					};
	
	
	
					Equipment::Equipment( CoreAnimation*	pCoreAnimation,enType type,Model* pParent){
						m_uiEquipmentType	=	type;
						m_uiMeshID			=	-1;
						m_pCoreAnimation		=	pCoreAnimation;
						m_pModel			=	pParent;

						SetNeedWorldMatrix(true);
					}
	
					Equipment::~Equipment(){
						Destroy();
					}
	
					U1 Equipment::Create(UInt uiMeshID,CAString& strMeshName,CAString& strMaterialName,UInt** pSubMesh){
						Destroy();
	
						if(m_pCoreAnimation==NULL	||	uiMeshID == -1)
							return false;
						m_uiMeshID	=	uiMeshID;
						m_strName	=	strMeshName;
	
						if(!m_pCoreAnimation->attachMesh(m_uiMeshID)){
							return false;
						}
						
						//获取该ID得模型
						CalMesh*	pCalMesh	=	m_pCoreAnimation->getMesh(m_uiMeshID);
						//m_pCoreAnimation->getUserData()
						if(pCalMesh==NULL)
							return	false;
						//判断子模型数量 如果为空直接返回
						if(pCalMesh->getSubmeshCount() == 0){
							m_pCoreAnimation->detachMesh(m_uiMeshID);
							return false;
						}
						//获取第一个子模型
						CalSubmesh*	pCalSubMesh	=	pCalMesh->getSubmesh(0);
						if(pCalSubMesh==NULL)
							return false;
	
						//创建材质
// 						m_pMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material*>(strMaterialName,AString("Material"));
// 						if(m_pMaterial	==NULL)
// 							m_pMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Material*>(AString("Material\\NoTexture.Material"),AString("Material"));
// 	
						//将装备的Mesh指针传出  在渲染的时候会用到
						if(pSubMesh!=NULL)
							*pSubMesh	=	(UInt*)pCalSubMesh;
						return true;
	
					}
	
					U1 Equipment::Create( UInt uiMeshID, CAString& strMeshName, CAString& strMaterialName, MeshHDBuffer* pHDBuff /*= NULL*/ ){
						Destroy();
	
						if(m_pCoreAnimation==NULL	||	uiMeshID == -1)
							return false;
						m_uiMeshID	=	uiMeshID;
						m_strName	=	strMeshName;
	
						if(!m_pCoreAnimation->attachMesh(m_uiMeshID)){
							return false;
						}
	
						//获取该ID得模型
						CalMesh*	pCalMesh	=	m_pCoreAnimation->getMesh(m_uiMeshID);
						//m_pCoreAnimation->getUserData()
						if(pCalMesh==NULL)
							return	false;
						//判断子模型数量 如果为空直接返回
						if(pCalMesh->getSubmeshCount() == 0){
							m_pCoreAnimation->detachMesh(m_uiMeshID);
							return false;
						}
						//获取第一个子模型
						CalSubmesh*	pCalSubMesh	=	pCalMesh->getSubmesh(0);
						if(pCalSubMesh==NULL)
							return false;
	


						MaterialSetInfo*	pSetInfo	=	MaterialParse::GetSingleton()->GetMaterialSetInfo(strMaterialName);
						if(pSetInfo==NULL){
							SetMaterialName("NoMaterial");
						}else{
							Material::Info	minfo;
							minfo.strTemplate	=	"MT_ObjectSkin";
							minfo.bUseSkin		=	true;
							minfo.vecFloatParam.resize(4);
							minfo.vecTextureName.resize(1);

							minfo.vecFloatParam[0]	=	pSetInfo->diffuse_opacity;//Float4(1,1,1,1);
							minfo.vecFloatParam[1]	=	Float4(1,1,1,0);
							minfo.vecFloatParam[2]	=	pSetInfo->specular_glossiness;//Float4(0.1,0.1,0.1,0.1);
							minfo.vecFloatParam[3]	=	pSetInfo->selfIllumColor_fresnel;//Float4(0,0,0,0);
							minfo.vecTextureName[0]	=	pSetInfo->mapTexture[enMSPT_TexDiffuse];
							//创建材质
							Material*	p	=	EngineSystem::GetSingleton()->CreateProduct<Material>(strMaterialName+"MRT",&minfo);
							SetMaterial(p);
							p->ReleaseRef();

							Material::Info	mdepthinfo;
							mdepthinfo.bUseSkin			=	true;
							mdepthinfo.strTemplate		=	"MT_ObjectSkin_ShadowDepth";
							p	=	EngineSystem::GetSingleton()->CreateProduct<Material>(strMaterialName+"ShadowDepth",&mdepthinfo);
							SetMaterial(p);
							p->ReleaseRef();
						}
// 						if(m_pMaterial	==NULL)
// 							m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<Render::IMaterial*>(AString("Material\\NoTexture.Material"),AString("Material"));
						//更新渲染缓冲
						if(pHDBuff!=NULL){
							m_DrawBuff.m_pVertexDeclare		=	pHDBuff->pVertexDeclare;
							m_DrawBuff.m_pVertexBuffer[0]	=	pHDBuff->pVertexBuff;
							m_DrawBuff.m_pIndexBuff			=	pHDBuff->pIndexBuff;

							m_DrawBuff.m_DrawOption.m_DrawType		=	Render::Draw::enPT_TRIANGLELIST;
							m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DIP;

							m_DrawBuff.m_DrawOption.m_uiVertexCount	=	pHDBuff->pVertexBuff->GetElementCount();
							m_DrawBuff.m_DrawOption.m_uiIndexCount	=	pHDBuff->pIndexBuff->GetElementCount();


						}

						return	true;
					}
					void Equipment::Destroy(){
						
						//清空渲染缓冲的数据
// 						if(m_DrawBuff.m_pIndexBuff!=NULL){
// 							Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pIndexBuff);
// 							m_DrawBuff.m_pIndexBuff	=	NULL;
// 						}
// 						if(m_pMaterial!=NULL){
// 							Render::System::GetSingleton()->DestroyProduct(m_pMaterial);
// 							m_pMaterial	=	NULL;
// 						}
// 						if(m_DrawBuff.m_pVertexBuff!=NULL){
// 							Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pVertexBuff);
// 							m_DrawBuff.m_pVertexBuff	=	NULL;
// 						}
// 						if(m_DrawBuff.m_pVertexDeclare!=NULL){
// 							Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pVertexDeclare);
// 							m_DrawBuff.m_pVertexDeclare	=	NULL;
// 						}
// 						
// 						m_DrawBuff.m_DrawOption.m_uiVertexCount	=	0;
// 						m_DrawBuff.m_DrawOption.m_uiFaceCount	=	0;
// 						m_uiMeshID								=	-1;
// 						m_strName.clear();
	
						//m_HardWareBuff.Clear();
	
					}
	
					U1 Equipment::IsNull(){
						if(m_pMaterial==NULL)
							return true;
						else
							return false;
					}

					Air::U32 Equipment::GetBoneCount()
					{
						return m_pCoreAnimation->getSkeleton()->getVectorBone().size();
					}

					Float44* Equipment::GetBoneMatrix()
					{
						return	m_pModel->GetBoneMatrix();
					}

					Float44* Equipment::GetWorldMatrix()
					{
						return	m_pModel->GetWorldMatrix();
					}

					AString GetTypeNameByID( Equipment::enType type ){
	
						if(type >= 15 || type < 0){
							return strTypeArray[14];
						}else{
							return strTypeArray[type];
						}
					}
	
					Equipment::enType GetTypeIDByName( AString strName ){
						for(UInt i=0;i<15;i++){
							if(strTypeArray[i].compare(strName.c_str()) == 0){
								return (Equipment::enType)i;
							}
						}
						return Equipment::enMax;
					}
	
				AString Model::ProductTypeName="CharacterModel";
				Model::Model( CAString& strName,Info* pInfo ):MovableObject(strName){

					m_Info					=	*pInfo;
					//m_strResourceName		=	*strResourceName;
					m_pResource				=	NULL;
					m_strCurrentCycleAction	=	"Idle.CAF";
					m_fLodLevel				=	1.0f;
					m_fAnimationSpeed		=	1.0f;
					AddFlag(enMOF_DEFAULT			);
					AddFlag(enMOF_REFLECT			);
					AddFlag(enMOF_CASTSHADOW		);
					AddFlag(enMOF_VISIABLE			);
					AddFlag(enMOF_DYNAMIC			);
					AddFlag(enMOF_UPDATE			);
					AddFlag(enMOF_NEED_FRUSTUM_CULL	);

					m_BoneMatrix	=	0;
					m_uiBoneCount	=	0;
					m_pTemplate		=	NULL;
					m_pAnimation	=	NULL;
					for(int i=0;i<3;i++){
						m_CycleAnimation[i].m_uiActionID=0xffffffff;
					}
				}
	
				Model::~Model(){
					if(m_BoneMatrix)
						delete m_BoneMatrix;
				}
	
				U1 Model::Create(){
					if(m_Info.strTemplate.empty())
						return false;
					m_pTemplate	=	EngineSystem::GetSingleton()->GetProduct<ModelTemplate>(m_Info.strTemplate);
					if(m_pTemplate==NULL)
						return false;
					
					m_pResource	=	EngineSystem::GetSingleton()->CreateProduct<Resource>(m_pTemplate->m_Info.strModelPath,&m_pTemplate->m_Info.strSkeletonName);
					if(m_pResource==NULL)
						return false;
					if(m_pResource->IsNull())
						return false;
					CoreMesh*	pCoreMesh		=	m_pResource->GetObjectT<CoreMesh*>();
					m_pAnimation				=	new	CoreAnimation(pCoreMesh);

					SetBoundBox(Float3(-1,0,-1),Float3(1,2,1));
					CalSkeleton*	pSkel	=	m_pAnimation->getSkeleton();
					std::vector<CalBone*>&	lstBone	=	pSkel->getVectorBone();
					m_uiBoneCount	=	lstBone.size();
					//ShaderShareParam&	dParam	=	GetGlobalSetting().m_ShaderParam;
					m_BoneMatrix	=	new Float44[m_uiBoneCount];

					U32 uiEquipmentCount	=	m_pTemplate->m_vecEquipment.size();
					for(U32 i=0;i<uiEquipmentCount;i++){
						AddEquipment(m_pTemplate->m_vecEquipment[i],m_pTemplate->m_vecMaterial[i],(Animation::Equipment::enType)i);
					}
					if(!m_pTemplate->m_vecState.empty()){
						m_strCurrentCycleAction	=	m_pTemplate->m_vecState[0];
						SetActionState(m_strCurrentCycleAction);
					}
					
					return true;
					
				}
	
				U1 Model::Destroy(){
					if(m_BoneMatrix!=NULL){
						delete m_BoneMatrix;
						m_BoneMatrix	=	NULL;
					}
					//摧毁装备列表
					EquipmentMapItr	iEquip	=	m_mapEquipment.begin();
					for(;iEquip!=m_mapEquipment.end();iEquip++){
						Equipment*	pEquip	=	iEquip->second;
						m_pResource->UnLoadMesh(pEquip->GetEquipmentName());
						SAF_D(pEquip);
					}
					m_mapEquipment.clear();
					
					//但是不摧毁动画列表
					m_mapAnimation.clear();
					m_mapCycleAnimation.clear();
	
					m_mapEquipmentMesh.clear();
	
					//先摧毁动画
					SAF_D(m_pAnimation);
					//再销毁资源
					SAFE_RELEASE_REF(m_pResource);
					SAFE_RELEASE_REF(m_pTemplate);
					return true;
				}
	
				Real Model::GetLodLevel(){
					return m_fLodLevel;
				}
	
				void Model::SetLodLevel( Real fLodLevel ){
					if(IsNull())
						return;
					m_fLodLevel	=	fLodLevel;
					CoreAnimation*	pAnimation	=	GetObjectT<CoreAnimation*>();
					pAnimation->setLodLevel(m_fLodLevel);
				}
	
				U1 Model::AddEquipment( CAString& strName,CAString& strMaterial,CAString& strTypeName ){
					//获取装备类型
					Equipment::enType	type	=	GetTypeIDByName(strTypeName);
					return AddEquipment(strName,strMaterial,type);
				}
	
				U1 Model::AddEquipment( CAString& strName,CAString& strMaterial,Equipment::enType type ){
					if(strName.empty() || type >=Equipment::enMax || type < 0 )
						return false;
					if(m_pResource==NULL)
						return false;
					SInt	uiMeshID	=	-1;
	
					MeshHDBuffer	meshBuff;
	
					//查找是否存在这个类型的装备
					EquipmentMapItr	i	=	m_mapEquipment.find(type);
					if(i!=m_mapEquipment.end()){
						Equipment*	equip	=	i->second;
						//如果这个类型的装备不为空
						if(equip==NULL){
							equip	=	new	Equipment(m_pAnimation,type,this);
						}else{
							if(!equip->IsNull()){
								CalModel*	pModel	=	GetObjectT<CalModel*>();
								pModel->detachMesh(equip->GetMeshID());
								m_pResource->UnLoadMesh(equip->GetEquipmentName());
								equip->Destroy();
							}
						}
						//载入模型
						
						uiMeshID	=	m_pResource->LoadMesh(strName,&meshBuff);
						if(uiMeshID==-1)
							return false;
						UInt*	pEquipmentMesh	=	NULL;
						//判定是否为硬件渲染
						
						if(!equip->Create(uiMeshID,strName,strMaterial,&meshBuff))
							return	false;
						
						m_mapEquipmentMesh.insert(EquipmentMeshMapPair(pEquipmentMesh,equip));
						return true;
	
					}
					//如果没有该类型的装备
					Equipment*	pEquip	=	NULL;
					//先载入模型
					uiMeshID	=	m_pResource->LoadMesh(strName,&meshBuff);
					if(uiMeshID	== -1){
						//m_pResource->UnLoadMesh(strName);
						return false;
					}
					//新建一个装备
					pEquip	=	new	Equipment(m_pAnimation,type,this);
					//判定是否为硬件渲染
					
					if(!pEquip->Create(uiMeshID,strName,strMaterial,&meshBuff))
						return	false;
					
					//放入列表中
					m_mapEquipment.insert(EquipmentMapPair(type,pEquip));
	
					return true;
				}
				U1 Model::RemoveEquipment( CAString& strTypeName ){
					Equipment::enType	type	=	GetTypeIDByName(strTypeName);
					return RemoveEquipment(type);
				}
	
				U1 Model::RemoveEquipment( Equipment::enType type ){
					if(type >=Equipment::enMax || type < 0 )
						return false;
					//查找是否存在这个类型的装备
					EquipmentMapItr	i	=	m_mapEquipment.find(type);
					if(i!=m_mapEquipment.end()){
						Equipment*	&equip	=	i->second;
						if(equip==NULL)
							return true;
						if(equip->IsNull())
							return	true;
						CalModel*	pModel	=	GetObjectT<CalModel*>();
						pModel->detachMesh(equip->GetMeshID());
						m_pResource->UnLoadMesh(equip->GetEquipmentName());
						equip->Destroy();
						
						//SAF_D(equip);
					}
					//m_mapEquipment.erase(i);
					return true;
				}
	
				U1 Model::PlayAction( CAString& strActionName ,Real	fBlendTime){
					if(strActionName.empty())
						return false;
					SInt	uiActionID	=	m_pResource->GetAnimationID(strActionName);
	
					CoreAnimation*	pAnim	=	(CoreAnimation*)m_pAnimation;
					//播放动画
					return	pAnim->getMixer()->executeAction(uiActionID, fBlendTime, fBlendTime);
				}
	
				U1 Model::SetActionState( CAString& strCycleActionName ,Real	fBlendTime){
					if(strCycleActionName.empty())
						return false;
					SInt	uiActionID	=	m_pResource->GetAnimationID(strCycleActionName);
					if(uiActionID==-1)
						return false;
					//查找是否存在于列表中
					for(int i=0;i<3;i++){
						//if(m_CycleAnimation[i].m_uiActionID!=uiActionID){
							m_pAnimation->getMixer()->clearCycle(m_CycleAnimation[i].m_uiActionID,fBlendTime);
						//}
						m_CycleAnimation[i].m_uiActionID=0xffffffff;
						m_CycleAnimation[i].m_strName.clear();
					}
					m_CycleAnimation[0].m_uiActionID	=	uiActionID;
					m_CycleAnimation[0].m_strName		=	strCycleActionName;

					m_pAnimation->getMixer()->blendCycle(uiActionID,1.0f,fBlendTime);
					return true;
				}
	
				U1 Model::SetActionState( CAString& strState0,CAString& strState1,Real fWeight0 /*= 0.5f*/,Real fBlendTime /*= 0.3f*/ ){
					if(strState0.empty()	||	strState1.empty())
						return false;
					SInt	uiActionID0	=	m_pResource->GetAnimationID(strState0);
					SInt	uiActionID1	=	m_pResource->GetAnimationID(strState1);
					if(uiActionID0==-1	||	uiActionID1==-1)
						return false;
					//查找是否存在于列表中
					for(int i=0;i<3;i++){
						UInt uiOldID	=	m_CycleAnimation[i].m_uiActionID;
						//if(uiOldID!=uiActionID0	&& uiOldID!=uiActionID1){
							m_pAnimation->getMixer()->clearCycle(uiOldID,fBlendTime);
						//}
						m_CycleAnimation[i].m_uiActionID=0xffffffff;
						m_CycleAnimation[i].m_strName.clear();
					}
					m_CycleAnimation[0].m_uiActionID	=	uiActionID0;
					m_CycleAnimation[0].m_strName		=	strState0;

					m_pAnimation->getMixer()->blendCycle(uiActionID0,fWeight0,fBlendTime);
					m_CycleAnimation[1].m_uiActionID	=	uiActionID1;
					m_CycleAnimation[1].m_strName		=	strState1;

					m_pAnimation->getMixer()->blendCycle(uiActionID1,1-fWeight0,fBlendTime);
					return true;
				}
	
				AString Model::GetActionState(){
					//获取当前状态
					return	m_strCurrentCycleAction;
				}
	
				void Model::Update(const FrameTime& frameTime){

					//当前帧不可见
					if(frameTime.uiFrameIndex	!=	m_uiVisiableFrame)
						return;

					CoreAnimation*	pAnimation	=	m_pAnimation;
					if(pAnimation){
						//m_CS.Enter();
						pAnimation->update(frameTime.fTimeDelta*m_fAnimationSpeed);
						//m_CS.Leave();
						//pAnimation->getSkeleton()->calculateBoundingBoxes();
						//pAnimation->getSkeleton()->getBoneBoundingBox(&m_BoundingBox.vMin.x,&m_BoundingBox.vMax.x);
	
						UpdateAttachObject(frameTime);

						CalSkeleton*	pSkel	=	m_pAnimation->getSkeleton();
						std::vector<CalBone*>&	lstBone	=	pSkel->getVectorBone();
						UInt	uiBoneCount	=	lstBone.size();

						Float44*	pMatrixArray	=	m_BoneMatrix;
						for(UInt i=0;i<uiBoneCount;i++){
							CalBone*	pBone	=	lstBone[i];
							const	CalQuaternion&	q	=	pBone->getRotationBoneSpace();
							const	CalVector&		v	=	pBone->getTranslationBoneSpace();
							pMatrixArray[i]	=	Float44(*(Float4*)&q);
							pMatrixArray[i].Transpose();
							pMatrixArray[i].SetPosition(*(Float3*)&v);
							//Render::System::GetSingleton()->MakeBoneMatrix(&pMatrixArray[i],(Float4*)&q,(Float3*)&v);
							//if(i==0){
							//	m_BoundingBox.vMin	=	v;
							//	m_BoundingBox.vMax	=	v;
							//}else{
							//	m_BoundingBox.Add(v);
							//}
						}
						m_bDirty	=	true;
					}
					__super::Update(frameTime);
				}

				void Model::Update( const Float44& ParentGlobalWorldMatrix, const Float4& ParentGlobalWorldQuat, const Float3& ParentGlobalWorldScale, U1 bParentDirty )
				{
					__super::Update(ParentGlobalWorldMatrix,ParentGlobalWorldQuat,ParentGlobalWorldScale,bParentDirty);
		
					CalCoreModel*			pModel	=	m_pAnimation->getCoreModel();
					std::vector<CalBone*>&	lstBone	=	m_pAnimation->getSkeleton()->getVectorBone();;
					//更新骨骼节点
					STD_LIST<AttachObject>::iterator	i	=	m_lstAttachObject.begin();
					for(;i!=m_lstAttachObject.end();i++){
						//m_mapAttachObjects.erase(i);

						AttachObject& aobj	=	(*i);
						const CalQuaternion&	q	=	lstBone[aobj.uiBoneIndex]->getRotationAbsolute();
						const CalVector&		v	=	lstBone[aobj.uiBoneIndex]->getTranslationAbsolute();
						Float44 matWorld;

						matWorld	=	Float44(*(Float4*)&q);
						matWorld.Transpose();
						matWorld.SetPosition(*(Float3*)&v);

						aobj.pObject->Update(matWorld*ParentGlobalWorldMatrix,ParentGlobalWorldQuat*Float4(q),ParentGlobalWorldScale,true);
					}
				}
	
				Real Model::GetAnimationSpeed(){
					return	m_fAnimationSpeed;
				}
	
				void Model::SetAnimationSpeed( Real fSpeed /*= 1.0f*/ ){
					if(fSpeed<0.0f)
						return;
					m_fAnimationSpeed	=	fSpeed;
				}
	
				void Model::SetAnimationSpeedOffset( Real fSpeedOffset /*= -0.01f*/ ){
					if(m_fAnimationSpeed+fSpeedOffset<0.0f)
						return;
					m_fAnimationSpeed	+=	fSpeedOffset;
				}
	
				void Model::GetBoneMatrix( UInt uiIndex,Float3* pPos,Float4* pQ /*= NULL*/ ){
					
					CalBone*	pBone	=	m_pAnimation->getSkeleton()->getBone(uiIndex);
					
					
					if(pPos!=NULL){
						const	CalVector&		v	=	pBone->getTranslationAbsolute();
						*pPos	=	Float3(v.x,v.z,v.y);
					}
					if(pQ!=NULL){
						const	CalQuaternion&	q	=	pBone->getRotationAbsolute();
						*pQ		=	Float4(q.w,q.x,q.z,q.y);
					}
				}

				Float44* Model::GetBoneMatrix()
				{
					return m_BoneMatrix;
				}


				U1 Model::attachObject(CAString&	strBoneName,MovableObject* pObject ){
					if(	strBoneName.empty()	|| pObject==NULL)
						return	false;
					detachObject(pObject);

					AttachObject aobj;
					aobj.uiBoneIndex	=	m_pAnimation->getCoreModel()->getBoneId(strBoneName);
					aobj.pObject		=	pObject;
					
					m_lstAttachObject.push_back(aobj);
	
					return	true;
				}
	
				U1 Model::detachObject( MovableObject* pObject ){
					STD_LIST<AttachObject>::iterator	i	=	m_lstAttachObject.begin();
					for(;i!=m_lstAttachObject.end();i++){
						if((*i).pObject	==	pObject){
							i = m_lstAttachObject.erase(i);
							return true;
						}
					}
					return	false;
				}
	
				void Model::UpdateAttachObject(const FrameTime& frameTime){

					CalCoreModel*			pModel	=	m_pAnimation->getCoreModel();
					std::vector<CalBone*>&	lstBone	=	m_pAnimation->getSkeleton()->getVectorBone();;
					//更新骨骼节点
					STD_LIST<AttachObject>::iterator	i	=	m_lstAttachObject.begin();
					for(;i!=m_lstAttachObject.end();i++){
						AttachObject& aobj	=	(*i);
						aobj.pObject->Update(frameTime);
					}
				}


				void Model::ProcessRenderObject( U32 uiPhaseFlag )
				{
					EquipmentMap::iterator	i	=	m_mapEquipment.begin();
					for(;i!=m_mapEquipment.end();i++){
						i->second->AddToRenderQueue(uiPhaseFlag);
					}
					STD_LIST<AttachObject>::iterator	itr	=	m_lstAttachObject.begin();
					for(;itr!=m_lstAttachObject.end();itr++){
						(*itr).pObject->ProcessRenderObject(uiPhaseFlag);
					}
				}

				Air::U32 Model::GetBoneCount()const
				{
					return m_uiBoneCount;
				}

				Air::U1 Model::OnCameraCull( Camera* pCamera )
				{
					
					STD_LIST<AttachObject>::iterator	i	=	m_lstAttachObject.begin();
					for(;i!=m_lstAttachObject.end();i++){
						AttachObject& aobj	=	(*i);
						aobj.pObject->OnCameraCull(pCamera);
					}
					return __super::OnCameraCull(pCamera);
				}

				void Model::EnableBoneExtraRotate( U32 uiIndex,const Float4& rot )
				{
					CalBone*	pBone	=	m_pAnimation->getSkeleton()->getBone(uiIndex);


					pBone->EnableExtraRotate(CalQuaternion(rot.x,rot.y,rot.z,rot.w));
				}

				void Model::DisableBoneExtraRotate( U32 uiIndex )
				{
					CalBone*	pBone	=	m_pAnimation->getSkeleton()->getBone(uiIndex);


					pBone->DisableExtraRotate();
				}

				U1 Model::HasBoneExtraRotate( U32 uiIndex )
				{
					CalBone*	pBone	=	m_pAnimation->getSkeleton()->getBone(uiIndex);
					return pBone->HasExtraRotate();
				}

				Air::U32 Model::GetBoneIndex( CAString& strName )
				{
					return m_pAnimation->getSkeleton()->getCoreSkeleton()->getCoreBoneId(strName);
				}

				float Model::GetAnimationLength( CAString& strAnimationName )
				{
					CalCoreModel*	pModel	=	m_pAnimation->getCoreModel();
					int iIndex	=	pModel->getCoreAnimationId(strAnimationName);
					if(iIndex==0xffffffff)
						return -1;

					return pModel->getCoreAnimation(iIndex)->getDuration();
				}


	// 			void Model::SetParent( Common::INode* pParentNode ){
	// 				if(m_pParentNode!=NULL){
	// 					m_pParentNode->RemoveChild(m_pAttachObjNode);
	// 				}
	// 				m_pParentNode	=	pParentNode;
	// 
	// 				if(m_pParentNode!=NULL){
	// 					m_pParentNode->AddChild(m_pAttachObjNode);
	// 				}
	// 			}
				// 
	// 			U1 Model::LoadHardWareModel(){
	// 				typedef		Render::Vertex::IBuff::PNTT_ANIM	VERTEXSTRUCT;
	// 				std::vector<VERTEXSTRUCT>						vertexData;
	// 				std::vector<UInt>								indexData;
	// 
	// 
	// 
	// 				vertexData.resize(50000);
	// 				indexData.resize(50000);
	// 				VERTEXSTRUCT*	pV	=	&vertexData[0];
	// 				UInt*			pI	=	&indexData[0];
	// 
	// 
	// 				m_pHardWareModel->setVertexBuff((char*)pV,sizeof(VERTEXSTRUCT));
	// 				m_pHardWareModel->setWeightBuffer(((char*)pV) + 12 ,sizeof(VERTEXSTRUCT));
	// 				m_pHardWareModel->setMatrixIndexBuff(((char*)pV) + 28 ,sizeof(VERTEXSTRUCT));  
	// 				m_pHardWareModel->setNormalBuffer(((char*)pV)+44,sizeof(VERTEXSTRUCT));
	// 				m_pHardWareModel->setTextureCoordNum(1);
	// 				m_pHardWareModel->setTextureCoordBuffer(0,((char*)pV)+56,sizeof(VERTEXSTRUCT));
	// 				m_pHardWareModel->setTangentSpaceBuffer(0,((char*)pV)+64,sizeof(VERTEXSTRUCT));
	// 				m_pHardWareModel->setIndexBuff((CalIndex*)pI);
	// 
	// 				m_pHardWareModel->load( 0, 0, 60);
	// 
	// 				Render::Vertex::IDeclare::Info	dInfo;
	// 				dInfo.SetPNTT_Animation();
	// 				m_HardWareBuff.pVertexDeclare	=	Render::System::GetSingleton()->Create<Render::Vertex::IDeclare*>("PNTTANIM","VertexDeclare",&dInfo);
	// 				Render::Vertex::IBuff::Info		vInfo(76,50000);
	// 				vInfo.InitData				=	&vertexData[0];
	// 				m_HardWareBuff.pVertexBuff		=	Render::System::GetSingleton()->Create<Render::Vertex::IBuff*>("Test","VertexBuff",&vInfo);
	// 				Render::Index::IBuff::Info		iInfo(50000);
	// 				iInfo.InitData				=	&indexData[0];
	// 				m_HardWareBuff.pIndexBuff		=	Render::System::GetSingleton()->Create<Render::Index::IBuff*>("Test","IndexBuff",&iInfo);
	// 
	// 				return	true;
	// 			}
	// 
	// 			void Model::UnLoadHardWareModel(){
	// 				Render::ISystem*	pSys	=	Render::System::GetSingleton();
	// 				if(pSys==NULL)
	// 					return;
	// 				MeshHDBuffer*	pInBuff	=	&m_HardWareBuff;
	// 				if(pInBuff->pVertexDeclare!=NULL){
	// 					pSys->DestroyProduct(pInBuff->pVertexDeclare);
	// 					pInBuff->pVertexDeclare	=	NULL;
	// 				}
	// 				if(pInBuff->pVertexBuff!=NULL){
	// 					pSys->DestroyProduct(pInBuff->pVertexBuff);
	// 					pInBuff->pVertexBuff	=	NULL;
	// 				}
	// 				if(pInBuff->pIndexBuff!=NULL){
	// 					pSys->DestroyProduct(pInBuff->pIndexBuff);
	// 					pInBuff->pIndexBuff	=	NULL;
	// 				}
	// 			}
			}
		}
	}
};