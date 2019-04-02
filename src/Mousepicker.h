#pragma once
#include "ofMain.h"
#include "Ray.h"

namespace ofxraycaster {
    class Mousepicker {
    public:
        Mousepicker(){};
        void setFromCamera(const glm::vec2& coords, const ofCamera& camera);
        void draw(const float radius = 20.0f);
        Ray& getRay();

    private:
        Ray ray;
        float nearClip=0.0f;
        float farClip=0.0f;
    };
}
