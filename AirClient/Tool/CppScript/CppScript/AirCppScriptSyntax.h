#ifndef AirCppScriptSyntax_h__
#define AirCppScriptSyntax_h__

#include "AirCppScriptDefineType.h"

namespace	Air{
	namespace	CppScript{
		enum enumNodeType{
			enNT_Unknown,
			enNT_Global,
			enNT_NameSpace,
			enNT_ImportFunction,
			enNT_Variable,
			enNT_Constant,
			enNT_Function,
			enNT_Object,
			enNT_Parameter,
			enNT_Statement,
			enNT_VariableStatement,
			enNT_IfStatement,
			enNT_ForStatement,
			enNT_WhileStatement,
			enNT_SwitchStatement,
			enNT_Expression,
			enNT_FunctionCall_Expression,
			enNT_New_Object_Expression,
			enNT_Delete_Object_Expression,
			enNT_Return_Object_Expression,
			enNT_Break_Object_Expression,
			enNT_Continue_Object_Expression,
			enNT_Block,

		};
		enum	enumSyntaxError{
			enSE_OK,
			enSE_UnexpectedEnd,
			enSE_PreDeclare_Must_Fallow_A_CppKeyword,
			enSE_PreDeclare_Fallow_Unknown,
			enSE_Include_Must_Fallow_A_String,
			enSE_Define_Cant_Fallow_A_Number,
			enSE_Define_Cant_Fallow_A_String,
			enSE_Define_Cant_Fallow_A_CppKeyword,
			enSE_Define_Cant_Fallow_A_Operator,
			enSE_Define_Cant_Fallow_A_Delimiter,
			enSE_Unrecognized_Operator,
			enSE_Unrecognized_Delimiter,
			enSE_NameSpace_Cant_Fallow_A_Number,
			enSE_NameSpace_Cant_Fallow_A_String,
			enSE_NameSpace_Cant_Fallow_A_CppKeyword,
			enSE_NameSpace_Cant_Fallow_A_Operator,
			enSE_NameSpace_Cant_Fallow_A_Delimiter,
			enSE_Unsigned_Not_Match_Void,
			enSE_Unsigned_Not_Match_Bool,
			enSE_Unsigned_Not_Match_Float,
			enSE_Unsigned_Not_Match_Double,
			enSE_Unrecognized_Variable_Type,
			enSE_Miss_Variable_Name,
			enSE_Variable_Name_Cant_Be_A_Number,
			enSE_Variable_Name_Cant_Be_A_CppKeyword,
			enSE_Variable_Name_Cant_Be_A_String,
			enSE_Illegal_Variable_Name,
			enSE_Variable_Name_Already_Declaration,
			enSE_Unsigned_Object_Cant_Be_A_Negative_Value,
			enSE_Bool_Object_Cant_Be_A_Negative_Value,
			enSE_Void_Cant_Be_Unsigned,
			enSE_Bool_Cant_Be_Unsigned,
			enSE_Float_Cant_Be_Unsigned,
			enSE_Variable_Miss_Delimiter_End_Of_Statement,
			enSE_Unrecognized_Variable_Init_Value,
			enSE_Unrecognized_Variable,
			enSE_Int_Variable_Need_A_Int_Init_Value,
			enSE_Float_Variable_Need_A_Float_Init_Value,
			enSE_CharPtr_Variable_Need_A_String_Init_Value,
			enSE_Function_Declare_Must_Fallow_Parameter,
			enSE_Unrecognized_Parameter,
			enSE_Function_Parameter_Name_Already_Exist,
			enSE_Illegal_Class_Or_Struct_Name,
			enSE_Class_Or_Struct_Name_Already_Exist,
			enSE_Unrecognized_Inherit_Type,
			enSE_Unrecognized_Inherit_Object,
			enSE_Unrecognized_Class_Or_Struct_Word,
			enSE_Public_Private_Protected_Must_Fallow_Colon,
			enSE_Variable_Array_Count_Must_Be_Int_Number,
			enSE_Variable_Array_Count_Must_Greater_Than_Zero,
			enSE_Miss_End_Of_SquareBracket,
			

			enSE_Unknown_Error	=	0xffffffff
		};

		template<typename T>
		void	DeleteAllElement(T& t){
			T::iterator i = t.begin();
			for(;i!=t.end();i++){
				delete *i;
				*i=NULL;
			}
			t.clear();
		}

		void	Print(const char* str);
		class	Node;
		typedef std::list<Node*>	NodeList;
		class	Node{
		public:
			Node();
			virtual	~Node();

			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParsePreDeclare(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseInclude(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		AddInclude(CAString& strName);
			virtual	enumSyntaxError		ParseDefine(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		AddDefine(CAString& strName);
			virtual	enumSyntaxError		ParseCppKeyword(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				IsVariableDeclare(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				IsFunctionDeclare(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				IsFunction(WordInfoVector& vecInfo,U32& idx);
			enumSyntaxError				ParseObjectType(WordInfoVector& vecInfo,U32& idx,ObjectType& t,Node** pObjectNode	=	NULL);
			enumSyntaxError				ParseVariableName(WordInfoVector& vecInfo,U32& idx,AString& strName,U1 bCheckExist	=	true);


			enumSyntaxError				FindBlock(WordInfoVector& vecInfo,U32& idx,WordInfoVector& outInfo,U32 uiKeyBegin,U32 uiKeyEnd);
			enumSyntaxError				FindStatementEnd(WordInfoVector& vecInfo,U32& idx,WordInfoVector& outInfo);
			enumSyntaxError				ParseExpression(WordInfoVector& vecInfo,U32& idx);

			enumNodeType	GetType()const{return m_Type;};
			CAString&		GetName()const{return m_strName;};
			void			SetType(enumNodeType t){m_Type=t;};
			void			SetName(CAString& str){m_strName=str;};
			Node*			GetParent(){return m_pParent;};
			void			SetParent(Node* p){m_pParent=p;};
			U32				GetChildCount(){return m_lstChild.size();};
			void			AddChild(Node* p);
			void			RemoveChild(Node* p);
			Node*			GetRootNode();
			Node*			FindNode(CAString& strName,enumNodeType type = enNT_Unknown,U1 bFindParent = true);
		protected:
			enumNodeType	m_Type;
			AString			m_strName;
			NodeList		m_lstChild;
			Node*			m_pParent;
		};

		

		class	NameSpaceNode	:	public	Node{
		public:
			NameSpaceNode(){
				m_Type			=	enNT_NameSpace;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
		};
		class	VariableNode	:	public	Node{
		public:
			VariableNode(){
				m_bHasInitValue	=	0;
				m_bSub			=	0;
				m_Type			=	enNT_Variable;
				pNodePtr		=	NULL;
				uiArrayCount	=	NULL;
				bHasDefault		=	0;
				m_pRightExpression	=	NULL;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			ObjectType					VariableType;
			AString						strDefault;
			U32							bHasDefault;
			U32							uiArrayCount;
			Node*						pNodePtr;
			AString						m_strInitValue;
			U32							m_bHasInitValue;
			U32							m_bSub;
			WordInfo					m_InitInfo;
			Node*						m_pRightExpression;
		};
		class	ConstantNode	:	public	Node{
		public:
			ConstantNode(){
				m_Type			=	enNT_Constant;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			WordInfo ConstInfo;
		};
		class	ExpressionNode	:	public	Node{
		public:
			ExpressionNode(){
				m_Type		=	enNT_Expression;
				pLeftNode	=	NULL;
				pRightNode	=	NULL;
				eOperator	=	enCKWT_Unknown;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*				pLeftNode;
			Node*				pRightNode;
			enumCppKeyWordType	eOperator;
		};
		class	FunctionCallExpressionNode	:	public	Node{
		public:
			FunctionCallExpressionNode(){
				m_Type		=	enNT_FunctionCall_Expression;
				pFunction	=	NULL;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			Node*							pFunction;
			std::vector<Node*>				pParameterArray;
		};
		class	NewObjectExpressionNode	:	public	Node{
		public:
			NewObjectExpressionNode(){
				m_Type		=	enNT_New_Object_Expression;
				pObject		=	NULL;
				uiNewCount	=	1;
			};
			Node*							pObject;
			std::vector<Node*>				pParameterArray;
			U32								uiNewCount;
		};
		class	DeleteObjectExpressionNode	:	public	Node{
		public:
			DeleteObjectExpressionNode(){
				m_Type		=	enNT_Delete_Object_Expression;
				pObject		=	NULL;
			};
			Node*							pObject;
		};
		class	ReturnExpressionNode	:	public	Node{
		public:
			ReturnExpressionNode(){
				m_Type		=	enNT_Return_Object_Expression;
				pReturn		=	NULL;
			};
			Node*							pReturn;
		};
		class	StatementNode	:	public	Node{
		public:
			StatementNode(){
				m_Type			=	enNT_Statement;
			};
			
		};
		class	VariableStatementNode	:	public	VariableNode{
		public:
			VariableStatementNode(){
				m_Type			=	enNT_Statement;
			};

		};
		class	IfStatementNode	:	public	StatementNode
		{
		public:
			IfStatementNode(){
				m_Type			=	enNT_IfStatement;
			};
		};
		class	ForStatementNode	:	public	StatementNode
		{
		public:
			ForStatementNode(){
				m_Type			=	enNT_ForStatement;
			};
		};
		class	WhileStatementNode	:	public	StatementNode
		{
		public:
			WhileStatementNode(){
				m_Type			=	enNT_WhileStatement;
			};
		};
		class	ParameterNode	:	public	VariableNode{
		public:
			ParameterNode(){
				m_Type	=	enNT_Parameter;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
		};
		typedef std::vector<ParameterNode*>	ParameterVector;

		class	FunctionNode	:	public	Node{
		public:
			FunctionNode(){
				m_Type			=	enNT_Function;
				m_bOnlyDeclare	=	true;
				m_bVirtual		=	0;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseParameter(WordInfoVector& vecInfo,U32& idx);
			virtual	enumSyntaxError		ParseFunction(WordInfoVector& vecInfo,U32& idx);
			U1							IsParamNameExist(CAString& strName);
			ParameterNode*				FindParameter(CAString& strName);
			ParameterNode				m_ReturnType;
			ParameterVector				m_vecParameter;
			U32							m_bOnlyDeclare;
			U32							m_bVirtual;
		};
		class	ImportFunctionNode	:	public	FunctionNode{
		public:
			ImportFunctionNode(){
				m_Type	=	enNT_ImportFunction;
				ieType	=	enCKWT_Unknown;;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			enumCppKeyWordType			ieType;
		};
		class	ObjectNode		:	public	Node{
		public:
			ObjectNode(){
				m_uiObjSize		=	4;
				m_bInherit		=	false;
				m_bVirtualTable	=	false;
				m_bDeclare		=	false;
				m_Type			=	enNT_Object;
				m_InheritType	=	enCKWT_Public;
				m_pInherit		=	NULL;
			};
			virtual	enumSyntaxError		Parse(WordInfoVector& vecInfo,U32& idx);
			U32							GetObjectSize();
			U32					m_uiObjSize;
			U1					m_bInherit;
			U1					m_bVirtualTable;
			U1					m_bDeclare;
			enumCppKeyWordType	m_InheritType;
			ObjectNode*			m_pInherit;
			
		};
	}
}
#endif // AirCppScriptSyntax_h__
