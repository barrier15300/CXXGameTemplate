#pragma once
#include "../Value/Value.h"

struct Polygon2D {

	Polygon2D() {
		Vertex[0].rhw = 1.f;
		Vertex[1].rhw = 1.f;
		Vertex[2].rhw = 1.f;
	}
	//Polygon2D() {}

	void SetPos(const Val2D<float> &p1, const Val2D<float> &p2, const Val2D<float> &p3) {
		Vertex[0].pos.x = p1.x;
		Vertex[0].pos.y = p1.y;
		Vertex[1].pos.x = p2.x;
		Vertex[1].pos.y = p2.y;
		Vertex[2].pos.x = p3.x;
		Vertex[2].pos.y = p3.y;
	}
	void SetColor(const Color3 &c1, const Color3 &c2, const Color3 &c3) {
		Vertex[0].dif = c1;
		Vertex[1].dif = c2;
		Vertex[2].dif = c3;
	}

	void Draw() {
		DrawPolygon2D(
			Vertex,
			1,
			DX_NONE_GRAPH,
			Alpha
		);
	}

	bool Alpha = true;
	VERTEX2D Vertex[3]{};
};