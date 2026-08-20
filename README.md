# Pasar Tengah Malam


## About the Game
about staying alive past midnight while local malaysian grown fruits attack the player

## Malaysia Day Theme
the setting and art assets were supposed to be malaysia theme, but ran out of time and couldnt reallly implement that, 
end up only with 4 pngs to represent malaysian local fruits

## Gameplay
its is ehavily inspired by the game indie game five nights at freddy's 1, where the player must manage their power, while also looking out for the enemies through cameras
different enemies have different mechanics

## Controls
toggle A and D to control the doors
press Q and E to control the lights

## Enemies
enemies are trying to enter your room, manage your power while also keeping the enemies away by closing the doors
durian only moves if you are not watching  on the camera
rambutan only moves once -  straight towards the door, close the door in time before it reaches the door
mangosteen moves towards the left door
jambu moves towards the right door

## Building and Running
raylib library installed, 
-install and build instructions too long to fit here, was built in msvc, raylib library was externally linked, need to link it correctly, or install through vcpkg, 
but not the latest raylib 6.1 beta as it has a bug with windows not updating correctly. 

## Why raylib?
I had prior experience using raylib, but with msvc and not linux g++

## What raylib Provides vs What I Built
raylib provided code to open a window and managed rendering, i only coded the game logic, and using raylib's draw functions to draw simple rectangles, 
and render 3D models on the screen with camra3D

## Scope and Cut Features
I intended to add better graphics, and 3D models, but due to time contraints, only managed to code part of the gameplay logic, 
the game I wanted to make would have 5 night cycles, but currently there is only 1.

## What I Would Do Differently
I would have planned a smaller scope, and use that to have more time
