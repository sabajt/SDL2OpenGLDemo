# SDL2 OpenGL C++ Demo
Small game engine example using SDL2, OpenGL and C++. This demo is a "wobbly" particle generator with customizable parameters.

There is a fair bit of unused code, copied this book / tutorial: from https://learnopengl.com/In-Practice/2D-Game/Breakout. This project was my first attempt at a custom game engine and learning a low level rendering API. It is not a good example of effecient rendering code, as it doesn't employ any batching or instancing.

## Wobbly Particles
The most interesting part of this project is the rendering technique which creates various "wobbly" circle-based shapes. The vertices that define models have an "ideal" position and an "actual" position. The ideal positions would be normal geometry, such as the points that define a triangle or square. The actual positions are physics based nodes (`PointMass.h`) which are seeded with an initial force, but are pulled into their ideal position. Each ideal position is the center of gravity for each actual position. By modifying a number of different parameters based on this concept, interesting visual effects are achieved.

A lot of this logic is found in the [WobbleObject](https://github.com/sabajt/SDL2OpenGLDemo/blob/main/GameEngine/src/Core/WobbleObject.cpp) and `WobbleRender` classes. 
