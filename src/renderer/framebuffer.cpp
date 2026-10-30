#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

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

void FrameBuffer::set_pixel(int x, int y, float r, float g, float b) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        std::cerr << "Invalid position in 'set_pixel()': " << x << ' ' << y << std::endl;
        return;
    }

    int offset = (y * _width + x) * 3;
    _data[offset]     = static_cast<unsigned char>(std::round(std::clamp(r, 0.0f, 255.0f)));
    _data[offset + 1] = static_cast<unsigned char>(std::round(std::clamp(g, 0.0f, 255.0f)));
    _data[offset + 2] = static_cast<unsigned char>(std::round(std::clamp(b, 0.0f, 255.0f)));
}

void FrameBuffer::clear(float r, float g, float b) {
    for (size_t i = 0; i + 2 < size(); i += 3) {
        _data[i]     = static_cast<unsigned char>(std::round(std::clamp(r, 0.0f, 255.0f)));
        _data[i + 1] = static_cast<unsigned char>(std::round(std::clamp(g, 0.0f, 255.0f)));
        _data[i + 2] = static_cast<unsigned char>(std::round(std::clamp(b, 0.0f, 255.0f)));
    }
}

bool FrameBuffer::save(const std::string& path, io::ImgOutputFormat format) const {
    return io::save(path, *this, format);
}

void FrameBuffer::line(int a_x, int a_y, int b_x, int b_y, float r, float g, float b) {
    if (a_x < 0 || a_y < 0 || a_x >= _width || a_y >= _height || b_x < 0 || b_y < 0 || b_x >= _width || b_y >= _height) {
        std::cerr << "Invalid position in 'line()': " << a_x << ' ' << a_y << ' ' << b_x << ' ' << b_y << std::endl;
        return;
    }

    bool steep = std::abs(b_y - a_y) > std::abs(b_x - a_x);
    if (steep) {
        std::swap(a_x, a_y);
        std::swap(b_x, b_y);
    }

    if (a_x > b_x) {
        std::swap(a_x, b_x);
        std::swap(a_y, b_y);
    }
    
    int dx = b_x - a_x;
    int dy = b_y - a_y;

    int dir = dy >= 0 ? 1 : -1;
    dy *= dir;

    auto solve = [&](int x, int y) {
        if (!steep) {
            set_pixel(x, y, r, g, b);
        }
        else {
            set_pixel(y, x, r, g, b);
        }
    };

    int y = a_y;
        
    int D = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        solve(a_x + i, y);

        if (D > 0) {
            y += dir;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}