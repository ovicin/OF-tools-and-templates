#include "ControlPanel.h"


//-------
Control::Control() {
    gui = new ofxUICanvas("control");
    guiPresets = new ofxUICanvas("controlPresets");
    setWidth(150);
    spacing = gui->getWidgetSpacing();
    headerSelected = false;
    setupGuiPresets();
    visible = true;
    metaActive = false;
    setActive(true);
    
    
    meta = new MetaController();
}

//-------
void Control::setupMetaController() {
    //if (meta == NULL) {
    //    meta = new MetaController();
    //}
    meta->setup(this);
    metaActive = true;
    setViewMeta(viewMeta);
}

//-------
void Control::removeMetaController() {
    if (metaActive) {
        setViewMeta(false);
        meta->disable();
        
        //delete meta;
        
        
        metaActive = false;
    }
}

//-------
void Control::setViewMeta(bool viewMeta) {
    this->viewMeta = viewMeta;
    if (metaActive) {
        meta->setVisible(viewMeta);
    }
    else {
        setupMetaController();
        setViewMeta(viewMeta);
    }
}

//-------
void Control::update(ofEventArgs &data) {
    if (active) {
        updateColors();
        if (metaActive) {
            meta->update();
        }
    }
}

//-------
void Control::draw(ofEventArgs &data) {
    if (active && metaActive) {
        meta->draw();
    }
}

//-------
void Control::setName(string name) {
    this->name = name;
    setupGuiPresets();
}

//-------
void Control::savePreset() {
    Presets presets;
    bool saved = presets.savePreset(*this);
    if (!saved) return;
    setupGuiPresets();
}

//-------
void Control::loadPreset(string path) {
    Presets presets;
    presets.loadPreset(*this, path, numLerpFrames);
}

//-------
void Control::setWidth(int width) {
    this->width = width;
    gui->setWidth(width);
    guiPresets->setWidth(width);
}

//-------
void Control::setGuiPosition(int x, int y) {
    gui->setPosition(x, y);
    guiPresets->setPosition(x, y);
}

//-------
void Control::setActive(bool active) {
    this->active = active;
    if (active) {
        ofAddListener(gui->newGUIEvent, this, &Control::guiEvent);
        ofAddListener(guiPresets->newGUIEvent, this, &Control::guiPresetsEvent);
        ofAddListener(ofEvents().update, this, &Control::update);
        ofAddListener(ofEvents().draw, this, &Control::draw);
    }
    else {
        ofRemoveListener(gui->newGUIEvent, this, &Control::guiEvent);
        ofRemoveListener(guiPresets->newGUIEvent, this, &Control::guiPresetsEvent);
        ofRemoveListener(ofEvents().update, this, &Control::update);
        ofRemoveListener(ofEvents().draw, this, &Control::draw);
    }
    setVisible(active);
}

//-------
void Control::setVisible(bool visible) {
    this->visible = visible;
    if (visible) {
        gui->enable();
        guiPresets->enable();
    }
    else {
        gui->disable();
        guiPresets->disable();
    }
    gui->setVisible(visible);
    guiPresets->setVisible(false);
    if (metaActive) {
        meta->setVisible(visible);
    }
}

//-------
void Control::toggleVisible() {
    setVisible(!visible);
}

//-------
void Control::togglePresetsVisible() {
    visible = !visible;
    gui->setVisible(visible);
    guiPresets->setVisible(!visible);
}

//-------
vector<ofxUIDropDownList *> Control::getMenus() {
    vector<ofxUIDropDownList *> dropdowns;
    for (map<string,vector<string> >::iterator it=menus.begin(); it!=menus.end(); ++it){
        ofxUIDropDownList *dropdown = (ofxUIDropDownList *) gui->getWidget(it->first);
        dropdowns.push_back(dropdown);
    }
    return dropdowns;
}

//-------
void Control::setupGuiPresets() {
    guiPresets->clearWidgets();
    guiPresets->setWidth(width);
    guiPresets->addLabelButton("controlHeader", false)->setLabelText(name);
    guiPresets->addLabelButton("Presets", false, 50.0f);
    ((ofxUILabelButton *) guiPresets->getWidget("Presets"))->setName("controlPresetsView");
    guiPresets->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    guiPresets->addLabelButton("Save", false, 40.0f);
    ((ofxUILabelButton *) guiPresets->getWidget("Save"))->setName("controlPresetsSave");
    guiPresets->addLabelToggle("Seq", false, 40.0f);
    ((ofxUILabelToggle *) guiPresets->getWidget("Seq"))->setName("viewMeta");
    guiPresets->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    guiPresets->addSpacer();
    guiPresets->addIntSlider("Lerp frames", 0, 120, &numLerpFrames);
    ofDirectory dir(ofToDataPath("presets/"+getName()+"/"));
    dir.allowExt("xml");
    dir.listDir();
    vector<string> filenames;
    for(int i = 0; i < dir.numFiles(); i++) {
        filenames.push_back(dir.getName(i));
    }
    presetNames = guiPresets->addDropDownList("presets", filenames);
    presetNames->setAutoClose(false);
    presetNames->open();
    guiPresets->addLabelButton(" > TouchOsc", false);
    guiPresets->autoSizeToFitWidgets();
    guiPresets->setVisible(!visible);
}

//-------
void Control::setupGui() {
    gui->clearWidgets();
    gui->setWidth(width);
    gui->addLabelButton("controlHeader", false)->setLabelText(name);
    gui->addLabelButton("Presets", false, 50.0f);
    ((ofxUILabelButton *) gui->getWidget("Presets"))->setName("controlPresetsView");
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addLabelButton("Save", false, 40.0f);
    ((ofxUILabelButton *) gui->getWidget("Save"))->setName("controlPresetsSave");
    gui->addLabelToggle("Seq", false, 40.0f);
    ((ofxUILabelToggle *) gui->getWidget("Seq"))->setName("viewMeta");
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    for (int i=0; i<guiElements.size(); i++) {
        if      (guiElements[i]->type == GuiElement::GUI_PARAMETER) {
            int idx = guiElements[i]->idxElement;
            if (!parametersVisible[parameters[idx]])   continue;
            ParameterBase::Type type = parameters[idx]->getType();
            if      (type == ParameterBase::BOOL) {
                addParameterToGui((Parameter<bool> *) parameters[idx]);
            }
            else if (type == ParameterBase::STRING) {
                addParameterToGui((Parameter<string> *) parameters[idx]);
            }
            else if (type == ParameterBase::INT) {
                addParameterToGui((Parameter<int> *) parameters[idx]);
            }
            else if (type == ParameterBase::FLOAT) {
                addParameterToGui((Parameter<float> *) parameters[idx]);
            }
            else if (type == ParameterBase::VEC2F) {
                addParameterToGui((Parameter<ofVec2f> *) parameters[idx]);
            }
            else if (type == ParameterBase::VEC3F) {
                addParameterToGui((Parameter<ofVec3f> *) parameters[idx]);
            }
            else if (type == ParameterBase::VEC4F) {
                addParameterToGui((Parameter<ofVec4f> *) parameters[idx]);
            }
        }
        else if (guiElements[i]->type == GuiElement::GUI_EVENT) {
            string name = guiElements[i]->nameElement;
            gui->addButton(name, false);
        }
        else if (guiElements[i]->type == GuiElement::GUI_MENU) {
            string name = guiElements[i]->nameElement;
            ofxUIDropDownList *menu = gui->addDropDownList(name, menus[name]);
            menu->setAutoClose(false);
            menu->open();
            menu->setPadding(1);
        }
        else if (guiElements[i]->type == GuiElement::GUI_LABEL) {
            string name = guiElements[i]->nameElement;
            gui->addSpacer();
            gui->addLabel(name);
            gui->addSpacer();
        }
        else if (guiElements[i]->type == GuiElement::GUI_SPACER) {
            gui->addSpacer();
        }
    }
    
    // set color of color sliders
    updateColors();
    
    gui->autoSizeToFitWidgets();
}

//-------
void Control::guiEvent(ofxUIEventArgs &e) {
    
    // menu select notification
    if (menus.count(e.getParentName()) > 0) {
        triggerMenuEvent(e.getParentName(), e.getName(), e.getToggle()->getValue());
    }
    
    // event notification
    else if (events.count(e.getName()) > 0) {
        if (e.getButton()->getValue() == 1) return;
        string state = e.getName();
        ofNotifyEvent(*events[state], state, this);
    }
    
    // label callback
    else if (e.getName() == "controlHeader") {
        if (e.getButton()->getValue() == 1) return;
        headerSelected = true;
    }
    
    // load presets
    else if (e.getName() == "controlPresetsView") {
        if (e.getButton()->getValue() == 1) return;
        togglePresetsVisible();
    }
    
    // save preset
    else if (e.getName() == "controlPresetsSave") {
        if (e.getButton()->getValue() == 1) return;
        savePreset();
    }
    
    // save preset
    else if (e.getName() == "viewMeta") {
        setViewMeta(e.getButton()->getValue() == 1);
    }
    
    // change string value
    else if (stringEvents.count(e.getName()) != 0) {
        string newString = ((ofxUITextInput *) e.widget)->getTextString();
        ((Parameter<string> *)stringEvents[e.getName()])->set(newString);
    }
    
    // color change
    else {
        string colorName = ofSplitString(e.getName(), "->")[0];
        if (colors.count(colorName) > 0) {
            colors[colorName]->update();
            gui->getWidget(colorName+"->x")->setColorFill(*colors[colorName]->color);
            gui->getWidget(colorName+"->y")->setColorFill(*colors[colorName]->color);
            gui->getWidget(colorName+"->z")->setColorFill(*colors[colorName]->color);
            gui->getWidget(colorName+"->w")->setColorFill(*colors[colorName]->color);
            gui->getWidget(colorName+"->x")->setColorFillHighlight(*colors[colorName]->color);
            gui->getWidget(colorName+"->y")->setColorFillHighlight(*colors[colorName]->color);
            gui->getWidget(colorName+"->z")->setColorFillHighlight(*colors[colorName]->color);
            gui->getWidget(colorName+"->w")->setColorFillHighlight(*colors[colorName]->color);
        }
    }
}

//-------
void Control::guiPresetsEvent(ofxUIEventArgs &e) {
    if (e.getName() == "controlHeader") {
        if (e.getButton()->getValue() == 1) return;
        headerSelected = true;
    }
    else if (e.getName() == "controlPresetsView") {
        if (e.getButton()->getValue() == 1) return;
        togglePresetsVisible();
    }
    else if (e.getName() == "controlPresetsSave") {
        if (e.getButton()->getValue() == 1) return;
        savePreset();
    }
    else if (e.getName() == "viewMeta") {
        setViewMeta(e.getButton()->getValue() == 1);
    }
    else if (e.getParentName() == "presets") {
        string path = ofToDataPath("presets/"+getName()+"/"+e.getName());
        loadPreset(path);
        togglePresetsVisible();
    }
    else if (e.getName() == " > TouchOsc") {
        if (e.getButton()->getValue() == 1) return;
        OscManager osc;
        osc.saveTouchOscLayout("myLayout", getParameters());
    }
}

//-------
void Control::triggerMenuEvent(string menuName, string selection, bool trigger) {
    if (selection == "")    return;
    if (trigger) {
        ofNotifyEvent(*menuEvents[menuName], selection, this);
        ((ofxUILabelToggle *) gui->getWidget(selection))->setValue(trigger);
    }
}

//-------
void Control::addParameterToGui(Parameter<bool> *parameter) {
    gui->addToggle(parameter->getName(), parameter->getReference());
}

//-------
void Control::addParameterToGui(Parameter<int> *parameter) {
    ofxUIMinimalIntSlider *slider = gui->addMinimalIntSlider(parameter->getName(), parameter->getMin(), parameter->getMax(), parameter->getReference());
    slider->setWarp(parameter->getWarp());
}

//-------
void Control::addParameterToGui(Parameter<float> *parameter) {
    ofxUIMinimalSlider *slider = gui->addMinimalSlider(parameter->getName(), parameter->getMin(), parameter->getMax(), parameter->getReference());
    slider->setWarp(parameter->getWarp());
}

//-------
void Control::addParameterToGui(Parameter<ofVec2f> *parameter) {
    gui->addSpacer();
    gui->setWidgetSpacing(0.1);
    ofxUIMinimalSlider *sliderX = gui->addMinimalSlider(parameter->getName()+"->x", parameter->getMin().x, parameter->getMax().x, &parameter->getReference()->x);
    ofxUIMinimalSlider *sliderY = gui->addMinimalSlider(parameter->getName()+"->y", parameter->getMin().y, parameter->getMax().y, &parameter->getReference()->y);
    sliderY->setLabelVisible(false);
    sliderX->setWarp(parameter->getWarp());
    sliderY->setWarp(parameter->getWarp());
    gui->addSpacer();
    gui->setWidgetSpacing(spacing);
}

//-------
void Control::addParameterToGui(Parameter<ofVec3f> *parameter) {
    gui->addSpacer();
    gui->setWidgetSpacing(0.1);
    ofxUIMinimalSlider *sliderX = gui->addMinimalSlider(parameter->getName()+"->x", parameter->getMin().x, parameter->getMax().x, &parameter->getReference()->x);
    ofxUIMinimalSlider *sliderY = gui->addMinimalSlider(parameter->getName()+"->y", parameter->getMin().y, parameter->getMax().y, &parameter->getReference()->y);
    ofxUIMinimalSlider *sliderZ = gui->addMinimalSlider(parameter->getName()+"->z", parameter->getMin().z, parameter->getMax().z, &parameter->getReference()->z);
    sliderY->setLabelVisible(false);
    sliderZ->setLabelVisible(false);
    sliderX->setWarp(parameter->getWarp());
    sliderY->setWarp(parameter->getWarp());
    sliderZ->setWarp(parameter->getWarp());
    gui->addSpacer();
    gui->setWidgetSpacing(spacing);
}

//-------
void Control::addParameterToGui(Parameter<ofVec4f> *parameter) {
    gui->addSpacer();
    gui->setWidgetSpacing(0.1);
    ofxUIMinimalSlider *sliderX = gui->addMinimalSlider(parameter->getName()+"->x", parameter->getMin().x, parameter->getMax().x, &parameter->getReference()->x);
    ofxUIMinimalSlider *sliderY = gui->addMinimalSlider(parameter->getName()+"->y", parameter->getMin().y, parameter->getMax().y, &parameter->getReference()->y);
    ofxUIMinimalSlider *sliderZ = gui->addMinimalSlider(parameter->getName()+"->z", parameter->getMin().z, parameter->getMax().z, &parameter->getReference()->z);
    ofxUIMinimalSlider *sliderW = gui->addMinimalSlider(parameter->getName()+"->w", parameter->getMin().w, parameter->getMax().w, &parameter->getReference()->w);
    sliderY->setLabelVisible(false);
    sliderZ->setLabelVisible(false);
    sliderW->setLabelVisible(false);
    sliderX->setWarp(parameter->getWarp());
    sliderY->setWarp(parameter->getWarp());
    sliderZ->setWarp(parameter->getWarp());
    sliderW->setWarp(parameter->getWarp());
    gui->addSpacer();
    gui->setWidgetSpacing(spacing);
}

//-------
void Control::addColor(string name, ofColor *value) {
    string sn = ofToString(ofRandom(1000));
    ofVec4f *vec = new ofVec4f(value->r, value->g, value->b, value->a);
    GuiColorVecPair *color = new GuiColorVecPair();
    color->color = value;
    color->vec = vec;
    colors[name] = color;
    ParameterBase *parameter = new Parameter<ofVec4f>(name, *vec, ofVec4f(0, 0, 0, 0), ofVec4f(255, 255, 255, 255), 1.0);
    parameters.push_back(parameter);
    parametersVisible[parameter] = true;
    guiElements.push_back(new GuiElement(GuiElement::GUI_PARAMETER, parameters.size()-1));
    setupGui();
}

//-------
void Control::addLabel(string name) {
    guiElements.push_back(new GuiElement(GuiElement::GUI_LABEL, 0, name));
}

//-------
void Control::addSpacer() {
    guiElements.push_back(new GuiElement(GuiElement::GUI_SPACER, 0, ""));
}

//-------
void Control::addParameterToGui(Parameter<string> *parameter) {
    gui->addLabel(parameter->getName()+":");
    ofxUITextInput *textInput = gui->addTextInput(parameter->getName(), *parameter->getReference());
    textInput->setAutoClear(false);
}

//-------
void Control::clear() {
    for (map<string, GuiColorVecPair*>::iterator it=colors.begin(); it!=colors.end(); ++it){
        delete it->second;
        colors.erase(it);
    }
    for (map<string, ofEvent<string>*>::iterator it=menuEvents.begin(); it!=menuEvents.end(); ++it){
        it->second->disable();
        it->second->clear();
        delete it->second;
        menuEvents.erase(it);
    }
    for (map<string, ofEvent<string>*>::iterator it=events.begin(); it!=events.end(); ++it){
        it->second->disable();
        it->second->clear();
        delete it->second;
        events.erase(it);
    }
    for (map<ParameterBase *, bool>::iterator it=parametersVisible.begin(); it!=parametersVisible.end(); ++it){
        parametersVisible.erase(it);
    }
    for (int i=0; i<parameters.size(); i++) {
        delete parameters[i];
    }
    for (int i=0; i<guiElements.size(); i++) {
        delete guiElements[i];
    }
    colors.clear();
    menuEvents.clear();
    menus.clear();
    events.clear();
    parameters.clear();
    parametersVisible.clear();
    guiElements.clear();
}

//-------
void Control::updateColors() {
    for (map<string, GuiColorVecPair*>::iterator it=colors.begin(); it!=colors.end(); ++it){
        it->second->update();
        gui->getWidget(it->first+"->x")->setColorFill(*colors[it->first]->color);
        gui->getWidget(it->first+"->y")->setColorFill(*colors[it->first]->color);
        gui->getWidget(it->first+"->z")->setColorFill(*colors[it->first]->color);
        gui->getWidget(it->first+"->w")->setColorFill(*colors[it->first]->color);
    }
}

//-------
Control::~Control() {
    setActive(false);
    gui->removeWidgets();
    gui->disable();
    guiPresets->removeWidgets();
    guiPresets->disable();
    clear();
    delete gui;
    delete guiPresets;
}