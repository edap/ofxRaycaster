#pragma once
#include "ofMain.h" // TODO how to include just glm?

namespace ofxraycaster {

template<class T>
class Plane {
public:
    Plane(){};
    Plane(T _orig, T _normal){
        orig = _orig;
        normal = _normal;
    };

    void draw(float radius = 20.);

    void setup(T _orig, T _normal){
        orig = _orig;
        normal = _normal;
    }

    void updateNormal(T _normal){
        normal = _normal;
    }

    void updateOrigin(T _orig){
        orig = _orig;
    }

    T getOrigin() const {
        return orig;
    }

    T getNormal() const {
        return normal;
    }
    

    T arbitraryOrthogonal(const T& vec);
private:
    T orig;
    T normal;


};

}// end namespace
