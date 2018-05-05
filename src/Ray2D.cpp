#include "Ray2D.h"

void ofxraycaster::Ray2D::setup(glm::vec2 _origin, glm::vec2 _direction){
    origin = _origin;
    direction = glm::normalize(_direction);
}

void ofxraycaster::Ray2D::setDirection(glm::vec2 _direction){
    direction = _direction;
};

glm::vec2 ofxraycaster::Ray2D::getOrigin() const {
    return origin;
};

glm::vec2 ofxraycaster::Ray2D::getDirection() const{
    return direction;
};

void ofxraycaster::Ray2D::draw(float radius){
    ofPushStyle();
    // draw origin
    ofSetColor(255, 0, 0);
    ofDrawCircle(origin.x, origin.y, radius);

    // draw direction
    ofSetColor(0,0,255);
    auto end = origin + (direction * (radius*4.));
    ofSetLineWidth(3);
    ofDrawLine(origin,end);
    ofSetLineWidth(1);
    ofPopStyle();
}

void ofxraycaster::Ray2D::intersectsPolyline(const ofPolyline& poly, bool& intersects, float& distance) {

}

void ofxraycaster::Ray2D::intersectsPlane(Plane plane, glm::vec2& intersection, bool& intersects){
    float distance;
    intersects = glm::intersectRayPlane(origin, direction,
                                        plane.getOrigin(), plane.getNormal(),
                                        distance);
    if (intersects) {
        intersection = origin + direction*distance;
    }
};

// https://gamedev.stackexchange.com/questions/109420/ray-segment-intersection
void ofxraycaster::Ray2D::intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool& intersects){
    intersects = false;
    //(x, y, dx, dy, x1, y1, x2, y2);
    float x = origin.x;
    float y = origin.y;
    float dx = direction.x;
    float dy = direction.y;

    float r, s, denom;
    //Make sure the lines aren't parallel, can use an epsilon here instead
    // Division by zero in C# at run-time is infinity. In JS it's NaN
    if (dy / dx != (b.y - a.y) / (b.x - a.x)){
        denom = ((dx * (b.y - a.y)) - dy * (b.x - a.x));
        if (denom != 0) {
            r = (((y - a.y) * (b.x - a.x)) - (x - a.x) * (b.y - a.y)) / denom;
            s = (((y - a.y) * dx) - (x - a.x) * dy) / denom;
            if (r >= 0 && s >= 0 && s <= 1) {
                intersects = true;
                intersection.x = x + r * dx;
                intersection.y = y + r * dy;
                //return { x: x + r * dx, y: y + r * dy };
            }
        }
    }
};

//float Ray::distanceToPlane(Plane plane) const{
//    float distance;
//    auto inter = glm::intersectRayPlane(origin, direction,
//                                        plane.getOrigin(), plane.getNormal(),
//                                        distance);
//    return distance;
//};
//
//bool Ray::intersectsPlane(Plane plane) const{
//    float distance;
//    return glm::intersectRayPlane(origin, direction,
//                                  plane.getOrigin(), plane.getNormal(),distance);
//};
