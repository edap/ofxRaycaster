#pragma once

#include "ofMain.h"
#include "ofxRaycaster.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    ofEasyCam camera;
    ofLight light;
    ofMaterial material;
    ofBoxPrimitive box;
    ofxPanel gui;
    ofParameter<bool> drawReflected = {"draw reflected rays", false};
    ofParameter<int> reflectedLength = {"reflected rays length", 100, 10, 1000};
    ofParameter<bool> drawRays = {"draw rays", true};
    ofParameter<bool> drawIntersections = {"draw intersections", true};
    ofParameter<bool> drawPrimitive = {"draw cube", false};


    std::vector<ofxraycaster::Ray> rays;
private:
    glm::vec3 getRandomDir() const;
    ofFloatColor col1 = ofFloatColor(ofColor(246,233,101));
    ofFloatColor col2 = ofFloatColor(ofColor(85,255,60));
    ofFloatColor col3 = ofFloatColor(ofColor(20,164,204));
    ofFloatColor col4 = ofFloatColor(ofColor(180,0,131));
    ofFloatColor col5 = ofFloatColor(ofColor(0,0,0));
};
