#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "Theory.h"
#include "Sequencer.h"
#include "Control.h"
#include "MantaController.h"


class Instrument
{
public:
    Instrument();
    ~Instrument();
    
    enum NoteMode   { MANUAL, AUTO };
    enum NoteType   { NOTE_ON, NOTE_OFF, NOTE_AUTO };
    enum OutputMode { PARAMETERS, NOTES };

    struct ParameterMapping {
        string name;
        int parameterId;
        float min, max;
        float rmin, rmax;
    };
    
    void setup();
    void connectTo(ofxAudioUnitMixer &mixer, int channel=0);
    
    void update();
    void draw();
    
    void setActive(bool active);
    void chooseSequencerMode(string &s);
    void toggleSmooth(string &s);
    
    void setupGui();
    void setupGuiPresets();
    void setupGuiSeqInspector(int guiActiveSeq);
    void setupGuiPadInspector(int guiActiveManta);
    void setupGuiPadInspector() { guiActiveIsSequencer ? setupGuiSeqInspector(guiActiveSeq) : setupGuiPadInspector(guiActiveManta); }
    void setupGuiParameterGroup(string parameterGroupName);
    
    void savePreset(string filename="");
    void loadPreset(string &filename);

    void showUI() {aalto.showUI();}
    void printParameterList();

protected:
    
    void noteEvent(NoteType type, int note, int velocity=127);
    void sequencerStepEvent(vector<float> &column);
    void sequencerInterpolatedStepEvent(vector<float> &column);
    void processColumn(vector<float> &column);

    void guiParametersEvent(ofxUIEventArgs &e);
    void guiStatsEvent(ofxUIEventArgs &e);
    
    void padClickEvent(int & pad);
    void sliderClickEvent(int & slider);
    void buttonClickEvent(int & button);
    
    void mantaPadEvent(ofxMantaEvent &e);
    void mantaPadVelocityEvent(ofxMantaEvent &e);
    void mantaSliderEvent(ofxMantaEvent &e);
    void mantaButtonEvent(ofxMantaEvent &e);
    
    Control control;
    OutputMode sequencerMode;

    MantaController manta;
    Sequencer sequencer;
    Theory theory;

    ofxAudioUnitSampler aalto; //, kaivo;
//  ofxAudioUnitMixer mixer;
//	ofxAudioUnitOutput output;
    
    map<int, int> noteEvents;
    bool noteStatus[128];
    bool noteManual, sequencerManta, mantaSendNotes, sequencerSmooth;
    int noteAutoFrameLength;
    int noteVelocity;
    
    map<string, vector<string> > parameterGroups;
    vector<string> parameterGroupNames;
    vector<ParameterMapping> parameters;
    map<int, ParameterMapping> mantaMap, seqMap;

    ofxUICanvas *guiP, *guiS;
    ofxUIDropDownList *guiParameterGroups, *guiParameters;
    ofxUIRangeSlider *guiParameterRange;
    ofxUITextInput *guiParameterMin, *guiParameterMax;
    
    int guiActiveManta, guiActiveSeq;
    bool guiActiveIsSequencer;
    bool guiToSwitchParameters;
    string guiToSwitchParametersName;
};
