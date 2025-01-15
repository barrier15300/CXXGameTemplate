#pragma once
#include "../Helper/DXHandle.h"

/// <summary>
/// TODO: Implementation Now
/// </summary>
struct FontData : public DXHandle<DXHandleType::Font> {

	using DXHandle::DXHandle;

	bool Create(const std::string &path) {

		return true;
	}

	


private:
	int InitImpl() {
		DeleteFontToHandle(m_Handle);
	}
};