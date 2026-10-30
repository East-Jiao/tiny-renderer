#pragma once

#include <string>

class FrameBuffer;

namespace io {
    enum class ImgOutputFormat {
        PPM_P3,
        PPM_P6,
        TGA,
        BMP,
        PNG
    };
    
    bool save(const std::string& path, const FrameBuffer& fb, ImgOutputFormat format);
}

bool savePPM(const std::string& path, const FrameBuffer& fb, io::ImgOutputFormat format);