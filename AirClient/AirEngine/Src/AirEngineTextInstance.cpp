#include "AirEngineTextInstance.h"
#include "AirRenderSystem.h"
#include "AirEngineSystem.h"
#include "AirGlobalSetting.h"
#include "AirCommonConverter.h"
#include "AirEngineFont.h"
namespace Air{
	
	namespace	Client{
		//struct	
	
	
		TextInstance::TextInstance( CAString& strName ,Info*	pInfo):InstanceEntity(strName,pInfo->uiMaxInstance){
			m_pFont	=	NULL;
			m_strMaterialName	=	pInfo->strMaterialName;
			m_uiTextSize		=	pInfo->uiSize;
			m_Rect[0]			=	0;
			m_Rect[1]			=	0;
			m_Rect[2]			=	300;
			m_Rect[3]			=	300;
		}
	
		U1 TextInstance::CreateModelVertexBuff(){
// 			VertexBuff::Info vInfo(12,4);
// 			m_pModelVertexBuff	=	Render::System::GetSingleton()->Create<VertexBuff*>("TextVertexBuff","VertexBuff",&vInfo);
// 			if(m_pModelVertexBuff	==	NULL)
// 				return false;
	
// 	 		Float3*	p	=	NULL;
// 	 		m_pModelVertexBuff->Lock(LockOption(0,0,(void**)&p));
// 	 		p[0]	=	Float3(-1.0f,	1.0f,	1.0f);
// 	 		p[1]	=	Float3(1.0f,	1.0f,	1.0f);
// 	 		p[2]	=	Float3(-1.0f,	-1.0f,	1.0f);
// 	 		p[3]	=	Float3(1.0f,	-1.0f,	1.0f);
// 	 		m_pModelVertexBuff->Unlock();
	
			//设置顶点数
// 			m_DrawBuff.m_DrawOption.m_uiVertexCount		=	4;
// 			//设置面数
// 			m_DrawBuff.m_DrawOption.m_uiFaceCount		=	2;
	
			return true;
		}
	
		U1 TextInstance::CreateInstanceVertexBuff(){
// 			VertexBuff::Info vInfo(sizeof(Render::Vertex::IBuff::InstanceData),1024);
// 			m_pInstanceVertexBuff	=	Render::System::GetSingleton()->Create<VertexBuff*>("TextInstance","VertexBuff",&vInfo);
// 			if(m_pInstanceVertexBuff	==	NULL)
// 				return false;
	// 		Float4		vDefault(0,0,0,0);
	// 		Float4*	v	=	NULL;
	// 		m_pInstanceVertexBuff->Lock(LockOption(0,0,(void**)v));
	// 		memset()
	// 		m_pInstanceVertexBuff->Unlock();
	
			//创建字体
			Font::Info	info;
			m_pFont	=	EngineSystem::GetSingleton()->CreateProduct<Font*>(AString("..\\Data\\STLITI.ttf"),AString("Font"),&info);
			
			return true;
		}
	
		U1 TextInstance::CreateDeclare(){
	
// 			VertexDeclare::Info info(0);
// 			info.SetP_Instance();
// 			VertexDeclare*	pDeclare	=	Render::System::GetSingleton()->Create<VertexDeclare*>(AString("TextInstance"),AString("VertexDeclare"),&info);
// 			if(pDeclare	==	NULL)
// 				return false;
// 			m_DrawBuff.m_pVertexDeclare	=	pDeclare;
			return true;
		}
	
		U1 TextInstance::CreateIndex(){
			//创建索引缓冲
			IndexBuffer::Info	IndexBuffInfo;
			IndexBuffInfo.SetIndexBuffer16(6);
			IndexBuffer*	pIndexBuff	=	Render::System::GetSingleton()->CreateProduct<IndexBuffer*>(AString("ScreenIndexBuff"),AString("IndexBuff"),&IndexBuffInfo);
			if(pIndexBuff==NULL){
				Render::System::GetSingleton()->DestroyProduct(pIndexBuff);
				return false;
			}
			//填充索引
			DWORD*	pIndex	=	NULL;
// 			pIndexBuff->Lock(LockOption(0,0,(void**)&pIndex));
// 			pIndex[0]	=	0;
// 			pIndex[1]	=	1;
// 			pIndex[2]	=	2;
// 			pIndex[3]	=	2;
// 			pIndex[4]	=	1;
// 			pIndex[5]	=	3;
// 	
// 			pIndexBuff->Unlock();
	
			//m_DrawBuff.m_pIndexBuff	=	pIndexBuff;
			return true;
		}
	
		void TextInstance::SetText( AString strText ){
			//将ACSII码转换为UNICODE
			m_strText	=	Common::Converter::Acsi2WideByte(strText);
			if(m_pInstanceVertexBuff==NULL)
				return;
	
			//文字数量
			UInt	uiCharSize	=	m_strText.size();
	
			static	Real&	ScreenWidth	=	GetGlobalSetting().m_ShaderParam.m_iScreenWidth;
			SInt	iNumCharPerLine		=	(SInt)m_Rect[2]/(SInt)m_uiTextSize;
			//获取字符串在纹理中的UV
			VectorArray	vArray	=	m_pFont->AddString(m_strText);
			//实体数据
//			VertexBuffer::InstanceData*	v	=	NULL;
			//当前行
			UInt	iLine	=	0;
			//当前横向偏移
			UInt	iX		=	0;
			//当前文字的大小
			UInt	iCharSize		=	m_uiTextSize;
			//上一个字符大小
			UInt	iLastCharSize	=	0;
			//需要渲染的文字数量
			UInt	iNumNeedRenderChar	=	0;
	
// 			m_pInstanceVertexBuff->Lock(LockOption(0,0,(void**)&v));
// 			for(UInt i=0;i<uiCharSize;i++){
// 				WChar	c	=	m_strText[i];
// 				//判断是否是英文字符 数字或者字符	则宽度为中文字符的一半
// 				if(c	<=	255){
// 					iCharSize	=	m_uiTextSize/2;
// 				}else{
// 					iCharSize	=	m_uiTextSize;
// 				}
// 	
// 				//判断是否为换行符	或者字符超过文字显示框的边界   则需要换行
// 				if(c	==	L'\n'	||	(iX	+	iLastCharSize/2 +	iCharSize)	>	m_Rect[2]){
// 					iLine++;
// 					iLastCharSize	=	0;
// 					iX				=	0;
// 					//如果是换行符  不需要渲染
// 					if(c	==	L'\n'){
// 						continue;
// 					}
// 				}
// 	
// 				//计算横向的便宜量
// 				iX	+=	(iLastCharSize	+	iCharSize)/2;
// 				iLastCharSize	=	iCharSize;
// 	
// 				Real	x		=	m_Rect[0]	+	iX;
// 				Real	y		=	m_Rect[1]	+	m_uiTextSize/2	+	m_uiTextSize*iLine;
// 	
// 				//判断文字是否超过底边  如果超过 则直接不渲染后面的文字
// 				if(y	>	m_Rect[3]){
// 					break;
// 				}
// 	
// 				//写入信息
// 				v[iNumNeedRenderChar].Position	=	Float4(iCharSize,m_uiTextSize,x,y);
// 				v[iNumNeedRenderChar].Color		=	vArray[i];
// 	
// 				//增加一个需要显示的文字
// 				iNumNeedRenderChar++;
// 				//调试信息
// 	// 			AChar str[128];
// 	// 			AString	 strPos	=	Converter::toString(v[i].Position);
// 	// 			AString	 strUV	=	Converter::toString(v[i].Color);
// 	// 			sprintf_s(str,128,"位置=%s UV=%s\n",strPos.c_str(),strUV.c_str());
// 	// 			OutputDebugStringA(str);
// 			}
// 			m_pInstanceVertexBuff->Unlock();
	
			SetInstanceCount(iNumNeedRenderChar);
		}
	
		AString TextInstance::GetText(){
			return	Common::Converter::WideByte2Acsi(m_strText);
		}
	
		void TextInstance::SetTextSize(UInt	uiSize){
			m_uiTextSize	=	uiSize;
			if(!m_strText.empty()){
				SetText(GetText());
			}
		}
	
		void TextInstance::SetTextRect( RECT rect ){
			m_Rect[0]	=	rect.left;
			m_Rect[1]	=	rect.top;
			m_Rect[2]	=	rect.right	-	rect.left;
			m_Rect[3]	=	rect.bottom	-	rect.top;
	
		}
	
		RECT TextInstance::GetTextRect(){
			RECT	rect;
			rect.left	=	m_Rect[0];
			rect.top	=	m_Rect[1];
			rect.right	=	m_Rect[0]	+	m_Rect[2];
			rect.bottom	=	m_Rect[1]	+	m_Rect[3];
			return	rect;
		}
		TextInstanceFactory::TextInstanceFactory(){
			m_strTypeName	=	"TextInstance";
		}
	
		IProduct* TextInstanceFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
			if(lstParam	==	NULL)
				return	false;
			TextInstance::Info*	pInfo	=	(TextInstance::Info*)lstParam;
			TextInstance*		pBuff	=	new	TextInstance(strName,pInfo);
	
			return	pBuff;
		}
	}
};