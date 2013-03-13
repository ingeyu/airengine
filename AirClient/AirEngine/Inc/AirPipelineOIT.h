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

			void	Update(Renderable* pRenderable);

			Render::Buffer*	m_pPixelBuffer_Counter;
			Render::Buffer*	m_pScreenMask;
			Material*		m_pPerPixelLinkedList;
			Material*		m_pSortRender;
		};
	}
}
#endif // AirPipelineOIT_h__
