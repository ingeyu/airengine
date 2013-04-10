/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InfernalHell	Xinhe
 \date      2011/05/12
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirClient\AirEngine\Inc
 \filename  EngineMaterialTemplate.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef ENGINEMATERIALTEMPLATE_HEAD_FILE
#define ENGINEMATERIALTEMPLATE_HEAD_FILE
#include "AirEnginePass.h"

namespace	Air{
	namespace Engine{
		class	Material;
		struct	MaterialTemplateInfo;

		typedef	std::map<U64,Material*>	MaterialHashMap;
		
	
		class	ENGINE_EXPORT	MaterialTemplate	:
			public	Common::IProduct{
		public:
			static AString ProductTypeName;
			MaterialTemplate(CAString&	strName,MaterialTemplateInfo*	pInfo);


			virtual	U1	Create();
			virtual	U1	Destroy();

			void					RenderWithPass(Pass&	pass);
			void					RenderOneObject(TextureArray& vecTexture,Renderable* pObj);
			void					RenderAllMaterial();
			void					AddMaterial(Material*	pMaterial);
			void					RemoveMaterial(Material*	pMaterial);

			Pass*					GetPass( U32 uiIndex );
			U1						HasRenderables();
			enumPhaseIndex			GetPhaseIndex()const;
			void					ClearRenderObject();
			U64						GetHash(){return	m_Hash;};
		protected:
			U64						m_Hash;
			PassVector				m_vecPass;

			MaterialTemplateInfo*	m_pInfo;
			
			MaterialHashMap			m_mapMaterialHash;
			U1						m_bInLibrary;
			enumPhaseIndex			m_uiPhaseIndex;
		};

	};//end of	namespace	Client
};//end of namespace Air
#endif // ENGINEMATERIALTEMPLATE_HEAD_FILE