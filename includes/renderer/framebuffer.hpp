#pragma once

#include <vector>
#include <string>

#include "io/image_io.hpp"
#include "math/math.hpp"

inline constexpr auto PPM_P3 = io::ImgOutputFormat::PPM_P3;
inline constexpr auto PPM_P6 = io::ImgOutputFormat::PPM_P6;
inline constexpr auto TGA    = io::ImgOutputFormat::TGA;
inline constexpr auto BMP    = io::ImgOutputFormat::BMP;
inline constexpr auto PNG    = io::ImgOutputFormat::PNG;

class FrameBuffer {
    private:
    int _width;
    int _height;
    std::vector<unsigned char> _data;

    void release();

    public:
    explicit FrameBuffer(int width, int height);
    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;
    FrameBuffer(FrameBuffer&&) noexcept = delete;
    FrameBuffer& operator=(FrameBuffer&&) noexcept = delete;
    ~FrameBuffer();

    //getters
    int width() const;
    int height() const;
    size_t size() const;
    std::vector<unsigned char>& data();
    const std::vector<unsigned char>& data() const;

    void set_pixel(int x, int y, const hrm::vec3& color);
    void clear(const hrm::vec3& color);
    bool save(const std::string& path, io::ImgOutputFormat format) const;

    void line(hrm::vec2 pa, hrm::vec2 pb, const hrm::vec3& color);
    void triangle(hrm::vec2 va, hrm::vec2 vb, hrm::vec2 vc, const hrm::vec3& color);
};