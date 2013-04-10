#include "AirRenderState.h"
#include "AirEngineMaterialParse.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{
			AString	State::ProductTypeName	=	"RenderState";
			State::State( CAString& strName,StateInfo*	pInfo ):IProduct(strName){
				if(pInfo!=NULL){
					m_Info		=	*pInfo;
					m_bCostom	=	true;
				}else{
					PassStateInfo*	p	=	MaterialParse::GetSingleton()->GetPassStateInfo(m_strProductName);
					if(p!=NULL)
						m_Info	=	*p;
					m_bCostom	=	false;
				}
			}

			Air::U1 State::Create(){
				return	true;
			}

			Air::U1 State::Destroy(){

				return	true;
			}

			void* State::GetState(){
				return	NULL;
			}

			Air::Engine::enumRenderStateType State::GetType()
			{
				return	m_Info.type;
			}

		}
	}
}