#include "stdafx.h"
#include "Server.h"



int _tmain(int argc, _TCHAR* argv[])
{

	DownloadServer server;
	server.Initialization();

	while(1){
		server.Update();
	}

	server.Release();

	return 0;
}