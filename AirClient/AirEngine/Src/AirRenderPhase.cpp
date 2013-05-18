#include "AirRenderPhase.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{
			U32	PhaseManager::m_uiMaxPhase	=	64;

			PhaseManager::PhaseManager(){
				m_vecPhase.resize(m_uiMaxPhase);
				//m_uiPhaseFlag	=	0;
			}

			Air::U1 PhaseManager::AddMaterialTemplate( MaterialTemplate* pTech ){
				if(pTech	==	NULL)
					return	false;

				U32	uiPhaseIdx	=	pTech->GetPhaseIndex();

				if(uiPhaseIdx	>=	m_uiMaxPhase){
					return	false;
				}

				m_vecPhase[uiPhaseIdx].AddMaterialTemplate(pTech);
				return	true;
			}

			Air::U1 PhaseManager::RemoveMaterialTemplate( MaterialTemplate* pTech ){
				if(pTech	==	NULL)
					return	false;

				U32	uiPhaseIdx	=	pTech->GetPhaseIndex();
				if(uiPhaseIdx	>=	m_uiMaxPhase){
					return	false;
				}

				m_vecPhase[uiPhaseIdx].RemoveMaterialTemplate(pTech);

				return	true;
			}



			void PhaseManager::SetPhaseFlag( U32 uiFlag ){
				m_PhaseOpt.flag	=	uiFlag;
			}

			Air::U32 PhaseManager::GetPhaseFlag(){
				return	m_PhaseOpt.flag;
			}

			void PhaseManager::AddPhaseFlag( enumPhaseIndex uiPhaseIndex ){
				m_PhaseOpt.AddIndex(uiPhaseIndex);
			}	

			void PhaseManager::ClearPhaseFlag(){
				m_PhaseOpt.Clear();
			}

			void PhaseManager::ClearRenderObject(){
				for(U32	i=0;i<32;i++)
					m_vecPhase[i].ClearRenderObject();
			}

			void PhaseManager::ClearRenderObject( U32 uiPhaseFlag ){
				for(U32	i=0;i<32;i++){
					if(uiPhaseFlag&(1<<i))
						m_vecPhase[i].ClearRenderObject();
				}
			}
			void PhaseManager::SetPhaseOption( PhaseOption& opt ){
				m_PhaseOpt	=	opt;
			}

			Air::U1 PhaseManager::RenderPhase( PhaseOption& opt ){
				PhaseIdxList::iterator	i	=	opt.lstPI.begin();
				for(;i!=opt.lstPI.end();i++){
					m_vecPhase[*i].RenderMaterialTemplate();
				}
				return	true;
			}

			Air::U1 PhaseManager::RenderPhase(){
				PhaseIdxList::iterator	i	=	m_PhaseOpt.lstPI.begin();
				for(;i!=m_PhaseOpt.lstPI.end();i++){
					m_vecPhase[*i].RenderMaterialTemplate();
				}
				return	true;
			}
			Phase::Phase(){

			}

			Phase::~Phase(){

			}

			Air::U1 Phase::AddMaterialTemplate( MaterialTemplate* pTemplate ){
				if(pTemplate==NULL)
					return	false;
				U64	uiHash				=	pTemplate->GetHash();

				m_mapMaterialTemplate[uiHash]	=	pTemplate;
				return	true;
			}

			Air::U1 Phase::RemoveMaterialTemplate( MaterialTemplate* pTemplate ){
				if(pTemplate==NULL)
					return	false;
				U64	uiHash				=	pTemplate->GetHash();
				MaterialTemplateMap::iterator	i	=	m_mapMaterialTemplate.find(uiHash);
				if(i!=m_mapMaterialTemplate.end()){
					m_mapMaterialTemplate.erase(i);
				}
				return	true;
			}

			Air::U1 Phase::RenderMaterialTemplate(){

				MaterialTemplateMap::iterator	i	=	m_mapMaterialTemplate.begin();
				for(;i!=m_mapMaterialTemplate.end();i++){
					i->second->RenderAllMaterial();
				}

				return	true;
			}

			void Phase::ClearRenderObject(){

				MaterialTemplateMap::iterator	i	=	m_mapMaterialTemplate.begin();
				for(;i!=m_mapMaterialTemplate.end();i++){
					i->second->ClearRenderObject();
				}
			}
		}
	}
}