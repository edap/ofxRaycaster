#pragma once

#include "ofMain.h"
#include "ofxRaycaster.h"

class ofApp : public ofBaseApp{
	public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);

        void drawSphereIntersection();
        void drawPlaneIntersection();
        void drawTriangleIntersection();
        void drawPrimitiveIntersection();
        void drawLine(glm::vec3 a, glm::vec3 b, ofColor color);

        ofEasyCam camera;
        ofLight light;
        ofMaterial material;
        int scene = 4;
        glm::vec3 lookAtRay = glm::vec3(0, 200, 0);

        ofNode center;
        float sphereRadius = 200;
        ofSpherePrimitive sphere;
        ofBoxPrimitive box;
        ofPlanePrimitive planePrimitive;
        glm::vec3 planeOrigin = glm::vec3(0,500,0);
        glm::vec3 planeNormal = glm::vec3(0,-1,0);
        ofNode triangleLookAt;

        glm::vec3 rayDirection;
        glm::vec3 rayOrigin;
        ofxraycaster::Ray ray;
        ofxraycaster::Plane plane;
};
