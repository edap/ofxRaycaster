#pragma once
#include "ofMain.h"

namespace ofxraycaster {
    class Ray2D {
    public:
        Ray2D(){};
        ///
        /// \brief it creates a ray given an origin T and a direction T
        /// @param [in] _origin
        /// @param [in] _direction
        /// ~~~~{.cpp}
        /// Ray2D p;
        /// ~~~~
        Ray2D(glm::vec2 _origin, glm::vec2 _direction);

        /// \brief it sets the origin and direction of a ray. For example,
        /// for a 2D ray:
        ///
        /// ~~~~{.cpp}
        /// ofxraycaster::Ray2D ray;
        /// ray.setup(glm::vec2(10,5), glm::vec2(1,0));
        /// ~~~~
        void setup(glm::vec2 _origin, glm::vec2 _direction);
        /// \brief it returns the origin of the ray,
        const glm::vec2 getOrigin();
        void setOrigin(glm::vec2 _origin);
        const glm::vec2 getDirection();
        void setDirection(glm::vec2 _direction);
        void draw(float radius = 20.);
        bool intersectsSegment(const glm::vec2 & a, const glm::vec2 & b, float & distance);
        bool intersectsPolyline(const ofPolyline & poly, float & distance, glm::vec2& surfaceNormal);

    private:
        glm::vec2 origin;
        glm::vec2 direction;
    };
    
}// end namespace
