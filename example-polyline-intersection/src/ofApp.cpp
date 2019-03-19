#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ray.setup(glm::vec2(200, 400), glm::vec2(1, -0.5));
    poly.addVertex(400, 100);
    poly.addVertex(800, 100);
    poly.addVertex(800, 600);
    poly.addVertex(400, 600);
    poly.close();
    poly.rotateDeg(45, glm::vec3(0,0,1));
    poly.translate(glm::vec2(500, -250));

}

//--------------------------------------------------------------
void ofApp::update(){;
    float sinedTime = sin(ofGetElapsedTimef()* 0.5);
    ray.setDirection(glm::vec2(1, sinedTime));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushStyle();
    ofSetColor(ofColor(0, 255, 0));
    poly.draw();
    ofPopStyle();

    ray.draw();

    glm::vec2 surfaceNormal; // store the intersection value
    float distance; // store the intersection value
    bool intersects = ray.intersectsPolyline(poly, distance, surfaceNormal);
    glm::vec2 intersection;

    ofPushStyle();
    // is there an intersection between the plane and the ray?
    if (intersects) {
        // draw the ray that hit the plane
        ofSetColor(100,0,100);
        intersection = ray.getOrigin() + ray.getDirection() * distance;
        ofDrawLine(ray.getOrigin(), intersection);

        // draw the reflected ray
        ofSetColor(50, 100, 200);
        auto reflectDir = glm::reflect(ray.getDirection(), surfaceNormal);
        ofDrawLine(intersection, intersection + reflectDir * ofGetWidth());
    }
    ofPopStyle();

    drawLegend(ray.getOrigin(), intersection, intersects);


}


// This method just add a description to each element of the sketch
void ofApp::drawLegend(glm::vec2 rayOrig, glm::vec2 intersection,bool intersects){

    ofPushStyle();
    // ray
    ofSetColor(255,0,0);
    ofDrawBitmapString("Origin of the ray", rayOrig.x-200, rayOrig.y);
    ofSetColor(0,0,255);
    ofDrawBitmapString("Direction of the ray", rayOrig.x+30, rayOrig.y+10);


    if (intersects) {
        //intersection, reflected light
        ofSetColor(255);
        ofDrawCircle(intersection, 10);
        ofDrawBitmapString("intersection point", intersection.x+30, intersection.y+10);
    }
    ofPopStyle();
};

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
