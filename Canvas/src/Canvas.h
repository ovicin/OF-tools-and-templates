#pragma once

#include "ofMain.h"

#include "Control.h"
#include "Layer.h"
#include "PostProcessor.h"
#include "PostGlitch.h"
#include "PostFx.h"



class Canvas
{
public:
    ~Canvas();
    void setup(int width, int height);
    void update();
    void draw(int x, int y);
    
    CanvasLayer* addLayer(LayerType type);
    void addLayer(CanvasLayer *layer);
    
    void addCreator(string &s) {addLayer(CANVAS_CREATOR);}
    void addModifier(string &s) {addLayer(CANVAS_MODIFIER);}
    void addPostProcessor(string &s) {addLayer(CANVAS_POST_PROCESSING);}
    void addPostGlitch(string &s) {addLayer(CANVAS_POST_GLITCH);}
    void addPostFx(string &s) {addLayer(CANVAS_POST_FX);}
    
    void setVisible(bool guiVisible);
    void toggleGuiVisible();

private:
    void setupGui();
    
    void setDeleteLayer(string &s);
    void deleteLayer();
    
    Control control;
    bool guiVisible;
    ofPoint guiPosition;
    vector<CanvasLayer *> layers;
    int width, height;

    int idxLayer;
    bool toDeleteLayer;

};
