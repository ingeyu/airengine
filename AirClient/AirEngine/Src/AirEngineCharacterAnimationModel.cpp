#include "AirEngineCharacterAnimationModel.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "..\..\AirCharacter\cal3d.h"
#include "AirEngineSceneNode.h"
#include "AirRenderSystem.h"
#include "AirEngineMaterial.h"
#include "AirEngineMaterialParse.h"
namespace Air{
	
	namespace	Client{
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

							minfo.vecFloatParam[0]	=	Float4(1,1,1,1);
							minfo.vecFloatParam[1]	=	Float4(0.5,0.5,0.5,0);
							minfo.vecFloatParam[2]	=	Float4(0.1,0.1,0.1,0.1);
							minfo.vecFloatParam[3]	=	Float4(0,0,0,0);
							minfo.vecTextureName[0]	=	pSetInfo->mapTexture[enMSPT_TexDiffuse];
							//创建材质
							Material*	p	=	EngineSystem::GetSingleton()->CreateProduct<Material*>(strMaterialName+"MRT","Material",&minfo);
							SetMaterial(p);
							p->ReleaseRef();

							Material::Info	mdepthinfo;
							mdepthinfo.bUseSkin			=	true;
							mdepthinfo.strTemplate		=	"MT_ObjectSkin_ShadowDepth";
							p	=	EngineSystem::GetSingleton()->CreateProduct<Material*>(strMaterialName+"ShadowDepth","Material",&mdepthinfo);
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
							m_DrawBuff.m_DrawOption.m_uiFaceCount	=	pHDBuff->pIndexBuff->GetElementCount()/3;


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
						CalSkeleton*	pSkel	=	m_pCoreAnimation->getSkeleton();
						std::vector<CalBone*>&	lstBone	=	pSkel->getVectorBone();
						UInt	uiBoneCount	=	lstBone.size();
						ShaderShareParam&	dParam	=	GetGlobalSetting().m_ShaderParam;


						Float44*	pMatrixArray	=	&dParam.m_BoneMatrixArray[0];
						for(UInt i=0;i<uiBoneCount;i++){
							CalBone*	pBone	=	lstBone[i];
							const	CalQuaternion&	q	=	pBone->getRotationBoneSpace();
							const	CalVector&		v	=	pBone->getTranslationBoneSpace();
							pMatrixArray[i]	=	Float44(*(Float4*)&q);
							pMatrixArray[i].Transpose();
							pMatrixArray[i].SetPosition(*(Float3*)&v);
							//Render::System::GetSingleton()->MakeBoneMatrix(&pMatrixArray[i],(Float4*)&q,(Float3*)&v);
						}
						return	pMatrixArray;
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
	
	
				Model::Model( CAString& strName,Info* pInfo ):Common::IProduct(strName){

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

				}
	
				Model::~Model(){
					
				}
	
				U1 Model::Create(){
					if(m_Info.strResourcePath.empty() || m_Info.strSkeleton.empty())
						return false;
					m_pResource	=	EngineSystem::GetSingleton()->CreateProduct<Resource*>(m_Info.strResourcePath,"Character",&m_Info.strSkeleton);
					if(m_pResource==NULL)
						return false;
					if(m_pResource->IsNull())
						return false;
					CoreMesh*	pCoreMesh		=	m_pResource->GetObjectT<CoreMesh*>();
					m_pAnimation				=	new	CoreAnimation(pCoreMesh);

					SetBoundBox(Float3(-1000,-2000,-1000),Float3(1000,2000,1000));

	
					
					return true;
					
				}
	
				U1 Model::Destroy(){
					//UnLoadHardWareModel();
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
						if(m_Info.bHardWare){
							if(!equip->Create(uiMeshID,strName,strMaterial,&meshBuff))
								return	false;
						}else{
							//创建模型
							if(!equip->Create(uiMeshID,strName,strMaterial,&pEquipmentMesh)){
								m_pResource->UnLoadMesh(strName);
								return false;
							}
						}
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
					if(m_Info.bHardWare){
						if(!pEquip->Create(uiMeshID,strName,strMaterial,&meshBuff))
							return	false;
					}else{
	
						UInt*	pEquipmentMesh	=	NULL;
						//创建模型
						if(!pEquip->Create(uiMeshID,strName,strMaterial,&pEquipmentMesh)){
							m_pResource->UnLoadMesh(strName);
							return false;
						}
						m_mapEquipmentMesh.insert(EquipmentMeshMapPair(pEquipmentMesh,pEquip));
					}
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
	
					CoreAnimation*	pAnim	=	(CoreAnimation*)m_pObject;
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
					ActionMapItr i	=	m_mapCycleAnimation.find(strCycleActionName.c_str());
					if(i==m_mapCycleAnimation.end()){
						Action	act;
						act.m_strName		=	strCycleActionName;
						act.m_uiActionID	=	uiActionID;
						m_mapCycleAnimation.insert(ActionMapPair(strCycleActionName.c_str(),act));
					}
					//获取动画操作类
					CoreAnimation*	pAnimation	=	m_pAnimation;
	
					//遍历列表
					i	=	m_mapCycleAnimation.begin();
					for(;i!=m_mapCycleAnimation.end();i++){
						//指定动画开启循环
						if(i->second.m_uiActionID	==	uiActionID){
							pAnimation->getMixer()->blendCycle(i->second.m_uiActionID,1.0f,fBlendTime);
						}else{
							//非指定动画关闭循环
							pAnimation->getMixer()->clearCycle(i->second.m_uiActionID,fBlendTime);
						}
					}
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
					ActionMapItr i	=	m_mapCycleAnimation.find(strState0.c_str());
					if(i==m_mapCycleAnimation.end()){
						Action	act;
						act.m_strName		=	strState0;
						act.m_uiActionID	=	uiActionID0;
						m_mapCycleAnimation.insert(ActionMapPair(strState0.c_str(),act));
					}
					i	=	m_mapCycleAnimation.find(strState1.c_str());
					if(i==m_mapCycleAnimation.end()){
						Action	act;
						act.m_strName		=	strState1;
						act.m_uiActionID	=	uiActionID1;
						m_mapCycleAnimation.insert(ActionMapPair(strState1.c_str(),act));
					}
					//获取动画操作类
					CoreAnimation*	pAnimation	=	(CoreAnimation*)m_pObject;
	
					//遍历列表
					i	=	m_mapCycleAnimation.begin();
					for(;i!=m_mapCycleAnimation.end();i++){
						//指定动画开启循环
						if(i->second.m_uiActionID	==	uiActionID0){
							pAnimation->getMixer()->blendCycle(i->second.m_uiActionID,fWeight0,fBlendTime);
						}else	if(i->second.m_uiActionID	==	uiActionID1){
							pAnimation->getMixer()->blendCycle(i->second.m_uiActionID,1-fWeight0,fBlendTime);
						}else{
							//非指定动画关闭循环
							pAnimation->getMixer()->clearCycle(i->second.m_uiActionID,fBlendTime);
						}
					}
					return true;
				}
	
				AString Model::GetActionState(){
					//获取当前状态
					return	m_strCurrentCycleAction;
				}
	
				void Model::Updata(){
					CoreAnimation*	pAnimation	=	m_pAnimation;
					if(pAnimation){
						m_CS.Enter();
						pAnimation->update(GetTimer().GetTimeDelta()*m_fAnimationSpeed);
						m_CS.Leave();
						//pAnimation->getSkeleton()->calculateBoundingBoxes();
	
						UpdataAttachObject();
					}
					__super::Updata();
				}
	
				void Model::Render(){

					//判定是采用软件渲染  还是硬件渲染
					if(m_Info.bHardWare){
						RenderHardWare();
					}else{
						RenderSoftWare();
					}
					//m_CS.Leave();
	
					RenderAttachObject();
					
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
	
				void Model::RenderSoftWare(){
					CoreAnimation*	pAnimation	=	(CoreAnimation*)m_pObject;
					// get the renderer of the model
					CalRenderer *pCalRenderer;
					pCalRenderer = pAnimation->getRenderer();
	
					//开始渲染整个角色
					if(!pCalRenderer->beginRendering()) return;
	
					UInt iVertexPos	=	0,iFacePos	= 0;
					//获取装备数量
					UInt meshCount	= pCalRenderer->getMeshCount();
	
					// render all meshes of the model
					for(UInt	i = 0; i < meshCount; i++){
						// get the number of submeshes
						//int submeshCount = pCalRenderer->getSubmeshCount(i);
						// render all submeshes of the mesh
						//for(UInt	j = 0; j < submeshCount; j++){
						// select mesh and submesh for further data access
						CalSubmesh*	pSubMesh	=	pCalRenderer->selectMeshSubmesh(i, 0);
						if(pSubMesh)
						{
							//调用装备的渲染函数来渲染
							EquipmentMeshMapItr	itr	=	m_mapEquipmentMesh.find((UInt*)pSubMesh);
							if(itr!=m_mapEquipmentMesh.end()){
								Equipment*	pEquip	=	itr->second;
	
								if(pEquip!=NULL){
									if(pEquip->IsNull())
										continue;
// 									m_DrawBuff.m_DrawOption.m_uiVertexCount	=	pCalRenderer->getVertexCount();
// 									m_DrawBuff.m_DrawOption.m_uiFaceCount	=	pCalRenderer->getFaceCount();
									//pCalRenderer->getf
	
// 									VertexBuff::PNTData* pVertex	=	NULL;
// 	
// 									m_DrawBuff.m_pVertexBuff->Lock(Client::Render::LockOption(0,m_DrawBuff.m_DrawOption.m_uiVertexCount*32,(void**)&pVertex,LOCK_DISCARD));
// 									int iNumVertex	=	pCalRenderer->getVerticesNormalsAndTexCoords(&pVertex->fArray[0]);
// 									m_DrawBuff.m_pVertexBuff->Unlock();
// 	
// 									CalIndex*	pIndex	=	NULL;
// 									m_DrawBuff.m_pIndexBuff->Lock(Client::Render::LockOption(0,m_DrawBuff.m_DrawOption.m_uiFaceCount*6,(void**)&pIndex,LOCK_DISCARD));
// 									int iNumFace	=	pCalRenderer->getFaces(pIndex);
// 									m_DrawBuff.m_pIndexBuff->Unlock();
	
// 									m_DrawBuff.m_DrawOption.m_uiVertexCount	=	iNumVertex;
// 									m_DrawBuff.m_DrawOption.m_uiFaceCount	=	iNumFace;
									//m_DrawBuff.m_pVertexBuff->UpdateData(&data);
	
									// 									m_DrawBuff.m_DrawOption.m_uiBaseVertexIndex	=	iVertexPos;
									// 									m_DrawBuff.m_DrawOption.m_uiStartIndex		=	iFacePos*3;
	
									//pEquip->Render(m_DrawBuff);
	
									// 									iVertexPos+=iNumVertex;
									// 									iFacePos+=iNumFace;
								}
	
							}
						}
	
						//}
	
					}
	
	
					pCalRenderer->endRendering();
				}
	
				void Model::RenderHardWare(){
					//更新整个骨骼矩阵到着色语言共享参数区
					m_CS.Enter();
	
	 				CoreAnimation*	pAnimation	=	(CoreAnimation*)m_pObject;
	 				CalSkeleton*	pSkel	=	pAnimation->getSkeleton();
	 				std::vector<CalBone*>&	lstBone	=	pSkel->getVectorBone();
	 				UInt	uiBoneCount	=	lstBone.size();
					ShaderShareParam&	dParam	=	GetGlobalSetting().m_ShaderParam;
	
	
					Float44*	pMatrixArray	=	&dParam.m_BoneMatrixArray[0];
					for(UInt i=0;i<uiBoneCount;i++){
						CalBone*	pBone	=	lstBone[i];
						const	CalQuaternion&	q	=	pBone->getRotationBoneSpace();
						const	CalVector&		v	=	pBone->getTranslationBoneSpace();
						//Render::System::GetSingleton()->MakeBoneMatrix(&pMatrixArray[i],(Float4*)&q,(Float3*)&v);
					}
	
					m_CS.Leave();
					//调用装备的渲染函数来渲染
					EquipmentMapItr	itr	=	m_mapEquipment.begin();
					for(;itr!=m_mapEquipment.end();itr++){
						Equipment*	pEquip	=	itr->second;
						if(pEquip==NULL)
							continue;
						//pEquip->Render(pEquip->m_pHareWareRenderBuff);
					}
				}
	
				void Model::GetBoneMatrix( UInt uiIndex,Float3* pPos,Float4* pQ /*= NULL*/ ){
					CalModel*	pAnim	=	(CalModel*)m_pObject;
					CalBone*	pBone	=	pAnim->getSkeleton()->getBone(uiIndex);
					
					
					if(pPos!=NULL){
						const	CalVector&		v	=	pBone->getTranslationAbsolute();
						*pPos	=	Float3(v.x,v.z,v.y);
					}
					if(pQ!=NULL){
						const	CalQuaternion&	q	=	pBone->getRotationAbsolute();
						*pQ		=	Float4(q.w,q.x,q.z,q.y);
					}
				}
	
				U1 Model::AttachObject2Bone(AString	strBoneName,MovableObject* pObject ){
					if(	strBoneName.empty()	||
						pObject==NULL)
						return	false;
	
					BoneNodeMapItr	i	=	m_mapBoneNode.find(strBoneName.c_str());
					//判断是否已存在列表中
					if(i!=m_mapBoneNode.end()){
						SceneNode*	pNode	=	i->second;
						if(pNode!=NULL){
							pNode->attachObject(pObject);
							m_mapBoneNode[strBoneName.c_str()]	=	pNode;
						}
						m_mapAttachObjects[pObject]				=	pNode;
					}else{
						//获取骨骼索引
						CalModel*		pAnim	=	(CalModel*)m_pObject;
						UInt	uiBoneIdx	=	pAnim->getCoreModel()->getBoneId(strBoneName);
						//获取骨骼变换
						Float3	v;
						Float4	q;
						GetBoneMatrix(uiBoneIdx,&v,&q);
						//创建节点
						SceneNode*	pNode	=	GetParentSceneNode()->CreateChildSceneNode();
						pNode->SetName(strBoneName);
						pNode->SetPosition(v);
						pNode->SetQuat(q);
						//绑定物体
						pNode->attachObject(pObject);
						//添加到列表
						m_mapBoneNode[strBoneName.c_str()]	=	pNode;
						m_mapAttachObjects[pObject]			=	pNode;
					}
	
					return	true;
				}
	
				U1 Model::detachObject( MovableObject* pObject ){
					if(pObject==NULL)
						return	true;
	
					AttachObjectMapItr	i	=	m_mapAttachObjects.find(pObject);
					if(i!=m_mapAttachObjects.end()){
						SceneNode*	pNode	=	i->second;
						if(pNode!=NULL){
							pNode->detachObject(pObject);
							if(	pNode->GetObjectList().empty()	&&
								pNode->GetChildNodeList().empty()){
								Common::INode*	pParent	=	pNode->GetParentSceneNode();
								pParent->RemoveChild(pNode,true);
							}
						}
						m_mapAttachObjects.erase(i);
					}
					return	true;
				}
	
				void Model::RenderAttachObject(){
	// 				if(m_pAttachObjNode!=NULL){
	// 					m_pAttachObjNode->UpdataResultMatrix();
	// 					m_pAttachObjNode->Updata();
	// 					m_pAttachObjNode->RenderObject();
	// 				}
				}
	
				void Model::UpdataAttachObject(){
					CalModel*		pAnim	=	m_pAnimation;
					CalCoreModel*	pModel	=	pAnim->getCoreModel();
					std::vector<CalBone*>&	lstBone	=	pAnim->getSkeleton()->getVectorBone();;
					//更新骨骼节点
					BoneNodeMapItr	i	=	m_mapBoneNode.begin();
					for(;i!=m_mapBoneNode.end();i++){
						//m_mapAttachObjects.erase(i);
	
						UInt	uiIdx		=	pModel->getBoneId(i->first.c_str());
						const CalQuaternion&	q	=	lstBone[uiIdx]->getRotationAbsolute();
						const CalVector&		v	=	lstBone[uiIdx]->getTranslationAbsolute();
						i->second->SetPosition(Float3(v.x,v.z,v.y));
						i->second->SetQuat(Float4(q.w,q.x,q.z,q.y));
	
	// 					const	CalVector&		v	=	pBone->getTranslationAbsolute();
	// 					*pPos	=	Float3(v.x,v.z,v.y);
	// 				}
	// 				if(pQ!=NULL){
	// 					const	CalFloat4&	q	=	pBone->getRotationAbsolute();
	// 					*pQ		=	Float4(q.w,q.x,q.z,q.y);
	 				}
					//更新骨骼绑定根节点
	// 				if(m_pParentNode!=NULL){
	// 					m_pAttachObjNode->SetPosition(m_pParentNode->GetPosition());
	// 					m_pAttachObjNode->SetQuat(m_pParentNode->GetQuat());
	// 					m_pAttachObjNode->SetScale(m_pParentNode->GetScale());
	// 					m_pAttachObjNode->UpdataMatrix(NULL);
	// 				}
				}
	
				SceneNode* Model::GetBoneSceneNode( AString strBoneName ){
					BoneNodeMapItr	i	=	m_mapBoneNode.find(strBoneName.c_str());
					//判断是否已存在列表中
					if(i!=m_mapBoneNode.end()){
						return	i->second;
					}else{
						//获取骨骼索引
						CalModel*		pAnim	=	(CalModel*)m_pObject;
						UInt	uiBoneIdx	=	pAnim->getCoreModel()->getBoneId(strBoneName);
						//获取骨骼变换
						Float3	v;
						Float4	q;
						GetBoneMatrix(uiBoneIdx,&v,&q);
						//创建节点
						SceneNode*	pNode	=	GetParentSceneNode()->CreateChildSceneNode();
						pNode->SetName(strBoneName);
						pNode->SetPosition(v);
						pNode->SetQuat(q);
						//添加到列表
						m_mapBoneNode[strBoneName.c_str()]	=	pNode;
	
						return	pNode;
					}
				}

				void Model::ProcessRenderObject( U32 uiPhaseFlag )
				{
					EquipmentMap::iterator	i	=	m_mapEquipment.begin();
					for(;i!=m_mapEquipment.end();i++){
						i->second->AddToRenderQueue(uiPhaseFlag);
					}
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
				ModelFactory::ModelFactory(){
					m_strTypeName	=	"CharacterAnimationModel";
				}
	
				IProduct* ModelFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
					if(lstParam == NULL)
						return NULL;
					Model::Info*	pInfo	=	(Model::Info*)lstParam;
					Model*	pBuff			=	new	Model(strName,pInfo);
	
					//Insert(pBuff);
					return pBuff;
				}
			}
		}
	}
};