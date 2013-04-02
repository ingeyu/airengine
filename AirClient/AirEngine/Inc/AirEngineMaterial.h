#ifndef RENDERMATERIAL_HEAD_FILE
#define RENDERMATERIAL_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
#include "AirCommonFile.h"
#include "AirCommonIniFile.h"
#include "AirEngineMaterialCommon.h"

namespace Air{
	
	
	namespace Engine{

		struct	Param{
			Param(){
				type	=	0;
			}
			UInt	type;
			Float4	fv4;
		};

		struct	RenderObject{
			RenderObject(){
				pObj	=	NULL;
			};
			Renderable*	pObj;
			Float44		World;
		};
		typedef	std::vector<Renderable*>			RenderObjectVector;
		typedef	std::vector<Render::Texture*>		TextureVector;
	
		//namespace	Render{
		/**	\brief	材质
		*
		*	材质
		*
		***/
		class	ENGINE_EXPORT	Material	:
			public	IProduct
		{
		public:
			struct	Info{
				Info(){
					bUseSkin		=	false;
					uiPriority		=	4;	
				}
				AString			strTemplate;
				VectorArray		vecFloatParam;
				StringVector	vecTextureName;
				U1				bUseSkin;
				U32				uiPriority;	///<	0~7优先级
			};
		public:
			Material(CAString&	strName,Info*	pInfo);

			virtual	U1	Create();
			virtual	U1	Destroy();

			enumPhaseIndex						GetPhaseIndex()const;
			void								AddRenderObject(Renderable*	pObj);
			void								ClearRenderObjects();
			U1									HasRenderables();
			void								RenderAllObjects();
			void								RenderOneObject(Renderable*	pObj);

			void								SetTexture(U32	uiIndex,Texture*	pTexture);
			void								SetTextureName(U32 uiIndex,CAString&	strTextureName);

			void								UpdataAutoParam();

			inline	TextureVector&				GetTextureArray(){
				return	m_vecTexture;
			}
			inline	MaterialTemplate*			GetTemplate(){
				return	m_pTemplate;
			};
			inline	Buffer*				GetConstantBuffer(){
				return	m_pConstantBuffer;
			};
			inline	U64							GetHash(){
				return	m_Hash;
			};
		protected:
			Buffer*						m_pConstantBuffer;
			MaterialTemplate*			m_pTemplate;
			RenderObjectVector			m_vecRenderObjects;
			TextureVector				m_vecTexture;
			Info						m_Info;
			CriticalSection				m_ObjectCS;
			U64							m_Hash;
		};

		typedef	std::map<U32,Material*>	MaterialMap;
	};
};
#endif // RENDERMATERIAL_HEAD_FILE