#include <vector>
#include <Object/Object.h>

class Triangle : public Object
{
public:

    Triangle(std::vector<VertexData> vertices, std::vector<uint32_t> indices, XMFLOAT3 startingPosition, XMFLOAT3 startingRotation, XMFLOAT3 startingScale) : Object(vertices, indices, startingPosition, startingRotation, startingScale) {
        // Additional initialization for Triangle3D if needed
    }

    static inline const std::vector<VertexData> Vertices =
    {
        // Front-facing vertices
        { {-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f } }, // Bottom-left vertex
        { {0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f } },  // Bottom-right vertex
        { {0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f } },    // Top vertex

        // Back-facing vertices (with flipped normals)
        // Note: Uncomment this section if rendering both sides of the triangle
        { {0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, -1.0f, 1.0f } },    // Top vertex
        { {0.5f, -0.5f, 0.0f}, {0.0f, -1.0f, 0.0f, 1.0f } },  // Bottom-right vertex
        { {-0.5f, -0.5f, 0.0f}, {-1.0f, 0.0f, 0.0f, 1.0f } }  // Bottom-left vertex
    };

    static inline const std::vector<uint32_t> Indices = {
         0, 1, 2,  // Front-facing triangle
         0, 2, 3,  // Back-facing triangle
         0, 3, 1,  // Side triangle
         1, 3, 2   // Side triangle
    };
};
