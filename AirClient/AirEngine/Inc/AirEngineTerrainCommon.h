#ifndef ENGINETERRAINCOMMON_HEAD_FILE
#define ENGINETERRAINCOMMON_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
#include "AirEngineRenderable.h"
#include "AirEngineMaterial.h"
#include "AirRenderBuffer.h"

#include "AirGlobalSetting.h"
#include "AirCommonProduct.h"
#include "AirCommonFactory.h"
namespace Air{
	
	namespace Engine{
		
			namespace	Terrain{
	#ifndef DIRECTION_ID
	#define DIRECTION_ID
	
	#define WEST	-1
	#define	EAST	1
	#define NORTH	-1
	#define SOUTH	1
	
	#endif
				/**	\brief	索引
				*
				*	索引
				*
				***/
				struct ID{
					ID(UInt w	=	0,UInt h	=	0){
						width	=	w;
						height	=	h;
					};
					ID(UInt uiIndex){
						index	=	uiIndex;
					};
	
					/**	\brief	获取邻居的索引
					*   
					*	@remarks 	获取旁边8个地形块的索引 （参数 请查看DIRECTION_ID）
					*	@see		DIRECTION_ID
					*	@return   	Client::Render::Terrain::ID
					*	@param		U16 usEastOrWest
					*	@param		U16 usNorthOrSouth
					*	@note
					*
					**/
					ID	GetNeighborID(U16	usEastOrWest,U16	usNorthOrSouth){
						return ID(width + usEastOrWest,height + usNorthOrSouth);
					};
					union{
						struct{
							U16	width;		///<	宽度
							U16	height;		///<	高度
						};
						UInt	index;		///<	索引
					};
				};
				enum	enumTextureType{
					enDeclareTexture0,
					enDeclareTexture1,
					enDeclareTexture2,
					enDeclareTexture3,
					enDeclareTexture4,
					enBlendTexture,
					enLightMapTexture,
					enNormalTexture0,
					enNormalTexture1,
					enNormalTexture2,
					enNormalTexture3,
					enNormalTexture4,
					enMaxTexture
				};
				enum	enumRenderType{
					enNoTexture			= 0,
					enUseTexture		= 1,
					enUseSpecular		= 1<<1,
					enUseNormal			= 1<<2,
					enUseLightMap		= 1<<3,
					enUseRealtimeShadow	= 1<<4,
					enUseSoftShadow		= 1<<5,
					enUseRT_Reflection	= 1<<6,
					enUseRT_Refrection	= 1<<7,
					enUseWireframe		= 1<<8
				};
				//地形信息
				struct MapInfo{
					MapInfo(){
						memset(strName,0,MAX_NAME);
						iRenderType	= enUseTexture | enUseSpecular ;
						iCacheTitle	=	1;
						pWaterMaterial		=	NULL;
	
					};
					AChar			strName[MAX_NAME];		///<	地图名字
					ID				WorldSize;				///<	地图大小
					ID				CurrentTitleID;			///<	当前块ID
					ID				CurrentPageID;			///<	当前页ID
					SInt			iRenderType;			///<	渲染选项(关系精度问题)
					SInt			iCacheTitle;			///<	缓冲块数量 （iCacheTitle*2 + 1）*（iCacheTitle*2 + 1）
					Material*		pWaterMaterial;			///<	水材质
					IndexBuffer*	pIndexBuff;				///<	索引声明
					VertexDeclare*	pVertexDeclare;			///<	顶点声明
					//Material*		m_
				};
				
				//碰撞信息
				struct CollisionInfo{
					UInt		uiType;				///<	类型(球体 立方体	胶囊)
					Float3		Position;			///<	位置
					Float4		Rotation;			///<	旋转
					Float3		Scale;				///<	缩放
				};		
				typedef	std::list<CollisionInfo>	CollisionList;		///<	碰撞信息列表
				typedef	CollisionList::iterator		CollisionListItr;	///<	碰撞信息列表迭代器
				//物品信息
				struct	ObjectInfo{
					AChar				strName[128];			///<	物品名
					AChar				strMaterialName[128];	///<	材质名
					Float3		Position;				///<	位置
					Float4	Rotation;				///<	旋转
					Float3		Scale;					///<	缩放
					CollisionList		m_lstCollisionInfo;		///<	碰撞信息
				};	
	
				/**	\brief	可加载
				*
				*	可加载
				*
				***/
				class	ILoadable{
				public:
					ILoadable(){
						m_bIsLoad	=	false;
					}
					virtual	~ILoadable(){
						if(m_bIsLoad){
							UnLoad();
						}
					};
	
					virtual U1	Load(){return true;};
					virtual U1	UnLoad(){return true;};
					virtual U1	New(){return true;};
					virtual U1	Save(){return true;};
	
					/**	\brief	是否已经加载
					*   
					*	@remarks 	是否已经加载
					*	@see		ILoadable
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	IsLoad(){return m_bIsLoad;};
				protected:
					U1	m_bIsLoad;			///<	是否已经加载
				};
	
				/**	\brief	基本地形
				*
				*	基本地形
				*
				***/
				class ENGINE_EXPORT	IPage	:
					public	MovableObject{
				public:
					static AString ProductTypeName;
					struct	Info{
						ID		uiID;
						AString	strMapPath;
						AString	GetPageName(){
							AChar	strName[MAX_NAME];
							sprintf_s(strName,MAX_NAME,"%sPage_%d_%d\\",strMapPath.c_str(),uiID.height,uiID.width);
							return strName;
						};
					};
				public:
					IPage(AString strName,Info*	pInfo);
					virtual ~IPage();
	
					ID			GetID();
	
					/**	\brief	创建
					*   
					*	@remarks 	创建
					*	@see		IPage
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1	Create();
	
					/**	\brief	摧毁
					*   
					*	@remarks 	摧毁
					*	@see		IPage
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1	Destroy();
	
					/**	\brief	更新
					*   
					*	@remarks 	更新
					*	@see		IPage
					*	@return   	void
					*	@note
					*
					**/
					virtual void	Update();
	
					virtual Float3		BrushHeight();
	
				protected:
					ID							m_uiID;				///<	地形ID
					Info						m_Info;				///<	页信息
					//AString 
	
				};
	
	
	
	// 			class IObject{
	// 			public:
	// 				IObject(){
	// 					m_bVisiable		= true;
	// 					m_bCastShadow	= true;
	// 				}
	// 				virtual ~IObject(){};
	// 				virtual	void	Update(Real	fTime){};
	// 				virtual void	Render(Real	fTime){};
	// 
	// 				inline	void			SetVisiable(U1	bVisiable){m_bVisiable	= bVisiable;};
	// 				inline	U1				IsVisiable(){return m_bVisiable;};
	// 				inline	void			SetCastShadow(U1	bCastShadow){return m_bCastShadow;};
	// 				inline	U1				IsCastShadow(){return m_bCastShadow;};
	// 				inline	BoundSphere&	GetBound(){return m_Bound;};
	// 
	// 				U1				m_bVisiable;		///<	是否可见
	// 				U1				m_bCastShadow;		///<	产生阴影
	// 				BoundSphere		m_Bound;			///<	包围盒
	// 
	// 			};
	
				U1	LoadResource(TCHAR*	strName,U8** pData,UInt& uiSize);
	
				ID	GetTitleIDByPosition(Real x,Real y);
				ID	GetPageIDByPosition(Real x,Real y);
	
	
	/*
				void   CFrustum::CalculateFrustum()   
				{           
					Real       proj[16]; //   This   will   hold   our   projection   matrix   
					Real       modl[16]; //   This   will   hold   our   modelview   matrix   
					Real       clip[16]; //   This   will   hold   the   clipping   planes   
	
					//   glGetFloatv()   is   used   to   extract   information   about   our   OpenGL   world.   
					//   Below,   we   pass   in   GL_PROJECTION_MATRIX   to   abstract   our   projection   matrix.   
					//   It   then   stores   the   matrix   into   an   array   of   [16].   
					glGetFloatv(   GL_PROJECTION_MATRIX,   proj   );   
	
					//   By   passing   in   GL_MODELVIEW_MATRIX,   we   can   abstract   our   model   view   matrix.   
					//   This   also   stores   it   in   an   array   of   [16].   
					glGetFloatv(   GL_MODELVIEW_MATRIX,   modl   );   
	
					//   Now   that   we   have   our   modelview   and   projection   matrix,   if   we   combine   these   2   matrices,   
					//   it   will   give   us   our   clipping   planes.     To   combine   2   matrices,   we   multiply   them.   
	
					clip[   0]   =   modl[   0]   *   proj[   0]   +   modl[   1]   *   proj[   4]   +   modl[   2]   *   proj[   8]   +   modl[   3]   *   proj[12];   
					clip[   1]   =   modl[   0]   *   proj[   1]   +   modl[   1]   *   proj[   5]   +   modl[   2]   *   proj[   9]   +   modl[   3]   *   proj[13];   
					clip[   2]   =   modl[   0]   *   proj[   2]   +   modl[   1]   *   proj[   6]   +   modl[   2]   *   proj[10]   +   modl[   3]   *   proj[14];   
					clip[   3]   =   modl[   0]   *   proj[   3]   +   modl[   1]   *   proj[   7]   +   modl[   2]   *   proj[11]   +   modl[   3]   *   proj[15];   
	
					clip[   4]   =   modl[   4]   *   proj[   0]   +   modl[   5]   *   proj[   4]   +   modl[   6]   *   proj[   8]   +   modl[   7]   *   proj[12];   
					clip[   5]   =   modl[   4]   *   proj[   1]   +   modl[   5]   *   proj[   5]   +   modl[   6]   *   proj[   9]   +   modl[   7]   *   proj[13];   
					clip[   6]   =   modl[   4]   *   proj[   2]   +   modl[   5]   *   proj[   6]   +   modl[   6]   *   proj[10]   +   modl[   7]   *   proj[14];   
					clip[   7]   =   modl[   4]   *   proj[   3]   +   modl[   5]   *   proj[   7]   +   modl[   6]   *   proj[11]   +   modl[   7]   *   proj[15];   
	
					clip[   8]   =   modl[   8]   *   proj[   0]   +   modl[   9]   *   proj[   4]   +   modl[10]   *   proj[   8]   +   modl[11]   *   proj[12];   
					clip[   9]   =   modl[   8]   *   proj[   1]   +   modl[   9]   *   proj[   5]   +   modl[10]   *   proj[   9]   +   modl[11]   *   proj[13];   
					clip[10]   =   modl[   8]   *   proj[   2]   +   modl[   9]   *   proj[   6]   +   modl[10]   *   proj[10]   +   modl[11]   *   proj[14];   
					clip[11]   =   modl[   8]   *   proj[   3]   +   modl[   9]   *   proj[   7]   +   modl[10]   *   proj[11]   +   modl[11]   *   proj[15];   
	
					clip[12]   =   modl[12]   *   proj[   0]   +   modl[13]   *   proj[   4]   +   modl[14]   *   proj[   8]   +   modl[15]   *   proj[12];   
					clip[13]   =   modl[12]   *   proj[   1]   +   modl[13]   *   proj[   5]   +   modl[14]   *   proj[   9]   +   modl[15]   *   proj[13];   
					clip[14]   =   modl[12]   *   proj[   2]   +   modl[13]   *   proj[   6]   +   modl[14]   *   proj[10]   +   modl[15]   *   proj[14];   
					clip[15]   =   modl[12]   *   proj[   3]   +   modl[13]   *   proj[   7]   +   modl[14]   *   proj[11]   +   modl[15]   *   proj[15];   
	
					//   Now   we   actually   want   to   get   the   sides   of   the   frustum.     To   do   this   we   take   
					//   the   clipping   planes   we   received   above   and   extract   the   sides   from   them.   
	
					//   This   will   extract   the   RIGHT   side   of   the   frustum   
					m_Frustum[RIGHT][A]   =   clip[   3]   -   clip[   0];   
					m_Frustum[RIGHT][B]   =   clip[   7]   -   clip[   4];   
					m_Frustum[RIGHT][C]   =   clip[11]   -   clip[   8];   
					m_Frustum[RIGHT][D]   =   clip[15]   -   clip[12];   
	
					//   Now   that   we   have   a   normal   (A,B,C)   and   a   distance   (D)   to   the   plane,   
					//   we   want   to   normalize   that   normal   and   distance.   
	
					//   Normalize   the   RIGHT   side   
					NormalizePlane(m_Frustum,   RIGHT);   
	
					//   This   will   extract   the   LEFT   side   of   the   frustum   
					m_Frustum[LEFT][A]   =   clip[   3]   +   clip[   0];   
					m_Frustum[LEFT][B]   =   clip[   7]   +   clip[   4];   
					m_Frustum[LEFT][C]   =   clip[11]   +   clip[   8];   
					m_Frustum[LEFT][D]   =   clip[15]   +   clip[12];   
	
					//   Normalize   the   LEFT   side   
					NormalizePlane(m_Frustum,   LEFT);   
	
					//   This   will   extract   the   BOTTOM   side   of   the   frustum   
					m_Frustum[BOTTOM][A]   =   clip[   3]   +   clip[   1];   
					m_Frustum[BOTTOM][B]   =   clip[   7]   +   clip[   5];   
					m_Frustum[BOTTOM][C]   =   clip[11]   +   clip[   9];   
					m_Frustum[BOTTOM][D]   =   clip[15]   +   clip[13];   
	
					//   Normalize   the   BOTTOM   side   
					NormalizePlane(m_Frustum,   BOTTOM);   
	
					//   This   will   extract   the   TOP   side   of   the   frustum   
					m_Frustum[TOP][A]   =   clip[   3]   -   clip[   1];   
					m_Frustum[TOP][B]   =   clip[   7]   -   clip[   5];   
					m_Frustum[TOP][C]   =   clip[11]   -   clip[   9];   
					m_Frustum[TOP][D]   =   clip[15]   -   clip[13];   
	
					//   Normalize   the   TOP   side   
					NormalizePlane(m_Frustum,   TOP);   
	
					//   This   will   extract   the   BACK   side   of   the   frustum   
					m_Frustum[BACK][A]   =   clip[   3]   -   clip[   2];   
					m_Frustum[BACK][B]   =   clip[   7]   -   clip[   6];   
					m_Frustum[BACK][C]   =   clip[11]   -   clip[10];   
					m_Frustum[BACK][D]   =   clip[15]   -   clip[14];   
	
					//   Normalize   the   BACK   side   
					NormalizePlane(m_Frustum,   BACK);   
	
					//   This   will   extract   the   FRONT   side   of   the   frustum   
					m_Frustum[FRONT][A]   =   clip[   3]   +   clip[   2];   
					m_Frustum[FRONT][B]   =   clip[   7]   +   clip[   6];   
					m_Frustum[FRONT][C]   =   clip[11]   +   clip[10];   
					m_Frustum[FRONT][D]   =   clip[15]   +   clip[14];   
	
					//   Normalize   the   FRONT   side   
					NormalizePlane(m_Frustum,   FRONT);   
				} 
				*/
			}
		
	
	};
};
#endif // RENDERTERRAINCOMMON_HEAD_FILE