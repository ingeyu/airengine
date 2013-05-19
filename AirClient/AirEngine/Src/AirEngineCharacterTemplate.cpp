#include "AirEngineCharacterTemplate.h"
#include "AirSlkReader.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirEngineSceneNode.h"
#include "AirGlobalSetting.h"
#include "AirResourceSystem.h"
#include "AirEngineMaterialParse.h"
#include "AirCSV.h"
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
				ResourceSystem::GetSingleton()->Find(m_Info.strModelPath + "Animation.csv",pData);
				if(pData.IsNull())
					return false;
				CSV csv;
				csv.Load(pData.buff,pData.size);


				for(U32 i=1;i<csv.m_uiLineCount;i++)
				{
					AString strFileName	=	csv.GetItem(4,i).pStr;
					m_vecState.push_back(strFileName);
				}


				ResourceSystem::GetSingleton()->Find(m_Info.strModelPath + "Equipment.csv",pData);
				if(pData.IsNull())
					return false;
				csv.Clear();
				csv.Load(pData.buff,pData.size);
				
				for(U32 i=1;i<csv.GetLineCount();i++)
				{
					
					AString strFileName	=	csv.GetItem(2,i).pStr;
					AString strMaterialName	=	csv.GetItem(3,i).pStr;

					m_vecEquipment.push_back(strFileName);
					m_vecMaterial.push_back(strMaterialName);
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

				CSV csv;
				csv.Load(pData.buff,pData.size);

				U32 uiLine	=	csv.GetLineCount();

				for(U32 i=1;i<uiLine;i++){

					ModelTemplate::Info	info;
	
					AString	strName			=	csv.GetItem(1,i).pStr;
					info.strSkeletonName	=	csv.GetItem(4,i).pStr;
					info.strModelPath		=	csv.GetItem(5,i).pStr;;

					EngineSystem::GetSingleton()->CreateProduct<ModelTemplate>(strName,&info);
				}
				return true;
			}

		}
	}
};