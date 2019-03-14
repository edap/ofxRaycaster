# ofxRaycaster

[![Build status](https://travis-ci.org/edap/ofxRaycaster.svg?branch=master)](https://travis-ci.org/edap/ofxRaycaster)
[![Build status](https://ci.appveyor.com/api/projects/status/p7l03tb6m1ctxbju?svg=true)](https://ci.appveyor.com/project/edap/ofxraycaster)
![img](img/screenshot.png)


This addon contains a definition of a ray in 2D and 3D dimension, and it includes methods to check for intersection with ofPrimitives, ofPolylines, segments, Plane etc ...

## How to use it:
Download this addon in your `addons` folder. Create a new project with the project generator and add as addon `ofxRaycaster`.
In your project, add at the top of your `ofApp.h` file

```cpp
#include "ofxRaycaster.h"
```
Now you are ready to use rays. To get started using a 2D ray in your project, declare a `ray` variable in your `ofApp.h` header file:

```cpp
ofxraycaster::Ray<glm::vec2> ray;
```

If you want to get your hands dirty with 3D rays, use instead of a 2D ray, a 3D one.
```cpp
ofxraycaster::Ray<glm::vec3> ray;
```

## Generic methods, for both 2D and 3D rays:

#### setup

```cpp
void setup(T _origin, T _direction)
```
it sets the origin and direction of a ray. For example, for a 2D ray:

```
ray.setup(glm::vec2(10,5), glm::vec2(1,0));
```

#### getOrigin

```cpp
T getOrigin();
```
It returns the origin of the vector. For example, for the 2D ray previously greated:
```cpp
ray.getOrigin(); // returns glm::vec2(10,5)
```

#### getDirection

```cpp
T getDirection();
```
It returns the direction of the vector. For example, for the 2D ray previously greated:
```cpp
ray.getDirection(); // returns glm::vec2(1,0)
```

#### setOrigin

```cpp
void setOrigin(T _origin);
```

It sets the origin of the ray;

#### setDirection

```cpp
void setDirection(T _origin);
```

It sets the direction of the ray;

#### draw

```cpp
void draw(float radius = 20.);
```

It draws a red circle indicating the position and a blue line indicating the direction, useful when debugging. It accepts a parameter to scale the dimension of the line representing the direction.


        

## 2D intersection methods:

#### intersectsPolyline
See example `example-polyline-intersection`

```cpp
bool intersectsPolyline(const ofPolyline & poly, float & distance, glm::vec2& surfaceNormal);
```

It checks for the intersection between a ray and an `ofPolyline`. If there is an intersection, it stores in `distance` and `surfaceNormal` respectively the distance from the origin to the intersection point, and a 2D normal of the segment of the polyline hit by the ray.

```cpp
ofxraycaster::Ray<glm::vec2> ray;
ofPolyline poly;

glm::vec2 surfaceNormal; // store the intersection value
float distance; // store the intersection value

if (ray.intersectsPolyline(poly, distance, surfaceNormal)) {
    glm::vec2 intersection = ray.getOrigin() + ray.getDirection() * distance;
    ofDrawLine(ray.getOrigin(), intersection);
}
```

#### intersectsSegment
See example `example-segment-intersection`

```cpp
bool intersectsSegment(const glm::vec2 & a, const glm::vec2 & b, float & distance)
```

It checks for the intersection between a ray and a segment. If there is an intersection, it stores in the variable `distance` the distance from the origin to the intersection point.


```cpp
ofxraycaster::Ray<glm::vec2> ray;
auto a = glm::vec2(10, 30);
auto b = glm::vec2(50, 50);
// the segment goes from point a to point b

float distance; // store the intersection value

if (ray.intersectsSegment(a, b, distance)) {
    glm::vec2 intersection = ray.getOrigin() + ray.getDirection() * distance;
    ofDrawLine(ray.getOrigin(), intersection);
}
```

## 3D intersection methods:

See `example-3D`

#### intersectsTriangle

It checks for the intersection between a ray and a triangle.

```cpp
bool intersectsTriangle(glm::vec3 const & vert0, glm::vec3 const & vert1, glm::vec3 const & vert2, glm::vec3 & baryPosition)
```


#### intersectsSphere

It checks for the intersection between a ray and a sphere.

```cpp
bool intersectsSphere(const glm::vec3 & _center, const float & _radius, glm::vec3& _position, glm::vec3 & _normal)
```

#### intersectsPrimitive

It checks for the intersection between a ray and an `ofPrimitive`.

```cpp
bool intersectsPrimitive(const of3dPrimitive& primitive,  glm::vec3 & baricentricCoords, glm::vec3 & intNormal)
```

#### intersectsPlane

It checks for the intersection between a ray and an `ofxraycaster::Plane<glm::vec3>`.

```cpp
bool intersectsPlane(ofxraycaster::Plane<T> plane, float & distance);
```
