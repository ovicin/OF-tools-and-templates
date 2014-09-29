#include "Canvas.h"


//----------------
void Canvas::setup(int width, int height) {
    this->width = width;
    this->height = height;
    guiVisible = true;
    guiPosition = ofPoint(5, 5);
    setupGui();
}

//----------------
void Canvas::setupGui() {
    control.clearParameters();
    control.setName("manage layers");
    control.addEvent(" +creator", this, &Canvas::addCreator);
    if (layers.size() > 0) {
        control.addEvent(" +modifier", this, &Canvas::addModifier);
        control.addEvent(" +postProcessor", this, &Canvas::addPostProcessor);
        control.addEvent(" +postGlitch", this, &Canvas::addPostGlitch);
        control.addEvent(" +postFx", this, &Canvas::addPostFx);
    }
    for (int i=0; i<layers.size(); i++) {
        control.addEvent(" -layer "+ofToString(i)+" ("+layers[i]->getName()+")", this, &Canvas::setDeleteLayer);
        layers[i]->setGuiPosition(guiPosition.x+170*i, guiPosition.y);
        if (i>0) layers[i]->setTexLayer(layers[i-1]);
    }
    control.setGuiPosition(guiPosition.x+170*layers.size(), guiPosition.y);
}

//----------------
void Canvas::addLayer(CanvasLayer *newLayer) {
    if (layers.size() > 0)
        newLayer->setup(width, height, layers[layers.size()-1]);
    else
        newLayer->setup(width, height);
    layers.push_back(newLayer);
    setupGui();
}

//----------------
CanvasLayer* Canvas::addLayer(LayerType type) {
    CanvasLayer *layer;
    if      (type == CANVAS_CREATOR)         layer = new CreatorLayer();
    else if (type == CANVAS_MODIFIER)        layer = new ModifierLayer();
    else if (type == CANVAS_POST_PROCESSING) layer = new PostProcessingLayer();
    else if (type == CANVAS_POST_GLITCH)     layer = new PostGlitchLayer();
    else if (type == CANVAS_POST_FX)         layer = new PostFxLayer();
    if (layers.size() > 0)
        layer->setup(width, height, layers[layers.size()-1]);
    else
        layer->setup(width, height);
    layers.push_back(layer);
    setupGui();
    return layer;
}

//----------------
void Canvas::setVisible(bool guiVisible) {
    this->guiVisible = guiVisible;
    for (int i=0; i<layers.size(); i++) {
        layers[i]->setVisible(guiVisible);
    }
    control.setVisible(guiVisible);
}

//----------------
void Canvas::toggleGuiVisible() {
    setVisible(!guiVisible);
}

//----------------
void Canvas::update() {
    if (toDeleteLayer) {
        deleteLayer();
        return;
    }
    for (int i=0; i<layers.size(); i++) {
        layers[i]->checkGuiCalls();
        layers[i]->render();
    }
}

//----------------
void Canvas::draw(int x, int y) {
    if (layers.size() == 0) return;
    layers[layers.size()-1]->draw(x, y);
}

//----------------
void Canvas::setDeleteLayer(string &s) {
    idxLayer = ofToInt(ofToString(s[8]));
    toDeleteLayer = true;
}

//----------------
void Canvas::deleteLayer() {
    CanvasLayer *layerToDelete = layers[idxLayer];
    layers.erase(layers.begin()+idxLayer);
    setupGui();
    delete layerToDelete;
    toDeleteLayer = false;
}

//----------------
Canvas::~Canvas() {
    for (int i=0; i<layers.size(); i++) {
        delete layers[i];
    }
    layers.clear();
}
