#ifndef AirPipelineOIT_h__
#define AirPipelineOIT_h__


#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{
		class	OIT{
		public:
			OIT();
			~OIT();


			U1	Initialize(Render::Window*	pMainWindow);
			U1	Release();

			void	UpdateOIT();

			Render::Buffer*	m_pPixelBuffer;
			Render::Buffer*	m_pScreenMask_Counter;
			Material*		m_pPerPixelLinkedList;
			Material*		m_pSortRender;
		};
	}
}
#endif // AirPipelineOIT_h__
