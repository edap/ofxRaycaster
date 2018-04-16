#pragma once
#include "ofMain.h"
#include "Plane.h"

namespace ofxraycaster {

class Ray2D {
public:
    Ray2D(){};

    void setup(glm::vec2 origin, glm::vec2 direction);
    glm::vec2 getOrigin() const;
    glm::vec2 getDirection() const;
    void setDirection(glm::vec2 direction);
    void draw(float radius = 20.);
    void intersectsPlane(ofxraycaster::Plane plane, glm::vec2& intersection, bool& intersects);
    void intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool& intersects);
    void intersectsPolyline(ofPolyline& poly, bool& intersects, float& distance);

private:
    glm::vec2 origin;
    glm::vec2 direction;
};

}
