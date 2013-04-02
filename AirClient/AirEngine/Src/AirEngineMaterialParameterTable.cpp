#include "AirEngineMaterialParameterTable.h"

namespace	Air{
	namespace	Engine{


		MaterialParameterTable::MaterialParameterTable( CAString& strName ):IProduct(strName)
		{

		}

		Air::U1 MaterialParameterTable::Create()
		{


			return	true;
		}

		Air::U1 MaterialParameterTable::Destroy()
		{

			return	true;
		}

		Air::U32 MaterialParameterTable::GetParameterCount()
		{
			return	m_Info.vecParameter.size();
		}

		MaterialParameter* MaterialParameterTable::GetParameter( CAString& strName )
		{
			return	NULL;
		}

		void MaterialParameterTable::SetParameterValue( CAString& strName,Real val )
		{

		}

		void MaterialParameterTable::SetParameterValue( CAString& strName,const Float2& val )
		{

		}

		void MaterialParameterTable::SetParameterValue( CAString& strName,const Float3& val )
		{

		}

		void MaterialParameterTable::SetParameterValue( CAString& strName,const Float4& val )
		{

		}

		void MaterialParameterTable::SetParameterValue( CAString& strName,const Matrix& val )
		{

		}

		void MaterialParameterTable::SetParameterValue( CAString& strName,const AString& val )
		{

		}

		void MaterialParameterTable::GetParameterValue( CAString& strName,Real& val )
		{

		}

		void MaterialParameterTable::GetParameterValue( CAString& strName,Float2& val )
		{

		}

		void MaterialParameterTable::GetParameterValue( CAString& strName,Float3& val )
		{

		}

		void MaterialParameterTable::GetParameterValue( CAString& strName,Float4& val )
		{

		}

		void MaterialParameterTable::GetParameterValue( CAString& strName,Matrix& val )
		{

		}

		void MaterialParameterTable::GetParameterValue( CAString& strName,AString& val )
		{

		}

	}
}