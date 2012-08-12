#ifndef GAMEACTOR_HEAD_FILE
#define GAMEACTOR_HEAD_FILE

#include "AirGame.h"
#include "AirGameHeader.h"

namespace Client{
	namespace	Game{
		/**	\brief	游戏角色
		*
		*	游戏角色
		*
		***/
		class	Actor	:
			public	IProduct,
			public	IUserData,
			public	IMovableObject{
		public:
			struct	Info{
				Info(){
					uiIndex	=	0;
				}
				UInt	uiIndex;
			};
		public:
			Actor(AString&	strName,Info*	pInfo);

			virtual	U1		Create();

			virtual	U1		Destroy();

			virtual	void	Updata();

			virtual	void	Render();
		};
	};
};
#endif // GAMEACTOR_HEAD_FILE