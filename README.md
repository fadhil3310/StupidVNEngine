
# StupidVNEngine

<div style="display:flex;">
<img src="./docs/2.png">
<img src="./docs/3.png">
</div>


![Example video](/docs/doc_video.mp4)


### A simple and easy-to-use game engine for Visual Novel.

Originally created for a school project.  [Here's the repo](https://github.com/hrtsnam/UAS_SDA_PROJECT).

## Features

* Support up to 3 characters to be shown at the same time (you can draw your character manually without using the built-in character drawing system if you want).
* Character animation (Fade, Slide, Jump, Shake, etc).
* Choice system and skip dialog.
* UI (Text, Button, Input field, etc).
* Page/scene transition.
* Everything is drawn on a Canvas, you can create your own Canvas and attach it to your page/scene.
* Custom immediate-mode drawing per page/scene.

> Please note that the window can't be resized and is fixed at 1000x550, unless if you modify the engine code of course.

## How to Use

Please refer to the repo i have attached above. Consider it as an example on how to use the engine.

## Building

### Dependency
* SFML 3.0.1

### Requirement
* C++ 17 compiler
* CMake
* Ninja

### Steps
1. Run `setup.ps1`/`setup.sh` (For Windows, use the `.ps1` one) to setup CMake and download all of the required dependencies.
2. Run `build.ps1`/`build.sh` to build the engine.
3. Run `run.ps1`/`run.sh` to run the game that you have made.

## Notice

I don't plan to continue developing this. This repo is only meant to be an archive of what i have built for my school project.