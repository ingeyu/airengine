#ifndef AirPostProcessHDR_h__
#define AirPostProcessHDR_h__

#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{
		class	Material;
		class	QuadRenderable;

		namespace	PostProcess{
			class	HDR{
			public:
				HDR();
				~HDR();

				void	Init();
				void	Release();
				void	UpdateTarget();
				RenderTarget*	m_pRT_Luminance[6];
				RenderTarget*	m_pRT_Brightness[2];
				Material*		m_matColorToLuminance;
				Material*		m_matDownScaleLuminance;
				Material*		m_matBrightness;
				Material*		m_matBrightBlur;
				Material*		m_matBloom;
				Material*		m_matFinal;
			};
		}
	}
}
#endif // AirHDR_h__
