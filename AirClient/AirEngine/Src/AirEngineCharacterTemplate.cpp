#include "AirEngineCharacterTemplate.h"
#include "AirSlkReader.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirEngineSceneNode.h"
#include "AirGlobalSetting.h"
#include "AirResourceSystem.h"
#include "AirEngineMaterialParse.h"
namespace Air{
	
	namespace	Engine{
		namespace	Character{


			AString ModelTemplate::ProductTypeName	=	"ModelTemplate";
			ModelTemplate::ModelTemplate( CAString& strName,Info* pInfo ):IProduct(strName)
			{
				if(pInfo!=NULL){
					m_Info	=	*pInfo;
				}
			}

			Air::U1 ModelTemplate::Create()
			{
				if(m_Info.strModelPath.empty())
					return false;

				CSlkReader r;
				Data	pData;
				ResourceSystem::GetSingleton()->Find(m_Info.strModelPath + "Animation.slk",pData);
				if(pData.IsNull())
					return false;
				if( !r.ReadFromString( (char*)pData.GetBuff(),pData.GetSize() ) ){
					return false;
				}

				int nLine = 2;
				int iRet;

				while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
				{
					if( CSlkReader::ret_nothisline == iRet )
						continue;

					CSlkReader::SField* field;
					
					UInt	i	=	4;

					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					//info.strName	=	field->data.szValue;

					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					AString strFileName	=	field->data.szValue;

					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_int )
						continue;

					U1 bLoop	=	(field->data.iValue == 1);
					if(bLoop)
						m_vecState.push_back(strFileName);
					else
						m_vecAction.push_back(strFileName);
				}


				ResourceSystem::GetSingleton()->Find(m_Info.strModelPath + "Equipment.slk",pData);
				if(pData.IsNull())
					return false;
				if( !r.ReadFromString( (char*)pData.GetBuff(),pData.GetSize() ) ){
					return false;
				}
				nLine = 2;
				while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
				{
					if( CSlkReader::ret_nothisline == iRet )
						continue;

					CSlkReader::SField* field;
					UInt	i	=	2;

					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;

					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					AString strFileName	=	field->data.szValue;

					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					AString strMaterialName	=	field->data.szValue;

					m_vecEquipment.push_back(strFileName);
					m_vecMaterial.push_back(strMaterialName);
					//if(m_pModel!=NULL)
					//	m_pModel->AddEquipment(info.strFileName,info.strMaterialName,info.strPart);
				}
				

				return true;
			}

			Air::U1 ModelTemplate::Destroy()
			{
				m_vecState.clear();
				m_vecAction.clear();
				m_vecEquipment.clear();
				m_vecMaterial.clear();
				return true;
			}

			U1 InitModelTemplate( CAString& strModelTemplateFileName )
			{
				AString	strCharacterConfigName	=	AString("Character/")	+	strModelTemplateFileName;

				CSlkReader r;

				Data	pData;
				ResourceSystem::GetSingleton()->Find(strCharacterConfigName,pData);
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
					ModelTemplate::Info	info;
					UInt	i	=	1;
					//id
					field	=	r.GetFieldOfLine(i++);
					if(!field || field->iFieldType != CSlkReader::field_int)
						continue;
					//info.uiID	=	field->data.iValue;
					//名字
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					AString	strName	=	field->data.szValue;
					//动画文件
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					//info.strAnimationFileName	=	field->data.szValue;
					//装备文件
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					//info.strEquipmentFileName	=	field->data.szValue;
					//骨骼名
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strSkeletonName	=	field->data.szValue;
					//路径
					field = r.GetFieldOfLine( i++ );
					if( !field || field->iFieldType != CSlkReader::field_string )
						continue;
					info.strModelPath	=	field->data.szValue;

					ResourceSystem::GetSingleton()->Find(info.strModelPath +"Equipment.material",pData);
					if(!pData.IsNull()){
						MaterialParse::GetSingleton()->CompileMaterialSet(pData.buff,pData.size);
					}

					EngineSystem::GetSingleton()->CreateProduct<ModelTemplate>(strName,&info);
				}
				return true;
			}

		}
	}
};