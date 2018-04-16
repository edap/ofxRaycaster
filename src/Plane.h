#pragma once
#include "ofMain.h" // TODO how to include just glm?

namespace ofxraycaster {

class Plane {
public:
    Plane();
    void setup(glm::vec2 orig, glm::vec2 normal);
    void draw(float radius = 20.);
    void updateNormal(glm::vec2 normal);
    void updateOrigin(glm::vec2 position);
    
    glm::vec2 getOrigin() const;
    glm::vec2 getNormal() const;

private:
    glm::vec2 orig;
    glm::vec2 normal;
    glm::vec3 arbitraryOrthogonal(const glm::vec3& vec);
    glm::vec2 arbitraryOrthogonal(const glm::vec2& vec);

};

}
