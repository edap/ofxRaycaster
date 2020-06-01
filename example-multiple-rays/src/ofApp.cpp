#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(col3);
    //center.setPosition(0, 200, 0);
    light.setPosition(0, 250, 250);
    ofSetSmoothLighting(true);
    light.setSpotlight();
    light.setDiffuseColor(col4);
    light.tiltDeg(-45);
    light.setup();

    material.setAmbientColor(col4);
    box.set(100);

    for(int i = 0; i< 300; i++){
        auto d = getRandomDir();
        auto pos = d * 200.0f;
        auto invDir = glm::normalize(glm::vec3(0.0f,0.0f,0.0f)-
                                               pos);
        ofxraycaster::Ray ray;
        ray.setup(pos, invDir);
        rays.push_back(ray);
    }
    gui.setup();

    gui.add(drawReflected);
    gui.add(reflectedLength);
    gui.add(drawPrimitive);
    gui.add(drawRays);
    gui.add(drawIntersections);
}

glm::vec3 ofApp::getRandomDir() const{
    float x = ofRandom(-1.0f, 1.0f);
    float y = ofRandom(-1.0f, 1.0f);
    float z = ofRandom(-1.0f, 1.0f);
    return glm::normalize(glm::vec3(x, y, z));
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    box.rollDeg(0.2f);
    box.panDeg(1.0f);
    box.tiltDeg(-1.0f);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    camera.begin();
    if (drawPrimitive) {
        material.begin();
        box.draw();
        material.end();
    }

    glm::vec2 baryCoord;
    float distance;
    glm::vec3 intersectionNormal;
    for (auto ray:rays) {

        if (ray.intersectsPrimitive(box, baryCoord, distance, intersectionNormal)) {
            auto intersection = ray.getOrigin() + ray.getDirection() * distance;

            // intersections points
            ofPushStyle();
            ofSetColor(col1);
            if (drawIntersections) {
                ofDrawSphere(intersection, 3);
            }

            //rays
            if (drawRays) {
                ofDrawLine(ray.getOrigin(), intersection);
            }
            ofPopStyle();

            ofPushStyle();
            ofSetColor(col2);

            // reflections
            if (drawReflected) {
                auto reflLightDir = glm::reflect(ray.getDirection(),intersectionNormal);
                ofDrawLine(intersection, intersection + reflectedLength.get() * reflLightDir);
            }
            ofPopStyle();
        }

    }
    camera.end();

    ofDisableDepthTest();
    gui.draw();

}
