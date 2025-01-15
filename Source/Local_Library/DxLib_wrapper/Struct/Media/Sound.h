#pragma once
#include "../Helper/DXHandle.h"

struct SoundData : public DXHandle<DXHandleType::Sound> {

	using DXHandle::DXHandle;

	enum class DataType {
		Stable = DX_SOUNDDATATYPE_MEMNOPRESS,
		DataStreamPlus = DX_SOUNDDATATYPE_MEMNOPRESS_PLUS,
		DataStream = DX_SOUNDDATATYPE_MEMPRESS,
		FileStream = DX_SOUNDDATATYPE_FILE,
	};

	/// 
	/// Data Create
	/// 
	bool Create(const std::string &path) {

		*this = LoadSoundMem(path.c_str());

		return !IsNull();
	}

	bool Create(const std::string &path, int buffernum) {

		*this = LoadSoundMem(path.c_str(), buffernum);

		return !IsNull();
	}

	/// 
	/// Data Use
	/// 
	void Play() {
		PlaySoundMem(m_Handle, DX_PLAYTYPE_BACK, TopPositionPlay);
	}

	bool IsPlay() {
		return CheckSoundMem(m_Handle);
	}

	void Stop() {
		StopSoundMem(m_Handle);
	}

	void SetVolume(float pal) {
		SetVolumeSoundMem(std::log(1 + (pal / 10)) * 10000, m_Handle);
	}

	/// 
	/// Base Data
	/// 
	static void SetDataType(DataType type) {
		SetCreateSoundDataType(static_cast<int>(type));
	}

	bool TopPositionPlay = false;

private:
	int InitImpl() {
		DeleteSoundMem(m_Handle);
	}
};
