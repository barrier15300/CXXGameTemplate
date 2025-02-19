#pragma once
#include "DxLib.h"


#include <filesystem>
#include <memory>
#include <string>


#pragma region MMEAPIwrapper

#include <Audiopolicy.h>
#include <MMDeviceAPI.h>
#include <psapi.h>
/// <summary>
/// base code
/// https://resemblances.click3.org/product_list/index.cgi/detail/87
/// </summary>

inline void CheckError(HRESULT hr) {
	if (!FAILED(hr)) {
		return;
	}
	auto message = std::system_category().message(hr);
	MessageBox(NULL, message.c_str(), TEXT("System Error"), MB_OK);
	::ExitProcess(1);
}

class ComBase {
private:
	static inline unsigned int counter = 0;
	static inline bool initialized = false;
protected:
	class ReleaseCom {
	public:
		void operator()(IUnknown *const ptr) {
			ptr->Release();
		}
	};
	static HRESULT CoCreateInstance(REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv) {
		if (!initialized) {
			::CoInitialize(nullptr);
			initialized = true;
		}
		return ::CoCreateInstance(rclsid, nullptr, CLSCTX_INPROC_SERVER, riid, ppv);
	}
public:
	ComBase() {
		counter++;
	}
	~ComBase() {
		counter--;
		if (counter == 0) {
			::CoUninitialize();
		}
	}
};

template<typename ComInterface>
class Com : public ComBase {
protected:
	std::unique_ptr<ComInterface, ReleaseCom> ptr;
public:
	Com(ComInterface *const raw) {
		ptr = std::unique_ptr<ComInterface, ReleaseCom>(raw);
	}
	ComInterface *operator&() {
		return ptr.get();
	}
};

template<typename ComInterface, typename UUIDOFType = ComInterface>
class ComCCI : public Com<ComInterface> {
private:
	static ComInterface *create() {
		ComInterface *raw;
		const HRESULT hr = ComBase::CoCreateInstance(__uuidof(UUIDOFType), IID_PPV_ARGS(&raw));
		CheckError(hr);
		return raw;
	}
public:
	ComCCI() : Com<ComInterface>(create()) {}
};

class SimpleAudioVolume : public Com<ISimpleAudioVolume> {
public:
	SimpleAudioVolume(ISimpleAudioVolume *const raw) : Com<ISimpleAudioVolume>(raw) {}
	void Set(const float value) {
		const HRESULT hr = ptr->SetMasterVolume(value, nullptr);
		CheckError(hr);
	}
	float Get() {
		float result;
		const HRESULT hr = ptr->GetMasterVolume(&result);
		CheckError(hr);
		return result;
	}
};

class AudioSessionControl : public Com<IAudioSessionControl2> {
private:
	class HandleCloser {
	public:
		void operator()(void *ptr) {
			::CloseHandle(reinterpret_cast<HANDLE>(ptr));
		}
	};
public:
	AudioSessionControl(IAudioSessionControl2 *const raw) : Com<IAudioSessionControl2>(raw) {}
	DWORD GetProcessId() {
		DWORD result;
		const HRESULT hr = ptr->GetProcessId(&result);
		CheckError(hr);
		return result;
	}
	std::filesystem::path GetProcessImageFilePath() {
		const DWORD processId = GetProcessId();
		const HANDLE processHandleRaw = ::OpenProcess(PROCESS_QUERY_INFORMATION, false, processId);
		std::unique_ptr<void, HandleCloser> processHandle(processHandleRaw);
		wchar_t path[MAX_PATH];
		::GetProcessImageFileNameW(processHandle.get(), path, _countof(path));
		return path;
	}
	std::wstring GetDisplayName() {
		wchar_t *result;
		const HRESULT hr = ptr->GetDisplayName(&result);
		CheckError(hr);
		return result;
	}
	SimpleAudioVolume GetVolumeInstance() {
		ISimpleAudioVolume *result;
		const HRESULT hr = ptr->QueryInterface(&result);
		CheckError(hr);
		return SimpleAudioVolume(result);
	}
	void SetVolume(const float value) {
		GetVolumeInstance().Set(value);
	}
	float GetVolume() {
		return GetVolumeInstance().Get();
	}
};

class AudioSessionControlOld : public Com<IAudioSessionControl> {
public:
	AudioSessionControlOld(IAudioSessionControl *const raw) : Com<IAudioSessionControl>(raw) {}
	AudioSessionControl Convert() {
		IAudioSessionControl2 *result;
		const HRESULT hr = ptr->QueryInterface(&result);
		CheckError(hr);
		return AudioSessionControl(result);
	}
};

class AudioSessionEnumerator : public Com<IAudioSessionEnumerator> {
private:
	unsigned int count;
	unsigned int GetCountRaw() {
		int result;
		const HRESULT hr = ptr->GetCount(&result);
		CheckError(hr);
		return static_cast<unsigned int>(result);
	}
	class Iterator {
	private:
		AudioSessionEnumerator &ptr;
		unsigned int index;
	public:
		Iterator(AudioSessionEnumerator &ptr, const unsigned int index) : ptr(ptr), index(index) {}
		AudioSessionControl operator*() {
			return ptr.GetSession(index);
		}
		void operator++() {
			index++;
		}
		bool operator!=(const Iterator &other) const {
			return index != other.index;
		}
		bool operator==(const Iterator &other) const {
			return index == other.index;
		}
	};
public:
	AudioSessionEnumerator(IAudioSessionEnumerator *const raw) : Com<IAudioSessionEnumerator>(raw) {
		count = GetCountRaw();
	}
	AudioSessionControl GetSession(const unsigned int index) {
		IAudioSessionControl *result;
		const HRESULT hr = ptr->GetSession(index, &result);
		CheckError(hr);
		return AudioSessionControlOld(result).Convert();
	}
	unsigned int GetCount() const {
		return count;
	}
	Iterator begin() {
		return Iterator(*this, 0);
	}
	Iterator end() {
		return Iterator(*this, GetCount());
	}
};

class AudioSessionManager : public Com<IAudioSessionManager2> {
public:
	AudioSessionManager(IAudioSessionManager2 *const raw) : Com<IAudioSessionManager2>(raw) {}
	AudioSessionEnumerator GetSessionEnumerator() {
		IAudioSessionEnumerator *result;
		const HRESULT hr = ptr->GetSessionEnumerator(&result);
		CheckError(hr);
		return AudioSessionEnumerator(result);
	}
};

class MMDevice : public Com<IMMDevice> {
public:
	MMDevice(IMMDevice *const raw) : Com<IMMDevice>(raw) {}
	AudioSessionManager ActivateSessionManager() {
		IAudioSessionManager2 *result;
		const HRESULT hr = ptr->Activate(__uuidof(IAudioSessionManager2), CLSCTX_INPROC_SERVER, nullptr, reinterpret_cast<void **>(&result));
		CheckError(hr);
		return AudioSessionManager(result);
	}
};

class MMDeviceEnumerator : public ComCCI<IMMDeviceEnumerator, MMDeviceEnumerator> {
public:
	MMDevice GetDefaultAudioEndpoint(EDataFlow flow, ERole role) {
		IMMDevice *result;
		const HRESULT hr = ptr->GetDefaultAudioEndpoint(flow, role, &result);
		CheckError(hr);
		return MMDevice(result);
	}
};

#pragma endregion

class SoundDevice {
	static inline MMDeviceEnumerator deviceenumerator{};
	static inline MMDevice device = deviceenumerator.GetDefaultAudioEndpoint(EDataFlow::eRender, ERole::eMultimedia);
	static inline SimpleAudioVolume volume = [&]() {
		auto enumrator = device.ActivateSessionManager().GetSessionEnumerator();
		for (auto ctrl : enumrator) {
			if (ctrl.GetProcessId() == ::GetCurrentProcessId()) {
				return ctrl.GetVolumeInstance();
			};
		}
		return enumrator.GetSession(0).GetVolumeInstance();
	}();

public:

	enum SoundDeviceType : int {
		None = 0,
		WASAPI,
		XAudio,
		MMEwaveOut,
		ASIO
	};

	void SetVolume(float pal) {
		volume.Set(pal);
	}

	static void SetDevice(SoundDeviceType type, bool exclusive, int bufsize, int samplerate) {
		int ns = (size_t)10000000 * bufsize / samplerate;
		switch (type) {
			case SoundDeviceType::WASAPI:
				SetEnableWASAPIFlag(TRUE, exclusive, ns, samplerate);
				break;
			case SoundDeviceType::XAudio:
				SetEnableXAudioFlag(TRUE);
				break;
			case SoundDeviceType::MMEwaveOut:
				SetEnableMMEwaveOutFlag(TRUE, bufsize, samplerate);
				break;
			case SoundDeviceType::ASIO:
				SetEnableASIOFlag(TRUE, bufsize, samplerate);
				break;
			default:
				SetDevice(SoundDeviceType::WASAPI, exclusive, bufsize, samplerate);
				break;
		}
	}
};