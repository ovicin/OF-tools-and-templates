#include "ofApp.h"

//-----------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    
    canvas.setup(1280, 800);
    canvas.addLayer(CANVAS_CREATOR);
    //canvas.addLayer(CANVAS_POST_FX);
}

//-----------
void ofApp::update(){
    canvas.update();
}

//-----------
void ofApp::draw() {
    canvas.draw(0, 0);
}

//-----------
void ofApp::keyPressed(int key){
    if (key=='g') {
        canvas.toggleGuiVisible();
    }
}