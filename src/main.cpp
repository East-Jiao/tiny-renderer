#include <iostream>
#include <string>

#include "renderer/framebuffer.hpp"
#include "math/math.hpp"
#include "io/model/obj.hpp"

const int Image_Width = 2048;
const int Image_Height = 2048;

int main() {
    FrameBuffer fb(Image_Width, Image_Height);
    fb.clear(hrm::vec3(0, 0, 0));
    
    // fb.triangle(hrm::vec2(35, 100), hrm::vec2(100, 500), hrm::vec2(200, 200), hrm::vec3(255, 0, 153));
    // fb.triangle(hrm::vec2(500, 30), hrm::vec2(500,1000), hrm::vec2(1024, 1024), hrm::vec3(255, 255, 255));
    Model m;
    load_obj("./media/model/diablo3_pose.obj", m);
    draw_model(fb, m, hrm::vec3(255.0f, 255.0f, 255.0f));


    if (fb.save("./out/test.ppm", PPM_P6)) {
        std::cout << "Success" << std::endl;
    }
    else {
        std::cout << "No file" << std::endl;
    }

    return 0;
}