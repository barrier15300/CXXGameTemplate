#pragma once
#include "../Include.hpp"

class Game : public IObjectBase {
public:
	
	virtual bool Init();
	virtual void Proc();
	virtual void Draw();
	virtual void End();

	std::string Title = "Game";
	Val2D<int> ScreenSize{1280, 720};
	int ColorBit = 32;

	struct {
		Config::Value<bool,	"System/FullScreen"> FullScreenFlag{false};
		Config::Value<bool,	"System/VSync"> VSyncFlag{true};
	} System;

	struct {
		struct {
			Config::Value<std::string,	"Sound/Device/Type"> Type{"WASAPI"};
			Config::Value<bool,			"Sound/Device/Exclusive"> ExclusiveFlag{false};
			Config::Value<int,			"Sound/Device/BufferSize"> BufferSize{480};
			Config::Value<int,			"Sound/Device/SampleRate"> SampleRate{192000};
		} Device;
		Config::Value<float, "Sound/Mastar"> Mastar{0.5f};
	} Sound;
};