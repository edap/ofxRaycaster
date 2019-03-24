#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(col5);
    //center.setPosition(0, 200, 0);
    light.setPosition(0, 250, 250);
    ofSetSmoothLighting(true);
    light.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    light.setSpotlight();
    light.setDiffuseColor(col3);
    light.tiltDeg(-45);
    light.setup();

    material.setShininess( 120 );
    material.setSpecularColor(ofColor(255, 0, 50));
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

    glm::vec3 baryCoord;
    glm::vec3 intersectionNormal;
    for (auto ray:rays) {

        if (ray.intersectsPrimitive(box, baryCoord, intersectionNormal)) {
            auto intersection = ray.getOrigin() + ray.getDirection() * baryCoord.z;

            // intersections points
            ofPushStyle();
            ofSetColor(col4);
            if (drawIntersections) {
                ofDrawSphere(intersection, 3);
            }

            //rays
            ofSetColor(col1);
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
