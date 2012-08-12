#ifndef ENGINETERRAINWORLD_HEAD_FILE
#define ENGINETERRAINWORLD_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineTerrainCommon.h"
#include "AirEngineTerrainTitle.h"
namespace Air{
	
	namespace Client{
	
		
			namespace	Terrain{
	
				typedef	stdext::hash_map<UInt,Title*>	TitleMap;			///<	地形块索引列表
				typedef	TitleMap::iterator				TitleMapItr;		///<	地形块索引列表迭代器
				typedef	TitleMap::value_type			TitleMapPair;		///<	地形块索引列表容器
	
				typedef	std::list<Title*>				TitleList;			///<	地形块列表
				typedef	TitleList::iterator				TitleListItr;		///<	地形块列表
	
				typedef	std::vector<Title*>				TitleVector;
				typedef	TitleVector::iterator			TitleVectorItr;
	
				/**	\brief	世界
				*
				*	世界
				*
				***/
				class ENGINE_EXPORT	World	:	
					public	ILoadable{
				public:
					World();
					virtual	~World();
	
					/**	\brief	载入地图
					*   
					*	@remarks 	载入地图
					*	@see		World
					*	@return   	U1
					*	@param		AChar * strName
					*	@note
					*
					**/
					virtual U1	Load(AChar* strName );
					/**	\brief	重新加载
					*   
					*	@remarks 	重新加载
					*	@see		World
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1	ReLoad();
					virtual U1	New();
					virtual U1	UnLoad();
					virtual U1	Save();
	
					virtual U1	ChangePosition(Real x,Real y );
	
					virtual void	Updata();
					virtual	void	Render();
	
					virtual U1	GetHeight(Real	x,Real	y,	Real*	z	= NULL);
				private:
					U1	LoadInfo(AChar* strName);
	
					U1	LoadTitle(	ID	titleID);
					U1	UnLoadTitle(ID	titleID);
	
					/**	\brief	切换地形块
					*   
					*	@remarks 	跨越地形块边界
					*	@see		World
					*	@return   	U1
					*	@param		ID currentTitleID
					*	@note
					*
					**/
					U1	ChangeTitle(ID	currentTitleID);
					/**	\brief	更新地形块
					*   
					*	@remarks 	更新地形块
					*	@see		World
					*	@return   	U1
					*	@note
					*
					**/
					U1	UpdataTitle();
	
	
					U1	RenderSky();
					U1	RenderTerrain();
					U1	RenderObject();
					U1	RenderGrass();
					U1	RenderWater();
					U1	RenderAlphaObject();
	
					U1	UpdataIndex();
	
					MapInfo				m_Info;						///<	地图信息
	
	
					TitleVector			m_TitleArray;				///<	用于渲染的地形块数组
					TitleMap			m_mapLoadedTitle;			///<	用于查询的地形块（已加载到内存的所有地形块）
					TitleList			m_lstLoadedTitle;			///<	用于卸载地形块列表（已加载到内存的所有地形块）
	
				};
			}
	
	};
};
#endif // RENDERTERRAINWORLD_HEAD_FILE