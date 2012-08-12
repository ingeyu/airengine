//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Union.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/

#ifndef UNION_HEAD_FILE
#define UNION_HEAD_FILE

#include "AirCommonHeader.h"
namespace Air{
	
	namespace Common{
	
		/**	\brief	联合体 
		*
		*	占4字节
		*
		***/
		class Union4{
		public:
			Union4(){};
			Union4(const Union4 &unin){
				*this = unin;
			};
			Union4(U1 bBool){
				m_Bool	= bBool;
			};
			Union4(S8 cChar){
				m_Char	= cChar;
			};
			Union4(S16 sShort){
				m_Short	= sShort;
			};
			Union4(SInt iInt){
				m_Int	= iInt;
			};
			Union4(Real fFloat){
				m_Float	= fFloat;
			};
			Union4(void* pVoid){
				m_pVoid	= pVoid;
			};
			Union4(U8 cUchar){
				m_Uchar	= cUchar;
			};
			Union4(U16 sUshort){
				m_Ushort	= sUshort;
			};
			Union4(UInt iUint){
				m_Uint	= iUint;
			};
			void operator = (U1 bBool){
				m_Bool	= bBool;
			};
			void operator = (S8 cChar){
				m_Char	= cChar;
			};
			void operator = (S16 sShort){
				m_Short	= sShort;
			};
			void operator = (SInt iInt){
				m_Int	= iInt;
			};
			void operator = (float fFloat){
				m_Float	= fFloat;
			};
			void operator = (void* pVoid){
				m_pVoid	= pVoid;
			};
			void operator = (U8 cUchar){
				m_Uchar	= cUchar;
			};
			void operator = (U16 sUshort){
				m_Ushort	= sUshort;
			};
			void operator = (UInt iUint){
				m_Uint	= iUint;
			};
			template<typename T_Handle>
			T_Handle Handle(){
				return (T_Handle)m_pVoid;
			};
			union{
				U1			m_Bool;
				S8			m_Char;
				S16			m_Short;
				SInt		m_Int;
				U8			m_Uchar;
				U16			m_Ushort;
				UInt		m_Uint;
				Real		m_Float;
				void*		m_pVoid;
				char*		m_pChar;
				String*		m_pString;
			};
		};
		/**	\brief	联合体
		*
		*	占8字节
		*
		***/
		class Union8{
		public:
			union{
				bool	m_Bool;
				char	m_Char;
				short	m_Short;
				int		m_Int;
				S64		m_Int64;
				U8		m_Uchar;
				U16		m_Ushort;
				UInt	m_Uint;
				Real	m_Float;
				DReal	m_Double;
				void*	m_pVoid;
				S8*		m_pChar;
			};
		};
	};
};

#endif // UNION_HEAD_FILE