#include "WorldGenerator.h"
#include <iostream>
std::pair<std::vector<Vertex>, std::vector<unsigned int>> WorldGenerator::getWorld() {
//    std::vector<Vertex> vertices = {
//            {-0.5f, -0.5f, 0.0f},
//            {0.5f, -0.5f, 0.0f},
//            {0.5f, 0.5f, 0.0f},
//            {-0.5f, 0.5f, 0.0f}
//    };
//
//    std::vector<unsigned int> indices = {
//            0, 2, 3,
//            0, 1, 2
//    };
//
//    return {std::move(vertices), std::move(indices)};

    const int size = 3;

    const float halfSize = static_cast<float>(size - 1) / 2.0f;

    std::vector<Vertex> vertices(size * size);
    std::vector<unsigned int> indices((size - 1) * (size - 1) * 6);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            vertices[i * size + j] = {j - halfSize, 0.0f, i - halfSize};
        }
    }

    unsigned int offset = 0;
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - 1; j++) {
            indices[offset + 0] = i * size + j;
            indices[offset + 1] = (i + 1) * size + (j + 1);
            indices[offset + 2] = (i + 1) * size + j;

            indices[offset + 3] = i * size + j;
            indices[offset + 4] = i * size + j + 1;
            indices[offset + 5] = (i + 1) * size + (j + 1);

            offset += 6;
        }
    }

    return {std::move(vertices), std::move(indices)};
}
