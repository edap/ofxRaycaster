# ofxRaycaster

[![Build status](https://travis-ci.org/edap/ofxRaycaster.svg?branch=master)](https://travis-ci.org/edap/ofxRaycaster)
[![Build status](https://ci.appveyor.com/api/projects/status/p7l03tb6m1ctxbju?svg=true)](https://ci.appveyor.com/project/edap/ofxraycaster)

##### Table of Contents  
[How to use it](#how-to)

[Methods for 2D and 3D rays](#generics)

[2D Intersection Methods](#2d-intersections) 

[3D Intersection Methods](#3d-intersections)

[Mouse Picker](#mousepicker)
   

![img](img/screenshot.png)


This addon contains a definition of a ray in 2D and 3D dimension, and it includes methods to check the intersection with segments, spheres, triangles, planes, ofPrimitive, ofPolyline and ofMesh.

<a name="how-to"/>

## How to use it:

</a>

Download this addon in your `addons` folder. Create a new project with the project generator and add as addon `ofxRaycaster`.
In your project, add at the top of your `ofApp.h` file

```cpp
#include "ofxRaycaster.h"
```
To get started using a 2D ray in your project, declare a `ray` variable in your `ofApp.h` header file:

```cpp
ofxraycaster::Ray2D ray;
```

If you want to use a 3D ray, declare the ray like this.

```cpp
ofxraycaster::Ray ray;
```

<a name="generics"/>

## Generic methods, for both 2D and 3D rays:

</a>

#### setup

```cpp
void setup(glm::vec2 origin, glm::vec2 direction)
```
Set the origin and direction of a ray. For example, for a 2D ray:

```
ray.setup(glm::vec2(10,5), glm::vec2(1,0));
```

#### getOrigin

```cpp
glm::vec2 getOrigin();
```
Return the origin of the vector. For example, for the 2D ray previously greated:
```cpp
ray.getOrigin(); // returns glm::vec2(10,5)
```

#### getDirection

```cpp
glm::vec2 getDirection();
```
Return the direction of the vector. For example, for the 2D ray previously greated:
```cpp
ray.getDirection(); // returns glm::vec2(1,0)
```

#### setOrigin

```cpp
void setOrigin(glm::vec3 origin);
```

Set the origin of the ray;

#### setDirection

```cpp
void setDirection(glm::vec2 _origin);
```

Set the direction of the ray;

#### draw

```cpp
void draw(float radius = 20.);
```

Draw a red circle indicating the position and a blue line indicating the direction, useful when debugging. It accepts a parameter to scale the dimension of the line representing the direction.

       
<a name="2d-intersections"/>

## 2D intersection methods:

</a>

| `example-polyline-intersection` | `example-segment-intersection`  |
|     :---:      |      :---:    |
|   ![img](img/polyline.gif )   | ![img](img/segment.gif )    | 


#### intersectsPolyline
See example `example-polyline-intersection`

```cpp
bool intersectsPolyline(const ofPolyline & poly, float & distance, glm::vec2& surfaceNormal);
```

Check the intersection between a ray and an `ofPolyline`. If there is an intersection, it stores in `distance` and `surfaceNormal` respectively the distance from the origin to the intersection point, and a 2D normal of the segment of the polyline hit by the ray.

```cpp
ofxraycaster::Ray2D ray;
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

Check the intersection between a ray and a segment. If there is an intersection, it stores in the variable `distance` the distance from the origin to the intersection point.


```cpp
ofxraycaster::Ray2D ray;
auto a = glm::vec2(10, 30);
auto b = glm::vec2(50, 50);
// the segment goes from point a to point b

float distance; // store the intersection value

if (ray.intersectsSegment(a, b, distance)) {
    glm::vec2 intersection = ray.getOrigin() + ray.getDirection() * distance;
    ofDrawLine(ray.getOrigin(), intersection);
}
```

<a name="3d-intersections"/>

## 3D intersection methods:

</a>


| `example-multiple-rays` | `example-mesh-intersection` | `example-3D` |
| :---:         |     :---:      |          :---: |
| ![img](img/multiple-rays.gif )   | ![img](img/mesh-intersection.gif )     | ![img](img/3D.gif )    |



#### intersectsTriangle

Check the intersection between a ray and a triangle. See `example-3D`.

```cpp
bool intersectsTriangle(glm::vec3 const & vert0, glm::vec3 const & vert1, glm::vec3 const & vert2, glm::vec3 & baryPosition)
```


#### intersectsSphere

Check the intersection between a ray and a sphere. See `example-3D`.

```cpp
bool intersectsSphere(const glm::vec3 & _center, const float & _radius, glm::vec3& _position, glm::vec3 & _normal)
```

#### intersectsPrimitive

Check the intersection between a ray and an `ofPrimitive`. See `example-3D`.

```cpp
bool intersectsPrimitive(const of3dPrimitive& primitive,  glm::vec3 & baricentricCoords, glm::vec3 & intNormal)
```

#### intersectsPlane

Check the intersection between a ray and an `ofxraycaster::Plane`. See `example-3D`.

```cpp
bool intersectsPlane(ofxraycaster::Plane plane, float & distance);
```

#### intersectsMesh

Check the intersection between a ray and a mesh. See `example-mesh-intersection`.


```
bool intersectsMesh(const ofMesh& mesh,  glm::vec3 & baricentricCoords, glm::vec3 & intNormal);
```

Example:

```cpp
void ofApp::draw(){
    cam.begin();
    mesh.draw();
    ray.draw();

    glm::vec3 baricentricCoordinates; // stores the barycentric coordinate of the triangle hit by the ray.
    glm::vec3 surfaceNormal; // stores the normal of the surface hit by the ray.
    bool intersects = ray.intersectsMesh(mesh, baricentricCoordinates, surfaceNormal);
    
    // is there an intersection between the mesh and the ray?
    if (intersects) {
        auto intersection =
            ray.getOrigin() + ray.getDirection() * baricentricCoordinates.z;
        // draw the ray hitting the mesh
        ofDrawLine(ray.getOrigin(), intersection);
        // draw the intersection point
        ofDrawSphere(intersection, 5);

        // draw the reflected light
        auto reflLight = glm::reflect(ray.getDirection(), surfaceNormal);
        ofDrawLine(intersection, intersection + 100 * reflLight);
    }
    cam.end();
}
```

When a `glm::mat4` containing the transformation matrix of the mesh is given as second argument, it takes the transformation into account. See `example-mesh-intersection`.

```
bool intersectsMesh(const ofMesh& mesh, const glm::mat4& transformationMatrix,  glm::vec3 & baricentricCoords, glm::vec3 & intNormal);
```

<a name="mousepicker"/>

## Mousepicker:

| `example-mousepicker` |
|     :---:      |
|   ![img](img/mousepicker.gif )| 



#### setFromCamera

```cpp
void setFromCamera(const glm::vec2 coords, const ofCamera camera);
```

Set the origin and the direction of the ray giving as argument an `ofCamera` and the mouse coordinates. See example `example-mousepicker`.

#### draw

```cpp
void draw(const float radius = 20);
```

Draw a sphere under the mouse. 

#### getRay

```cpp
Ray& getRay();
```

Return the 3D ray that goes from the camera points towards the mouse.


</a>

                            
