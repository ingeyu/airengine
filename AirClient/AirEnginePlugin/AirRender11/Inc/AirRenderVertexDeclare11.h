/*****************************************************/
/* @All Right Reserved (C), 2009-2012, AIR TECO CO.


 \author    InterfalHell	Xinhe
 \date      2011/03/29
 \version   ver 0.6.0.0
 \filepath  f:\EngineSource\Air\AirClient\AirEnginePlugin\AirRender9
 \filename  RenderVertexDeclarationManager.h
 \note     
       
 \attention:
			
 \remarks    created by InterfalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef RENDERVERTEXDECLARE_HEAD_FILE
#define RENDERVERTEXDECLARE_HEAD_FILE

#include "AirRenderHeader11.h"

namespace	Air{
	namespace Client{
	
		namespace	Render{

			//typedef	Vertex::IDeclare::ElementVector	VDElementVector;

			class	VertexDeclare11	:	public	Vertex::IDeclare{
			public:
				VertexDeclare11(CAString&	strName,Info*	pInfo);

				virtual	void*	GetDeclare();
				DxVertexDeclare*	m_pDeclare;
			};

		}
	
	};//end of	namespace	Client
};//end of namespace Air
#endif // RENDERVERTEXDECLARATIONMANAGER_HEAD_FILE