#pragma once
#include "DxLib.h"
#include "Struct.h"

using FontHandle = DXHandle<DXHandleType::Font>;

struct FontData {

	FontData() {}
	~FontData() {}

	void Create(const std::string &filepath) {
		FontHash = unique_fontdata.Regist(filepath);
	}

	void Delete() {
		unique_fontdata.Delete(FontHash);
	}

	FontHandle Handle = -1;

private:

	size_t FontHash = 0;

	static struct {
		size_t Regist(const std::string &filepath) {
			size_t FilepathHash = hasher(filepath);
			HANDLE rawhandle = AddFontFile(filepath.c_str());
			if (unique_fonts.find(FilepathHash) == unique_fonts.end()) {
				unique_fonts[FilepathHash] = rawhandle;
			}
			else {
				Delete(FilepathHash);
				Regist(filepath);
			}
			return FilepathHash;
		}

		void Delete(const size_t hash) {
			auto it = unique_fonts.find(hash);
			if (it != unique_fonts.end()) {
				RemoveFontFile((*it).second);
				unique_fonts.erase(hash);
			}
		}

	private:
		std::unordered_map<size_t, HANDLE> unique_fonts;
		std::hash<std::string> hasher;
	} unique_fontdata;
};
