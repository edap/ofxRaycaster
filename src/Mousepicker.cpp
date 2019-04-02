#include "Mousepicker.h"

void ofxraycaster::Mousepicker::draw(const float radius){
    ofPushStyle();
    ofSetColor(255,0,0);
    ofDrawSphere(ray.getOrigin() + ray.getDirection() * far, radius);
    ofPopStyle();
}

ofxraycaster::Ray& ofxraycaster::Mousepicker::getRay(){
    return ray;
}

// http://antongerdelan.net/opengl/raycasting.html
void ofxraycaster::Mousepicker::setFromCamera(const glm::vec2& mouse, const ofCamera& camera){
    // set far and clip plane. Not used atm
    // but will come later with orthographic camera support(TODO)
    far = camera.getFarClip();
    near = camera.getNearClip();

    glm::vec3 screenMouse (mouse.x,mouse.y,0);
    auto worldMouse = camera.screenToWorld(screenMouse);
    auto worldMouseEnd = camera.screenToWorld(glm::vec3(screenMouse.x, screenMouse.y, 1.0f));

    auto worldMouseDirection = worldMouseEnd - worldMouse;

    ray.setup(camera.getGlobalPosition(), glm::normalize(worldMouseDirection));
};
