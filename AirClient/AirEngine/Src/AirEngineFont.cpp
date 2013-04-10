#include "AirEngineFont.h"
#include "AirRenderTexture.h"
#include "AirRenderTarget.h"
#include "AirRenderSystem.h"
#include "AirGlobalSetting.h"

#include <ft2build.h>
#include FT_FREETYPE_H


namespace Air{
	
	
	namespace	Engine{
	
		AString	Font::ProductTypeName="Font";
		Font::Font( AString strName,Info* pInfo ):IProduct(strName){
			m_Info			=	*pInfo;
			m_pLibrary		=	NULL;
			m_pFace			=	NULL;
			m_pCharTexture	=	NULL;
			m_vLastPosition	=	Float2(0,0);
		}
	
		U1 Font::Create(){
			//0表示没有错误
			SInt	error	=	0;
			//初始化Freetype
			error	=	FT_Init_FreeType( &m_pLibrary );
			//加载字体
			error	=	FT_New_Face( m_pLibrary,m_strProductName.c_str(),0,&m_pFace );
	
			if(error!=0){
				EngineLogError((AChar*)m_strProductName.c_str(),"Create	Font Failed!");
				return false;
			}
	
			//设置字体大小
			error	=	FT_Set_Char_Size(
				m_pFace,    /* handle to face object           */
				0,       /* char_width in 1/64th of points  */
				16*64,   /* char_height in 1/64th of points */
				300,     /* horizontal device resolution    */
				300 );   /* vertical device resolution      */
			//设置字体像素大小
			error = FT_Set_Pixel_Sizes(
				m_pFace,   /* handle to face object */
				0,      /* pixel_width           */
				24 );   /* pixel_height          */
	
			AString	strFontName;
			GlobalSetting::ParsePath(m_strProductName,NULL,&strFontName,NULL);
	
			Texture::Info	texInfo;
			texInfo.SetManageTexture(m_Info.uiTexSize,m_Info.uiTexSize,enTFMT_R8G8_UNORM);

			
			m_pCharTexture	=	Render::System::GetSingleton()->CreateProduct<Texture>(("..\\Data\\Font.dds"),&texInfo);
	
			if(m_pCharTexture==NULL){
				Destroy();
				return false;
			}
			m_pObject	=	(UInt*)m_pCharTexture;
			return	true;
		}
	
		U1 Font::Destroy(){
			if(m_pCharTexture!=NULL){
				m_pCharTexture->ReleaseRef();
				m_pCharTexture	=	NULL;
			}
			if(m_pFace!=NULL){
				FT_Done_Face(m_pFace);
				m_pFace	=	NULL;
			}
			if(m_pLibrary!=NULL){
				FT_Done_FreeType(m_pLibrary);
				m_pLibrary	=	NULL;
			}
	
			m_pObject	=	NULL;
			return	true;
		}
	
		Float4 Font::AddChar( WChar c ){
			Float4	v	=	Float4(0,0,0,0);
			//判断改字符是否已经生成
			if(GetCharPosSize(c,v))
				return	v;
			else{
				U1	bEnglish	=	false;
				if(c	<=	255){
					bEnglish	=	true;
				}
				//没有则先生成字体图
				U8*	pBuff	=	NULL;
				CreateCharBitmap(c,v,&pBuff);
				//然后再合并到字体纹理中，并返回该字符在图片中位置和大小
				Combine2Texture(pBuff,v.x,v.y,v,bEnglish);
				//存入列表中
				m_mapChar.insert(CharMapPair(c,v));
				return v;
			}
		}
	
		VectorArray Font::AddString( WString s ){
			UInt	uiNumChar	=	s.size();
			VectorArray	vArray;
			vArray.resize(uiNumChar);
	
			for(UInt i=0;i<uiNumChar;i++){
				vArray[i]	=	AddChar(s[i]);
			}
			//test测试代码
			//m_pCharTexture->SaveToFile("..\\Data\\Font");
			return	vArray;
		}
	
		U1 Font::CreateCharBitmap( WChar c,Float4& vPosSize,U8** pBuff ){
			SInt error	=	0;
			FT_GlyphSlot    glyph	=	NULL;
	
			FT_Load_Glyph(m_pFace, FT_Get_Char_Index(m_pFace,  c ), FT_LOAD_DEFAULT);
			error  =  FT_Render_Glyph(m_pFace->glyph,  FT_RENDER_MODE_NORMAL);
			if ( ! error)
			{
				//  convert glyph to bitmap with 256 gray 
				glyph		=	m_pFace->glyph;//->
				FT_Bitmap&     bitmap  =  glyph->bitmap;
				*pBuff		=	bitmap.buffer;
				vPosSize.x	=	bitmap.width;
				vPosSize.y	=	bitmap.rows;
	
			}
			return true;
		}
	
		U1 Font::GetCharPosSize( WChar c,Float4& vPosSize ){
			CharMapItr	i	=	m_mapChar.find(c);
			if(i!=m_mapChar.end()){
				vPosSize	=	i->second;
				return true;
			}
			return	false;
		}
	
		U1 Font::Combine2Texture( U8* pBuff,SInt w,SInt h,Float4& vPosSize,U1	bEng ){
			if(m_pCharTexture==NULL)
				return	false;
			//Render::ITexture*		pTexture	=	m_pCharTexture->GetTexture();
			const Texture::Info&	texInfo		=	m_pCharTexture->GetInfo();
	
			//SInt	halfWidth	=	w/2;
			//SInt	halfHeight	=	h/2;
			
	
			if(m_vLastPosition.x	+	m_uiCharSize	>	texInfo.width){
				m_vLastPosition.x	=	0;
				m_vLastPosition.y	+=	m_uiCharSize;
			}
	
			if(m_vLastPosition.y	>	texInfo.height){
				EngineLogError((AChar*)(m_strProductName.c_str()),"字体数量超过纹理大小");
				return	false;
			}
			//英文字符宽度减少 测试之后中文字符的0.5比较合适
			if(bEng){
				vPosSize.x	=	(Real)(m_Info.uiSize)/(Real)m_Info.uiTexSize*0.6f;
			}else{
				vPosSize.x	=	(Real)(m_Info.uiSize)/(Real)m_Info.uiTexSize;
			}
			
			vPosSize.y	=	(Real)(m_Info.uiSize-2)/(Real)m_Info.uiTexSize;
			vPosSize.z	=	(Real)(m_vLastPosition.x)/(Real)m_Info.uiTexSize;
			vPosSize.w	=	(Real)(m_vLastPosition.y)/(Real)m_Info.uiTexSize;
	
	// 		AChar	str[128];15927748449
	// 		sprintf_s(str,128,"%f,%f\n",m_vLastPosition.x,m_vLastPosition.y);
	// 		::OutputDebugStringA(str);
	
	
			
			SInt	jDst	=	0;
			if(bEng){
				//英文要以底边对齐
				jDst	=	m_vLastPosition.y	+ (m_uiCharSize-h-2);
			}else{
				//中文要居中对齐
				jDst	=	m_vLastPosition.y;
			}
			
			SInt	jSrc	=	0;
	
// 			Render::ITexture::LockRectOption	option;
// 			m_pCharTexture->Lock(&option,LOCK_NO_DIRTY_UPDATE);
// 			U8*	p	=	(U8*)option.pData;
// 	
// 			for(;jSrc<h;jSrc++,jDst++){
// 				SInt	iSrc	=	0;
// 				SInt	iDst	=	m_vLastPosition.x;
// 				for(;iSrc<w;iSrc++,iDst++){
// 					p[jDst*texInfo.width+iDst]	=	pBuff[jSrc*w+iSrc];
// 				}
// 			}
// 			m_pCharTexture->UnLock();
	
			m_vLastPosition.x	+=	m_uiCharSize;
	
			return true;
		}
	
		Texture* Font::GetTexture(){
			return	m_pCharTexture;
		}
		UInt	Font::m_uiCharSize	=	25;
	
	}
};