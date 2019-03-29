#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setSize(1024,768);
    settings.setGLVersion(3, 2);
    ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
