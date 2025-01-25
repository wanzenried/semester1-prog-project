# prog1-exam
This is my exam project for 1st semester introduction to programming.  
The project was open ended, meaning it was almost allowed to do anything as long as the goals of the course were met.

The project is a "small" handheld capable of playing games. Currently the only available game is a small implementation of tetris, but the code is structured in a way that should make it easier to implement other games. The screen has a resolution of 20x12 pixels, and has 3 buttons for inputs.

## Inspiration
Inspired by the [Hackaday Tiny Games Chalenge](https://hackaday.io/contest/196871-tiny-games-challenge) that ran from July till September 2024, I decided to implement Tetris in C and C++, and getting it to run on an Arduino Nano.  
To challenge myself, I decided to use a 20x4 lcd display as the screen.

## Parts used
The project is fairly simple hardware wise, only using four different component types:
- 1x Arduino Nano (ATmega168)
- 1x Buckconverter (MP1584)
- 1x 20x4 LCD with I2C adapter
- 3x generic pushbuttons

## How to make your own
I might do a writeup on how to build one of these in the future

### License
This project is licensed under [The MIT License](License)