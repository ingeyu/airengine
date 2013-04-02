#include "AirEngineViewport.h"
#include "AirGlobalSetting.h"
#include "AirRenderSystem.h"
#include "AirRenderTarget.h"
#include "AirEngineCamera.h"

namespace	Air{
	namespace	Engine{


		Viewport::Viewport( Real fWidth /*= 1.0f*/, 
							Real fHeight /*= 1.0f*/, 
							Real fX /*= 0.0f*/, 
							Real fY /*= 0.0f*/ )
		{
			m_fX	=	fX;
			m_fY	=	fY;
			m_fWidth	=	fWidth;
			m_fHeight	=	fHeight;
			m_pTarget	=	NULL;
		}

		void Viewport::SetPosition( Real fX,Real fY ){
			m_fX	=	fX;
			m_fY	=	fY;
		}

		void Viewport::SetSize( Real fWidth,Real fHeight ){
			m_fWidth	=	fWidth;
			m_fHeight	=	fHeight;
		}

		Air::Real Viewport::GetX(){
			return	m_fX;
		}

		Air::Real Viewport::GetY(){
			return	m_fY;
		}

		Air::Real Viewport::GetWidth(){
			return	m_fWidth;
		}

		Air::Real Viewport::GetHeight(){
			return	m_fHeight;
		}

		Air::U32 Viewport::GetAbsX(){
			return	m_fX*m_pTarget->GetWidth();
		}

		Air::U32 Viewport::GetAbsY(){
			return	m_fY*m_pTarget->GetHeight();
		}

		Air::U32 Viewport::GetAbsWidth(){
			return	m_fWidth*m_pTarget->GetWidth();
		}

		Air::U32 Viewport::GetAbsHeight(){
			return	m_fHeight*m_pTarget->GetHeight();
		}

		Air::U1 Viewport::Update(){
			//Render::System::GetSingleton()->SetViewport(this);

			m_pCamera->Render2D(GetAbsWidth(),GetAbsHeight());

			return	true;
		}

		Air::U1 Viewport::UpdataCubeFace( U32 uiIndex ){
			//Render::System::GetSingleton()->SetViewport(this);

			m_pCamera->RenderCubeMap(uiIndex,GetAbsWidth(),GetAbsHeight());

			return	true;
		}

		void Viewport::SetCamera( Camera* pCamera ){
			m_pCamera	=	pCamera;
		}

		Camera* Viewport::GetCamera(){
			return	m_pCamera;
		}

		void Viewport::SetTarget( RenderTarget* pTarget )
		{
// 			if(m_pTarget!=NULL){
// 				m_pTarget->RemoveViewport()
// 			}
			m_pTarget	=	pTarget;
		}

		RenderTarget* Viewport::GetTarget()
		{
			return	m_pTarget;
		}

	}
}