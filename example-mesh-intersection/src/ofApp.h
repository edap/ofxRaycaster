#pragma once

#include "ofMain.h"
#include "ofxRaycaster.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofxraycaster::Ray ray;
    glm::vec2 p1 = glm::vec2(400, 80);
    glm::vec2 p2 = glm::vec2(600, 600);
    ofFloatColor col1 = ofFloatColor(ofColor(246,233,101));
    ofFloatColor col2 = ofFloatColor(ofColor(85,255,60));
    ofFloatColor col3 = ofFloatColor(ofColor(20,164,204));
    ofFloatColor col4 = ofFloatColor(ofColor(180,0,131));
    ofFloatColor col5 = ofFloatColor(ofColor(0,0,0));

    ofMesh mesh;
    ofNode node;
    ofEasyCam cam;
    ofLight light;
    ofMaterial material;
    ofIcoSpherePrimitive icosphere;

    bool transformation = false;
    

    
};
