#pragma once
#include "ofMain.h"
#include "Ray.h"

namespace ofxraycaster {
    class Raycaster {
    public:
        Raycaster(){};
        Raycaster(const glm::vec3 _origin, const glm::vec3 _direction, const float near, const float far);
        void set(const glm::vec3 _origin, const glm::vec3 _direction);
        void setFromCamera(const glm::vec2 coords, const ofCamera camera);
        void draw();

    private:
        Ray ray;
        float near = 0;
        float far = 0;
    };
}
