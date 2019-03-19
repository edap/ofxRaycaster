#pragma once
#include "ofMain.h" // TODO how to include just glm?

namespace ofxraycaster {

    class Plane {
    public:
        Plane(){}
        Plane(glm::vec3 _orig, glm::vec3 _normal);

        void draw(float radius = 20.);
        void setup(glm::vec3 _orig, glm::vec3 _normal);
        void updateNormal(glm::vec3 _normal);
        void updateOrigin(glm::vec3 _orig);
        const glm::vec3 getOrigin();
        const glm::vec3 getNormal();
        glm::vec3 arbitraryOrthogonal(const glm::vec3& vec);

    private:
        glm::vec3 orig;
        glm::vec3 normal;
        
    };
}
