#include <QImage>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../ffd/bezier_function.h"
#include "../stl/stl_import.h"

int main() 
{
    QImage img(":/ffd_input.png");
    int w = img.width();
    int h = img.height();
    std::map<std::array<float, 2>, QRgb> transf_img_arr;
    
    std::array<glm::vec2, 3> a1 = { glm::vec2(0.0, 0.0), glm::vec2(0.0, 0.5), glm::vec2(0.0, 1.0) };
    std::array<glm::vec2, 3> a2 = { glm::vec2(0.5, 0.0), glm::vec2(0.5, 0.5), glm::vec2(0.5, 1.4) };
    std::array<glm::vec2, 3> a3 = { glm::vec2(0.9, 0.0), glm::vec2(1.0, 0.5), glm::vec2(1.0, 1.0) };
    std::array<std::array<glm::vec2, 3>, 3> ctrl2d = { a1, a2, a3 };
    
    float mx(-FLT_MAX), my(-FLT_MAX);
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            glm::vec2 t = bezier<3,3>(glm::vec2((float)i/w, (float)j/h), ctrl2d) * glm::vec2(w, h);
            transf_img_arr[{t.x, t.y}] = img.pixel(i, j);
            mx = mx < t.x ? t.x : mx;
            my = my < t.y ? t.y : my;
        }
    }
    
    qDebug() << "min/max" << mx << my;
    
    QImage transf_img(mx+1, my+1, QImage::Format_RGB32);
    for(auto e : transf_img_arr) {
        QPoint p = QPoint((int)e.first[0], (int)e.first[1]);
        transf_img.setPixel(p, e.second);
    }
    transf_img.save("ffd_result.png");
    
    return 0;
}
