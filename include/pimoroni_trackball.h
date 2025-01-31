#ifndef PIMORONI_TRACKBALL_H
#define PIMORONI_TRACKBALL_H

#include <Arduino.h>
#include <Wire.h>
#include <pimoroniTrackball.h>
#include "events.h"
#include "layer_control.h"
#include "layouts_manager_cat.h"

extern pimoroniTrackball trackball;

class Pimoroni_Trackball{
public:
    void initialize();
    void read();
private:
    int y_mouse;
    int x_mouse;
    // TODO: Find a better way to do Smoothing. This just snaps in place.
    int multiplier; 
};
extern Pimoroni_Trackball pimoroni_trackball;
#endif