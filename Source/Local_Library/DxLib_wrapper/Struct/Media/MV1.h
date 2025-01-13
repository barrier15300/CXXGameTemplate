#pragma once
#include "../Helper/DXHandle.h"

struct MV1Data: public DXHandle<DXHandleType::Model> {

	using DXHandle::DXHandle;
	struct _ChainSettingImpl;

	bool Create(const std::string &path) {

		*this = MV1LoadModel(path.c_str());
		
		return true;
	}

	void Draw() {
		MV1DrawModel(*this);
	}

	_ChainSettingImpl Setting() {
		return _ChainSettingImpl(*this);
	}

private:
	struct _ChainSettingImpl : public DXHandle<DXHandleType::None> {

		using DXHandle::DXHandle;
		using TIHS = _ChainSettingImpl;
		
		TIHS &SetPosition(Val3D<float> pos)		{ MV1SetPosition(*this,pos); return *this; }
		TIHS &SetScale(Val3D<float> scale)		{ MV1SetScale(*this, scale); return *this; }
		TIHS &SetRotate(Val3D<float> rotate)	{ MV1SetRotationXYZ(*this, rotate); return *this; }
		TIHS &SetVisible(bool flag)				{ MV1SetVisible(*this, flag); return *this; }
		TIHS &SetDifColor(Color32 scale)		{ MV1SetDifColorScale(*this, scale); return *this; }
		TIHS &SetSpcColor(Color32 scale)		{ MV1SetSpcColorScale(*this, scale); return *this; }
		TIHS &SetEmiColor(Color32 scale)		{ MV1SetEmiColorScale(*this, scale); return *this; }
		TIHS &SetAmbColor(Color32 scale)		{ MV1SetAmbColorScale(*this, scale); return *this; }
		TIHS &SetOpacity(float opacity)			{ MV1SetVisible(*this, opacity); return *this; }

	};

	int InitImpl() {
		MV1DeleteModel(*this);
	}
};