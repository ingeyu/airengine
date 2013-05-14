#include "AirParticleRenderer.h"
#include "AirParticle.h"
namespace	Air{
	namespace	Engine{


		ParticleRenderer::ParticleRenderer(CAString& strName,Info* pInfo):IProduct(strName)
		{

		}

		Air::U1 ParticleRenderer::Create()
		{
			return true;
		}

		Air::U1 ParticleRenderer::Destroy()
		{
			return true;
		}

		void ParticleRenderer::OnParticleRender( Render::Device* pDevice,Particle* pParticle )
		{

		}

	}
}