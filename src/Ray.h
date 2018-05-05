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

    // GENERIC METHODS. Methods available for 2D and 3D vectors ///////////////
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

    void draw(float radius = 20.);

    // Returns the linear-interpolation from the ray origin along its direction vector where t is in the range from 0 to infinite.
    T lerp(const float t) const {
        auto result = direction;
        result *= t;
        result += origin;
        return result;
    }

    void intersectsPlane(Plane plane, T& intersection, bool& intersects){
        float distance;
        intersects = glm::intersectRayPlane(origin, direction,
                                            plane.getOrigin(), plane.getNormal(),
                                            distance);
        if (intersects) {
            intersection = origin + direction*distance;
        }
    };


    // 2D METHODS. They are available only if the ray is a 2D ray //////////////
    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec2, V>::value || std::is_same<ofVec2f, V>::value, void>::type
    intersectsSegmentDistance(glm::vec2 a, glm::vec2 b, float& distance, bool& intersects){
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

    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec2, V>::value || std::is_same<ofVec2f, V>::value, void>::type
    // https://gamedev.stackexchange.com/questions/109420/ray-segment-intersection
    intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool& intersects){
        intersects = false;

        float distance = 0;
        intersectsSegmentDistance(a, b, distance, intersects);
        if (intersects) {
            intersection.x = origin.x + distance * direction.x;
            intersection.y = origin.y + distance * direction.y;
        }
    };


    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec2, V>::value || std::is_same<ofVec2f, V>::value, void>::type
    intersectsPolyline(const ofPolyline& poly, glm::vec2& intersection, glm::vec2& surfaceNormal, bool& intersects){

        vector<glm::vec3> container = poly.getVertices();
        float distance = std::numeric_limits<float>::infinity();
        for (int i = 0; i < container.size(); i++) {
            // If it is an opened polyline, do not check for the intersection
            // between the last point of the polyline and the first one
            if (!poly.isClosed() && i == container.size() -1) {
                continue;
            }

            // qui in realta' dovresti chiudere solo se la poly e' closed.
            auto endSegmentIndex = container.size() == (i + 1) ? 0 : i + 1;

            float tmpDistance = distance;
            bool tmpIntersect = false;
            intersectsSegmentDistance(container[i], container[endSegmentIndex],
                                      tmpDistance, tmpIntersect);
            if (tmpIntersect) {
                if (intersects == false) { intersects = true; };
                if (tmpDistance < distance) {
                    //first find the direction of the segment.
                    glm::vec2 segmentDir = glm::normalize(container[i] - container[endSegmentIndex]);
                    // and then use as normal a vector orthogonal to the direction.
                    surfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);
                    distance = tmpDistance;
                }
            }
            
        }
        
        if (intersects) {
            intersection.x = origin.x + distance * direction.x;
            intersection.y = origin.y + distance * direction.y;
        }
    };

    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec2, V>::value || std::is_same<ofVec2f, V>::value, void>::type

private:
    T origin;
    T direction;
};

}// end namespace

