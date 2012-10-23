#ifndef AirEnginePipeline_h__
#define AirEnginePipeline_h__

#include "AirRenderSystem.h"

#include "AirInterfaceInputSystem.h"

namespace	Air{
	namespace	Client{
		class QuadRenderable;
		class Material;
		class Light;


		class	FrameListener{
		public:
			virtual	U1	OnBeforeRenderFrame(const	FrameTime&	frame){return	true;};
			virtual	U1	OnAfterRenderFrame(const	FrameTime&	frame){return	true;};
		};

		class	ENGINE_EXPORT	Pipeline	:	
			public	IProduct,
			public	OIS::MouseListener,
			public	OIS::KeyListener,
			public	Common::MutilListenerManager<FrameListener>{
		public:

			Pipeline(CAString&	strName);
			virtual	~Pipeline();

			virtual	U1		Create();
			virtual	U1		Destroy();

			virtual	void	Update(const FrameTime& frameTime);
			virtual	U1		RenderOneFrame(const FrameTime& frameTime);

			virtual	U1		SetCurrentScene(Scene*	pCurrentScene);
			Scene*			GetCurrentScene();

			inline	RenderWindow*		GetMainWindow(){
				return	m_pMainWindow;
			};

			virtual bool mouseMoved( const OIS::MouseEvent &arg );
			virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
			virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

			virtual bool keyPressed( const OIS::KeyEvent &arg );
			virtual bool keyReleased( const OIS::KeyEvent &arg );
		protected:
			RenderWindow*	m_pMainWindow;
			RenderTarget*	m_pMRT;
			RenderTarget*	m_pShadowDepth;
			RenderTarget*	m_pRT_ShadowMask;
			Light*			m_pMainLight;


			Scene*			m_pScene;
			QuadRenderable*	m_pQuad;
			Material*		m_pQuadCopy;
			Material*		m_pSSAO;
			Material*		m_pShadowMask;

			Float3			vMoveDirection;
			float			fVolocity;
		};
	}
}
#endif // AirEnginePipeline_h__
