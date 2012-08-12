/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/12
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EngineTechnique.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINETECHNIQUE_HEAD_FILE
#define ENGINETECHNIQUE_HEAD_FILE

#include "AirEnginePass.h"

namespace	Air{
	namespace Client{
		class MaterialTemplate;
		struct TechniqueInfo;
	
		class	ENGINE_EXPORT	Technique	:
			public	Common::IObject{
		public:
			Technique(TechniqueInfo*	pInfo);
			virtual	~Technique();

			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual	void	Render();
			virtual	void	RenderOneObject(TextureArray& vecTexture,Renderable* pObj);
			Pass*			GetPass(U32	uiIndex);
			U32				GetPassCount();
			U64				GetHash();
			enumQualityType	GetQuality();
			void			SetQuality(enumQualityType	type);
			void			ClearRenderObject();
		protected:
			U64						m_Hash;
			PassVector				m_vecPass;
			TechniqueInfo*			m_pInfo;
			MaterialTemplate*		m_pTemplate;
			enumQualityType			m_uiQuality;
		};

		typedef	std::vector<Technique*>		TechniqueVector;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINETECHNIQUE_HEAD_FILE