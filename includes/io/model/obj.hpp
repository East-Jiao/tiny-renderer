#pragma once

#include <string>
#include <vector>
#include <utility>

#include "math/vec2.hpp"
#include "renderer/framebuffer.hpp"

struct Model {
    std::vector<hrm::Vec2> verts;
    std::vector<std::pair<int, int>> edges;
};

bool load_obj(const std::string& path, Model& out);
void draw_model(FrameBuffer& fb, const Model& model, float r, float g, float b);