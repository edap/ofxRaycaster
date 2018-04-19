#pragma once
#include "ofMain.h"
#include "Plane.h"

namespace ofxraycaster {

template<class T>

class Ray {
public:
    Ray(){};

// generic methods

    void setup(T _origin, T _direction){
        origin = _origin;
        direction = glm::normalize(_direction);
    };

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



// 2D methods
    template<>
    // https://gamedev.stackexchange.com/questions/109420/ray-segment-intersection
    void intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool& intersects){
        intersects = false;
        //(x, y, dx, dy, x1, y1, x2, y2);
        float x = origin.x;
        float y = origin.y;
        float dx = direction.x;
        float dy = direction.y;

        float r, s, denom;
        //Make sure the lines aren't parallel, can use an epsilon here instead
        // Division by zero in C# at run-time is infinity. In JS it's NaN
        if (dy / dx != (b.y - a.y) / (b.x - a.x)){
            denom = ((dx * (b.y - a.y)) - dy * (b.x - a.x));
            if (denom != 0) {
                r = (((y - a.y) * (b.x - a.x)) - (x - a.x) * (b.y - a.y)) / denom;
                s = (((y - a.y) * dx) - (x - a.x) * dy) / denom;
                if (r >= 0 && s >= 0 && s <= 1) {
                    intersects = true;
                    intersection.x = x + r * dx;
                    intersection.y = y + r * dy;
                    //return { x: x + r * dx, y: y + r * dy };
                }
            }
        }
    };

// 3D methods

private:
    T origin;
    T direction;
};

}// end namespace
