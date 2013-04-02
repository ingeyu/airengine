#ifndef INTERFACEGAMEDATAINFO_HEAD_FILE
#define INTERFACEGAMEDATAINFO_HEAD_FILE
namespace Air{
	
	namespace Engine{
	
		namespace	Game{
			namespace	Data{
				enum	enumState{
					enWaiting,
					enJoining,
					enGaming,
					enGameOver
				};
				namespace	Infomation{
					struct	Player{
						AChar	strName[32];
						UInt	uiID;
						SInt	uiLife;
						SInt	uiMinAttack;
						SInt	uiMaxAttack;
						SInt	uiAttackVelocity;
	
						UInt	uiMoveVelocity;
						UInt	uiHealth;
						UInt	uiMaxHealth;
	
						Vector3		vPosition;
						Quaternion	vQuat;
	
						Vector3		vOrgin;
						Vector3		vDirection;
						UInt		uiShoot;
	
					};
	
					struct	Room{
						AChar	strName[32];
						AChar	strIP[16];
						U16		port;
						SInt	usNumPlayer;
						SInt	usMaxPlayer;
					};
	
				}
				typedef		Infomation::Player	PlayerInfo;
				typedef		Infomation::Room	RoomInfo;
				typedef	std::map<UInt,Infomation::Player>		PlayerMap;
				typedef	std::map<AString,Infomation::Room>		RoomMap;
			}
		}
	
	};
};
#endif // INTERFACEGAMEDATAINFO_HEAD_FILE