#include "Plane.h"

ofxraycaster::Plane::Plane(glm::vec3 _orig, glm::vec3 _normal){
    orig = _orig;
    normal = _normal;
}

void ofxraycaster::Plane::setup(glm::vec3 _orig, glm::vec3 _normal){
    orig = _orig;
    normal = _normal;
}

void ofxraycaster::Plane::updateNormal(glm::vec3 _normal){
    normal = _normal;
}

void ofxraycaster::Plane::updateOrigin(glm::vec3 _orig){
    orig = _orig;
}

const glm::vec3 ofxraycaster::Plane::getOrigin() {
    return orig;
}

const glm::vec3 ofxraycaster::Plane::getNormal() {
    return normal;
}

glm::vec3 ofxraycaster::Plane::arbitraryOrthogonal(const glm::vec3& vec){
    bool b0 = (vec.x <  vec.y) && (vec.x <  vec.z);
    bool b1 = (vec.y <= vec.x) && (vec.y <  vec.z);
    bool b2 = (vec.z <= vec.x) && (vec.z <= vec.y);

    auto d = glm::cross(vec, glm::vec3(int(b0), int(b1), int(b2)));
    cout << d << endl;
    return d;
}


void ofxraycaster::Plane::draw(float radius){
    ofPushStyle();
    ofSetColor(0,255,0);
    // draw position of the plane
    // TODO, draw a frid with a normal;
    ofPopStyle();
}
