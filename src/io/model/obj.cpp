#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>

#include "math/vec2.hpp"
#include "io/model/obj.hpp"
#include "renderer/framebuffer.hpp"

bool load_obj(const std::string& path, Model& out) {
    std::ifstream f(path);
    if (!f) return false;

    std::vector<hrm::vec2> raw;
    std::vector<std::vector<int>> faces;

    std::string line;
    while (std::getline(f, line)) {
        if (line.size() < 2) continue;
        
        if (line[0] == 'v' && line[1] == ' ') {
            std::istringstream iss(line);
            char v;
            float x, y, z;
            iss >> v >> x >> y >> z;
            raw.push_back(hrm::vec2(x, y)); 
        }
        else if (line[0] == 'f' && line[1] == ' ') {
            std::istringstream iss(line);
            char f;
            iss >> f;

            std::vector<int> face;
            std::string token;
            while (iss >> token) {
                int idx = std::stoi(token.substr(0, token.find('/')));

                if (idx < 0) {
                    idx += static_cast<int>(raw.size());
                }
                else {
                    idx -= 1;   // 1-based -> 0-based
                }

                face.push_back(idx);
            }
            if (face.size() >= 2) {
                faces.push_back(std::move(face));
            }
        }
    }

    if (raw.empty()) {
        return false;
    }

    //确定包装盒大小
    float minX = std::numeric_limits<float>::max(), maxX = std::numeric_limits<float>::min();
    float minY = std::numeric_limits<float>::max(), maxY = std::numeric_limits<float>::min();
    for (auto& p : raw) {
        minX = std::min(minX, p.x), maxX = std::max(maxX, p.x);
        minY = std::min(minY, p.y), maxY = std::max(maxY, p.y);
    }
    float sx = maxX - minX > 1e-8f ? 1.0f / (maxX - minX) : 1.0f;
    float sy = maxY - minY > 1e-8f ? 1.0f / (maxY - minY) : 1.0f;

    out.verts.clear();
    out.verts.reserve(raw.size());
    for (auto& p : raw) {
        out.verts.push_back(hrm::vec2((p.x - minX) * sx, (p.y - minY) * sy));
    }

    out.edges.clear();
    for (auto& face : faces) {
        int n = static_cast<int>(face.size());
        for (int i = 0; i < n; i++) {
            out.edges.emplace_back(face[i], face[(i + 1) % n]);
        }
    }

    return true;
}

void draw_model(FrameBuffer& fb, const Model& model, float r, float g, float b) {
    int width = fb.width(), height = fb.height();
    for (auto& [i0, i1] : model.edges) {
        const hrm::vec2& pa = model.verts[i0];
        const hrm::vec2& pb = model.verts[i1];
        int a_x = (int)(pa.x * (width - 1)), a_y = (int)((1.0f - pa.y) * (height - 1));
        int b_x = (int)(pb.x * (width - 1)), b_y = (int)((1.0f - pb.y) * (height - 1));
        fb.line(a_x, a_y, b_x, b_y, r, g, b);
    }
}