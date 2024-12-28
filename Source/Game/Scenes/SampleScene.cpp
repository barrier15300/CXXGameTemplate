#include "SampleScene.h"

bool SampleScene::Init() {
	//Don.Create(Donfilepath);
	//Ka.Create(Kafilepath);
	return true;
}

void SampleScene::Proc() {
	auto &&pos = this->pos.Get();

	InputState inputs[4] = {
		Input.Keyboard()[Keys::D],
		Input.Keyboard()[Keys::F],
		Input.Keyboard()[Keys::J],
		Input.Keyboard()[Keys::K]
	};

	//if (inputs[0].Down()) {
	//	Ka.Play();
	//}
	//if (inputs[1].Down()) {
	//	Don.Play();
	//}
	//if (inputs[2].Down()) {
	//	Don.Play();
	//}
	//if (inputs[3].Down()) {
	//	Ka.Play();
	//}

	if (timer.Elapsed().Second() > 3) {
		timer.Reset();
	}
	if (Input.Keyboard()[Keys::Left].Down()) {
		timer.Start();
	}
	if (Input.Keyboard()[Keys::Down].Down()) {
		timer.Stop();
	}
	if (Input.Keyboard()[Keys::Right].Down()) {
		timer.Reset();
	}

	return;
}

void SampleScene::Draw() {

	input.Update((Input.Keyboard()[Keys::Up].Press()));
	auto [press, hold, release] = input.GetStates();

	double rate = Easing::GetRate(timer.Elapsed().Second() / std::numbers::e, Easing::Out, Easing::Cubic);
	double pirate = rate * 2 * PI;

	const Val2D<double> rotatevector[2] {
		{std::cos(pirate), std::sin(pirate) },
		{-std::sin(pirate), std::cos(pirate) }
	};

	Val2D<double> origin{300,300};
	double nm = 4;
	Val2D<double> p1{std::polar<double>(std::sqrt(2) * 100, (2 * PI) * (0.5 / nm))};
	Val2D<double> p2{std::polar<double>(std::sqrt(2) * 100, (2 * PI) * (1.5 / nm))};
	Val2D<double> p3{std::polar<double>(std::sqrt(2) * 100, (2 * PI) * (2.5 / nm))};
	Val2D<double> p4{std::polar<double>(std::sqrt(2) * 100, (2 * PI) * (3.5 / nm))};
	Color4 c1{0x00ff0000};
	Color4 c2{0x0000ff00};
	Color4 c3{0x000000ff};
	Color4 c4{0x00000000};
	
	p1 = rotatevector[0] * p1.x + rotatevector[1] * p1.y;
	p2 = rotatevector[0] * p2.x + rotatevector[1] * p2.y;
	p3 = rotatevector[0] * p3.x + rotatevector[1] * p3.y;
	p4 = rotatevector[0] * p4.x + rotatevector[1] * p4.y;
	
	Polygon2D polygon{};
	
	polygon.SetPos(origin + p1, origin + p2, origin + p3);
	polygon.SetColor(c1, c2, c3);
	polygon.Draw();
	
	polygon.SetPos(origin + p1, origin + p3, origin + p4);
	polygon.SetColor(c1, c3, c4);
	polygon.Draw();
	
	DrawFormatString(0, 0, Color3{255, 255, 255}, "p1: %s", p1.ToString().c_str());
	DrawFormatString(0, 0, Color3{255, 255, 255}, "\np2: %s", p2.ToString().c_str());
	DrawFormatString(0, 0, Color3{255, 255, 255}, "\n\np3: %s", p3.ToString().c_str());
	DrawFormatString(0, 0, Color3{255, 255, 255}, "\n\n\nc1: %s", c1.ToString(false).c_str());

	//DrawFormatString(0, 0, Color3{255, 255, 255}, "\npress: %x\nhold: %x\nrelease: %x\nfps: %d", press, hold, release, (int)GetFPS());
	//DrawFormatString(0, 0, Color3{255, 255, 255}, "\npress: %x", (byte)input.GetState());
	
	

	return;
}

void SampleScene::End() {
	return;
}
