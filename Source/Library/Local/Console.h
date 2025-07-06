#pragma once
#include <io.h>
#include <Fcntl.h>

class AttachConsole {
	int hConsole = 0;
	
	AttachConsole() {
		FILE* fp;
		
		AllocConsole();

		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);
	}
	~AttachConsole() {
		FreeConsole();
	}

public:

	static AttachConsole& GetInstance() {
		static AttachConsole instance;
		return instance;
	}
};
