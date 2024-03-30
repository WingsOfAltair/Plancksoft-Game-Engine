#pragma once

#include <vector>
#include <Object/Object.h>

class Cube : public Object
{
public:

	Cube(std::vector<VertexData> vertices, std::vector<uint32_t> indices, XMFLOAT3 startingPosition, XMFLOAT3 startingRotation, XMFLOAT3 startingScale) : Object(vertices, indices, startingPosition, startingRotation, startingScale) {
		
	}

	static inline const std::vector<VertexData> Vertices =
	{
		{ {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f } },
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f } },
		{ {0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f } },
		{ {0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f } },

		{ {-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 1.0f, 1.0f } },
		{ {-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f } },
		{ {0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f } },
		{ {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 1.0f } },
	};

	static inline const std::vector<uint32_t> Indices = {
		// Front face
	   0, 1, 2,
	   0, 2, 3,

	   // Back face
	   4, 6, 5,
	   4, 7, 6,

	   // Top face
	   1, 5, 6,
	   1, 6, 2,

	   // Bottom face
	   0, 3, 7,
	   0, 7, 4,

	   // Left face
	   3, 2, 6,
	   3, 6, 7,

	   // Right face
	   0, 4, 5,
	   0, 5, 1
	};
};