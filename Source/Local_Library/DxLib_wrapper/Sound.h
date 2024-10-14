#pragma once
#include "DxLib.h"
#include "Struct.h"
#include <string>
#include <utility>
#include <unordered_map>

using SoundHandle = DXHandle<DXHandleType::Sound>;
using SoftSoundHandle = DXHandle<DXHandleType::SoftSound>;

struct SoftSound;

struct SoundData {

	SoundData() {}
	~SoundData() {
		Delete();
	}
	
	enum PlayType {
		Normal = DX_PLAYTYPE_NORMAL,
		BackGround = DX_PLAYTYPE_BACK,
		Loop = DX_PLAYTYPE_LOOP
	};

	enum DataType {
		Load = DX_SOUNDDATATYPE_MEMNOPRESS,
		StreamOfMemStore = DX_SOUNDDATATYPE_MEMNOPRESS_PLUS,
		StreamOfMem = DX_SOUNDDATATYPE_MEMPRESS,
		FileStream = DX_SOUNDDATATYPE_FILE,
	};

	bool Create(std::string filepath, DataType datatype = s_defaultDataType, int buffersize = 3) {
		auto a = setdatatype(datatype);
		m_Handle = LoadSoundMem(filepath.c_str(), buffersize);
		if (m_Handle == -1) {
			return false;
		}
		s_Data.Regist(m_Handle, m_Volume);
		return true;
	}

	bool Create(SoftSoundHandle handle, int buffersize = 3) {
		m_Handle = LoadSoundMemFromSoftSound(handle, buffersize);
		if (m_Handle == -1) {
			return false;
		}
		s_Data.Regist(m_Handle, m_Volume);
		return true;
	}

	void Delete() {
		if (m_Handle == -1) {
			return;
		}
		s_Data.Delete(m_Handle);
		DeleteSoundMem(m_Handle);
		m_Handle = -1;
	}

	void Play() const {
		PlaySoundMem(m_Handle, m_PlayType);
	}

	void SetVolume(float volume) {
		m_Volume = volume;
		__SetVolumeSoundMem(m_Handle, m_Volume, s_Data.GetSharedVolume(s_Data.findhandlefortag(m_Handle)));
	}

	static void SetSharedVolume(float volume, const std::string& astag = "") {
		bool emptyflag = astag.empty();
		size_t hash = s_Data.hasher(astag);
		s_Data.SetSharedVolume(volume, hash);
		for (auto &&[handle, vat] : s_Data.Handles) {
			if (emptyflag || hash == vat.second) {
				__SetVolumeSoundMem(
					handle,
					volume,
					*vat.first
				);
			}
		}
	}
	static float GetSharedVolume(const std::string &tag = "") { return s_Data.GetSharedVolume(s_Data.hasher(tag)); }

	const SoundHandle &GetHandle() const {
		return m_Handle;
	}

private:

	SoundHandle m_Handle = -1;
	float m_Volume = 1;
	
	PlayType m_PlayType = s_defaultPlayType;
	inline static constexpr PlayType s_defaultPlayType = BackGround;
	DataType m_DataType = s_defaultDataType;
	inline static constexpr DataType s_defaultDataType = Load;

	struct setdatatype {
		setdatatype(DataType datatype) {
			SetCreateSoundDataType(datatype);
		}
		~setdatatype() {
			SetCreateSoundDataType(Load);
		}
	};

	inline static struct {
		std::hash<std::string_view> hasher;
		std::unordered_map<SoundHandle, std::pair<float *, size_t>> Handles{};
		std::unordered_map<size_t, float> SharedVolumes{{hasher(""), 1}};
		void Regist(SoundHandle handle, float &volume, const std::string &tag = "") {
			size_t hash = hasher(tag);
			Handles[handle] = {&volume, hash};
			if (!tag.empty()) {
				SharedVolumes[hash] = 1;
			}
		}
		void Delete(SoundHandle handle) {
			Handles.erase(handle);
		}
		bool findkey(size_t key) { return SharedVolumes.find(key) != SharedVolumes.end(); }
		size_t findhandlefortag(SoundHandle handle) {
			return Handles[handle].second;
		}
		void SetSharedVolume(float volume, size_t key) {
			if (findkey(key)) {
				SharedVolumes[key] = volume;
			}
		}
		float GetSharedVolume(size_t key) {
			if (findkey(key)) {
				return SharedVolumes[key];
			}
			return 0;
		}
	} s_Data{};

	static void __SetVolumeSoundMem(SoundHandle handle, float handleval, float sharedval) {
		SetVolumeSoundMem(
			std::pow(handleval * sharedval, 0.25) * 10000,
			handle
		);
	}
};

struct SoftSoundData {

	template<class... Args>
	SoftSoundData(Args &&...args) {
		Create(std::forward<Args>(args)...);
	}
	~SoftSoundData() {}

	bool Create(int channel, int bit, int samplerate, LONGLONG length, bool isfloat = false) {
		m_Handle = MakeSoftSoundCustom(channel, bit, samplerate, length, isfloat);
		if (m_Handle == -1) {
			return false;
		}
		return true;
	}

	bool Create(std::string filepath) {
		m_Handle = LoadSoftSound(filepath.c_str());
		if (m_Handle == -1) {
			return false;
		}
		DX_HANDLETYPE_GRAPH;
		return true;
	}

	void Delete() {
		DeleteSoftSound(m_Handle);
		m_Handle = -1;
	}



private:

	SoftSoundHandle m_Handle = -1;

};
