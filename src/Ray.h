#pragma once
#include "ofMain.h"
#include "Plane.h"

namespace ofxraycaster {
    class Ray {
    public:
        Ray(){};
        ///
        /// \brief it creates a ray given an origin T and a direction T
        /// @param [in] _origin
        /// @param [in] _direction
        /// ~~~~{.cpp}
        /// ofPixels p;
        /// ofLoadImage(p, "pathToImage.jpg");
        /// ~~~~
        Ray(glm::vec3 _origin, glm::vec3 _direction);

        /// \brief it sets the origin and direction of a ray. For example,
        /// for a 3D ray:
        ///
        /// ~~~~{.cpp}
        /// ofxraycaster::Ray3D ray;
        /// ray.setup(glm::vec3(10,5,0), glm::vec2(1,0,0));
        /// ~~~~
        void setup(glm::vec3 _origin, glm::vec3 _direction);

        const glm::vec3 getOrigin();
        void setOrigin(glm::vec3  _origin);
        const glm::vec3  getDirection();
        void setDirection(glm::vec3 _direction);
        void draw(float radius = 20.);
        bool intersectsPlane(ofxraycaster::Plane plane, float & distance);
        bool intersectsTriangle(glm::vec3 const & vert0, glm::vec3 const & vert1, glm::vec3 const & vert2, glm::vec3 & baryPosition);
        bool intersectsSphere(const glm::vec3 & _center, const float & _radius, glm::vec3& _position, glm::vec3 & _normal);
        bool intersectsPrimitive(const of3dPrimitive& primitive,  glm::vec3 & baricentricCoords, glm::vec3 & intNormal);
        bool intersectsMesh(const ofMesh& mesh,  glm::vec3 & baricentricCoords, glm::vec3 & intNormal);
        bool intersectsMesh(const ofMesh& mesh, const glm::mat4& transformationMatrix,  glm::vec3 & baricentricCoords, glm::vec3 & intNormal);


    private:
        glm::vec3 origin;
        glm::vec3 direction;
    };
}

