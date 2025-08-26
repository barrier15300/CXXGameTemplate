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

static inline int __NoWorkDeleteFunc(int) { return 0; }
template<DXHandleType handletype = DXHandleType::None,int (*deleter_func)(int) = __NoWorkDeleteFunc>
struct DXHandle {

	constexpr DXHandle() : m_Handle(HandleNull) { }
	constexpr explicit DXHandle(int from) : m_Handle(from) {}

	constexpr DXHandle(const DXHandle& from) = delete;
	constexpr DXHandle(DXHandle &&from) noexcept : m_Handle(from.m_Handle) {
		from.m_Handle = HandleNull;
	}
	~DXHandle() {
		Init();
	}

	constexpr DXHandle &operator=(DXHandle &&from) noexcept {
		m_Handle = from.m_Handle;
		from.m_Handle = HandleNull;
		return *this;
	}

	bool IsAsyncState() const {
		return !Check(CheckHandleASyncLoad(m_Handle));
	}
	void AWait() const {
		WaitHandleASyncLoad(m_Handle);
	}

	static bool Check(int state) {
		if (state == -1) {
			return false;
		}
		return (bool)state;
	}

	static int GetHandleLimitCount() {
		return GetMaxHandleNum(static_cast<int>(handletype));
	}
	static int GetHandleUsingCount() {
		return GetHandleNum(static_cast<int>(handletype));
	}
	static int GetAvailableCount() {
		return GetHandleLimitCount() - GetHandleUsingCount();
	}

	constexpr int GetRawHandle() const {
		return m_Handle;
	}

	constexpr void Init(int from = HandleNull) {
		deleter_func(*this);
		m_Handle = from;
	}

	static constexpr int HandleNull = -1;

protected:

	constexpr operator int() const {
		return m_Handle;
	}
	
	constexpr bool IsNull() {
		return m_Handle == HandleNull;
	}

	int m_Handle;
};

template<>
struct DXHandle<DXHandleType::None> {

	constexpr DXHandle() : m_Handle(HandleNull) { }
	constexpr explicit DXHandle(int from) : m_Handle(from) { }
	constexpr operator int() const {
		return m_Handle;
	}

	static constexpr int HandleNull = -1;

protected:

	int m_Handle;
};