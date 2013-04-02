#include "AirRenderVertexDeclare.h"

namespace	Air{
	namespace	Engine{
		namespace	Render{

			void* Vertex::IDeclare::GetDeclare(){
				return	NULL;
			}

			Air::U1 Vertex::IDeclare::Create(){
				if(m_Info.m_vectorElement.empty()){
					return	false;
				}
				return true;
			}

			Air::U1 Vertex::IDeclare::Destroy(){
				return	true;
			}
		}
	}
}