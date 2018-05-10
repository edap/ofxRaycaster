#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ray.setup(glm::vec2(200, 400), glm::vec2(1, -0.5));
}

//--------------------------------------------------------------
void ofApp::update(){;
    float sinedTime = sin(ofGetElapsedTimef()* 1.5) * 0.3;
    ray.setDirection(glm::vec2(1, sinedTime));
}

//--------------------------------------------------------------
void ofApp::draw(){

    ray.draw();
    ofDrawLine(p1, p2);

    float distance; // store the distance value
    glm::vec2 intersection;
    bool intersects = ray.intersectsSegment(p1, p2, distance);

    ofPushStyle();
    // is there an intersection between the segment and the ray?
    if (intersects) {
        // draw the ray that hit the segment
        ofSetColor(100, 0, 100);
        intersection = ray.getOrigin() + ray.getDirection() * distance;
        ofDrawLine(ray.getOrigin(), intersection);
        // draw the reflection
        // https://glm.g-truc.net/0.9.4/api/a00131.html
        ofSetColor(60, 200, 200);

        // This is wrong, there is not such a thing as a normal of a segment.
        // But we can fake it and make the segment acts as a surface reflecting
        // light. How do we fake it?

        // we first find the direction of the segment.
        glm::vec2 segmentDir = glm::normalize(p1 - p2);
        // and then we use as normal a vector orthogonal to direction.
        glm::vec2 segmentSurfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);

        auto reflectDir = glm::reflect(ray.getDirection(), segmentSurfaceNormal);
        ofDrawLine(intersection, intersection + reflectDir * ofGetWidth());
    }
    ofPopStyle();

    drawLegend(ray.getOrigin(), intersection, intersects);
}


// This method just add a description to each element of the sketch
void ofApp::drawLegend(glm::vec2 rayOrig, glm::vec2 intersection,bool intersects){
    ofPushStyle();
    // ray
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("Origin of the ray", rayOrig.x - 200, rayOrig.y);
    ofSetColor(0, 0, 255);
    ofDrawBitmapString("Direction of the ray", rayOrig.x + 30, rayOrig.y + 10);

    // segment
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Segment", p1.x + 30, p1.y);


    if (intersects) {
        //intersection, reflected light
        ofSetColor(100, 0, 100);
        ofDrawCircle(intersection, 10);
        ofDrawBitmapString("intersection point",
                           intersection.x + 30, intersection.y + 10);
        // reflection
        ofSetColor(60,200,200);
        ofDrawBitmapString("reflected light",
                           intersection.x - 100, intersection.y - 20);
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
