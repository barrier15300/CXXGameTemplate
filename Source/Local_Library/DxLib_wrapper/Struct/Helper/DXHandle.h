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

static int __nowork_deleter_func(int) { return 0; }
template<DXHandleType handletype = DXHandleType::None,int (*deleter_func)(int) = __nowork_deleter_func>
struct DXHandle {

	DXHandle() : m_Handle(HandleNull) { }
	//DXHandle(int from): m_Handle(from) { }
	~DXHandle() {
		Init();
	};

	operator const int() const {
		return m_Handle;
	}

	int GetLimitHandleCount() const {
		return GetMaxHandleNum(static_cast<int>(handletype));
	}
	int GetUsingHandleCount() const {
		return GetHandleNum(static_cast<int>(handletype));
	}
	int GetAvaliableCount() const {
		return GetLimitHandleCount() - GetUsingHandleCount();
	}

	void Init(int from = HandleNull) {
		deleter_func(*this);
		m_Handle = from;
	}

	inline static const int HandleNull = -1;

protected:

	bool IsNull() {
		return m_Handle == HandleNull;
	}

	int m_Handle;
};

template<>
struct DXHandle<DXHandleType::None> {

	DXHandle() : m_Handle(HandleNull) { }
	DXHandle(int from) : m_Handle(from) { }
	operator const int() const {
		return m_Handle;
	}

	inline static const int HandleNull = -1;

protected:

	int m_Handle;
};