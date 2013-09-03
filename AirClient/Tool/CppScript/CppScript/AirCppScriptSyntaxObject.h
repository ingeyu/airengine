#ifndef AirCppScriptSyntaxObject_h__
#define AirCppScriptSyntaxObject_h__

#include "AirCppScriptSyntaxNode.h"

namespace	Air{
	namespace	CppScript{		
		class	FunctionNode;
		class	ObjectNode		:	public	Node{
		public:
			ObjectNode(){
				m_uiObjSize		=	0;
				m_bInherit		=	false;
				m_bVirtualTable	=	false;
				m_bDeclare		=	false;
				m_Type			=	enNT_Object;
				m_InheritType	=	enCKWT_Public;
				m_pInherit		=	NULL;
				m_uiVirtualCount=	0;
				m_uiMemberOffset=	0;
				m_uiVFTOffset	=	0;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			U32							GetObjectSize();
			U32							GetVirtualFunctionCount();
			void						AddVirtualFunction(FunctionNode* p);
			virtual	enumSyntaxError		GenerateCode(Assemble& asmGen);
			void						AllocVFT(Assemble& asmGen);

			virtual	Node*	FindNode(CAString& strName,enumNodeType type = enNT_Unknown,U1 bFindParent = true);
			virtual	Node*	FindNodeDown(CAString& strName,enumNodeType type = enNT_Unknown,U1 bFindChild = true);
			U32*			GetVFTPtr(Assemble& asmGen);
			U32				GetVFTOffset();
			ObjectNode*		GetInherit(){return m_pInherit;};
		protected:
			U32								m_uiObjSize;
			U1								m_bInherit;
			U1								m_bVirtualTable;
			U1								m_bDeclare;
			enumCppKeyWordType				m_InheritType;
			ObjectNode*						m_pInherit;
			std::vector<FunctionNode*>		m_vecVirtualFunction;
			U32								m_uiVirtualCount;
			U32								m_uiMemberOffset;
			std::vector<U32>				m_vecVFT;
			U32								m_uiVFTOffset;
		};
	}
}
#endif // AirCppScriptSyntaxObject_h__
