#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstddef>

#include "renderer/framebuffer.hpp"
#include "io/image_io.hpp"

void FrameBuffer::release() {
    //TODO: 添加句柄等成员之后，释放句柄资源
}

FrameBuffer::~FrameBuffer() {
    release();
}

FrameBuffer::FrameBuffer(int width, int height)
    : _width(width), _height(height), _data(std::vector<unsigned char>(width * height * 3, 0)) {

}

int FrameBuffer::width() const {
    return _width;
}

int FrameBuffer::height() const {
    return _height;
}

size_t FrameBuffer::size() const {
    return _data.size();
}

std::vector<unsigned char>& FrameBuffer::data() {
    return _data;
}
const std::vector<unsigned char>& FrameBuffer::data() const {
    return _data;
}

void FrameBuffer::set_pixel(int x, int y, const hrm::vec3& color) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        std::cerr << "Invalid position in 'set_pixel()': " << x << ' ' << y << std::endl;
        return;
    }

    int offset = (y * _width + x) * 3;
    _data[offset]     = static_cast<unsigned char>(std::round(std::clamp(color.x, 0.0f, 255.0f)));
    _data[offset + 1] = static_cast<unsigned char>(std::round(std::clamp(color.y, 0.0f, 255.0f)));
    _data[offset + 2] = static_cast<unsigned char>(std::round(std::clamp(color.z, 0.0f, 255.0f)));
}

void FrameBuffer::clear(const hrm::vec3& color) {
    for (std::size_t i = 0; i + 2 < size(); i += 3) {
        _data[i]     = static_cast<unsigned char>(std::round(std::clamp(color.x, 0.0f, 255.0f)));
        _data[i + 1] = static_cast<unsigned char>(std::round(std::clamp(color.y, 0.0f, 255.0f)));
        _data[i + 2] = static_cast<unsigned char>(std::round(std::clamp(color.z, 0.0f, 255.0f)));
    }
}

bool FrameBuffer::save(const std::string& path, io::ImgOutputFormat format) const {
    return io::save(path, *this, format);
}

void FrameBuffer::line(hrm::vec2 pa, hrm::vec2 pb, const hrm::vec3& color) {
    if (pa.x < 0 || pa.y < 0 || pa.x >= _width || pa.y >= _height || pb.x < 0 || pb.y < 0 || pb.x >= _width || pb.y >= _height) {
        std::cerr << "Invalid position in 'line()': " << pa.x << ' ' << pa.y << ' ' << pb.x << ' ' << pb.y << std::endl;
        return;
    }

    bool steep = std::abs(pb.y - pa.y) > std::abs(pb.x - pa.x);
    if (steep) {
        std::swap(pa.x, pa.y);
        std::swap(pb.x, pb.y);
    }

    if (pa.x > pb.x) {
        std::swap(pa, pb);
    }
    
    int dx = static_cast<int>(pb.x - pa.x);
    int dy = static_cast<int>(pb.y - pa.y);

    int dir = dy >= 0 ? 1 : -1;
    dy *= dir;

    auto solve = [&](int x, int y) {
        if (!steep) {
            set_pixel(x, y, color);
        }
        else {
            set_pixel(y, x, color);
        }
    };

    int y = static_cast<int>(pa.y);
        
    int D = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        solve(static_cast<int>(pa.x) + i, y);

        if (D > 0) {
            y += dir;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}

void FrameBuffer::triangle(hrm::vec2 va, hrm::vec2 vb, hrm::vec2 vc, const hrm::vec3& color) {
    float S = hrm::cross(vb - va, vc - va);

    if (std::abs(S) < 1e-4f) {
        return;
    }
    if (S > 0) {
        return;
    }
    
    int minX = std::min(std::min(va.x, vb.x), vc.x);
    int minY = std::min(std::min(va.y, vb.y), vc.y);
    int maxX = std::max(std::max(va.x, vb.x), vc.x);
    int maxY = std::max(std::max(va.y, vb.y), vc.y);

    //Box
    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            float px = x + 0.5f;
            float py = y + 0.5f;
            hrm::vec2 p(px, py);  

            float w_a = hrm::cross(vb - p, vc - p);
            float w_b = hrm::cross(vc - p, va - p);
            float w_c = hrm::cross(va - p, vb - p);

            if (w_a > 0 || w_b > 0 || w_c > 0) {
                continue;
            }

            float alpha = w_a / S;
            float beta  = w_b / S;
            float gamma = w_c / S;

            set_pixel(x, y, color);
        }
    }
}











//脚印
/* Use scanline to draw triangle
    if (va.y > vb.y) { std::swap(va, vb);}
    if (vb.y > vc.y) { std::swap(vb, vc);}
    if (va.y > vb.y) { std::swap(va, vb);}

    float th = vc.y - va.y;
    if (va.y != vb.y) {
        float sh = vb.y - va.y;
        for (int y = std::ceil(va.y - 0.5f); y <= std::floor(vb.y - 0.5f); y++) {
            float yf = y + 0.5f;    //像素中心
            float x1 = va.x + (vc.x - va.x) * (yf - va.y) / th;
            float x2 = va.x + (vb.x - va.x) * (yf - va.y) / sh;
            for (int x = std::ceil(std::min(x1, x2) - 0.5f); x <= std::floor(std::max(x1, x2) - 0.5f); x++) {
                set_pixel(x, y, color);
            }
        }
    }

    if (vb.y != vc.y) {
        float sh = vc.y - vb.y;
        for (int y = std::ceil(vb.y - 0.5f); y <= std::floor(vc.y - 0.5f); y++) {
            float yf = y + 0.5f;
            float x1 = va.x + (vc.x - va.x) * (yf - va.y) / th;
            float x2 = vb.x + (vc.x - vb.x) * (yf - vb.y) / sh;
            for (int x = std::ceil(std::min(x1, x2) - 0.5f); x <= std::floor(std::max(x1, x2) - 0.5f); x++) {
                set_pixel(x, y, color);
            }
        }
    }
*/

