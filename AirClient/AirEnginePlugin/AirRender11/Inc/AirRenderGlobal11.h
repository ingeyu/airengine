#ifndef RENDERGLOBAL_HEAD_FILE
#define RENDERGLOBAL_HEAD_FILE


#include "AirRenderHeader11.h"

#include "AirCommonLog.h"
namespace Air{
	
	
	namespace Client{
	
	
	
		namespace	Render{
			class	System;
			class	Device11;
	
	
	
			class Global{
			public:
				Global();
				virtual	~Global();
	
	
				
				GlobalSetting*				pGlobalSetting;
				DxDevice*					m_pDevice;
				Device11*					m_pRenderDevice;
	
				U1							m_bReseting;
				
				
			protected:
			private:
			};
			Global&	GetGlobal();
		}
	
	};
};
#endif // RENDERGLOBAL_HEAD_FILE