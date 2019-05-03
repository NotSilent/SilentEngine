#pragma once
#include <vector>

#include "Vertex.h"

class WorldGenerator {
public:
    static std::pair<std::vector<Vertex>, std::vector<unsigned int>> getWorld();

private:
};
