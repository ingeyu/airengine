#include "AirEngineCharacterManager.h"
#include "AirSlkReader.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirEngineSceneNode.h"
#include "AirGlobalSetting.h"
#include "AirInterfaceResourceSystem.h"
#include "AirEngineMaterialParse.h"
namespace Air{
	
	namespace	Engine{
		namespace	Character{
			//Manager g_CharacterMgr;
	
	
			Manager::Manager(){
				m_uiCurrentId	=	0;
				m_pModel		=	NULL;
				
				m_pNode			=	NULL;
			}
	
			Manager::~Manager(){
	
			}
	
			U1 Manager::LoadSLK( CAString& strName ){
				AString	strCharacterConfigName	=	AString("Character/")	+	strName;
	
				CSlkReader r;
				
				Data	pData;
				GetGlobalSetting().m_pResourceSystem->Find(strCharacterConfigName,pData);
				if(pData.IsNull())
					return	false;
				if( !r.ReadFromString( (char*)pData.GetBuff(),pData.GetSize()) ){
					//assert(false);
					return FALSE;
				}
	
				int nLine = 2;
				int iRet;
	
				while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
				{
					if( CSlkReader::ret_nothisline == iRet )
						continue;
	
					CSlkReader::SField* field;
					CharacterInfo	info;
					UInt	i	=	1;
					//id
					field	=	r.GetFieldOfLine(i++);
					if(!field || field->iFieldType != CSlkReader::field_int)
						continue;
					info.uiID	=	field->data.iValue;
					//名字
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strName	=	field->data.szValue;
					//动画文件
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strAnimationFileName	=	field->data.szValue;
					//装备文件
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strEquipmentFileName	=	field->data.szValue;
					//骨骼名
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strSkeletonName	=	field->data.szValue;
					//路径
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strPath	=	field->data.szValue;
					if(!info.strPath.empty()){
						Data data;
						GetGlobalSetting().m_pResourceSystem->Find(info.strPath+"Equipment.material",data);
						if(!data.IsNull()){
							MaterialParse::GetSingleton()->CompileMaterialSet(data.buff,data.size);
						}
					}
	
					m_mapCharacterInfo.insert(CharacterInfoMapPair(info.strName,info));
				}
				return true;
			}
	
	
			Animation::Model* Manager::Create( CAString& strName,CAString& strType ){
				CharacterInfoMapItr	i	=	m_mapCharacterInfo.find(strType.c_str());
				if(i!=m_mapCharacterInfo.end()){
					//if(iID == uiIndex){
					CharacterInfo&	info	=	i->second;
					Destroy();
					Animation::Model::Info	modelInfo;
					modelInfo.strResourcePath	=	info.strPath;
					modelInfo.strSkeleton		=	info.strSkeletonName;
	
					m_pModel	=	EngineSystem::GetSingleton()->CreateProduct<Animation::Model>(strName,&modelInfo);
					if(m_pNode!=NULL)
						m_pNode->attachObject(m_pModel);
					LoadAnimation(info.strPath	+	"Animation.slk");
					LoadEquipment(info.strPath	+	"Equipment.slk");
				}
				return	m_pModel;
			}
			void Manager::LoadAnimation( CAString& strAnimationName ){
				CSlkReader r;
				Data	pData;
				GetGlobalSetting().m_pResourceSystem->Find(strAnimationName,pData);
				if(pData.IsNull())
					return;
				if( !r.ReadFromString( (char*)pData.GetBuff(),pData.GetSize() ) ){
					assert(false);
					return;
				}
	
				int nLine = 2;
				int iRet;
	
				while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
				{
					if( CSlkReader::ret_nothisline == iRet )
						continue;
	
					CSlkReader::SField* field;
					AnimationInfo	info;
					UInt	i	=	4;
	
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strName	=	field->data.szValue;
	
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strFileName	=	field->data.szValue;
	
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_int )
						continue;
	
					info.bLoop	=	(field->data.iValue == 1);
					if(info.bLoop)
						m_lstStateAnimation.push_back(info);
					else
						m_lstAnimation.push_back(info);
				}	
			}
	
			void Manager::LoadEquipment( CAString& strEquipmentName ){
				CSlkReader r;
				Data	pData;
				GetGlobalSetting().m_pResourceSystem->Find(strEquipmentName,pData);
				if(pData.IsNull())
					return;
				if( !r.ReadFromString( (char*)pData.GetBuff(),pData.GetSize() ) ){
					assert(false);
					return;
				}
	
				int nLine = 2;
				int iRet;
	
				while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
				{
					if( CSlkReader::ret_nothisline == iRet )
						continue;
	
					CSlkReader::SField* field;
					EquipmentInfo	info;
					UInt	i	=	2;
	
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strPart	=	field->data.szValue;
	
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strFileName	=	field->data.szValue;
	
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strMaterialName	=	field->data.szValue;
	
					//m_lstAnimation.push_back(info);
					if(m_pModel!=NULL)
						m_pModel->AddEquipment(info.strFileName,info.strMaterialName,info.strPart);
				}	
			}
	
			void Manager::Destroy(){
				if(m_pModel!=NULL){
					m_pModel->ReleaseRef();
					m_pModel	=	NULL;
					m_lstAnimation.clear();
					m_lstStateAnimation.clear();
				}
			}
	
			void Manager::Update( Real fTimeDelta ){
				if(m_pModel!=NULL)
					m_pModel->Update();
			}
	
			void Manager::Render(){
				if(m_pModel!=NULL)
					m_pModel->Render();
			}
	
			Real Manager::GetAnimationSpeed(){
				if(m_pModel!=NULL)
					return m_pModel->GetAnimationSpeed();
				return 1.0f;
			}
	
			void Manager::SetAnimationSpeed( Real fSpeed /*= 1.0f*/ ){
				if(m_pModel!=NULL)
					return	m_pModel->SetAnimationSpeed(fSpeed);
			}
	
			void Manager::SetAnimationSpeedOffset( Real fSpeedOffset /*= -0.01f*/ ){
				if(m_pModel!=NULL)
					return	m_pModel->SetAnimationSpeedOffset(fSpeedOffset);
			}
	
			void Manager::Action( CAString& strName,Real fBlend ){
				if(m_pModel!=NULL)
					m_pModel->PlayAction(strName , fBlend);
	
			}
	
			void Manager::State( CAString& strName ){
				if(strName.empty()	||	strName	==	m_strState)
					return;
				if(m_pModel!=NULL)
					m_pModel->SetActionState(strName);
			}
	
			AString Manager::NextAction(){
				static	UInt	iPos	=	0;
				UInt	uiSize	=	m_lstAnimation.size();
				for(UInt i=0;i!=uiSize;i++){
					if(iPos>=uiSize)iPos=0;
					UInt	iCurrent	=	iPos++;
					if(m_pModel!=NULL)
						m_pModel->PlayAction(m_lstAnimation[iCurrent].strFileName);
					return	m_lstAnimation[iCurrent].strName;
				}
				return "";
			}
	
			AString Manager::NextState(){
				static	UInt	iPos	=	0;
				UInt	uiSize	=	m_lstStateAnimation.size();
				for(UInt i=0;i!=uiSize;i++){
					if(iPos>=uiSize)iPos=0;
					UInt	iCurrent	=	iPos++;
					if(m_pModel!=NULL)
						m_pModel->SetActionState(m_lstStateAnimation[iCurrent].strFileName);
					return	m_lstStateAnimation[iCurrent].strName;
				}
				return "";
			}
	
			void Manager::SetMaterial( CAString& strType,CAString& strMaterial ){
	
			}
	
			void Manager::Remove( CAString& strType ){
				m_pModel->RemoveEquipment(Animation::Equipment::enHair);
			}
	
			void Manager::Add(){
				m_pModel->AddEquipment("fw_hair.cmf","Material\\fw_hair.Material","Hair");
			}
	
			void Manager::SetSceneNode( SceneNode* pNode ){
				if(pNode==NULL)
					return;
				m_pNode	=	pNode->CreateChildSceneNode();
				m_pNode->SetQuat(Float4(Float3(1,0,0),-3.1415926f*0.5f));
				m_pNode->SetScale(Float3(0.05f,0.05f,0.05f));
				//m_pNode->SetPosition(Float3(0,-1,-1.5));
			}

			SceneNode* Manager::GetSceneNode()
			{
				return	m_pNode;
			}

		}
	}
};