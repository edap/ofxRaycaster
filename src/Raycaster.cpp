#include "Raycaster.h"

ofxraycaster::Raycaster::Raycaster(const glm::vec3 _origin, const glm::vec3 _direction, const float _near, const float _far){
    ray.setup( _origin, _direction );
    near = _near;
    far = _far;
};

void ofxraycaster::Raycaster::set(const glm::vec3 _origin, const glm::vec3 _direction){
    ray.setup( _origin, _direction );
}

void ofxraycaster::Raycaster::draw(){
    ofPushStyle();
    ofSetColor(255,0,0);
    ofDrawSphere(ray.getOrigin() + ray.getDirection() * 2000, 5);
    ofPopStyle();
}

// http://antongerdelan.net/opengl/raycasting.html
void ofxraycaster::Raycaster::setFromCamera(const glm::vec2 coords, const ofCamera camera){

    // 2d Viewport Coordinates
    float x = (2.0f * coords.x) / ofGetWidth() - 1.0f;
    float y = 1.0f - (2.0f * coords.y) / ofGetHeight();

    // 3D Normalised Device Coordinates
    float z = -1.0f; // the camera looks on the negative z axis
    glm::vec3 rayNds = glm::vec3(x, y, z);


    // 4D Homogeneous Clip Coordinates
    glm::vec4 rayClip = glm::vec4(rayNds, 1.0);

    // 4D Eye (Camera) Coordinates
    glm::vec4 rayEye = glm::inverse(camera.getProjectionMatrix()) * rayClip;

    // Now, we only needed to un-project the x,y part, so let's manually set the z,w part to mean "forwards, and not a point". From http://antongerdelan.net/opengl/raycasting.html
    rayEye = glm::vec4(rayEye.x,rayEye.y, -1.0, 0.0);

    // 4D World Coordinates
    glm::vec3 rayWorld = glm::vec3(glm::inverse(camera.getModelViewMatrix()) * rayEye);

    rayWorld = glm::normalize(rayWorld);


    ray.setup(camera.getGlobalPosition(), rayWorld);
};
