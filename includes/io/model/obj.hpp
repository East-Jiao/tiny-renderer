#pragma once

#include <string>
#include <vector>
#include <utility>

#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "renderer/framebuffer.hpp"

struct Face {
    std::vector<int> indices;
};

struct Triangle {
    int i0;
    int i1;
    int i2;
};

struct Model {
    std::vector<hrm::vec2> verts;
    std::vector<Face> faces;
    std::vector<Triangle> triangles;
    std::vector<std::pair<int, int>> edges;
};

bool load_obj(const std::string& path, Model& out);
void draw_model(FrameBuffer& fb, const Model& model, const hrm::vec3& color);