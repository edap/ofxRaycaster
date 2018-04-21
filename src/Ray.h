#pragma once
#include "ofMain.h"
#include "Plane.h"

namespace ofxraycaster {

template<class T>
class Ray {
public:
    Ray(){};
    Ray(T _origin, T _direction){
        origin = _origin;
        direction = glm::normalize(_direction);
    };

    void setup(T _origin, T _direction){
        origin = _origin;
        direction = glm::normalize(_direction);
    };

    // generic methods

    T getOrigin() const {
        return origin;
    };

    void setOrigin(T _origin){
        origin = _origin;
    };

    T getDirection() const {
        return direction;
    };

    void setDirection(T _direction){
        direction = _direction;
    };

    // Returns the linear-interpolation from the ray origin along its direction vector where t is in the range from 0 to infinite.
    T lerp(const float t) const {
        auto result = direction;
        result *= t;
        result += origin;
        return result;
    }

    void draw(float radius = 20.){
        ofPushStyle();
        // draw origin
        ofSetColor(255, 0, 0);
        ofDrawSphere(origin.x, origin.y, radius);

        // draw direction
        ofSetColor(0,0,255);
        auto end = origin + (direction * (radius*4.));
        ofSetLineWidth(3);
        ofDrawLine(origin,end);
        ofSetLineWidth(1);
        ofPopStyle();
    };

    // 2D specific methods
    void intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool& intersects);
    void intersectsSegmentDistance(glm::vec2 a, glm::vec2 b, float& distance, bool& intersects);
    void intersectsPolyline(const ofPolyline& poly, glm::vec2& intersection, bool& intersects);

private:
    T origin;
    T direction;
};

}// end namespace

