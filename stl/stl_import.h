#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <fstream>
#include <cassert>


namespace stl {
    #pragma pack(push, 1)
    struct face {
        glm::vec3 _norm;
        glm::vec3 _vert_1;
        glm::vec3 _vert_2;
        glm::vec3 _vert_3;
        uint16_t _attribute = 0;
    };
    #pragma pack(pop)

    struct bbox {
        glm::vec3 _min;
        glm::vec3 _max;
    
        float scale() const;
        glm::vec3 offset() const;
    };

    class format {
        // small check to guarantee sanity
        static_assert(sizeof(face) == sizeof(glm::vec3) * sizeof(float) + sizeof(uint16_t), "size mismatch: face not compatible with stl format");
       
        uint8_t _header[80] = { 0 };
        std::vector<face> _faces;
       
        public:
            format() = default;
            format(const std::string &file);
            
            bool load(const std::string &filename);
            const std::vector<face> &faces() const;
           
            static bbox estimate_bbox(const std::vector<face> &);
            //! Scaled down to 0 <= x <= 1
            static std::vector<face> normalized(const bbox &, const std::vector<face> &, const glm::vec3 &transl = glm::vec3(0));
           
            // operator overload to access face
            face& operator[](std::size_t idx) { return _faces[idx]; }
            const face& operator[](std::size_t idx) const { return _faces[idx]; }
    };
};
