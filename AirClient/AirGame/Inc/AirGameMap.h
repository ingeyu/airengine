#ifndef GAMEMAP_HEAD_FILE
#define GAMEMAP_HEAD_FILE

namespace Client{

	namespace	Game{
		class	Map{
		public:
			Map(AString	strName);

			virtual	U1	Create();
		};
	}

};
#endif // GAMEMAP_HEAD_FILE