#pragma once
#include "DxLib.h"

enum class DXHandleType : int {
	None = DX_HANDLETYPE_NONE,
	Graph = DX_HANDLETYPE_GRAPH,
	SoftImage = DX_HANDLETYPE_SOFTIMAGE,
	Sound = DX_HANDLETYPE_SOUND,
	SoftSound = DX_HANDLETYPE_SOFTSOUND,
	Music = DX_HANDLETYPE_MUSIC,
	Movie = DX_HANDLETYPE_MOVIE,
	Mask = DX_HANDLETYPE_GMASK,
	Font = DX_HANDLETYPE_FONT,
	KeyInput = DX_HANDLETYPE_KEYINPUT,
	NetWork = DX_HANDLETYPE_NETWORK,
	Light = DX_HANDLETYPE_LIGHT,
	Shader = DX_HANDLETYPE_SHADER,
	ModelBase = DX_HANDLETYPE_MODEL_BASE,
	Model = DX_HANDLETYPE_MODEL,
	VertexBuffer = DX_HANDLETYPE_VERTEX_BUFFER,
	IndexBuffer = DX_HANDLETYPE_INDEX_BUFFER,
	File = DX_HANDLETYPE_FILE,
	ShadowMap = DX_HANDLETYPE_SHADOWMAP,
	ShaderConstantBuffer = DX_HANDLETYPE_SHADER_CONSTANT_BUFFER,
	Live2DCubism4Model = DX_HANDLETYPE_LIVE2D_CUBISM4_MODEL,
	HandleTypeCount
};

template<DXHandleType handletype>
struct DXHandle {

	DXHandle() : m_handle(-1) {}
	DXHandle(int from) : m_handle(from) {}
	~DXHandle() { InitImpl(); };

	operator const int() {
		return m_handle;
	}
	operator const int() const {
		return m_handle;
	}

	int GetLimitHandleCount() const {
		return GetMaxHandleNum(static_cast<int>(m_type));
	}
	int GetUsingHandleCount() const {
		return GetHandleNum(static_cast<int>(m_type));
	}
	int GetAvaliableCount() const {
		return GetUsingHandleCount() - GetLimitHandleCount();
	}

	virtual int InitImpl() = 0;

protected:
	int m_handle;
	inline static DXHandleType m_type = handletype;
};