#pragma once
#include "ofMain.h"
#include "ofxRaycaster.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    ofxraycaster::Ray2D ray;
    ofPolyline poly;

    ofFloatColor col1 = ofFloatColor(ofColor(246,233,101));
    ofFloatColor col2 = ofFloatColor(ofColor(85,255,60));
    ofFloatColor col3 = ofFloatColor(ofColor(20,164,204));
    ofFloatColor col4 = ofFloatColor(ofColor(180,0,131));
    ofFloatColor col5 = ofFloatColor(ofColor(0,0,0));

    glm::vec2 offset = glm::vec2(ofGetWidth()/2, ofGetHeight()/2);
    float angle;
    float xoff;
    float yoff;
    float radius;
};
