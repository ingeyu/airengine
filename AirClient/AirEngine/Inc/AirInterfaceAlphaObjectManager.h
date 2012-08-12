#ifndef INTERFACEALPHAOBJECTMANAGER_HEAD_FILE
#define INTERFACEALPHAOBJECTMANAGER_HEAD_FILE

#include "AirEngineHeader.h"

namespace Air{
	
	namespace Client{
		class	Renderable;
	
		/**	\brief	半透明物体
		*
		*	半透明物体
		*
		***/
		struct	AlphaObject{
			AlphaObject(){
				pRenderObj	=	NULL;
				fDistance	=	0;
			};
			Renderable*		pRenderObj;
			//Float44						mat;			///<	世界矩阵
			Float3						vPos;
			Real						fDistance;		///<	距离
		};
		/**	\brief	半透明物体渲染管理器
		*
		*	半透明物体渲染管理
		*
		***/
		class	IAlphaObjectManager{
		public:
			IAlphaObjectManager();
			/**	\brief	插入半透明物体
			*   
			*	@remarks 	插入半透明
			*	@see		IAlphaObjectManager
			*	@return   	void
			*	@param		AlphaObject obj
			*	@note
			*
			**/
			virtual	void	PushAlphaObject(AlphaObject	obj);
	
			/**	\brief	渲染所有半透明物体
			*   
			*	@remarks 	渲染半透明物体
			*	@see		IAlphaObjectManager
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	RenderAlphaObject();
	
			//typedef		std::list<AlphaObject>			AObjectList;
			//typedef		AObjectList::iterator			AObjectListItr;
			//typedef		AObjectList::reverse_iterator	AObjectListRItr;
	
			//AObjectList		m_lstAlphaObject;
			Float3*		m_pCameraPosition;
		};
	
	};
};
#endif // INTERFACEALPHAOBJECTMANAGER_HEAD_FILE