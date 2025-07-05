#pragma once
#include "../Helper/Helper.h"

struct SoundData : public DXHandle<DXHandleType::Sound, DeleteSoundMem> {

	using DXHandle::DXHandle;

	enum class DataType {
		Stable = DX_SOUNDDATATYPE_MEMNOPRESS,
		DataStreamPlus = DX_SOUNDDATATYPE_MEMNOPRESS_PLUS,
		DataStream = DX_SOUNDDATATYPE_MEMPRESS,
		FileStream = DX_SOUNDDATATYPE_FILE,
	};

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
	/// Factory
	/// 
	
	static SoundData Make(const std::string &path, DataType type, int buffernum = 3) {
		SoundData ret;
		SetCreateSoundDataType(static_cast<int>(type));
		ret.Init(LoadSoundMem(path.c_str(), buffernum));
		SetCreateSoundDataType(static_cast<int>(DataType::Stable));
		return ret;
	}

	static SoundData Make(const std::string &path, int buffernum = 3) {
		SoundData ret = Make(path, DataType::Stable, buffernum);
		return ret;
	}

	bool TopPositionPlay = true;

};
