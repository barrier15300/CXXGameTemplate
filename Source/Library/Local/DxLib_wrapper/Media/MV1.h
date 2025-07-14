#pragma once
#include "../Helper/Helper.h"
#include "../Value/Value.h"

#define FUNC_GETTER(T, name) const T& name() const { return m_##name; }

struct ModelData : DXHandle<DXHandleType::Model, MV1DeleteModel> {

	using DXHandle::DXHandle;
	struct _ChainSettingImpl;

	bool Create(const std::string &path) {
		
		Init(MV1LoadModel(path.c_str()));
		
		return !IsNull();
	}

	void Draw() {
		MV1DrawModel(*this);
	}

	_ChainSettingImpl Settings() {
		return _ChainSettingImpl(this);
	}

	FUNC_GETTER(Val3D<float>, Pos);
	FUNC_GETTER(Val3D<float>, Scale);
	FUNC_GETTER(Val3D<float>, Rotate);
	FUNC_GETTER(bool, Visible);
	FUNC_GETTER(Color4F, DifColor);
	FUNC_GETTER(Color4F, SpcColor);
	FUNC_GETTER(Color4F, EmiColor);
	FUNC_GETTER(Color4F, AmbColor);
	FUNC_GETTER(float, Opacity);

private:
	struct _ChainSettingImpl {

		_ChainSettingImpl(ModelData* from) { data = from; }
		~_ChainSettingImpl() { data = nullptr; }

		using This = _ChainSettingImpl;
		
		This &Position(Val3D<float> pos)	{ MV1SetPosition(data->m_Handle, pos); data->m_Pos = pos; return *this; }
		This &Scale(Val3D<float> scale)		{ MV1SetScale(data->m_Handle, scale); data->m_Scale = scale; return *this; }
		This &Rotate(Val3D<float> rotate)	{ MV1SetRotationXYZ(data->m_Handle, rotate); data->m_Rotate = rotate; return *this; }
		This &Visible(bool flag)			{ MV1SetVisible(data->m_Handle, flag); data->m_Visible = flag; return *this; }
		This &DifColor(Color4F scale)		{ MV1SetDifColorScale(data->m_Handle, scale); data->m_DifColor = scale; return *this; }
		This &SpcColor(Color4F scale)		{ MV1SetSpcColorScale(data->m_Handle, scale); data->m_SpcColor = scale; return *this; }
		This &EmiColor(Color4F scale)		{ MV1SetEmiColorScale(data->m_Handle, scale); data->m_EmiColor = scale; return *this; }
		This &AmbColor(Color4F scale)		{ MV1SetAmbColorScale(data->m_Handle, scale); data->m_AmbColor = scale; return *this; }
		This &Opacity(float opacity)		{ MV1SetOpacityRate(data->m_Handle, opacity); data->m_Opacity = opacity; return *this; }

	private:
		ModelData* data = nullptr;
	};

	Val3D<float> m_Pos;
	Val3D<float> m_Scale;
	Val3D<float> m_Rotate;
	bool m_Visible{};
	Color4F m_DifColor;
	Color4F m_SpcColor;
	Color4F m_EmiColor;
	Color4F m_AmbColor;
	float m_Opacity{};
};

#undef FUNC_GETTER