#pragma once

#include <vector>

struct Cube
{
public:
	std::vector<VertexData> Vertices =
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

	std::vector<uint32_t> Indices = {
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