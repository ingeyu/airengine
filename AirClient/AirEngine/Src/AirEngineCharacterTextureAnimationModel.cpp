#include "AirEngineCharacterTextureAnimationModel.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "..\..\AirCharacter\cal3d.h"
namespace Air{
	
	namespace	Client{
		namespace	Character{
			namespace	Animation{
	
	
				TextureModel::TextureModel( CAString& strName,Info* pInfo )
					:Model(strName,pInfo){
	
				}
	
				U1 TextureModel::Create(){
					Render::Texture::Info	info;
					info.SetDynamicTexture(1024,1,enTFMT_R32G32B32A32_FLOAT);
					info.usage			=	Render::enUSAGE_DEFAULT;

					m_pBoneTexture		=	Render::System::GetSingleton()->CreateProduct<Render::Texture*>(m_strProductName,("Texture"),&info);
					info.usage			=	Render::enUSAGE_SYSTEM_MEMORY;
					m_pTempBoneTexture	=	Render::System::GetSingleton()->CreateProduct<Render::Texture*>(m_strProductName	+	"Temp",("Texture"),&info);
					
					return	__super::Create();
				}
	
				U1 TextureModel::Destroy(){
					SAFE_RELEASE_REF(m_pBoneTexture);
					SAFE_RELEASE_REF(m_pTempBoneTexture);
					return	__super::Destroy();
				}
	
				void TextureModel::Updata(){
					CoreAnimation*	pAnimation	=	(CoreAnimation*)m_pObject;
					if(pAnimation){
						pAnimation->update(GetGlobalSetting().m_ShaderParam.m_fEngineTimeDelta*m_fAnimationSpeed);
					
						CalSkeleton*	pSkel			=	pAnimation->getSkeleton();
						std::vector<CalBone*>&	lstBone	=	pSkel->getVectorBone();
						UInt	uiBoneCount	=	lstBone.size();
						static	Float44 g_TempBoneMatrix[256];
						for(UInt i=0;i<uiBoneCount;i++){
							const	CalQuaternion&	q	=	lstBone[i]->getRotationBoneSpace();
							const	CalVector&		v	=	lstBone[i]->getTranslationBoneSpace();
	 						Float44	m(Float4(q.w,q.x,q.y,q.z));
	 						Float3*	pP	=	(Float3*)&v;
							static Float3 vScale(1,1,1);
	 						g_TempBoneMatrix[i]	=	Float44(*pP,vScale,Float4(q));//(m.transpose();
	 						//g_TempBoneMatrix[i].(*pP);
// 							Float44	m(Float4(q.w,q.x,q.y,q.z));
// 								
// 							m[3][0]	=	v.x;
// 							m[3][1]	=	v.y;
// 							m[3][2]	=	v.z;
					//		g_TempBoneMatrix[i]	=	m;//.transpose();
						}
// 						Render::ITexture::LockRectOption	option;
// 						option.pData	=	NULL;
// 						option.pitch	=	1024*16;
// 						if(m_pTempBoneTexture->Lock(&option)){
// 							memcpy(option.pData,&g_TempBoneMatrix[0],sizeof(Float44)*uiBoneCount);
// 							m_pTempBoneTexture->UnLock();
// 							
// 	
// 						}
	
						UpdataAttachObject();
					}
				}
	
				void TextureModel::RenderHardWare(){
					static POINT p =	{0,0};
					//Render::System::GetSingleton()->UpdataSurface(m_pTempBoneTexture,NULL,m_pBoneTexture,p);
					GetGlobalSetting().m_ShaderParam.m_pBoneTexture	=	m_pBoneTexture;
					//调用装备的渲染函数来渲染
					EquipmentMapItr	itr	=	m_mapEquipment.begin();
					for(;itr!=m_mapEquipment.end();itr++){ 
						Equipment*	pEquip	=	itr->second;
						if(pEquip==NULL)
							continue;
						//pEquip->Render(pEquip->m_pHareWareRenderBuff);
					}
				}
	
				TextureModelFactory::TextureModelFactory(){
					m_strTypeName	=	"CharacterTextureModel";
				}
	
				IProduct* TextureModelFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /* = NULL */ ){
					if(lstParam==NULL)
						return	NULL;
					return	new	TextureModel(strName,(Model::Info*)lstParam);
				}
			}
		}
	}
};