#ifndef AirEngineMaterialSet_h__
#define AirEngineMaterialSet_h__

#include "AirEngineMaterial.h"

namespace	Air{
	namespace	Engine{


		class	ENGINE_EXPORT	MaterialSet	:	public	TProduct<MaterialSet>{
		public:
			MaterialSet(CAString& strName);

			virtual	U1	Create();
			virtual	U1	Destroy();


			Material*	GetPhaseMaterial(enumPhaseIndex	idx);
			void		RemovePhaseMaterial(enumPhaseIndex	idx);
			void		AddMaterial(Material*	pMaterial);
			void		AddMaterial(CAString& strMaterialName);
			void		AddRenderObject(Renderable*	pObj,U32	uiPhaseFlag);
		protected:

			MaterialMap		m_mapMaterial;
		};

		typedef	U1	(*GeneratorFunc)(MaterialSet*,MaterialSetInfo*,CAString&,U1);
		typedef	STD_HASHMAP<AString,GeneratorFunc>	GeneratorFuncMap;

		class	ENGINE_EXPORT	MaterialSetGenerator	:	public	Singleton<MaterialSetGenerator>{
		public:
			MaterialSetGenerator();
			virtual	~MaterialSetGenerator();

			void			AddGenerator(CAString&	strTypeName,GeneratorFunc	func);

			MaterialSet*	GenerateMaterialSet(CAString&	strName,CAString&	strType,U1 bUseSkin,MaterialSetInfo*	pSetInfo	=	NULL);
		protected:
			GeneratorFuncMap	m_mapGeneratorFunc;
		};
	}
}
#endif // AirEngineMaterialSet_h__