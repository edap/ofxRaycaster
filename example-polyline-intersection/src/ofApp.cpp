#include "ofApp.h"

void ofApp::setup(){
    ofBackground(col3);
    ray.setup(glm::vec2(200, 400), glm::vec2(1, -0.5));

    yoff = 0;
    radius = 200;
}

void ofApp::update(){;
    float sinedTime = sin(ofGetElapsedTimef()* 0.5);
    ray.setDirection(glm::normalize(glm::vec2(1, sinedTime)));
}

void ofApp::draw(){
    poly.clear();
    xoff = 0;
    for(float angle = 0; angle < TWO_PI; angle+= 0.1 ){
        float newRadius = radius + ofMap(ofNoise(xoff+yoff), 0, 1, -25, 25);
        float x = offset.x + newRadius * cos(angle);
        float y = offset.y + newRadius * sin(angle);
        poly.addVertex(x, y);

        xoff += 0.15;
    }
    yoff += 0.05;
    poly.setClosed(true);

    ofPushStyle();
    ofSetColor(col4);
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
