#include "ofMain.h"
#include "Plane.h"
#include "Ray.h"


/// \brief it creates a ray given an origin T and a direction T
/// @param [in] _origin
/// @param [in] _direction
ofxraycaster::Ray::Ray(glm::vec3 _origin, glm::vec3 _direction){
    origin = _origin;
    direction = glm::normalize(_direction);
}

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
}

/// \brief it returns the origin of the ray,
const glm::vec3 ofxraycaster::Ray::getOrigin() {
    return origin;
}

void ofxraycaster::Ray::setOrigin(glm::vec3 _origin){
    origin = _origin;
}

const glm::vec3 ofxraycaster::Ray::getDirection() {
    return direction;
}

void ofxraycaster::Ray::setDirection(glm::vec3 _direction){
    direction = _direction;
}

void ofxraycaster::Ray::draw(float radius){
    ofPushStyle();
    // draw origin
    ofSetColor(246,233,101);
    ofDrawSphere(origin, radius);

    // draw direction
    auto end = origin + (direction * (radius*10.0f));
    ofSetLineWidth(3);
    ofDrawLine(origin,end);
    ofSetLineWidth(1);
    ofPopStyle();
}

bool ofxraycaster::Ray::intersectsPlane(ofxraycaster::Plane plane, float & distance){
    return glm::intersectRayPlane(origin, direction,
                                  plane.getOrigin(), plane.getNormal(),
                                  distance);
}

bool ofxraycaster::Ray::intersectsTriangle(glm::vec3 const & vert0, glm::vec3 const & vert1, glm::vec3 const & vert2, glm::vec2 & baryPosition, float &distance){
    return glm::intersectRayTriangle(origin, direction, vert0, vert1, vert2, baryPosition, distance);
}

bool ofxraycaster::Ray::intersectsSphere(const glm::vec3 & _center, const float & _radius, glm::vec3& _position, glm::vec3 & _normal){

    return glm::intersectRaySphere(origin, direction, _center, _radius, _position, _normal);
}

bool ofxraycaster::Ray::intersectsPrimitive(const of3dPrimitive& primitive,  glm::vec2 & baricentricCoords, float &distance, glm::vec3 & intNormal) {
    // at the beginning, no intersection is found and the distance to the closest surface
    // is set to an high value;
    bool found = false;
    float distanceToTheClosestSurface = std::numeric_limits<float>::max();
    for (const ofMeshFace& face : primitive.getMesh().getUniqueFaces()) {
        bool intersection = glm::intersectRayTriangle(
                                                      origin, direction,
                                                      glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(0), 1.f)),
                                                      glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(1), 1.f)),
                                                      glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(2), 1.f)),
                                                      baricentricCoords,
                                                      distance);
        // when an intersection is found, it updates the distanceToTheClosestSurface value
        // this value is used to order the new intersections, if a new intersection with a smaller baricenter.z
        // value is found, this one will become the new intersection
        if (intersection) {
            if (distance < distanceToTheClosestSurface) {
                found = true;
                distanceToTheClosestSurface = distance;

                intNormal = glm::normalize(
                   glm::vec3(primitive.getGlobalTransformMatrix() *
                             glm::vec4(face.getFaceNormal(), 1.0f))
                );
            }
        }
    }
    distance = distanceToTheClosestSurface;
    return found;
}

bool ofxraycaster::Ray::intersectsMesh(const ofMesh& mesh, glm::vec2 & baricentricCoords, float &distance, glm::vec3 & intNormal){

    // Guards. intersectsMesh only works with indexed geometries of
    // traingles
    if (mesh.getMode() != OF_PRIMITIVE_TRIANGLES) {
        ofLog() << "intersectsMesh works only with OF_PRIMITIVE_TRIANGLES";
        return false;
    }

    if (mesh.getNumIndices() < 3) {
        ofLog() << "mesh intersection works only with indexed geometries";
        return false;
    }

    if (mesh.getNumIndices()%3 != 0) {
        ofLog() << "the total number of the indices is not a multiple of 3";
        return false;
    }

    // at the beginning, no intersection is found and the distance
    // to the closest surface is set to an high value;
    bool found = false;
    float distanceToTheClosestSurface = std::numeric_limits<float>::max();
    for (unsigned int i = 0; i< mesh.getNumIndices(); i+=3) {
        bool intersection = glm::intersectRayTriangle(
                              origin, direction,
                              mesh.getVertex(mesh.getIndex(i)),
                              mesh.getVertex(mesh.getIndex(i+1)),
                              mesh.getVertex(mesh.getIndex(i+2)),
                              baricentricCoords,
                              distance
        );

        // when an intersection is found, it updates the distanceToTheClosestSurface value
        // this value is used to order the new intersections, if a new intersection with a smaller baricenter.z
        // value is found, this one will become the new intersection
        if (intersection) {
            if (distance < distanceToTheClosestSurface) {
                found = true;
                distanceToTheClosestSurface = distance;

                const int ia = mesh.getIndex(i);
                const int ib = mesh.getIndex(i+1);
                const int ic = mesh.getIndex(i+2);

                glm::vec3 e1 = mesh.getVertex(ia) - mesh.getVertex(ib);
                glm::vec3 e2 = mesh.getVertex(ic) - mesh.getVertex(ib);

                intNormal = glm::cross(e1,e2);
            }
        }
    }
    distance = distanceToTheClosestSurface;
    return found;
}

bool ofxraycaster::Ray::intersectsMesh(const ofMesh& mesh, const glm::mat4& transformationMatrix, glm::vec2 & baricentricCoords, float &distance, glm::vec3 & intNormal){

    // Guards. intersectsMesh only works with indexed geometries of
    // traingles
    if (mesh.getMode() != OF_PRIMITIVE_TRIANGLES) {
        ofLog() << "intersectsMesh works only with OF_PRIMITIVE_TRIANGLES";
        return false;
    }

    if (mesh.getNumIndices() < 3) {
        ofLog() << "mesh intersection works only with indexed geometries";
        return false;
    }

    if (mesh.getNumIndices()%3 != 0) {
        ofLog() << "the total number of the indices is not a multiple of 3";
        return false;
    }

    // at the beginning, no intersection is found and the distance
    // to the closest surface is set to an high value;
    bool found = false;
    float distanceToTheClosestSurface = std::numeric_limits<float>::max();
    for (unsigned int i = 0; i< mesh.getNumIndices(); i+=3) {
        bool intersection = glm::intersectRayTriangle(
                              origin, direction,
                              glm::vec3(transformationMatrix * glm::vec4(mesh.getVertex(mesh.getIndex(i)), 1.0f)),
                              glm::vec3(transformationMatrix * glm::vec4(mesh.getVertex(mesh.getIndex(i+1)), 1.0f)),
                              glm::vec3(transformationMatrix * glm::vec4(mesh.getVertex(mesh.getIndex(i+2)), 1.0f)),
                              baricentricCoords,
                              distance
        );


        if (intersection) {
            if (distance < distanceToTheClosestSurface) {
                found = true;
                distanceToTheClosestSurface = distance;

                const int ia = mesh.getIndex(i);
                const int ib = mesh.getIndex(i+1);
                const int ic = mesh.getIndex(i+2);

                glm::vec3 e1 = mesh.getVertex(ia) - mesh.getVertex(ib);
                glm::vec3 e2 = mesh.getVertex(ic) - mesh.getVertex(ib);
                glm::vec4 no = glm::vec4(glm::cross(e1,e2), 1.0f);
                
                intNormal = glm::vec3(transformationMatrix * no);
            }
        }
    }
    distance = distanceToTheClosestSurface;
    return found;
}
