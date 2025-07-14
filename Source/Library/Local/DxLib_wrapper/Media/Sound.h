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
		return Check(CheckSoundMem(m_Handle));
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

struct SoftSoundData : public DXHandle<DXHandleType::SoftSound, DeleteSoftSound> {

	using DXHandle::DXHandle;

	///
	/// Data Use
	/// 

	int GetChannel() const {
		return Format.channel;
	}
	
	int GetFrequency() const {
		return Format.samplePerSec;
	}

	int GetBitPerSample() const {
		return Format.bitPerSample;
	}

	bool IsFloatType() const {
		return Format.isFloatType != 0;
	}

	size_t GetSampleNum() const {
		return GetSoftSoundSampleNum(*this);
	}

	template<class T = int16_t>
	std::span<T> GetSamples() const {
		auto begin = reinterpret_cast<T*>(GetSoftSoundDataImage(*this));
		return std::span<T>(begin, GetSampleNum());
	}

	void _UpdateFormat() {
		GetSoftSoundFormat(*this, &Format.channel, &Format.bitPerSample, &Format.samplePerSec, &Format.isFloatType);
	}

	///
	/// Factory
	///

	static SoftSoundData Make(const std::string &path) {
		SoftSoundData ret;
		ret.Init(LoadSoftSound(path.c_str()));
		ret._UpdateFormat();
		return ret;
	}

	static SoftSoundData Make(int channel, int bitPerSample, int samplePerSec, size_t sampleNum, bool isFloatType = false) {
		SoftSoundData ret;
		ret.Init(MakeSoftSoundCustom(channel, bitPerSample, samplePerSec, sampleNum, isFloatType));
		ret._UpdateFormat();
		return ret;
	}

private:

	struct SoundFormat {
		int channel = -1;
		int bitPerSample = -1;
		int samplePerSec = -1;
		int isFloatType = -1;
	} Format{};
};
