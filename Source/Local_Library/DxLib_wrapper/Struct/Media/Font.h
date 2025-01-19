#pragma once
#include "../Helper/DXHandle.h"

/// <summary>
/// TODO: Implementation Now
/// </summary>
struct FontData : public DXHandle<DXHandleType::Font, DeleteFontToHandle> {

	using DXHandle::DXHandle;

	bool Create(const std::string &path) {

		return true;
	}

	


};