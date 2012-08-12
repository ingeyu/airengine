#ifndef ENGINETERRAINGRASS_HEAD_FILE
#define ENGINETERRAINGRASS_HEAD_FILE

namespace Client{

	

		namespace	Terrain{

			class Grass{
			public:
				//D3DXFloat4	vPosition;///<	xyw	= 位置	w = 摇摆偏移量和缩放系数
				typedef		std::vector<D3DXFloat4>	PositionVector;
				typedef		PositionVector::iterator	PositionVectorItr;
				class List{
					PositionVector	m_vecGrass;
					TCHAR*			m_strTexture;
				};
				typedef		std::map<std::string,List>	GroupMap;
				typedef		GroupMap::iterator			GroupMapItr;
				typedef		GroupMap::value_type		GroupMapPair;
				class Group{
				public:
					GroupMap	m_mapList;
					void	Add(TCHAR* strTextureName,PositionVector vecGrassPosition);
				};
			};
		}
	

};
#endif // RENDERTERRAINGRASS_HEAD_FILE