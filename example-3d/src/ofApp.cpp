#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(80, 80, 200);
    center.setPosition(0, 200, 0);
    light.setPosition(0, 400, 400);
    ofSetSmoothLighting(true);
    light.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    light.setSpotlight();
    light.setDiffuseColor(ofFloatColor::yellow);
    light.tiltDeg(-45);
    light.setup();

    material.setShininess( 120 );
    material.setSpecularColor(ofColor(255, 255, 255, 255));

    rayDirection = glm::vec3(0,1,0);
    rayOrigin = glm::vec3(0, -300, 0);
    ray.setup(rayOrigin, rayDirection);

    //triangle
    triangleLookAt.setPosition(0,0, 100);
    triangleLookAt.setParent(center);

    //sphere
    sphere.setResolution(100);
    sphere.setRadius(sphereRadius);
    sphere.setParent(center);

    //box
    box.set(sphereRadius);
    box.setParent(center);

    //plane
    // A plane is infinite, therefore the ofPlanePrimitive is not correct,
    // but it is useful to visualize the plane
    planePrimitive = ofPlanePrimitive(ofGetWidth()*2, ofGetHeight()*2, 20, 20);
    planePrimitive.setPosition(planeOrigin);
    planePrimitive.tiltDeg(90);
    plane.setup(planeOrigin, planeNormal);

    center.rollDeg(30.0f);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    lookAtRay.x= ofMap(sin(ofGetElapsedTimef()), -1, 1, -300, 300);
    rayDirection = glm::normalize(lookAtRay - rayOrigin);
    ray.setDirection(rayDirection);

    if(scene == 4){
        center.setPosition(0, 200, 0);
        center.rollDeg(0.5f);
    }else if(scene == 1){
        center.truck(sin(ofGetElapsedTimef())*5);
    }else if(scene == 2 || scene == 3){
        center.setPosition(0, 200, 0);
        center.panDeg(0.2);
        center.tiltDeg(0.2);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapString("press 1 to 4 to change the intersection modes", 10, 20);
    ofEnableDepthTest();
    camera.begin();
    //ofDrawAxis(200);

    light.draw();

    switch(scene) {
        case 1:
            drawSphereIntersection();
            break;
        case 2:
            drawPlaneIntersection();
            break;
        case 3:
            drawTriangleIntersection();
            break;
        case 4:
            drawPrimitiveIntersection();
            break;
        default:
            drawSphereIntersection();
            break;
    }
    camera.end();
}

void ofApp::drawSphereIntersection(){
    material.begin();
    sphere.draw();
    material.end();

    ray.draw();
    glm::vec3 position;
    glm::vec3 normal;

    if(ray.intersectsSphere(sphere.getGlobalPosition(),
                             sphereRadius,
                             position,
                             normal)){
        // ray hits
        drawLine(ray.getOrigin(), position, ofFloatColor::red);
        // reflected light
        auto reflDir = glm::reflect(ray.getDirection(),normal);
        drawLine(position, position + reflDir * ofGetWidth(), ofFloatColor::orange);
    }
};

void ofApp::drawPlaneIntersection(){
    ray.draw();
    material.begin();
    planePrimitive.draw();
    material.end();

    float distance;
    if(ray.intersectsPlane(plane, distance)){
        auto position = ray.getOrigin() + ray.getDirection() * distance;
        // ray hits
        drawLine(ray.getOrigin(), position, ofFloatColor::red);
        // reflected light
        auto reflDir = glm::reflect(ray.getDirection(),planeNormal);
        drawLine(position, position + reflDir * ofGetWidth(), ofFloatColor::orange);
    }
};

void ofApp::drawTriangleIntersection(){
    glm::vec3 baryCoordinates;
    ofNode v1,v2,v3;

    v1.setPosition(-200, -200, 0);
    v2.setPosition(0, 200, 0);
    v3.setPosition(+200, -200, 0);
    v1.setParent(center);
    v2.setParent(center);
    v3.setParent(center);

    material.begin();
    ofDrawTriangle(v1.getGlobalPosition(),
                   v2.getGlobalPosition(),
                   v3.getGlobalPosition());

    auto a = v1.getGlobalPosition();
    auto b = v2.getGlobalPosition();
    auto c = v3.getGlobalPosition();
    ofDrawTriangle(a,b,c);
    //triangleLookAt.draw();
    material.end();
    
    ray.draw();

    if(ray.intersectsTriangle(a,b,c, baryCoordinates)){
        auto pos = ray.getOrigin() + ray.getDirection() * baryCoordinates.z;
        drawLine(ray.getOrigin(), pos, ofFloatColor::red);
        // reflected light
        auto triangleNormal = glm::normalize(triangleLookAt.getGlobalPosition() - center.getGlobalPosition());
        auto reflLight = glm::reflect(ray.getDirection(), triangleNormal);
        drawLine(pos, ray.getOrigin() + 100 * reflLight, ofFloatColor::orange);
    }
};

void ofApp::drawPrimitiveIntersection(){

    material.begin();
    box.draw();
    material.end();
    ray.draw();

    glm::vec3 baricentricCoordinates;
    glm::vec3 intNormal;
    if(ray.intersectsPrimitive(box, baricentricCoordinates, intNormal)){

        auto intersection = ray.getOrigin() +
            ray.getDirection() * baricentricCoordinates.z;

        drawLine(ray.getOrigin(), intersection, ofFloatColor::red);
        // reflected light
        auto reflLight = glm::reflect(ray.getDirection(),intNormal);
        drawLine(intersection, ray.getOrigin() + 100 * reflLight, ofFloatColor::orange);
    }
};

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case '1':
            scene = 1;
            break;
        case '2':
            scene = 2;
            break;
        case '3':
            scene = 3;
            break;
        case '4':
            scene = 4;
            break;
        default:
            scene = 1;
            break;
    }
}

void ofApp::drawLine(glm::vec3 a, glm::vec3 b, ofColor color){
    ofPushStyle();
    ofSetLineWidth(20);
    ofSetColor(color);
    ofDrawLine(a, b);
    ofPopStyle();
};

