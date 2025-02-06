#pragma once
#include "../Media/Graph.h"
#include "../Value/Value.h"

struct Vertex2D {

	Vertex2D() {}
	Vertex2D(const Val2D<float>& pos,float rhw,const Color4& dif,const Val2D<float>& uv) :
		pos(pos), rhw(rhw), color(dif), uv(uv) {}
	Vertex2D(const VERTEX2D& from) {
		pos = Val2D<float>(from.pos.x, from.pos.y);
		rhw = from.rhw;
		color = Color4(from.dif);
	}

	operator VERTEX2D() const {
		VERTEX2D ret;
		ret.pos.x = pos.x;
		ret.pos.y = pos.y;
		ret.rhw = rhw;
		ret.dif = color;
		ret.u = uv.x;
		ret.v = uv.y;
		return ret;
	}

	union {
		Val2D<float> pos;
		std::array<float, 3> _arr{};
	};
	float rhw = 1;
	Color4 color{};
	Val2D<float> uv{};
};

struct IndexedVertex2D {

	IndexedVertex2D() {}
	IndexedVertex2D(size_t vertexsize, size_t indexsize) {
		vertex.resize(vertexsize);
		index.resize(indexsize);
	}

	std::vector<Vertex2D> vertex;
	std::vector<unsigned int> index;

	void Draw(bool alpha = false) const {
		GraphData none;
		none.Init(DX_NONE_GRAPH);
		Draw(none, alpha);
	}

	void Draw(const GraphData &data, bool alpha = false) const {
		DrawPolygon32bitIndexed2D((VERTEX2D*)vertex.data(), vertex.size(), index.data(), index.size() / 3, data, alpha);
	}
};

namespace Vertex {

namespace Factory2D {

static IndexedVertex2D Line(const Val2D<float> &p1, const Val2D<float> &p2, const Color4& color, float thickness = 1.f) {
	IndexedVertex2D ret(4,6);
	float half = thickness / 2;
	Val2D<float> norm = (p2 - p1).Normalized();
	Val2D<float> v = norm.Rotate(norm.Angle() + pi / 2) * half;
	ret.vertex[0].pos = p1 + -v;
	ret.vertex[1].pos = p2 + -v;
	ret.vertex[2].pos = p2 + v;
	ret.vertex[3].pos = p1 + v;
	ret.index = {0,1,2,2,3,0};
	for (auto& v : ret.vertex) {
		v.color = color;
	}
	return ret;
}

static IndexedVertex2D Triangle(const Val2D<float> &p1, const Val2D<float> &p2, const Val2D<float> &p3, const Color4& color) {
	IndexedVertex2D ret(3, 3);
	ret.vertex[0].pos = p1;
	ret.vertex[1].pos = p2;
	ret.vertex[2].pos = p3;
	for (auto& v : ret.vertex) {
		v.color = color;
	}
	ret.index = {0,1,2};
	return ret;
}

static IndexedVertex2D RectAngle(const Val2D<float>& p1, const Val2D<float>& p2, const Color4& color) {
	IndexedVertex2D ret(4, 6);
	ret.vertex[0].pos = p1;
	ret.vertex[1].pos = {p2.x, p1.y};
	ret.vertex[2].pos = p2;
	ret.vertex[3].pos = {p1.x, p2.y};
	for (auto& v : ret.vertex) {
		v.color = color;
	}
	ret.index = {0,1,2,2,3,0};
	return ret;
}

static IndexedVertex2D RegulerPolygon(const Val2D<float>& size, const Val2D<float>& pos, const Color4& color, unsigned int vertexnum = 3, float angle = 0) {
	if (vertexnum < 3) {
		return RegulerPolygon(size, pos, color, 3);
	}

	IndexedVertex2D ret(vertexnum + 1, vertexnum * 3);
	for (size_t i = 0; i < vertexnum; ++i) {
		Vertex2D& v = ret.vertex[i];
		float rad = 2 * pi * (i / (float)vertexnum) + angle;
		v.pos = Val2D<float>(cos(rad), sin(rad)) * size + pos;
		v.color = color;
		ret.index[i * 3] = vertexnum;
		ret.index[i * 3 + 1] = i;
		ret.index[i * 3 + 2] = i + 1;
	}

	ret.vertex[vertexnum].pos = pos;
	ret.vertex[vertexnum].color = color;
	
	ret.index[(vertexnum - 1) * 3 + 2] = 0;

	return ret;
}

static IndexedVertex2D Circle(const Val2D<float> &size, const Val2D<float> &pos, const Color4 &color, unsigned int vertexnum = 16) {
	if (vertexnum < 16) {
		return RegulerPolygon(size, pos, color, 16);
	}
	return RegulerPolygon(size, pos, color, vertexnum);
}

static Val2D<float> __FramedImpl(const Val2D<float> &p1, const Val2D<float> &p2, const Val2D<float> &p3) {
	auto&& d1 = (p1 - p2).Normalized(), d2 = (p3 - p2).Normalized();
	double rad = Val2D<double>::Angle(d1, d2);
	return d1.Rotate(rad / 2) * (1 / cos(rad / 2));
}

static IndexedVertex2D Framed(const IndexedVertex2D &geometryVertex, float thickness = 1, size_t rIgnoreCount = 0) {
	IndexedVertex2D ret;
	size_t vertexnum = geometryVertex.vertex.size() - rIgnoreCount;
	float half = thickness / 2;
	
	ret.vertex.resize(vertexnum * 2);

	for(size_t i = 0; i < vertexnum; ++i) {
		auto&& v1 = geometryVertex.vertex[i];
		auto&& v2 = geometryVertex.vertex[(i + 1) % vertexnum];
		auto&& v3 = geometryVertex.vertex[(i + 2) % vertexnum];

		auto&& c = __FramedImpl(
			v1.pos,
			v2.pos,
			v3.pos
		) * half;

		size_t first = i * 2, second = i * 2 + 1;

		ret.vertex[first].pos = v2.pos + -c;
		ret.vertex[second].pos = v2.pos + c;

		ret.vertex[first].color = v1.color;
		ret.vertex[second].color = v1.color;
	}

	size_t polygonnum = ret.vertex.size();
	
	if (polygonnum < 1) [[unlikely]] {
		return ret;
	}

	ret.index.resize(polygonnum * 3);

	for (size_t i = 0, c = polygonnum / 2; i < c; ++i) {
		ret.index[(i * 6) + 0] = (i * 2 + 0) % polygonnum;
		ret.index[(i * 6) + 1] = (i * 2 + 1) % polygonnum;
		ret.index[(i * 6) + 2] = (i * 2 + 2) % polygonnum;
		ret.index[(i * 6) + 3] = (i * 2 + 3) % polygonnum;
		ret.index[(i * 6) + 4] = (i * 2 + 2) % polygonnum;
		ret.index[(i * 6) + 5] = (i * 2 + 1) % polygonnum;
	}

	return ret;
}

static IndexedVertex2D FrameIndexed(const IndexedVertex2D &geometryVertex, float thickness = 1, size_t rIgnoreCount = 0) {
	IndexedVertex2D ret;
	size_t vertexnum = geometryVertex.vertex.size() - rIgnoreCount;
	float half = thickness / 2;

	for (size_t i = 0; i < vertexnum; ++i) {

	}

	return ret;
}

} // namespace Factory

} // namespace Polygon