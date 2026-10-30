#include <iostream>
#include <string>

#include "renderer/framebuffer.hpp"
#include "io/model/obj.hpp"

const int Image_Width = 256;
const int Image_Height = 256;

int main() {
    FrameBuffer fb(Image_Width, Image_Height);
    fb.clear(0, 0, 0);
    
    Model m;
    std::string m_path = "./media/model/diablo3_pose.obj";
    load_obj(m_path, m);
    draw_model(fb, m, 255, 0, 153);

    if (fb.save("./out/test.ppm", PPM_P6)) {
        std::cout << "Success" << std::endl;
    }
    else {
        std::cout << "No file" << std::endl;
    }

    return 0;
}