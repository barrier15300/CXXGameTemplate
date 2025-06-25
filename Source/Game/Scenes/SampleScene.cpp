#include "SampleScene.h"
#include "Wips/function_ref.h"

bool SampleScene::Init() {
	Graph = GraphData::Make("Asset/coursesymbol_easy.png");
	
	Don = SoundData::Make(Donfilepath);
	Ka = SoundData::Make(Kafilepath);

	Input.Mouse.Lock();

	Scene->Regist<FunctionRefTest>();

	return true;
}

void SampleScene::Proc() {

	auto a = 45 / (90. * 16);

	angle += a;

	if (Input.Keyboard[Keys::A].Down()) {
		angle -= a;
	}
	
	if (Input.Keyboard[Keys::D].Down()) {
		angle += a;
	}

	if (Input.Keyboard[Keys::Up].Down()) {
		idx += 1;
	}

	if (Input.Keyboard[Keys::Down].Down()) {
		idx -= 1;
	}

	return;
}

void SampleScene::Draw() {

	Val2D<float> off = { 640, 360 };
	Val2D<float> size = { 512, 512 };

	Rect2D<float> rect = { off - size / 2, size };

	auto center = rect.MidCenter();

	std::vector<IndexedVertex2D> vList;

	for (size_t i = 0; i < 1024; ++i) {
		vList.push_back(Vertex::Factory2D::RectAngle(rect.LeftTop(), rect.RightBottom(), { 255,255,255,255 }));
	}

	idx.SetMax(vList.size() - 1);

	float thickness = 3.f;

	auto convangle = [](float angle) {
		angle = std::fmod(angle, 90);
		if (angle < 0) {
			angle = 90 + angle;
		}
		return angle / 180 * mathcv::pi;
		};

	vList[0].Framed(thickness).Draw();

	auto r = 1.;

	Val2D<float> poses[4]{};
	std::transform(vList[0].vertex.begin(), vList[0].vertex.end(), poses, [&](auto&& v) {
		return v.pos;
		});
	
	for (size_t i = 0; i < vList.size(); ++i) {
		auto&& vl = vList[i];
		bool f = (i == (size_t)idx);
		Color4 color = f ? Color4{0, 255, 0, 255} : Color4{ 255, 255, 255, 255 };
		for (size_t j = 0; auto&& v : vl.vertex) {
			auto vec = poses[j] - center;
			auto rot = vec.Rotate(convangle(angle));
			auto sized = rot * (1 / std::cos(mathcv::pi / 4 - convangle(angle))) / std::sqrt(2);

			v.pos = sized + center;
			v.color = color;
			poses[j] = sized + center;
			j++;
		}
		vl.Framed(thickness).Draw();
	}

	auto vec = (vList[idx].vertex[0].pos - center);
	auto len = vec.Length();
	auto line = len / std::sqrt(2) * 2;
	auto fmtstr = fmt::format("\nidx: {}\nV2D: {}\nLength: {}\nLine: {}\nAngle: {}", idx.ToString(), vec.ToString(), len, line, convangle(angle * ((size_t)idx + 1)));

	if (Input.Keyboard[Keys::N].Down()) {
		SetClipboardText(fmt::format("{}", angle * ((size_t)idx + 1)).c_str());
	}
	if (Input.Keyboard[Keys::M].Down()) {
		SetClipboardText(fmt::format("{}", line).c_str());
	}

	printFPS();
	DrawString(0, 0, fmtstr.c_str(), Color3{ 255,255,255 });

	return;
}

void SampleScene::End() {
	return;
}
