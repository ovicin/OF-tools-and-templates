#pragma once

#include "ofMain.h"
#include "MantaController.h"
#include "Learn.h"


class MantaLearn : public Learn
{
public:
    MantaLearn();
    
    void update();
    void draw();
    
    void addAllPadsAsInput();
    void addSlidersAsInput();
    void addButtonsAsInput();
    void addNumFingersAsInput();
    void addPadSumAsInput();
    void addPadAverageAsInput();
    void addPerimterAsInput();
    void addAverageInterFingerDistanceAsInput();
    void addCentroidAsInput();
    void addWeightedCentroidAsInput();
    
protected:
    
    MantaController manta;
};
