/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InterfalHell	Xinhe
 \date      2011/08/31
 \version   ver 0.6.0.0
 \filepath  f:\Air\trunk\AirClient\AirEngine\Inc
 \filename  AirEngineViewport.h
 \note     
       
 \attention:
			
 \remarks    created by InterfalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef AIRENGINEVIEWPORT_HEAD_FILE
#define AIRENGINEVIEWPORT_HEAD_FILE

#include "AirEngineHeader.h"

namespace	Air{
	namespace Engine{
		namespace	Render{
			class	Target;
		}
		class	ENGINE_EXPORT	Viewport	:	public	MemoryObject{
		public:
			Viewport(	Real	fWidth	=	1.0f,
						Real	fHeight	=	1.0f,
						Real	fX	=	0.0f,
						Real	fY	=	0.0f);

			void	SetPosition(Real	fX,Real	fY);
			void	SetSize(Real	fWidth,Real	fHeight);

			Real	GetX();
			Real	GetY();
			Real	GetWidth();
			Real	GetHeight();
			U32		GetAbsX();
			U32		GetAbsY();
			U32		GetAbsWidth();
			U32		GetAbsHeight();

			U1		Update();
			U1		UpdateCubeFace(U32	uiIndex);
			void	SetCamera(Camera*	pCamera);
			Camera*	GetCamera();
			void	SetTarget(RenderTarget*	pTarget);
			RenderTarget*	GetTarget();
		protected:
			Real	m_fX;
			Real	m_fY;
			Real	m_fWidth;
			Real	m_fHeight;
			RenderTarget*	m_pTarget;
			Camera*			m_pCamera;
		};

		typedef	STD_MAP<U32,Viewport*>	ViewportMap;
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // AIRENGINEVIEWPORT_HEAD_FILE