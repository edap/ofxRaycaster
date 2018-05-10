#include "Ray.h"

// In this file there are only template specialization

/////////////////////////2D Methods specialization ////////////
namespace ofxraycaster {

    template<>
    void Ray<glm::vec2>::draw(float radius){
        ofPushStyle();
        // draw origin
        ofSetColor(255, 0, 0);
        ofDrawCircle(origin, radius);

        // draw direction
        ofSetColor(0,0,255);
        auto end = origin + (direction * (radius*4.));
        ofSetLineWidth(3);
        ofDrawLine(origin,end);
        ofSetLineWidth(1);
        ofPopStyle();
    }

    /////////////////////////3D Methods specialization ////////////
    template<>
    void Ray<glm::vec3>::draw(float radius){
        ofPushStyle();
        // draw origin
        ofSetColor(255, 0, 0);
        ofDrawSphere(origin, radius);

        // draw direction
        ofSetColor(0,0,255);
        auto end = origin + (direction * (radius*4.));
        ofSetLineWidth(3);
        ofDrawLine(origin,end);
        ofSetLineWidth(1);
        ofPopStyle();
    }
}





