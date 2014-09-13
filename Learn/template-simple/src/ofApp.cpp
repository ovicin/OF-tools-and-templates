#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    inputParam.setName("inputParam");
    inputParam.setMin(2.0);
    inputParam.setMax(5.0);

    outputParam.setName("outputParam");
    outputParam.setMin(10.0);
    outputParam.setMax(100.0);

    learn.setup();
    
    learn.addInput("hello", 1, 5);  // add OSC param
    learn.addInput(&inputParam);         // add ofxParam param

    learn.addInput("bybbe", 1, 5);  // add OSC param
    learn.addInput("g", 1, 5);  // add OSC param
    learn.addInput("world", 1, 5);  // add OSC param
    learn.addInput("gbegin", 1, 5);  // add OSC param
    learn.addInput("gend", 1, 5);  // add OSC param

    
    learn.addOutput("this", 10, 20);
    learn.addOutput("that", 1, 10);
    learn.addOutput("other", 1, 10);
    learn.addOutput(&outputParam);

}

//--------------------------------------------------------------
void ofApp::update(){
    learn.update();
    
    inputParam = ofMap(mouseX, 0, ofGetWidth(), 2, 5);
    
    ofEllipse(ofMap(outputParam, outputParam.getMin(), outputParam.getMax(), 0, ofGetWidth()), 10, 10, 10);
}

//--------------------------------------------------------------
void ofApp::draw(){
    learn.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}