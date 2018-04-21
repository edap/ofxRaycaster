#include "Ray.h"

// 2D methods
template<>
void ofxraycaster::Ray<glm::vec2>::intersectsSegmentDistance(glm::vec2 a, glm::vec2 b, float& distance, bool& intersects){
    intersects = false;

    float x = origin.x;
    float y = origin.y;
    float dx = direction.x;
    float dy = direction.y;

    float s, denom;
    if (dy / dx != (b.y - a.y) / (b.x - a.x)){
        denom = ((dx * (b.y - a.y)) - dy * (b.x - a.x));
        if (denom != 0) {
            distance = (((y - a.y) * (b.x - a.x)) - (x - a.x) * (b.y - a.y)) / denom;
            s = (((y - a.y) * dx) - (x - a.x) * dy) / denom;
            if (distance >= 0 && s >= 0 && s <= 1) {
                intersects = true;
                //return { x: x + r * dx, y: y + r * dy };
            }
        }
    }
    
};

template<>

// https://gamedev.stackexchange.com/questions/109420/ray-segment-intersection
void ofxraycaster::Ray<glm::vec2>::intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool& intersects){
    intersects = false;

    float distance = 0;
    intersectsSegmentDistance(a, b, distance, intersects);
    if (intersects) {
        intersection.x = origin.x + distance * direction.x;
        intersection.y = origin.y + distance * direction.y;
    }
};



template<>
void ofxraycaster::Ray<glm::vec2>::intersectsPolyline(const ofPolyline& poly, glm::vec2& intersection, bool& intersects){

    vector<glm::vec3> container = poly.getVertices();
    float distance = std::numeric_limits<float>::infinity();
    for (int i = 0; i < container.size(); i++) {
        cout << distance << endl;

        auto endSegmentIndex = container.size() == (i + 1) ? 0 : i + 1;
        cout << "qui" << endl;
        cout << i << endl;
        cout << endSegmentIndex << endl;

        float tmpDistance = distance;
        bool tmpIntersect = false;
        intersectsSegmentDistance(container[i], container[endSegmentIndex],
                                  tmpDistance, tmpIntersect);
        if (tmpIntersect) {
            if (intersects == false) { intersects = true; };
            if (tmpDistance < distance) {
                distance = tmpDistance;
            }
        }

    }

    if (intersects) {
        intersection.x = origin.x + distance * direction.x;
        intersection.y = origin.y + distance * direction.y;
    }
};




