#pragma once
#include "../Media/Graph.h"
#include "../Value/Value.h"

struct Vertex2D {

	Vertex2D() {}
	Vertex2D(const Val2D<float>& pos,float rhw,const Color4& dif,const Val2D<float>& uv) :
		pos(pos), rhw(rhw), dif(dif), uv(uv) {}
	Vertex2D(const VERTEX2D& from) {
		pos = Val2D<float>(from.pos.x, from.pos.y);
		rhw = from.rhw;
		dif = Color4(from.dif);
	}

	operator VERTEX2D() const {
		VERTEX2D ret;
		ret.pos.x = pos.x;
		ret.pos.y = pos.y;
		ret.rhw = rhw;
		ret.dif = dif;
		ret.u = uv.x;
		ret.v = uv.y;
		return ret;
	}

	union {
		Val2D<float> pos;
		std::array<float,3> _arr{};
	};
	float rhw{};
	Color4 dif{};
	Val2D<float> uv{};
};

struct IndexedVertex2D {

	IndexedVertex2D() {}
	IndexedVertex2D(size_t vertexsize, size_t indexsize) {
		vertex.resize(vertexsize);
		index.resize(indexsize);
	}

	std::vector<Vertex2D> vertex;
	std::vector<unsigned short> index;

	void Draw() const {
		DrawPolygonIndexed2D((VERTEX2D*)vertex.data(), vertex.size(), index.data(), index.size(), DX_NONE_GRAPH, TRUE);
	}
};

namespace Vertex {

namespace Factory2D {

static IndexedVertex2D RectAngle(const Val2D<float>& size, const Val2D<float>& pos, const Color4& color) {
	IndexedVertex2D ret(4, 6);
	ret.vertex[0].pos = pos;
	ret.vertex[1].pos = pos + Val2D<float>(size.x,0);
	ret.vertex[2].pos = pos + size;
	ret.vertex[3].pos = pos + Val2D<float>(0,size.y);
	for(auto& v : ret.vertex) {
		v.rhw = 1;
		v.dif = color;
		v.uv = {};
	}
	ret.index = {0,1,2,2,3,0};
	return ret;
}

static IndexedVertex2D Circle(const Val2D<float>& size, const Val2D<float>& pos, const Color4& color, unsigned short vertexnum = 3) {
	IndexedVertex2D ret(vertexnum + 1, vertexnum * 3);
	for(size_t i = 0; i < vertexnum; ++i) {
		Vertex2D& v = ret.vertex[i];
		float rad = 2 * pi * (i / (float)vertexnum);
		v.pos = Val2D<float>(cos(rad), sin(rad)) * size + pos;
		v.rhw = 1;
		v.dif = color;
		v.uv = {};
		ret.index[i * 3] = vertexnum;
		ret.index[i * 3 + 1] = i;
		ret.index[i * 3 + 2] = i + 1;
	}

	ret.vertex[vertexnum].pos = pos;
	ret.vertex[vertexnum].rhw = 1;
	ret.vertex[vertexnum].dif = color;
	ret.vertex[vertexnum].uv = {};
	
	ret.index[(vertexnum - 1) * 3 + 2] = 0;

	return ret;
}

static IndexedVertex2D Line(const Val2D<float>& p1, const Val2D<float>& p2, const Color4& color, float thickness = 1.f) {
	IndexedVertex2D ret(4, 6);
	Val2D<float> distance = p2 - p1;
	float half = thickness / 2;
	float rad = distance.Angle();
	Val2D<float> v{-half * sin(rad), half * cos(rad)};
	ret.vertex[0].pos = p1 + -v;
	ret.vertex[1].pos = p2 + -v;
	ret.vertex[2].pos = p2 + v;
	ret.vertex[3].pos = p1 + v;
	ret.index = {0,1,2,2,3,0};
	for(auto& v : ret.vertex) {
		v.rhw = 1;
		v.dif = color;
		v.uv = {};
	}
	return ret;
}

} // namespace Factory

} // namespace Polygon