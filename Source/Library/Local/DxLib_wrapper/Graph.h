#pragma once
#include "DxLib.h"
#include "Struct.h"
#include <vector>
#include <string>
#include <map>
#include <functional>

struct GraphData {

	GraphData() {}
	GraphData(const std::string &filepath, bool transflag = false, const Val2D<int> &div = {1, 1}, const Val2D<int> &drawsize = {0, 0}) {
		this->Load(filepath, transflag, div, drawsize);
	}
	~GraphData() { this->Delete(); }

	void Load(const std::string &filepath, bool transflag = false, const Val2D<int> &div = {1, 1}, const Val2D<int> &drawsize = {0, 0}) {

		Div = div;
		if (drawsize.x == 0 || drawsize.y == 0) {
			GetImageSize_File(filepath.c_str(), &Size.x, &Size.y);
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
			Size.x,
			Size.y,
			m_Handles.begin()._Ptr
		);

		TransFlag = transflag;
	}
	void Delete() {
		DeleteSharingGraph(m_Handles.front());
		m_Handles = {-1};
	}
	void Draw(const Val2D<float> &pos = {0, 0}, size_t index = 0, const Val2D<float> &origin = {0.5, 0.5}) {
		if (index >= m_Handles.size()) {
			return;
		}
		Rect2D<float> offset = {Size * origin, Size + (Size * -origin)};
		DrawExtendGraphF(
			pos.x - offset.x,
			pos.y - offset.y,
			pos.x + offset.w,
			pos.y + offset.h,
			m_Handles[index],
			TransFlag
			);
	}

	const int GetHandle(size_t index = 0) const { return m_Handles.at(index); }

	bool TransFlag = false;
	Val2D<int> Size;
	Val2D<int> Div;

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

	void Create(const Val2D<int> &drawsize, bool transflag, auto &&func) {
		m_Handle = MakeScreen(Size.x, Size.y, TransFlag);
		auto callback = [=]() {
			SetDrawScreen(m_Handle);
			func();
			SetDrawScreen(DX_SCREEN_BACK);
		};
		callback();
		m_CallBackIndex = CallBack.Regist(std::move(callback));
	}
	void Delete() {
		DeleteGraph(m_Handle);
		m_Handle = -1;
		CallBack.Remove(m_CallBackIndex);
		m_CallBackIndex = 0;
	}
	void Draw(const Val2D<float>& pos = {0, 0}) const {
		Val2D<float> offset = Size * Origin;
		DrawGraphF(
			pos.x - offset.x,
			pos.y - offset.y,
			m_Handle,
			TransFlag
		);
	}

	bool TransFlag = false;
	Val2D<float> Origin{0.5, 0.5};
	Val2D<int> Size;

private:

	size_t m_CallBackIndex = 0;
	int m_Handle = -1;

	inline static struct _CallBack {
		_CallBack() {
			static auto f = [&]() { Restore(); };
			auto pf = (void(*)())((void *)&f);
			SetRestoreGraphCallback(pf);
		}

		size_t Regist(std::function<void()> &&callbackfunc) {
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
		void Restore() {
			for (auto&& func : Funcs) {
				func.second();
			}
		}

		std::unordered_map<size_t, std::function<void()>> Funcs;

	} CallBack = _CallBack();
};