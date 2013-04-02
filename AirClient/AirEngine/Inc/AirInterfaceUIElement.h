#ifndef INTERFACEUIELEMENT_HEAD_FILE
#define INTERFACEUIELEMENT_HEAD_FILE

#include "AirInterfaceUIImage.h"
namespace Air{
	
	
	namespace Engine{
	
		namespace	UI{
			class	IImage;
			/**	\brief	渲染缓冲
			*
			*	渲染缓冲
			*
			***/
			class	Buffer{
			public:
				Float4	m_vPositionSize;		///<	位置和大小
				Float4	m_vUV;					///<	图片位置和大小
				Float4	m_vColor;				///<	设置颜色
				Float4	m_vCustom;				///<	自定义
			};
			/**	\brief	界面元素类
			*
			*	界面元素类
			*
			***/
			class	ENGINE_EXPORT	IElement	:
				public	Buffer{
			public:
				enum	enumType{
					enTexture,		///<	图片
					enCharacter,	///<	文字
					enVideo,		///<	视频
					enMax
				};
	
			public:
				IElement();
				UInt	m_uiMark;				///<	标记	用于更新数据
			};
	
			typedef		std::vector<IElement>	ElementArray;
			typedef		ElementArray::iterator	ElementArrayItr;
	
			typedef		std::vector<ElementArray>	StateArray;
			typedef		StateArray::iterator		StateArrayItr;
		}
	
	};
};
#endif // INTERFACEUIELEMENT_HEAD_FILE