#ifndef AirRenderState11_h__
#define AirRenderState11_h__

#include "AirRenderHeader11.h"
#include "AirRenderState.h"

namespace	Air{
	namespace	Client{
		namespace	Render{
			class	State11	:	
				public	State{
			public:
				State11(CAString&	strName,PassStateInfo*	pInfo);

				virtual	U1	Create();
				virtual	U1	Destroy();
				virtual	void*	GetState();
				void*		m_pDxState;
			};
		}
	}
}

#endif // AirRenderState11_h__