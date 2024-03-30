#include <vector>
#include <cmath>
#include <Object/Object.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Sphere : public Object
{
public:
    Sphere(std::vector<VertexData> vertices, std::vector<uint32_t> indices, XMFLOAT3 startingPosition, XMFLOAT3 startingRotation, XMFLOAT3 startingScale) : Object(vertices, indices, startingPosition, startingRotation, startingScale) {}

    static void generateSphere(std::vector<VertexData>& vertices, std::vector<uint32_t>& indices, int latitudeDivisions, int longitudeDivisions, float radius = 0.5f, float offsetX = 0.0f, float offsetY = 0.0f, float offsetZ = 0.0f) {
        for (int lat = 0; lat <= latitudeDivisions; ++lat) {
            float theta = lat * M_PI / latitudeDivisions;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            for (int lon = 0; lon <= longitudeDivisions; ++lon) {
                float phi = lon * 2 * M_PI / longitudeDivisions;
                float sinPhi = sin(phi);
                float cosPhi = cos(phi);

                float x = cosPhi * sinTheta + offsetX;
                float y = cosTheta + offsetY;
                float z = sinPhi * sinTheta + offsetZ;

                vertices.push_back({ {radius * x, radius * y, radius * z}, {1.0f, 0.0f, 0.0f, 1.0f} });
            }
        }

        for (int lat = 0; lat < latitudeDivisions; ++lat) {
            for (int lon = 0; lon < longitudeDivisions; ++lon) {
                int current = lat * (longitudeDivisions + 1) + lon;
                int next = current + longitudeDivisions + 1;

                indices.push_back(current);
                indices.push_back(next);
                indices.push_back(current + 1);

                indices.push_back(current + 1);
                indices.push_back(next);
                indices.push_back(next + 1);
            }
        }
    }
                                                                     
    static inline std::vector<VertexData> SphereVertices = []() {
        std::vector<VertexData> vertices;
        std::vector<uint32_t> indices;
                                                                                         
        generateSphere(vertices, indices, 20, 20, 0.5f, 1.0f, 2.0f, 3.0f);

        return vertices;
        }();

        static inline std::vector<uint32_t> SphereIndices = []() {
            std::vector<VertexData> vertices;
            std::vector<uint32_t> indices;

            generateSphere(vertices, indices, 20, 20, 0.5f, 1.0f, 2.0f, 3.0f);

            return indices;
            }();

};
