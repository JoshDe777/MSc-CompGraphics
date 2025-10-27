# Computer Graphics Project Repository

|  General Info  | |
| ---|---|
| Working Title | `Minotaur's Maze` |
| Final Title | `Minotaur's Maze` |
| Student | `Joshua O'Donnell`, jodonne5@tcd.ie, `25353241` |
| Target Platform(s) | `PC` |
| Start Date | 17.10.2025 |
| Study Program | M.Sc. Computer Science - AR/VR|
| Engine Version | 1.0 |

### Abstract

This Repository will contain my Computer Graphics (CS7GV6) project, aiming to produce a simulation of a minotaur chasing something, or someone, through a torchlit labyrinth.

The project is enabled by my prior work in my undergraduate degree, in which I have conceived and implemented a rudimentary game engine, with the support of some external libraries. The state of said engine at the start of the project (to track new additions within the scope of this project) can be found at the repository under https://github.com/JoshDe777/gamelab3-ocean_outlaws (project repository for the aforementioned software project). This repository is also neither a continuation, nor a branch of the above repository, changes can be viewed in full in the commit history as well.

## Software and Hardware requirements

EisEngine is a C++ game engine, and should be usable in any IDE upon importation - using CMake. The engine was built on and for CLion, which is the recommended platform for use. 

The resulting application is playable exclusively on computers supporting the GLEW implementation of OpenGL, so platforms running on Windows, Linux, Mac OS X, FreeBSD, Irix, and Solaris.
The keys are classic keyboard keys, a mouse is required for head movement.

The following external libraries should come with the download when downloading the ~/code/extern folder or using the engine from the repository, but as requirements I'll list them up here just in case:
Box2D, GLAD, GLFW, GLM, Tinygltf, stb_image, SoLoud, FastNoise, assimp.

The engine requires a minimum CMake version of 3.21.

No additional software or hardware should be required.