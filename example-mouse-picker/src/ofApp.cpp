#include "ofApp.h"

void ofApp::setup(){
    cam.setPosition(0,50, 1000);

    icosphere.set(200, 1);
    mesh.append(icosphere.getMesh());

    light.setAmbientColor(col4);
    light.setup();
    light.setPosition(200,600,400);
    light.enable();

    material.setAmbientColor(col4);

    for (unsigned int i = 0; i < 140; i++) {
        ofIcoSpherePrimitive ico(50, 1);
        ico.setPosition(ofRandom(-ofGetWidth()/2.0f, ofGetWidth()/2.0f),
                        ofRandom(ofGetHeight()/2.0f, -ofGetHeight()/2.0f),
                        ofRandom(400, -400));
        icospheres.push_back(ico);
    }

    ofEnableDepthTest();
}

void ofApp::update(){

}

void ofApp::draw(){
    ofBackground(col3);
    cam.begin();
    light.draw();

    material.begin();

    glm::vec2 baricentricCoordinates;
    float distance;
    glm::vec3 surfaceNormal;
    bool found = false;
    unsigned int indexIntersectedPrimitive = 0;
    float distanceToClosestIntersection = numeric_limits<float>::max();

    // iterates through all the primitives and find the closest one.
    for (unsigned int i = 0; i<icospheres.size(); i++) {
        auto & ico = icospheres.at(i);
        ico.draw();

        bool intersects = mousepicker.getRay().intersectsPrimitive(ico,  baricentricCoordinates, distance, surfaceNormal);
        if (intersects && (distance < distanceToClosestIntersection)) {
            found = true;
            distanceToClosestIntersection = distance;
            indexIntersectedPrimitive = i;
        }

    }
    material.end();

    if (found) {
        ofPushStyle();
        ofSetColor(col5);
        auto intersection = mousepicker.getRay().getOrigin() +
                            mousepicker.getRay().getDirection() *
                            distanceToClosestIntersection;
        ofDrawSphere(intersection, 5);
        icospheres.at(indexIntersectedPrimitive).drawWireframe();
        ofPopStyle();
    }

    mousepicker.draw();
    cam.end();
}

void ofApp::mouseMoved(int x, int y ){
    mousepicker.setFromCamera(glm::vec2(x,y), cam);
};

