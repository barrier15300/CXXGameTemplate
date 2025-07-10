#pragma once
#include <consoleapi.h>

class AttachConsole {
	int hConsole = 0;
	
	AttachConsole() {
		FILE* fp;
		
		AllocConsole();

		fopen_s(&fp, "CONOUT$", "w");
		fopen_s(&fp, "CONOUT$", "w");
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
