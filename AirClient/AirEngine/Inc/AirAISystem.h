#ifndef AirAISystem_h__
#define AirAISystem_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	AI{
		class	ENGINE_EXPORT	System	:	
			public	Common::IFactoryManager,
			public	Singleton<System>
		{
		public:
			System();

			
			virtual	U1	Create();
			virtual	U1	Destroy();

			void				SVOUpdate(U32* svoData,U32 uiDepth,float fScale);
			STD_VECTOR<Float3>	SVOFindPath(const Float3& vStart,const Float3& vTarget);
		protected:
			U32*		m_SVO;
			U32			m_uiDepth;
			float		m_fSVOScale;
		};
	}
}
#endif // AirAISystem_h__
