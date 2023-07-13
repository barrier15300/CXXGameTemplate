#include "O_Sample.h"

void O_Sample::Init() {
	image.Load(SPRITE.GetSpriteDatas());

	image.pos.x = 640;
	image.pos.y = 360;
}

void O_Sample::Update() {

}

void O_Sample::Draw() {
	image.Draw();
}

void O_Sample::End() {

}

