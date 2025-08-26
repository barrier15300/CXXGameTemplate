#pragma once
#include "../Helper/DXHandle.h"
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

class GDIInitializer {
	
	GDIInitializer() {
		Gdiplus::GdiplusStartup(&Token, &gdiplusStartupInput, nullptr);
	}
	~GDIInitializer() {
		Gdiplus::GdiplusShutdown(Token);
	}
	
	ULONG_PTR Token;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

public:

	static GDIInitializer& GetInstance() {
		static GDIInitializer instance;
		return instance;
	}

	const Gdiplus::GdiplusStartupInput& GetStartupInput() const {
		return gdiplusStartupInput;
	}
};

struct FontData : public DXHandle<DXHandleType::Font, DeleteFontToHandle> {

	using DXHandle::DXHandle;

	enum CharCodeFormat : int {
		ShiftJIS = DX_CHARCODEFORMAT_SHIFTJIS,
		GB2312 = DX_CHARCODEFORMAT_GB2312,
		UHC = DX_CHARCODEFORMAT_UHC,
		BIG5 = DX_CHARCODEFORMAT_BIG5,
		UTF16LE = DX_CHARCODEFORMAT_UTF16LE,
		UTF16BE = DX_CHARCODEFORMAT_UTF16BE,
		Windwos1252 = DX_CHARCODEFORMAT_WINDOWS_1252,
		ISO_IEC_8859_15 = DX_CHARCODEFORMAT_ISO_IEC_8859_15,
		UTF8 = DX_CHARCODEFORMAT_UTF8,
		ASCII = DX_CHARCODEFORMAT_ASCII,
		UTF32LE = DX_CHARCODEFORMAT_UTF32LE,
		UTF32BE = DX_CHARCODEFORMAT_UTF32BE,
	};

	bool Load(const std::string& path, int size, int thick, int edgeSize = 0, size_t index = 0) {
		Init(Make(path, size, thick, edgeSize, index));
		return !IsNull();
	}

	template<class T>
	inline void Draw(const std::string& str, const Val2D<T>& pos, const Val2D<T>& offset, const Color3& color = {}, const Color3& edgeColor = {}) {
		if constexpr (std::is_integral<T>::value) {
			DrawStringToHandle(
				pos.x - offset.x,
				pos.y - offset.y,
				str.c_str(),
				color,
				*this,
				edgeColor
			);
		}
		else {
			DrawStringFToHandle(
				pos.x - offset.x,
				pos.y - offset.y,
				str.c_str(),
				color,
				*this,
				edgeColor
			);
		}
	}

	Val2D<int> GetSize(const std::string& text) const {
		size_t c = 1;
		size_t idx = 0;
		while ((idx = text.find('\n', idx + 1)) != std::string::npos) {
			++c;
		}
		Val2D<int> ret = {
			GetDrawStringWidthToHandle(text.data(), text.size(), *this),
			GetFontSizeToHandle(*this) * c
		};
		return ret;
	}

	void SetCharCodeFormat(CharCodeFormat format) {
		SetFontCharCodeFormatToHandle(format, *this);
	}
	void SetFontSpace(int pixel) {
		SetFontSpaceToHandle(pixel, *this);
	}
	void SetFontLineSpace(int pixel) {
		SetFontLineSpaceToHandle(pixel, *this);
	}

	static FontData Make(const std::string& path, int size, int thick, int edgeSize = 0, size_t index = 0) {
		FontData font;
		
		font.Init(
			CreateFontToHandle(
				GetFontNameAndLoad(path, index).c_str(),
				size,
				thick,
				DX_FONTTYPE_ANTIALIASING_EDGE_4X4,
				DX_CHARSET_UTF8,
				edgeSize
			)
		);
		font.SetCharCodeFormat(CodeFormat);

		return font;
	}

	static std::string GetFontNameAndLoad(std::string path, size_t index) {

		if (FontNameCollections.find(path) != FontNameCollections.end()) {
			if (index >= FontNameCollections[path].size()) {
				index = 0;
			}
			return FontNameCollections[path][index];
		}

		auto& gdi = GDIInitializer::GetInstance();
		
		Gdiplus::PrivateFontCollection fontCollection;
		
		auto wpath = cp_to_wide(path, CodeFormat);
		fontCollection.AddFontFile(wpath.c_str());
		
		int familyCount = fontCollection.GetFamilyCount();
		int found = 0;
		Gdiplus::FontFamily* families = (Gdiplus::FontFamily*)malloc(familyCount * sizeof(Gdiplus::FontFamily));
		fontCollection.GetFamilies(familyCount, families, &found);
		
		if (found <= 0) {
			return "";
		}
		else if (index >= found) {
			index = 0;
		}
		
		constexpr size_t FontNameMaxLength = 256;
		
		std::vector<std::string> names;
		names.reserve(familyCount);
		std::transform(families, families + familyCount, std::back_inserter(names), [](auto&& v) {
			WCHAR familyName[FontNameMaxLength]{};
			v.GetFamilyName(familyName);
			return wide_to_cp(familyName, CodeFormat);
			});

		free(families);

		FontNameCollections[path] = std::move(names);

		return GetFontNameAndLoad(path, index);
	}

	static inline CharCodeFormat CodeFormat = UTF8;
	static inline std::unordered_map<std::string_view, std::vector<std::string>> FontNameCollections;
};


