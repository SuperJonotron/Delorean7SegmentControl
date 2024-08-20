# Delorean7SegmentControl
Helper library for controlling the 7-segment displays for my DeloreanClock project

## Introduction

This project is designed to be used with my DeloreanClock project. It is a wrapper around another library that controls various 7-segment display modules.  This particular use case is around the TM1637 4-pin version. 

Originally I used a different library to control the TM1637 but the amount that were being controlled caused the updates to take multiple seconds, which makes for a bad clock.  I found a better and faster library that had no git repo or official arduino library.

Manual for library: http://lygte-info.dk/project/DisplayDriver%20UK.html

I have used this as the core library to the wrapper that takes care of all the actual commnication to the TM1637 modules and included it directly into this library.


## Motivation

Originally this was all contained within the DeloreanClock project but I wanted to separate out as much reusable code as I could in case I wanted to use it again and not reinvent the wheel.  As the name implies, it is designed specifically around the DeloreanClock project so the methods may never translate to anything else but it's there stand alone in case anybody can use it for their purposes or if I ever needed a small adjustment to what i'm doing with the displays on the clock.
 

## Usage

ToDo

## Examples
ToDo

