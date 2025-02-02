#ifndef PIMORONI_TRACKBALL_H
#define PIMORONI_TRACKBALL_H

#include <Arduino.h>
#include <Wire.h>
#include <pimoroniTrackball.h> //ncreynolds
#include "events.h"
#include "layer_control.h"
#include "layouts_manager_cat.h"

extern pimoroniTrackball trackball;
class PimoroniTrackball{
public:
    void initialize();
    void read();
    void smooth();
private:
    int y_mouse;
    int x_mouse;
    // TODO: This is for testing only. Once PR, replace with mouse_factor.
    float x_multiplier, y_multiplier;
};
extern PimoroniTrackball pimoroni_trackball;
#endif