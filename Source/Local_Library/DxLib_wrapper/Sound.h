#pragma once
#include "DxLib.h"
#include "Struct.h"
#include <cmath>
#include <string>
#include <unordered_map>
#include <utility>

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
		return true;
	}

	bool Create(SoftSoundHandle handle, int buffersize = 3) {
		m_Handle = LoadSoundMemFromSoftSound(handle, buffersize);
		if (m_Handle == -1) {
			return false;
		}
		return true;
	}

	void Delete() {
		if (m_Handle == -1) {
			return;
		}
		DeleteSoundMem(m_Handle);
		m_Handle = -1;
	}

	void Play() const {
		PlaySoundMem(m_Handle, m_PlayType);
	}

	void SetVolume(float volume) {
		m_Volume = volume;
		__SetVolumeSoundMem(m_Handle, m_Volume);
	}
	float GetVolume() const {
		return m_Volume;
	}

	const SoundHandle GetHandle() const {
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

	static void __SetVolumeSoundMem(SoundHandle handle, float val) {
		SetVolumeSoundMem(
			std::pow(val, 0.25) * 10000,
			handle
		);
	}
};

struct SoftSoundData {

	SoftSoundData() {}
	~SoftSoundData() {
		Delete();
	}

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
		return true;
	}

	void Delete() {
		DeleteSoftSound(m_Handle);
		m_Handle = -1;
	}

private:

	SoftSoundHandle m_Handle = -1;

};
