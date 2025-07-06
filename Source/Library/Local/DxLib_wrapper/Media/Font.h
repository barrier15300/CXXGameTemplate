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

struct FontData;

struct DrawableString {

	friend FontData;

	DrawableString() {}

	template<class T>
	void Draw(const Val2D<T>& pos, const Val2D<float>& origin = {});
	
private:
	Val2D<int> Size;
	std::string Text;
	const FontData* Font = nullptr;
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

	Color3 Color{255,255,255};
	Color3 EdgeColor;

	void SetCharCodeFormat(CharCodeFormat format) {
		SetFontCharCodeFormatToHandle(format, *this);
	}

	void SetFontSpace(int pixel) {
		SetFontSpaceToHandle(pixel, *this);
	}

	void SetFontLineSpace(int pixel) {
		SetFontLineSpaceToHandle(pixel, *this);
	}

	DrawableString ToDrawable(const std::string_view& text) const {
		DrawableString ret;
		ret.Text = text;
		ret.Font = this;
		size_t c = 1;
		size_t idx = 0;
		while ((idx = ret.Text.find('\n', idx + 1)) != std::string::npos) {
			++c;
		}
		ret.Size = {
			GetDrawStringWidthToHandle(text.data(), text.size(), *this),
			GetFontSizeToHandle(*this) * c
		};
		return ret;
	}

	static FontData Make(const std::string& path, int size, int thick, int edgesize = 0, size_t index = 0) {
		FontData font;
		
		font.Init(
			CreateFontToHandle(
				GetFontNameAndLoad(path, index).c_str(),
				size,
				thick,
				DX_FONTTYPE_ANTIALIASING_EDGE_4X4,
				DX_CHARSET_UTF8,
				edgesize
			)
		);
		font.SetCharCodeFormat(CodeFormat);

		return font;
	}

	static std::string GetFontNameAndLoad(std::string path, size_t index) {
		
		auto& gdi = GDIInitializer::GetInstance();
		auto& input = gdi.GetStartupInput();

		if (FontNameCollections.find(path) != FontNameCollections.end()) {
			if (index >= FontNameCollections[path].size()) {
				index = 0;
			}
			return FontNameCollections[path][index];
		}

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
		
		WCHAR familyName[LF_FACESIZE]{};
		families[index].GetFamilyName(familyName);

		std::vector<std::string> names;
		names.resize(familyCount);
		std::transform(families, families + familyCount, names.begin(), [](auto&& v) {
			WCHAR _familyName[LF_FACESIZE]{};
			v.GetFamilyName(_familyName);
			return wide_to_cp(_familyName, CodeFormat);;
			});

		free(families);

		FontNameCollections[path] = std::move(names);

		return wide_to_cp(familyName, CodeFormat);
	}

	static inline CharCodeFormat CodeFormat = UTF8;
	static inline std::unordered_map<std::string_view, std::vector<std::string>> FontNameCollections;
};


template<class T>
inline void DrawableString::Draw(const Val2D<T>& pos, const Val2D<float>& origin) {
	Val2D<float> offset = {
		origin.x * Size.x,
		origin.y * Size.y
	};
	if constexpr (std::is_integral_v<T>) {
		DrawStringToHandle(
			pos.x - offset.x,
			pos.y - offset.y,
			Text.data(),
			Font->Color,
			Font->GetRawHandle(),
			Font->EdgeColor
		);
	}
	else {
		DrawStringFToHandle(
			pos.x - offset.x,
			pos.y - offset.y,
			Text.data(),
			Font->Color,
			Font->GetRawHandle(),
			Font->EdgeColor
		);
	}
}