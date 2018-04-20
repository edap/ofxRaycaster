#include "Ray.h"

// 2D methods
template<>

// https://gamedev.stackexchange.com/questions/109420/ray-segment-intersection
void ofxraycaster::Ray<glm::vec2>::intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool& intersects){
    intersects = false;

    float x = origin.x;
    float y = origin.y;
    float dx = direction.x;
    float dy = direction.y;

    float r, s, denom;
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

template<>
void ofxraycaster::Ray<glm::vec2>::intersectsPolyline(const ofPolyline& poly, glm::vec2& intersection, bool& intersects){

    vector<glm::vec3> container = poly.getVertices();
    for (int i = 0; i < container.size(); i++) {

        auto endSegmentIndex = container.size() == (i-1) ? 0 : i+1;

        intersectsSegment(container[i], container[endSegmentIndex], intersection, intersects);

    }
};




