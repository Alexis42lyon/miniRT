
# MiniRT

A little 3d pathtracer

## About
this project is the 2nd graphical project at 42, the goal is to create a cpu raytracer using the mlx graphics library, the original subject only ask for a small raytracer, you will find here a extended version featuring pathtracing, texture mapping, multithreading, fully movable camera and runtime settings

## Features
### materials
all material are store in the ./scenes/material.rt file
to add a new material simply add a new entry at the end, this is all the settings,

|name|description|values|
|------|-----|-----|
|name|name of mat|string: "my-name"|
|albedo|mat color|vec3: [0, 255]|
|emission|emission power (color is same as albedo) |int: [0, +inf]|
|roughness|0 = relfective, 1 = not relfective|float: [0.0, 1.0]|
|shininess|0 = not shiny, 512 = very shiny|int: [0, +inf]|
|specular coef|intensity of spec reflection|float: [0.0, 1.0] |
|use checker|is the object affected by the checker grid|int: [0, 1] |
|texture map|path for texture (leave '#' for null)|string: "./my-texture.ppm" |
|normal map|path for normal map (leave '#' for null)|string: "./my-normal.ppm"|

(texture / normal maps need to be using .ppm format)

example: ```default 125,125,150 0.0 1 126 0.6 1 # # ```

### File configuration
files are using the .rt format

this is all possible entry with the option needed:
|name|description|options|
|------|-----|-----|
|C |camera|`vec3: position` `vec3:direction`, `int:fov [0, 180]`|
|A |ambiant light|`float: ratio [0.0, 1.0]` `vec3:color [0, 255]`|
|L |light|`vec3:position` `float: ratio [0.0, 1.0]` `vec3:color [0, 255]`|
|sp |sphere|`vec3:position` `float: scale` `string:material name`|
|pl |plane|`vec3:position` `vec3: normal` `string:material name`|
|cy |cylinder|`vec3:position` `vec3: normal` `float: diameter` `float: height` `string:material name`|
|co |cone|`vec3:position` `vec3: normal` `float: diameter` `float: height` `string:material name`|

example map:
```
A   1                                  150,150,255
C   0.2,0,3       0,0,-1    70
L   0,1.5,2                0.2           241,120,57

sp  0,0,0                  0.5         default
sp  -2.1,0,-1                  1           white

cy 0,1.1,0  0,1,0 0.3  0.8  blue

pl  0,-0.8,0        0,1,0               red

```

### Interaction
to interact with the object in the scene use the control panel to so. 

> the panel can be disable by settings `SHOW_BUTTON` to 0 in `includes/button.h`

here is the available keybinds:
|key|description|
|----|---|
|`escape`| exit the program|
|`press right mouse button`| enter movement mode|
|`release right mouse button`| exit movement mode|
|`mouse movement`| move the camera direction (is movement is enable)|
|`wasd`| move the camera (only work if movement mode is on)|
|`0`|reload the scene|
|`1`|toggle grayscale filter|
|`2`|toggle pixelate filter|
|`3`|toggle invert filter|
|`4`|toggle chromatic aberation filter|
|`5`|toggle posterize filter|
|`6`|toggle depth of field|
|`z`|toggle ambiant pass|
|`x`|toggle diffuse pass|
|`c`|toggle specular pass|
|`v`|toggle uv pass|
|`b`|toggle normal|
|`n`|toggle depth map pass|
|`k`|show camera settings|
|`f`|show frame render time|
|`r`|reset camera orientation|
|`g`|save render (.ppm format)|

#### Miscelanous
you can change the window inside the makefile, `WIDHT` and `HEIGHT` are the window size, you can set `SSAA_FACTOR` to 2 or 3, this will turn on supersampling, denoising and antialiasing, however expect heavy slowdown

> /!\ a window of 960x540 with SSAA_FACTOR set to 2 will take ~1.7GB, carefull with large windows size / hight SSAA_FACTOR 

## Installation

1. clone the repo
```bash
  git clone https://github.com/abidolet/miniRT.git miniRT
  cd miniRT
```

1. build using make
```bash
  make
```
    
## Usage/Examples

#### requirement
to run the project, you will need a scenes/ folder inside must be a `material.rt` file containing your materials
you also need a `<scene-name>.rt` containing a valid scene

#### running miniRT

run miniRT:
```
./miniRT <scene>.rt
```
the project already has a few examples scene, to try you can run:
```
./miniRT scenes/<name>
```
available scenes are `showcase.rt`, `mirror.rt`, `room.rt`, `42.rt`, `lights.rt`


## Screenshots

scenes/showcase.rt
[![Project-20250412054030.jpg](https://i.postimg.cc/brVzJr1R/Screenshot-from-2025-05-07-13-24-01.png)](https://postimg.cc/tYBSSyMs)

scenes/mirror.rt
[![Project-20250412054030.jpg](https://i.postimg.cc/v808XqC6/Screenshot-from-2025-05-07-14-49-09.png)](https://postimg.cc/tYBSSyMs)

scenes/room.rt
[![Project-20250412054030.jpg](https://i.postimg.cc/J4trF3WY/Screenshot-from-2025-05-07-14-55-00.png)](https://postimg.cc/tYBSSyMs)


|differents pass|
|----|
|[![Project-20250412054030.jpg](https://i.postimg.cc/h40F0Xzy/Screenshot-from-2025-05-07-15-16-56.png)](https://postimg.cc/tYBSSyMs) |
|uv pass|
[![Project-20250412054030.jpg](https://i.postimg.cc/pTDw4T0d/Screenshot-from-2025-05-07-15-16-48.png)](https://postimg.cc/tYBSSyMs) |
depth map pass
[![Project-20250412054030.jpg](https://i.postimg.cc/NfG3CQRg/Screenshot-from-2025-05-07-15-17-03.png)](https://postimg.cc/tYBSSyMs)



|more renders|
|----|
|[![Project-20250412054030.jpg](https://i.postimg.cc/c1PDwZT9/mini-RT-render-2121699479.png)](https://postimg.cc/tYBSSyMs) |
|with some filters apply|
[![Project-20250412054030.jpg](https://i.postimg.cc/c6q8HFRh/mini-RT-render-1873529600.png)](https://postimg.cc/tYBSSyMs) |
[![Project-20250412054030.jpg](https://i.postimg.cc/1R8C840V/Screenshot-from-2025-05-07-15-23-47.png)](https://postimg.cc/tYBSSyMs)



## Acknowledgements

 - [cherno raytracing series](https://youtu.be/gfW1Fhd9u9Q?si=0JJXZGSj0m92Ba5W)
 - [raytracing in a weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
 - [texture mapping](http://raytracerchallenge.com/bonus/texture-mapping.html)
 - [normal mapping](https://learnopengl.com/Advanced-Lighting/Normal-Mapping)
 - [phong model](https://users.csc.calpoly.edu/~zwood/teaching/csc471/final09/nkowshik_webpage/)
 - [ppm images](https://paulbourke.net/dataformats/ppm/)

## Contributors
[@abidolet](https://github.com/Alexis42lyon)

[@mjuncker](https://github.com/Maxime-juncker)
