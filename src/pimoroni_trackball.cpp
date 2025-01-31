#include "pimoroni_trackball.h"
Pimoroni_Trackball pimoroni_trackball;

void Pimoroni_Trackball::initialize(){
    Wire.begin();
    trackball.begin();
    // TODO: Find a better way to do this.
    pimoroni_trackball.multiplier = 2;
    trackball.setRGBW(23, 178, 255, 255); // This is just me liking #17B2FF

}

void Pimoroni_Trackball::read(){
    if(trackball.changed()){
        // This might require modification on the Lynx App.
        // y_mouse = (trackball.down() - trackball.up()) * layouts_manager.mouse_factor[layer_control.active_layer][0];
        // x_mouse = (trackball.right() - trackball.left()) * layouts_manager.mouse_factor[layer_control.active_layer][1];
        
        // TODO: We need to find a way to smooth
        y_mouse = (trackball.down()  - trackball.up()  ) * pimoroni_trackball.multiplier;
        x_mouse = (trackball.right() - trackball.left()) * pimoroni_trackball.multiplier;
        if (x_mouse != 0 || y_mouse != 0) { 
            if (config.device_side==RIGHT){ Mouse.move( y_mouse,-x_mouse); }
            if (config.device_side==LEFT ){ Mouse.move(-y_mouse, x_mouse); }
        }
        if (trackball.click()) { 
            trackball.setRGBW(255,255, 255, 255);
            Mouse.press(MOUSE_LEFT); 
        }
        if (trackball.release() && Mouse.isPressed(MOUSE_LEFT)) {
            trackball.setRGBW(23, 178, 255, 255);
            Mouse.release(MOUSE_LEFT);
        }
    }
}