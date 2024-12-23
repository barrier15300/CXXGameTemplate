#pragma once
#include "../Helper/DXHandle.h"

struct SoundData : public DXHandle<DXHandleType::Sound> {

	using DXHandle::DXHandle;

	enum class DataType {
		Stable = DX_SOUNDDATATYPE_MEMNOPRESS,
		DataStreamPlus = DX_SOUNDDATATYPE_MEMNOPRESS_PLUS,
		DataStream = DX_SOUNDDATATYPE_MEMPRESS,
		Stream = DX_SOUNDDATATYPE_FILE,
	};

	bool Create(const std::string &path, int buffernum = 3) {

		*this = LoadSoundMem(path.c_str(), buffernum);

		return true;
	}

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

	static void SetDataType(DataType type) {
		SetCreateSoundDataType(static_cast<int>(type));
	}

	bool TopPositionPlay = false;

private:
	int InitImpl() {
		DeleteSoundMem(m_Handle);
	}
};
