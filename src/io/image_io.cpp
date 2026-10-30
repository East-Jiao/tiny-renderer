#include <string>
#include <iostream>
#include <fstream>

#include "io/image_io.hpp"
#include "renderer/framebuffer.hpp"

bool savePPM(const std::string& path, const FrameBuffer& fb, io::ImgOutputFormat format) {
    std::ofstream f(path, std::ios::binary | std::ios::trunc);
    if (!f) { 
        std::cerr << "No such file or directory: " << path << std::endl;
        return false;
    }

    const auto& d = fb.data();
    
    if (format == io::ImgOutputFormat::PPM_P3) {
        f << "P3\n" << fb.width() << ' ' << fb.height() << "\n255\n";
        for (size_t i = 0; i + 2 < d.size(); i += 3) {
            f << int(d[i]) << ' ' << int(d[i + 1]) << ' ' << int(d[i + 2]) << '\n';
        }
    }
    else if (format == io::ImgOutputFormat::PPM_P6) {
        f << "P6\n" << fb.width() << ' ' << fb.height() << "\n255\n";
        f.write(reinterpret_cast<const char*>(d.data()), static_cast<std::streamsize>(d.size()));
    }
    else {
        std::cerr << "Unknown format for saving PPM: " << static_cast<int>(format) << std::endl;
        return false;
    }
    return static_cast<bool>(f);
}

namespace io {
    bool save(const std::string& path, const FrameBuffer& fb, ImgOutputFormat format) {
        switch (format) {
            case ImgOutputFormat::PPM_P3:
            case ImgOutputFormat::PPM_P6:
                return savePPM(path, fb, format);
            break;
            case ImgOutputFormat::TGA:
                //saveTGA()
                return false;
                break;
            case ImgOutputFormat::BMP:
                //saveBMP()
                return false;
                break;
            case ImgOutputFormat::PNG:
                //savePNG()
                return false;
                break;
            default:
                std::cerr << "Unknown format for saving: " << static_cast<int>(format) << std::endl;
                return false;
                break;
        }
    }
}