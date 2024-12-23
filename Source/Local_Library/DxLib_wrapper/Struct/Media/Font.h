#pragma once
#include "../Helper/DXHandle.h"

struct FontData : public DXHandle<DXHandleType::Font> {

	using DXHandle::DXHandle;

	void Create() {

	}

	


private:
	int InitImpl() {
		DeleteFontToHandle(m_Handle);
	}
};