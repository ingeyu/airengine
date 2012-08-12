#ifndef AirCommonProperty_h__
#define AirCommonProperty_h__

#include "AirCommonHeader.h"
#include "AirCommonFunction.h"

namespace	Air{
	namespace	Common{
		typedef	void	UnKnownType;

		//typedef	IFunction<void

		class	IProperty{
		public:
			virtual	~IProperty(){};
			inline	const	AString&	GetName()const{
				return	m_strName;
			};
			inline	void				SetName(CAString&	strName){
			};
			virtual	AString				GetTypeName()const						=	NULL;
			virtual	void				GetValue(UnKnownType**	pOutValue)const	=	NULL;
			virtual	void				SetValue(UnKnownType*	pInValue)		=	NULL;
			template<typename T_Object>
			virtual	void				SetCallBack(void*	pCallBack,T_Object*	pObj)	=	NULL;
		protected:
			AString	m_strName;
		};

		template<typename	T_Type>
		class	IPropertyT	:	public	IProperty
		{
		public:
			virtual	~IProperty(){
				m_pCallBack.Clean();
			};

			virtual	AString				GetTypeName()const{
				return	typeid(T_Type).name();
			};
			virtual	void				GetValue(UnKnownType**	pOutValue)const{
				GetValue(**(T_Type**)pOutValue);
			};
			virtual	void				SetValue(UnKnownType*	pInValue){
				SetValue(*(T_Type*)pInValue)
			};
			virtual	void				GetValue(T_Type&		pOutValue)const{
				pOutValue	=	GetValue();
			};
			template<typename T_Object>
			virtual	void				SetCallBack(void*	pCallBack,T_Object*	pObj){
				if(pCallBack!=NULL&&pObj!=NULL){
					MemberFunction<T_Object,T_Type>::MemberCallBack	pCB	=	(MemberFunction<T_Object,T_Type>::MemberCallBack)pCallBack;
					m_pCallBack	=	FunctionSlot(pCB,pObj);
				}
			};

			virtual	const	T_Type&		GetValue()const							=	NULL;
			virtual	void				SetValue(const	T_Type&	pInValue)		=	NULL;

			FunctionSlot	m_pCallBack;
		};

		template<typename	T_Type>
		class	PropertyT	:	public	IPropertyT<T_Type>
		{
		public:
			
			virtual	const	T_Type&		GetValue()const{
				return	m_Value;
			};
			virtual	void				SetValue(const	T_Type&	pInValue){
				m_Value	=	pInValue;
			};
		protected:
			T_Type		m_Value;
		};

		template<typename	T_Type>
		class	PropertyT_Construct	:	public	PropertyT<T_Type>{
		public:
			PropertyT_Construct():m_Value(0){};
			PropertyT_Construct(CAString&	strName):m_strName(strName),m_Value(0){};
			PropertyT_Construct(CAString&	strName,const T_Type&	val):m_strName(strName),m_Value(val){};
		};

		template<typename	T_Type>
		class	PropertyT_NoConstruct	:	public	PropertyT<T_Type>{
		public:
			PropertyT_Construct(){};
			PropertyT_Construct(CAString&	strName):m_strName(strName){};
			PropertyT_Construct(CAString&	strName,const T_Type&	val):m_strName(strName),m_Value(val){};
		};

		typedef	std::map<AString,IProperty*>	PropertyMap;
		typedef	PropertyMap::iterator			PropertyMapItr;
		typedef	PropertyMap::const_iterator		PropertyMapCItr;

		class	PropertyManager{
		public:
			PropertyManager();

			U32		GetPropertyCount()const{
				return	m_mapProperty.size();
			};
			const	PropertyMap&	GetPropertyList()const{
				return	m_mapProperty;
			};
			IProperty*				GetProperty(CAString&	strName)const{
				PropertyMapCItr	i	=	m_mapProperty.find(strName);
				if(i!=m_mapProperty.end())
					return	i->second;
				return	NULL;
			};
			AString					GetPropertyTypeName(CAString&	strName)const{
				PropertyMapCItr	i	=	m_mapProperty.find(strName);
				if(i!=m_mapProperty.end()){
					IProperty*	p	=	i->second;
					if(p!=NULL){
						return	p->GetTypeName();
					}
				}
				return	"";
			}

			void	AddProperty(IProperty*	pProperty);
			void	AddProperty(CAString&	strName,IProperty*	pProperty);
			void	RemoveProperty(CAString&	strName);



		protected:
			PropertyMap	m_mapProperty;
		};
	}
}
#endif // AirCommonProperty_h__
