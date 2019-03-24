#include "ofApp.h"

void ofApp::setup(){
    ray.setup(glm::vec2(200, 400), glm::vec2(1, -0.5));
}

void ofApp::update(){;
    float sinedTime = sin(ofGetElapsedTimef()* 1.5) * 0.3;
    ray.setDirection(glm::vec2(1, sinedTime));
}

void ofApp::draw(){
    ofBackground(col5);
    ray.draw();
    ofSetColor(col3);
    ofDrawLine(p1, p2);

    float distance; // store the distance value
    glm::vec2 intersection;
    bool intersects = ray.intersectsSegment(p1, p2, distance);

    ofPushStyle();
    // is there an intersection between the segment and the ray?
    if (intersects) {
        // draw the ray that hit the segment
        ofSetColor(col1);
        intersection = ray.getOrigin() + ray.getDirection() * distance;
        ofDrawLine(ray.getOrigin(), intersection);
        // draw the reflection
        // https://glm.g-truc.net/0.9.4/api/a00131.html

        //intersection
        ofSetColor(col4);
        ofDrawCircle(intersection, 10);
        ofDrawBitmapString("intersection point",
                           intersection.x + 30, intersection.y + 10);
        // reflection
        ofSetColor(col2);

        // There is not such a thing as a normal of a segment.
        // But we can fake it and make the segment acts as a surface reflecting light.

        // We first find the direction of the segment.
        glm::vec2 segmentDir = glm::normalize(p1 - p2);
        // and then we use as normal a vector orthogonal to direction.
        glm::vec2 segmentSurfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);

        auto reflectDir = glm::reflect(ray.getDirection(), segmentSurfaceNormal);
        ofDrawLine(intersection, intersection + reflectDir * ofGetWidth());

        ofDrawBitmapString("reflected light",
                           intersection + reflectDir * 100);
    }
    ofPopStyle();
}


