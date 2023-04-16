#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxKorgNanoKontrolConstants.h"




struct Object
{
    int scene;
    int val;
    int midiId;
};


enum KONTROL_VERSION {KONTROL,KONTROL2};


static int buttons_v1[] = {23,33,24,34,25,35,26,36,27,
                           37,28,38,29,39,30,40,31,41,
                           67,76,68,77,69,78,70,79,71,
                           80,72,81,73,82,74,83,75,84,
                           107,116,108,117,109,118,110,119,111,
                           120,112,121,113,122,114,123,115,124,
                           16,17,16,17,16,17,16,17,16,
                           17,16,17,16,17,16,17,16,17};

static int sliders_v1[] = {2,3,4,5,6,8,9,12,13,
                          42,43,50,51,52,53,54,55,56,
                          85,86,87,88,89,90,91,92,93,
                          7,7,7,7,7,7,7,7,7};

static int potentiometers_v1[] = {14,15,16,17,18,19,20,21,22,
                                 57,58,59,60,61,62,63,65,66,
                                 94,95,96,97,102,103,104,105,106,
                                 10,10,10,10,10,10,10,10,10};

static int kontrol_v1[] = {47,45,48,49,46,44,0};

/*

Info about MIDI values on Korg Nano Kontrol Version 1
Channel value doesn't change by Scene button until 4th scene by default
You can fix it via Korg's Nano Kontrol Editor software
For the best practise I implemented to default values.
 
scene 4
slider list
 

1- ccontrol:7 channell:1
2- ccontrol:7 channell:2
3- control:7 channel:3
4- control:7 channel:4
5- control:7 channel:5
6- control:7 channel:6
7- control:7 channel:7
8- control:7 channel:8
9- control:7 channel:9

 
scene 4
button list
1- b1: 16 , b2: 17 , channel :1
2- b1: 16 , b2: 17 , channel :2
3- b1: 16 , b2: 17 , channel :3
4- b1: 16 , b2: 17 , channel :4
5- b1: 16 , b2: 17 , channel :5
6- b1: 16 , b2: 17 , channel :6
7- b1: 16 , b2: 17 , channel :7
8- b1: 16 , b2: 17 , channel :8
9- b1: 16 , b2: 17 , channel :9
 
scene 4
potentiometer list
1- p1: 10 , channel :1
2- p1: 10 , channel :2
3- p1: 10 , channel :3
4- p1: 10 , channel :4
5- p1: 10 , channel :5
6- p1: 10 , channel :6
7- p1: 10 , channel :7
8- p1: 10 , channel :8
9- p1: 10 , channel :9
 
 */
//static std::vector<int> nanoKontrolButtonMapping (buttons_v1, buttons_v1 + sizeof(buttons_v1) / sizeof(int) );
//static std::vector<int> nanoKontrolAxisMapping (sliders_v1, sliders_v1 + sizeof(sliders_v1) / sizeof(int));

/*
static std::vector<char> nanoKontrol2ButtonMapping {32, 33, 34, 35, 36, 37, 38, 39, 48, 49, 50, 51, 52, 53, 54, 55, 64, 65, 66, 67, 68, 69, 70, 71, 43, 44, 42, 41, 45,58, 59, 60, 61, 62, 46};
static std::vector<char> nanoKontrol2AxisMapping {0,1,2,3,4,5,6,7, 16,17,18,19,20,21,22,23};
*/
class ofxKorgNanoKontrol : public ofxMidiListener {

public:
    ofxKorgNanoKontrol();
    ~ofxKorgNanoKontrol();
    
    void getListMidiDevices();
    
    int getSliderVal(int _control,int _sceneId = 1);
    int getPotVal(int _control,int _sceneId = 1);
    int getButtonVal(int _control,int _sceneId = 1);
    
    
    int getVal(int _control, int _type = K_TYPE_SLIDER, int _sceneId = 1);
    
    void setup(bool autoSet = false, int _portNum = 0);
    void showGui(bool _showGui, int posX = 0, int posY = 0);

    ofEvent<int> sceneButtonPressed;
    ofEvent<int> pushButtonPressed;
    ofEvent<int> sliderValChanged;
    ofEvent<int> potValChanged;
    
private:
    ofxMidiIn midiIn;
    ofxMidiOut midiOut;
    ofxMidiMessage midiMessage;
    
    
    
    KONTROL_VERSION version; // KONTROL or KONTROL2
    
    int findKontrolPort();
    int portNum;
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    vector<Object> sliderVals;
    vector<Object> potVals;
    vector<Object> buttonVals;
    vector<Object> kontrolVals;
    int sceneIdCounter;
    
    bool sceneButton;
    
    // GUI related
    
    int ySpace;
    int yPosMult;
    int yStartPos;
    
    int xPosMult;
    
    
};
