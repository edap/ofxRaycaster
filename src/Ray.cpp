#include "ofMain.h"
#include "Plane.h"
#include "Ray.h"


/// \brief it creates a ray given an origin T and a direction T
/// @param [in] _origin
/// @param [in] _direction
/// ~~~~{.cpp}
/// ofPixels p;
/// ofLoadImage(p, "pathToImage.jpg");
/// ~~~~
ofxraycaster::Ray::Ray(glm::vec3 _origin, glm::vec3 _direction){
    origin = _origin;
    direction = glm::normalize(_direction);
};

/// \brief it sets the origin and direction of a ray. For example,
/// for a 2D ray:
///
/// ~~~~{.cpp}
/// ofxraycaster::Ray<glm::vec2> ray;
/// ray.setup(glm::vec2(10,5), glm::vec2(1,0));
/// ~~~~
void ofxraycaster::Ray::setup(glm::vec3 _origin, glm::vec3 _direction){
    origin = _origin;
    direction = glm::normalize(_direction);
};

/// \brief it returns the origin of the ray,
const glm::vec3 ofxraycaster::Ray::getOrigin() {
    return origin;
};

void ofxraycaster::Ray::setOrigin(glm::vec3 _origin){
    origin = _origin;
};

const glm::vec3 ofxraycaster::Ray::getDirection() {
    return direction;
};

void ofxraycaster::Ray::setDirection(glm::vec3 _direction){
    direction = _direction;
};

void ofxraycaster::Ray::draw(float radius){
    ofPushStyle();
    // draw origin
    ofSetColor(255, 0, 0);
    ofDrawSphere(origin, radius);

    // draw direction
    ofSetColor(0,0,255);
    auto end = origin + (direction * (radius*4.));
    ofSetLineWidth(3);
    ofDrawLine(origin,end);
    ofSetLineWidth(1);
    ofPopStyle();
};



bool ofxraycaster::Ray::intersectsPlane(ofxraycaster::Plane plane, float & distance){
    return glm::intersectRayPlane(origin, direction,
                                  plane.getOrigin(), plane.getNormal(),
                                  distance);
};


bool ofxraycaster::Ray::intersectsTriangle(glm::vec3 const & vert0, glm::vec3 const & vert1, glm::vec3 const & vert2, glm::vec3 & baryPosition){

    return glm::intersectRayTriangle(origin, direction, vert0, vert1, vert2, baryPosition);
}

bool ofxraycaster::Ray::intersectsSphere(const glm::vec3 & _center, const float & _radius, glm::vec3& _position, glm::vec3 & _normal){

    return glm::intersectRaySphere(origin, direction, _center, _radius, _position, _normal);


}

bool ofxraycaster::Ray::intersectsPrimitive(const of3dPrimitive& primitive,  glm::vec3 & baricentricCoords, glm::vec3 & intNormal) {
    // at the beginning, no intersection is found and the distance to the closest surface
    // is set to an high value;
    bool found = false;
    float distanceToTheClosestSurface = numeric_limits<float>::max();
    for (const ofMeshFace& face : primitive.getMesh().getUniqueFaces()) {
        bool intersection = glm::intersectRayTriangle(
                                                      origin, direction,
                                                      glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(0), 1.f)),
                                                      glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(1), 1.f)),
                                                      glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(2), 1.f)),
                                                      baricentricCoords);
        // when an intersection is found, it updates the distanceToTheClosestSurface value
        // this value is used to order the new intersections, if a new intersection with a smaller baricenter.z
        // value is found, this one will become the new intersection
        if (intersection) {
            if (baricentricCoords.z < distanceToTheClosestSurface) {
                found = true;
                distanceToTheClosestSurface = baricentricCoords.z;

                intNormal = glm::normalize(
                   glm::vec3(primitive.getGlobalTransformMatrix() *
                             glm::vec4(face.getFaceNormal(), 1.0f))
                );
            }
        }
    }
    baricentricCoords.z = distanceToTheClosestSurface;
    return found;
};
        


