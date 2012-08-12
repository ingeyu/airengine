#ifndef AirEngineMaterialParameterTable_h__
#define AirEngineMaterialParameterTable_h__

#include "AirEngineMaterialSet.h"

namespace	Air{
	namespace	Client{
		class	MaterialParameterTable	:	public	IProduct{
		public:
			struct	Info{
				MaterialParameterVector	vecParameter;
				StringVector			vecMaterial;
			};
		public:
			MaterialParameterTable(CAString& strName);

			virtual	U1	Create();
			virtual	U1	Destroy();

			U32					GetParameterCount();
			MaterialParameter*	GetParameter(CAString&	strName);
			void				SetParameterValue(CAString& strName,Real			val);
			void				SetParameterValue(CAString& strName,const Float2&	val);
			void				SetParameterValue(CAString& strName,const Float3&	val);
			void				SetParameterValue(CAString& strName,const Float4&	val);
			void				SetParameterValue(CAString& strName,const Matrix&	val);
			void				SetParameterValue(CAString& strName,const AString&	val);

			void				GetParameterValue(CAString& strName,Real&		val);
			void				GetParameterValue(CAString& strName,Float2&		val);
			void				GetParameterValue(CAString& strName,Float3&		val);
			void				GetParameterValue(CAString& strName,Float4&		val);
			void				GetParameterValue(CAString& strName,Matrix&		val);
			void				GetParameterValue(CAString& strName,AString&	val);
			Info		m_Info;
		};
	}
}
#endif // AirEngineMaterialParameterTable_h__