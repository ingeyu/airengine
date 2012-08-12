#ifndef AirCommonFlag_h__
#define AirCommonFlag_h__

#include "AirCommonHeader.h"

namespace	Air{
	template<typename	T_Type>
	class	Flag{
	public:
		Flag(){
			m_uiFlag	=	0;
		};
		U1		HasFlag(T_Type	uiFlag){
			return	(m_uiFlag&(1<<uiFlag))>0;
		};

		void	AddFlag(T_Type	uiFlag){
			m_uiFlag	|=	1<<uiFlag;
		};
		void	SetFlag(U32	uiFlag){
			m_uiFlag	=	uiFlag;
		};
		void	RemoveFlag(T_Type	uiFlag){
			m_uiFlag	&=	~(1<<uiFlag);
		};
		void	ClearFlag(){
			m_uiFlag	=	0;
		};
		
		U32		m_uiFlag;
	};
}
#endif // AirCommonFlag_h__
