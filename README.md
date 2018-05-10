# ofxRaycaster
WIP raycaster

This addon contains a definition of a ray in 2D and 3D dimension, and it includes methods to check for intersection with ofPrimitives, ofPolylines, segments, Plane etc ...

## How to use it:
Download this addon in you `addons` folder. Create a new project with the project generator and add as addon `ofxRaycaster`.
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

It checks for the intersection between a ray and an `ofPolyline`. If there is an intersection, it stores in the variable `distance` and `surfaceNormal` the distance from the origin to the intersection point and a 2D normal of the segment of the polyline hitten by the ray.

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




