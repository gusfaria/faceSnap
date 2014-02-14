#pragma once

#define OFX_UI_FONT_NAME "sans-serif"

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

#include "ofxFaceTracker.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void exit();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void onGuiEvent( ofxUIEventArgs &e );
    
    //cammera and facetracker
    ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ofVec2f position;
	float scale;
	ofVec3f orientation;
	ofMatrix4x4 rotationMatrix;
	
	Mat translation, rotation;
	ofMatrix4x4 pose;
    
    ofxUITextInput *textBox;
    
    int stage;
    int counter;
    
    //snap shot
    int 				snapCounter;
    char 				snapString[255];
    ofImage 			img;
    bool 				bSnapshot;
    
    //button
    bool bClick;
    //type
    bool bFirst;
    string typeStr;
    ofTrueTypeFont helveticafont30;
    ofTrueTypeFont helfont15;

    
    
    //GUI
    void setGUI(); //button
    void setGUI2(); //input text
    
    ofxUICanvas *gui;
    ofxUICanvas *gui2;
    
    ofBuffer    buffer;
    ofFile      myfile;
    
    bool bDebug;

};
