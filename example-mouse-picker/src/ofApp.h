#pragma once

#include "ofMain.h"
#include "ofxRaycaster.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y );

    ofFloatColor col1 = ofFloatColor(ofColor(246,233,101));
    ofFloatColor col2 = ofFloatColor(ofColor(85,255,60));
    ofFloatColor col3 = ofFloatColor(ofColor(20,164,204));
    ofFloatColor col4 = ofFloatColor(ofColor(180,0,131));
    ofFloatColor col5 = ofFloatColor(ofColor(0,0,0));

    ofMesh mesh;
    ofCamera cam;
    ofLight light;
    ofMaterial material;
    ofIcoSpherePrimitive icosphere;

    vector<ofIcoSpherePrimitive> icospheres;
    ofxraycaster::Mousepicker mousepicker;

};
