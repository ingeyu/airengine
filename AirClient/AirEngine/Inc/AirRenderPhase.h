/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/28
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EnginePhase.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINEPHASE_HEAD_FILE
#define ENGINEPHASE_HEAD_FILE

#include "AirEngineMaterialTemplate.h"

namespace	Air{
	namespace Client{
		typedef	std::map<U64,MaterialTemplate*>	MaterialTemplateMap;
		typedef	std::vector<MaterialTemplateMap>	MaterialTemplateMapVector;

		namespace	Render{
			class	Phase{
			public:
				Phase();
				~Phase();

				U1	AddMaterialTemplate(MaterialTemplate*	pTech);
				U1	RemoveMaterialTemplate(MaterialTemplate*	pTech);
				
				U1	RenderMaterialTemplate();
				void			ClearRenderObject();

				MaterialTemplateMap	m_mapMaterialTemplate;
			}; 

			typedef	std::vector<Phase>	PhaseVector;

			class	PhaseManager{
			public:
				PhaseManager();

				U1				AddMaterialTemplate(MaterialTemplate*	pTech);
				U1				RemoveMaterialTemplate(MaterialTemplate*	pTech);
				U1				RenderPhase(PhaseOption&	opt);
				U1				RenderPhase();


				void			SetPhaseFlag(U32	uiFlag);
				U32				GetPhaseFlag();
				void			SetPhaseOption(PhaseOption&	opt);
				void			AddPhaseFlag(enumPhaseIndex	uiPhaseIndex);
				void			ClearPhaseFlag();
				void			ClearRenderObject();
				void			ClearRenderObject(U32	uiPhaseFlag);


				PhaseVector		m_vecPhase;
				PhaseOption		m_PhaseOpt;
				static	U32		m_uiMaxPhase;
			};
		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINEPHASE_HEAD_FILE