#ifndef ENGINETERRAINTITLE_HEAD_FILE
#define ENGINETERRAINTITLE_HEAD_FILE

#include "AirEngineTerrainCommon.h"
#include "AirEngineTerrainPage.h"
#include "AirEngineTerrainWater.h"
//#include "RenderObject.h"
namespace Air{
	
	namespace Client{
	
		
			namespace	Terrain{
				class	ENGINE_EXPORT	Title{
				public:
					Title();
					virtual ~Title();
	
					virtual bool	GetHeight(Real	x,Real	y,	Real*	z);
	
					virtual U1		Load();
					virtual U1		UnLoad();
					virtual U1		IsLoad();
	
					virtual void	Updata();
					virtual void	Render();
	
				protected:
	
					//Water				m_Water;
					Page*				m_pPageArray;
	
				public:
					static	SInt			Size;
					
				};
				/*
				//(Title)	= 2*2(Page)
				----------
				|	|	|
				|	|	|
				----------
				|	|	|
				|	|	|
				----------
				
				*/
				//static	SInt	Title::Size	=	2;
			}
		
	
	};
};
#endif // RENDERTERRAINTITLE_HEAD_FILE