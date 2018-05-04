#pragma once

#include "ofMain.h"
#include "ofxRaycaster.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    void drawLegend(glm::vec2 rayOrig, glm::vec2 intersection,bool intersects);

    ofxraycaster::Ray<glm::vec2> ray;
    ofxraycaster::Plane plane;

    glm::vec2 p1 = glm::vec2(700, 80);
    glm::vec2 p2 = glm::vec2(900, 600);
		
};
