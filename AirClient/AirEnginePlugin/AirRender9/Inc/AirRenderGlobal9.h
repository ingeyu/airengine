#ifndef RENDERGLOBAL_HEAD_FILE
#define RENDERGLOBAL_HEAD_FILE


#include "AirRenderHeader9.h"

#include "AirCommonLog.h"
namespace Air{
	
	
	namespace Client{
	
	
	
		namespace	Render{
			class	System;
			class	Device9;
	
	
	
			class Global{
			public:
				Global();
				virtual	~Global();
	
	
				
				GlobalSetting*				pGlobalSetting;
				DxLight						m_Sun;
				DxLight						m_Light[8];
				DxDevice*					m_pDevice;
				Device9*						m_pRenderDevice;
	
				U1							m_bReseting;
				
				
			protected:
			private:
			};
			Global&	GetGlobal();
		}
	
	};
};
#endif // RENDERGLOBAL_HEAD_FILE