// #ifndef RENDERLINE_HEAD_FILE
// #define RENDERLINE_HEAD_FILE
// 
// #include "AirRenderHeader.h"
// #include "AirRenderFactory.h"
// 
// namespace Client{
// 
// 	namespace	Render{
// 		class	Line	:
// 			public	Product{
// 		public:
// 			struct	SingleLine{
// 				SingleLine(){
// 					vSrc	=	Vector3::ZERO;
// 					vDst	=	Vector3::UNIT_Y;
// 				}
// 				Vector3	vSrc;
// 				Vector3	vDst;
// 			};
// 			typedef	std::vector<SingleLine>	LineArray;
// 			/**	\brief	创建信息
// 			*
// 			*	创建信息
// 			*
// 			***/
// 			struct	Info{
// 				Info(){
// 					uiColor	=	0xFFFF0000;
// 					fWidth	=	2;
// 				}
// 				LineArray	m_LineArray;	///<	直线数组
// 				Real		fWidth;			///<	直线宽度
// 				UInt		uiColor;		///<	直线颜色
// 			};
// 		public:
// 			Line(AString&	strName,Info*	pInfo);
// 
// 			virtual	U1	Create();
// 
// 			virtual	U1	Destroy();
// 
// 			virtual	U1	OnLostDevice();
// 
// 			virtual	U1	OnResetDevice();
// 
// 			virtual	void	Render();
// 
// 			virtual	void	SetColor(Real	r,Real	g,Real	b);
// 			virtual	void	SetWidth(Real	fWidth);
// 			virtual	void	SetLineArray(LineArray&	lArray);
// 
// 
// 			Info		m_Info;
// 			LPD3DXLINE	m_pLine;
// 		};
// 	}
// 
// };
// #endif // RENDERLINE_HEAD_FILE