#pragma once
#include "../Include.hpp"

class Game : public IObjectBase {
public:
	Game() { Name = __func__; }
	IObjectBase* ObjectInit() { return new Game(); }
	
	virtual bool Init();
	virtual void Proc();
	virtual void Draw();
	virtual void End();

	Val2D<int> ScreenSize{1280, 720};
	int ColorBit = 32;

	struct {
		decltype(Config)::Value<"System/FullScreen", bool> FullScreenFlag{false};
		decltype(Config)::Value<"System/VSync", bool> VSyncFlag{true};
	} System;

	struct {
		struct {
			decltype(Config)::Value<"Sound/Device/Type", std::string> Type{"WASAPI"};
			decltype(Config)::Value<"Sound/Device/Exclusive", bool> ExclusiveFlag{false};
			decltype(Config)::Value<"Sound/Device/BufferSize", int> BufferSize{480};
			decltype(Config)::Value<"Sound/Device/SampleRate", int> SampleRate{192000};
		} Device;
		decltype(Config)::Value<"Sound/Mastar", float> Mastar{0.5f};
	} Sound;
};