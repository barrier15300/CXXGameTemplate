#pragma once
#include "DxLib.h"
#include "Struct.h"
#include <vector>
#include <string>
#include <map>
#include <functional>

struct GraphData {

	GraphData() {}
	GraphData(const std::string &filepath, bool transflag = false, const Pos2D<int> &div = {1, 1}, const Size2D<int> &drawsize = {0, 0}) {
		this->Load(filepath, transflag, div, drawsize);
	}
	~GraphData() { this->Delete(); }

	void Load(const std::string &filepath, bool transflag = false, const Pos2D<int> &div = {1, 1}, const Size2D<int> &drawsize = {0, 0}) {

		Div = div;
		if (drawsize.width == 0 || drawsize.height == 0) {
			GetImageSize_File(filepath.c_str(), &Size.width, &Size.height);
		}
		else {
			Size = drawsize;
		}
		Size = Size / Div;

		this->Delete();
		m_Handles.resize(static_cast<size_t>(Div.x) * Div.y);
		LoadDivGraph(
			filepath.c_str(),
			Div.x * Div.y,
			Div.x, Div.y,
			Size.width,
			Size.height,
			m_Handles.begin()._Ptr
		);

		TransFlag = transflag;
	}
	void Delete() {
		DeleteSharingGraph(m_Handles.front());
		m_Handles = {-1};
	}
	void Draw(const Pos2D<float> &pos = {0, 0}, size_t index = 0) {
		if (index >= m_Handles.size()) {
			return;
		}
		Rect2D<float> offset = {Size * Origin, Size - Size * Origin};
		DrawExtendGraphF(
			pos.x - offset.left,
			pos.y - offset.top,
			pos.x + offset.right,
			pos.y + offset.bottom,
			m_Handles[index],
			TransFlag
			);
	}
	void Draw(const Pos2D<float> &pos = {0, 0}, const Size2D<float> &origin = {0.5, 0.5}, size_t index = 0) {
		if (index >= m_Handles.size()) {
			return;
		}
		Rect2D<float> offset = {Size * origin, Size - (Size * origin)};
		DrawExtendGraphF(
			pos.x - offset.left,
			pos.y - offset.top,
			pos.x + offset.right,
			pos.y + offset.bottom,
			m_Handles[index],
			TransFlag
			);
	}

	const int GetHandle(size_t index = 0) const { return m_Handles.at(index); }

	bool TransFlag = false;
	Size2D<float> Origin{0.5, 0.5};
	Size2D<int> Size;
	Pos2D<int> Div;

private:
	std::vector<int> m_Handles = {-1};
};

struct DrawBlend {
	
	enum Type {
		None = DX_BLENDMODE_NOBLEND,
		Alpha = DX_BLENDMODE_ALPHA,
		Add = DX_BLENDMODE_ADD,
		Sub = DX_BLENDMODE_SUB,
		Mul = DX_BLENDMODE_MUL,
		PMA_Alpha = DX_BLENDMODE_PMA_ALPHA,
		PMA_Add = DX_BLENDMODE_PMA_ADD,
		PMA_Sub = DX_BLENDMODE_PMA_SUB,
	};

	DrawBlend(Type t, int param) {
		m_NowBlendMode = true;
		SetDrawBlendMode(t, param);
	}
	~DrawBlend() {
		if (m_NowBlendMode) {
			SetDrawBlendMode(None, 0);
		}
		m_NowBlendMode = false;
	}

private:

	inline static bool m_NowBlendMode = false;
};

struct OptimizationGraph {

	void Create(const Size2D<int> &drawsize, bool transflag, auto &&func) {
		m_CallBackIndex = CallBack.Regist([=](){ this->_Create(drawsize, transflag, func); });
		this->_Create(drawsize, transflag, func);
	}
	void Delete() {
		DeleteGraph(m_Handle);
		m_Handle = -1;
		CallBack.Remove(m_CallBackIndex);
		m_CallBackIndex = 0;
	}
	void Draw(const Pos2D<float>& pos = {0, 0}) const {
		Pos2D<float> offset = Size * Origin;
		DrawGraphF(
			pos.x - offset.x,
			pos.y - offset.y,
			m_Handle,
			TransFlag
		);
	}

	bool TransFlag = false;
	Size2D<float> Origin{0.5, 0.5};
	Size2D<int> Size;

private:

	void _Create(const Size2D<int> &drawsize, bool transflag, auto &&func) {
		TransFlag = transflag;
		Size = drawsize;

		m_Handle = MakeScreen(Size.width, Size.height, TransFlag);
		SetDrawScreen(m_Handle);

		func();

		SetDrawScreen(DX_SCREEN_BACK);
	}

	size_t m_CallBackIndex = 0;
	int m_Handle = -1;

	inline static struct _CallBack {
		_CallBack() {
			static auto f = [&]() { GraphCallBack(); };
			auto pf = (void(*)())((void *)&f);
			SetRestoreGraphCallback(pf);
		}

		size_t Regist(auto &&callbackfunc) {
			size_t ret = 0;
			for (size_t i = 0; auto && find : Funcs) {
				size_t diff = find.first - i;
				if (diff > 1) {
					ret = i + 1;
					break;
				}
				else {
					++ret;
				}
				i = find.first;
			}
			Funcs[ret] = callbackfunc;
			return ret;
		}
		void Remove(size_t index) {
			Funcs.erase(index);
		}

	private:
		void GraphCallBack() {
			for (auto&& func : Funcs) {
				func.second();
			}
		}

		std::unordered_map<size_t, std::function<void()>> Funcs;

	} CallBack = _CallBack();
};