#pragma once
#include"IndexedTriangleList.h"
#include "DrawableBase.h"

class Rect
{
public:
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		namespace dx = DirectX;

		constexpr float halfSide = 1.0f / 2.0f;

		std::vector<dx::XMFLOAT3> vertices;
		vertices.emplace_back(-halfSide, -halfSide, -15.0f);
		vertices.emplace_back(halfSide, -halfSide, -15.0f);
		vertices.emplace_back(-halfSide, halfSide, -15.0f);
		vertices.emplace_back(halfSide, halfSide, -15.0f);

		std::vector<V> verts(vertices.size());
		for (size_t i = 0; i < vertices.size(); i++)
		{
			verts[i].pos = vertices[i];
		}

		return {
			std::move(verts),{
			0, 2, 1,
			2, 3, 1,
			}
		};
	}
};

