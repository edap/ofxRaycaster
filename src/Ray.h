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

    bool intersectsPlane(ofxraycaster::Plane<T> plane, float & distance){
        return glm::intersectRayPlane(origin, direction,
                                            plane.getOrigin(), plane.getNormal(),
                                            distance);
    };


    // 2D METHODS. They are available only if the ray is a 2D ray //////////////
    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec2, V>::value || std::is_same<ofVec2f, V>::value, void>::type
    intersectsSegmentDistance(const glm::vec2 & a, const glm::vec2 & b, float & distance, bool & intersects){
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
    intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool & intersects){
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
    intersectsPolyline(const ofPolyline & poly, glm::vec2 & intersection, glm::vec2& surfaceNormal, bool & intersects){

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

    // 3D Methods
    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec3, V>::value || std::is_same<ofVec3f, V>::value, bool>::type
    intersectsTriangle(glm::vec3 const & vert0, glm::vec3 const & vert1, glm::vec3 const & vert2, glm::vec3 & baryPosition){

        return glm::intersectRayTriangle(origin, direction, vert0, vert1, vert2, baryPosition);
    }

    // 3D Methods
    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec3, V>::value || std::is_same<ofVec3f, V>::value, bool>::type
    intersectsSphere(const glm::vec3 & _center, const float & _radius, glm::vec3& _position, glm::vec3 & _normal){

        return glm::intersectRaySphere(origin, direction, _center, _radius, _position, _normal);


    }

    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec3, V>::value || std::is_same<ofVec3f, V>::value, glm::vec3>::type
    getPointOnTriangle(const glm::vec3 & _baryPosition) const {
        return origin + (direction * _baryPosition.z);
    };

    template<class V = T>
    typename std::enable_if<std::is_same<glm::vec3, V>::value || std::is_same<ofVec3f, V>::value, bool>::type
    intersectsPrimitive(const of3dPrimitive& primitive,  glm::vec3 & intPosition, glm::vec3 & intNormal, ofColor & color) {
        // at the beginning, no intersection is found and the distance to the closest surface
        // is set to an high value;
        bool found = false;
        float distanceToTheClosestSurface = numeric_limits<float>::max();

        for (const ofMeshFace& face : primitive.getMesh().getUniqueFaces()) {
            glm::vec3 baricenter;
            bool intersection = glm::intersectRayTriangle(
                                                          origin, direction,
                                                          glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(0), 1.f)),
                                                          glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(1), 1.f)),
                                                          glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(2), 1.f)),
                                                          baricenter);
            // when an intersection is found, it updates the distanceToTheClosestSurface value
            // this value is used to order the new intersections, if a new intersection with a smaller baricenter.z
            // value is found, this one will become the new intersection
            if (intersection) {
                if (baricenter.z < distanceToTheClosestSurface) {
                    found = true;
                    if(face.hasColors()){
                        color = face.getColor(1);
                    };
                    distanceToTheClosestSurface = baricenter.z;
                    intNormal = face.getFaceNormal();
                    intPosition = getPointOnTriangle(baricenter);
                }
            }
        }
        return found;
    };


private:
    T origin;
    T direction;
};

}// end namespace

