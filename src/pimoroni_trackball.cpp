#include "pimoroni_trackball.h"
PimoroniTrackball pimoroni_trackball;

void PimoroniTrackball::initialize()
{
    Wire.begin();
    trackball.begin();
    // TODO: Repalce these with settings from Lynx App.
    pimoroni_trackball.x_multiplier = 1.5;
    pimoroni_trackball.y_multiplier = 1.5;
    trackball.setRGBW(23, 178, 255, 0); // This is just me liking #17B2FF
}

void PimoroniTrackball::read()
{
    if(trackball.changed()){
        // TODO: This requires modification on the Lynx App. -- hence test value
        // y_mouse = (trackball.down() - trackball.up()) * layouts_manager.mouse_factor[layer_control.active_layer][0];
        // x_mouse = (trackball.right() - trackball.left()) * layouts_manager.mouse_factor[layer_control.active_layer][1];
        
        smooth(); //Smooth Reading
        if (x_mouse != 0 || y_mouse != 0) {
            if (config.device_side==RIGHT){ Mouse.move( y_mouse,-x_mouse); }
            if (config.device_side==LEFT ){ Mouse.move(-y_mouse, x_mouse); }
        }
        if (trackball.click()) {
            // TODO: Repalce with a setting from Lynx App.
            trackball.setRGBW(0,0,0, 255);
            Mouse.press(MOUSE_LEFT);
        }
        if (trackball.release() && Mouse.isPressed(MOUSE_LEFT)) {
            // TODO: Repalce with a setting from Lynx App.
            trackball.setRGBW(23, 178, 255, 0);
            Mouse.release(MOUSE_LEFT);
        }
    }
}

// To Smooth movmeent. This is based on un1tz3r0/Pimoroni_Trackball
void PimoroniTrackball::smooth(){
    float fy = (trackball.down()  - trackball.up()  ) * pimoroni_trackball.y_multiplier;
    float fx = (trackball.right() - trackball.left()) * pimoroni_trackball.x_multiplier;

    // apply exponential smoothing to x and y independently
    static float sx = 0, sy = 0;
    static const float smooth = 0.075;
    
    sx = fx*smooth + (1.0-smooth)*sx;
    sy = fy*smooth + (1.0-smooth)*sy;

    // acceleration is based on magnitude of motion vector. 
    float flen = sqrt(fx*fx + fy*fy);

    // apply asymmetric exponential smoothing (aka envelope follower 
    // with differing rise and fall rates, for the synthesiser fans)
    // to the magnitude
    static const float slenrise = 0.05, slenfall = 0.0125;
    static float slen = 0;
    if(flen < slen)
        slen = flen * slenfall + (1.0 - slenfall) * slen;
    else
        slen = flen * slenrise + (1.0 - slenrise) * slen;

    // scale and clip acceleration factor to taste, then multiply by the smoothed x and y, 
    // so our acceleration is simply a modified, distorted exponential curve with order two 
    static const float scalefact = 10.5;
    static const float scalemin = 1.0;
    float scaledx = sx * max(scalemin, slen * scalefact);
    float scaledy = sy * max(scalemin, slen * scalefact);

    // add any rounding error from the previous report to this one, before rounding. 
    // this way subpixel movement is still reported as intermittent single pixel moves,
    // and motion in general feels much more natural and easy to control with the ball
    static float residx = 0;
    static float residy = 0;
    scaledx = scaledx - residx;
    scaledy = scaledy - residy;
    residx = (float)round(scaledx) - scaledx;
    residy = (float)round(scaledy) - scaledy;
    x_mouse = round(scaledx);
    y_mouse = round(scaledy);
    Serial.println(x_mouse*.5);
    Serial.println(y_mouse*.5);
}