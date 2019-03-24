#include "ofApp.h"

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

void ofApp::update(){;
    float sinedTime = sin(ofGetElapsedTimef()* 0.5);
    ray.setDirection(glm::normalize(glm::vec2(1, sinedTime)));
}

void ofApp::draw(){
    ofPushStyle();
    ofSetColor(col3);
    poly.draw();
    ofPopStyle();

    ray.draw();

    glm::vec2 surfaceNormal; // store the intersection value
    float distance; // store the intersection value
    bool intersects = ray.intersectsPolyline(poly, distance, surfaceNormal);
    glm::vec2 intersection;

    ofPushStyle();
    // is there an intersection between the polyline and the ray?
    if (intersects) {
        // draw the ray that hits the polyline
        ofSetColor(col1);
        intersection = ray.getOrigin() + ray.getDirection() * distance;
        ofDrawLine(ray.getOrigin(), intersection);
        // draw the intersection point
        ofSetColor(col4);
        ofDrawCircle(intersection, 10);
        ofDrawBitmapString("intersection point", intersection.x+30, intersection.y+10);

        // draw the reflected ray
        ofSetColor(col2);
        auto reflectDir = glm::reflect(ray.getDirection(), surfaceNormal);
        ofDrawLine(intersection, intersection + reflectDir * ofGetWidth());
        ofDrawBitmapString("reflected light direction", intersection + reflectDir*80);
    }
    ofPopStyle();
}
