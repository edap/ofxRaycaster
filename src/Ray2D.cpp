#include "Ray2D.h"

ofxraycaster::Ray2D::Ray2D(glm::vec2 _origin, glm::vec2 _direction){
  origin = _origin;
  direction = glm::normalize(_direction);
};

/// \brief it sets the origin and direction of a ray. For example,
/// for a 2D ray:
///
/// ~~~~{.cpp}
/// ofxraycaster::Ray2D ray;
/// ray.setup(glm::vec2(10,5), glm::vec2(1,0));
/// ~~~~
void ofxraycaster::Ray2D::setup(glm::vec2 _origin, glm::vec2 _direction){
  origin = _origin;
  direction = glm::normalize(_direction);
};

/// \brief it returns the origin of the ray,
const glm::vec2 ofxraycaster::Ray2D::getOrigin(){
  return origin;
};

void ofxraycaster::Ray2D::setOrigin(glm::vec2 _origin){
  origin = _origin;
};

const glm::vec2 ofxraycaster::Ray2D::getDirection(){
  return direction;
};

void ofxraycaster::Ray2D::setDirection(glm::vec2 _direction){
  direction = _direction;
};

void ofxraycaster::Ray2D::draw(float radius){
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
};



bool ofxraycaster::Ray2D::intersectsSegment(const glm::vec2 & a, const glm::vec2 & b, float & distance){
  bool intersects = false;
  distance = std::numeric_limits<float>::infinity();

  float x = origin.x;
  float y = origin.y;
  float dx = direction.x;
  float dy = direction.y;

  float s, denom;
  if (dy / dx != (b.y - a.y) / (b.x - a.x)){
      denom = ((dx * (b.y - a.y)) - dy * (b.x - a.x));
      if (denom != 0) {
          distance = (((y - a.y) * (b.x - a.x)) - (x - a.x) * (b.y - a.y)) / denom;
          s = (((y - a.y) * dx) - (x - a.x) * dy) / denom;
          if (distance >= 0 && s >= 0 && s <= 1) {
              intersects = true;
              //return { x: x + r * dx, y: y + r * dy };
          }
      }
  }

  return intersects;

};

bool ofxraycaster::Ray2D::intersectsPolyline(const ofPolyline & poly, float & distance, glm::vec2& surfaceNormal){

  vector<glm::vec3> container = poly.getVertices();
  distance = std::numeric_limits<float>::infinity();
  bool intersects = false;
  for (int i = 0; i < container.size(); i++) {
      // If it is an opened polyline, do not check for the intersection
      // between the last point of the polyline and the first one
      if (!poly.isClosed() && i == container.size() -1) {
          continue;
      }

      // qui in realta' dovresti chiudere solo se la poly e' closed.
      auto endSegmentIndex = container.size() == (i + 1) ? 0 : i + 1;

      float tmpDistance = distance;
      bool tmpIntersect =
          intersectsSegment(container[i],
                                    container[endSegmentIndex],
                                    tmpDistance);
      if (tmpIntersect) {
          if (intersects == false) { intersects = true; };
          if (tmpDistance < distance) {
              //first find the direction of the segment.
              glm::vec2 segmentDir = glm::normalize(container[i] - container[endSegmentIndex]);
              // and then use as normal a vector orthogonal to the direction.
              surfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);
              distance = tmpDistance;
          }
      }

  }

  return intersects;
};




  
