#include "Cube.h"

Cube::Cube()
{
    mVertices =
    {
        // Front face
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},  // 0
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},   // 1
        {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},    // 2
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},   // 3

        // Back face
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},  // 4
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}}, // 5
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},  // 6
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}}    // 7
    };

    mIndices =
    {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Right face
        1, 4, 7,
        7, 2, 1,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        5, 0, 3,
        3, 6, 5,

        // Top face
        3, 2, 7,
        7, 6, 3,

        // Bottom face
        5, 4, 1,
        1, 0, 5
    };

	InitBuffer();
}

void Cube::Update()
{
}
