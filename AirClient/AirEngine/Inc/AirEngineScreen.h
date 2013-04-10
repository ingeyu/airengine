#ifndef AirEngineScreen_h__
#define AirEngineScreen_h__

#include "AirEngineHeader.h"

namespace	Air{
	namespace	Engine{
		class	Pipeline;
		class	ENGINE_EXPORT	Screen	:public		IProduct{
		public:
			static AString ProductTypeName;
			struct Info 
			{
				Info(){

				};
				AString	strPipelineName;
			};
		public:
			Screen(CAString& strName,Info* pInfo);
			virtual	U1	Create();
			virtual	U1	Destroy();

			//返回指针会增加引用计数
			Pipeline*	GetPipeline();
			U1			RenderOneFrame(const FrameTime& frameTime);
			void		SetCurrentScene(Scene*	pScene);
			Scene*		GetCurrentScene();
		protected:
			Pipeline*	OnCreatePipeline(CAString&	strPipelineName);


			Pipeline*	m_pPipeline;
			Info		m_Info;
		};
	}
}
#endif // AirEngineScreen_h__
