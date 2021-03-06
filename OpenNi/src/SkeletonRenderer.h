#pragma once

#include "OpenNi.h"


class OpenNi;


class SkeletonRenderer {
public:
    void setup(OpenNi *openNi, int width, int height) {
        this->openNi = openNi;
        this->width = width;
        this->height = height;
        setupControl();
    }
    
    void setGuiPosition(int x, int y) {control.setGuiPosition(x, y);}
    void setGuiVisible(bool visible);
    void toggleGuiVisible() {setGuiVisible(!visible);}

    void setCalibration(ofxKinectProjectorToolkit *kpt) {
        this->kpt = kpt;
        calibrated = true;
    }
    
    void update() {
        
    }
    
    void draw() {
        ofPushMatrix();
        ofPushStyle();
        
        if (drawJointLines)     renderJointLines();
        if (drawOutwardLines)   renderOutwardLines();
        
        ofPopStyle();
        ofPopMatrix();
    }
    
    void renderJointLines();
    void renderOutwardLines();

    
    
    OpenNi *openNi;
    ofxKinectProjectorToolkit *kpt;
    bool calibrated = false;
    int width, height;
    
    
private:
    
    void setupControl();
    
    Control control;
    
    bool drawJointLines;
    bool drawOutwardLines;
    
    int iterations;
    float randomOffset;
    ofColor color;
    float lineWidth;
    int numLines;
    int radius;
    
    bool visible;
};