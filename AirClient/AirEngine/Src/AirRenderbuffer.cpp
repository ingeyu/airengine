#include "AirRenderbuffer.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{


			Buffer::Buffer( CAString& strName,Info* pInfo ):IProduct(strName)
			{
				if(pInfo!=NULL){
					m_Info	=	*pInfo;
				}
			}

			Buffer::~Buffer()
			{

			}

			Air::U1 Buffer::Create()
			{
				if(	m_Info.uiElementCount	==	0	||
					m_Info.uiElementSize	==	0)
				{
					return	false;
				}

				return	true;
			}

			void Buffer::OnLostDevice()
			{
				if(	m_Info.usage	==	enUSAGE_DYNAMIC)
				{
					Destroy();
				}
			}

			void Buffer::OnResetDevice()
			{
				if(	m_Info.usage	==	enUSAGE_DYNAMIC){
					NotifyDirty();
				}
			}

			Air::U1 Buffer::IsDirty()
			{
				return	m_bDirty;
			}

			void Buffer::NotifyDirty()
			{
				m_bDirty	=	true;
			}

			Air::U1 Buffer::Destroy()
			{
				return	true;
			}

			Air::U1 Buffer::UpdateData( void* pData )
			{
				if(pData==NULL)
					return	false;
				SAF_DA(m_Info.InitData);
				m_Info.InitData	=	pData;
				NotifyDirty();
				return	true;
			}

		}
	}
}