#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
//    ofBackground(40);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);

    //GUI
    setGUI();
    setGUI2();
    
	cam.initGrabber(640, 480);
	
	tracker.setup();
    
    bClick = true;
    
    snapCounter = 0;
	bSnapshot = false;
	memset(snapString, 0, 255);
    
    bFirst = true;
    
    ofTrueTypeFont::setGlobalDpi(72);
    helveticafont30.loadFont("HelveticaNeueLTStd-Blk.otf", 30);
    helfont15.loadFont("HelveticaNeueLTStd-Roman.otf", 12);

    typeStr.clear();
    stage = 0;
    
    counter = 0;
    bDebug = false;
}

//--------------------------------------------------------------
void testApp::exit(){
    
    delete gui;
    delete gui2;
}

void testApp::onGuiEvent(ofxUIEventArgs &e) {
    string name = e.widget->getName();
    
    if (name == "INPUT TEXT") {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: ";
            //            ofUnregisterKeyEvents((testApp*)this);
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
            //            ofRegisterKeyEvents(this);
        }
        typeStr = textinput->getTextString();
        cout << typeStr << endl;
    } else if (name == "SEND"){
        bClick = !bClick;
        bSnapshot = true;
        counter = 0;
        cout << "Button clicked" << endl;
    }
    
}
//--------------------------------------------------------------
void testApp::setGUI(){
    ofColor paddingColor = ofColor(255,0,0,200);
    gui = new ofxUICanvas(ofGetWindowWidth()/2-50,ofGetWindowHeight()/2 + 200,100,35);
    gui->setDrawBack(false);
    gui->setColorBack(paddingColor);
    gui->addLabelButton("SEND", false);
    
    ofAddListener(gui->newGUIEvent,this,&testApp::onGuiEvent);
}
//--------------------------------------------------------------
void testApp::setGUI2(){
    
    gui2 = new ofxUICanvas(ofGetWindowWidth()/2 - 150,(ofGetWindowHeight()/2) - 80, 300, 40);
    gui2->setDrawBack(false);
    gui2->setFontSize(OFX_UI_FONT_MEDIUM, 14);
    textBox = gui2->addTextInput("INPUT TEXT", "INSERT YOUR NAME", 35);
    textBox->setAutoClear(true);
    ofAddListener(gui2->newGUIEvent,this,&testApp::onGuiEvent);
}

//--------------------------------------------------------------
void testApp::update(){
    cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
		position = tracker.getPosition();
		scale = tracker.getScale();
		orientation = tracker.getOrientation();
		rotationMatrix = tracker.getRotationMatrix();
        ofDrawBitmapStringHighlight("position: " +ofToString(position), ofPoint(10,10));
	}
    
    counter ++;
    if (counter > 200) {
        counter = 0;
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackgroundGradient(ofColor(40,40,40), ofColor(20,20,20), OF_GRADIENT_CIRCULAR);

    if(stage != 1){
        gui->toggleVisible();
        gui2->toggleVisible();
    }
    
    if (stage == 0) {
        ofSetColor(255);
        helveticafont30.drawString("DO YOU HAVE SOMETHING TO HIDE?", ofGetWindowWidth()/2-340 , ofGetWindowHeight()/2);
        helveticafont30.drawString("LET THE NSA KNOW WHERE YOU ARE!", ofGetWindowWidth()/2-345 , ofGetWindowHeight()/2 + 45);
        
    } else if (stage == 1) {
        ofSetColor(255);
        helveticafont30.drawString("IS IN NEW YORK", ofGetWindowWidth()/2 - 142 , ofGetWindowHeight()/2);
        helfont15.drawString("Latitude: 40.704196  | Longitude: -74.042358", ofGetWindowWidth()/2 - 132, ofGetWindowHeight()/2 + 25);
        
    } else if (stage == 2) {
        helveticafont30.drawString("THANK YOU FOR YOUR COOPERATION.", ofGetWindowWidth()/2 - 310 , ofGetWindowHeight()/2);
        if(counter >= 140) stage = 0;
    }
    
    if(tracker.getFound()) {
        bFirst = false;
        
        if(counter >= 100 && stage == 0) {
            stage = 1;
        }
        
        if (bSnapshot == true){
            
            unsigned char *camPixels = cam.getPixels();
            img.setFromPixels(camPixels, cam.width, cam.height, OF_IMAGE_COLOR);
            img.crop(tracker.getPosition().x-150, tracker.getPosition().y-150, 300,300);
            string fileName;
//            string dir = "/Users/gusfaria11/Documents/openframeworks_v0.8.0/apps/thesis/PhotoFace/bin/data/img/";
//            string dir = "/Users/gusfaria11/Documents/openframeworks_v0.8.0/apps/thesis/RT_FaceDetect/bin/data/faces/";
            
            string dir = "/Users/gusfaria11/Documents/ofx_v0.8.0/apps/thesis/RT_FaceDetect/bin/data/faces/";
            
//            if(typeStr == ""){
//                fileName = "snapshot_"+ofToString(10000+snapCounter)+".png";
//            } else {
                fileName = typeStr+".png";
//            }

            img.saveImage(dir+fileName);
            sprintf(snapString, "saved %s", fileName.c_str());
            
            //send text to another file.
//            string mydir = "/Users/gusfaria11/Documents/openframeworks_v0.8.0/apps/thesis/RT_FaceDetect/bin/data/train2.txt";
            string mydir = "/Users/gusfaria11/Documents/ofx_v0.8.0/apps/thesis/RT_FaceDetect/bin/data/train2.txt";
//            myfile.open(mydir);
//            string str = "HELLO its me again!\n";
//            cout << str.length() << endl;
//            buffer.allocate(fileName.length());
//            buffer.append(fileName+"\n");
//            myfile.writeFromBuffer(buffer);

//            bool fileWritten = ofBufferToFile(mydir, buffer);
//            buffer.append(fileName+"\n");
//            myfile.close();
            

            
            snapCounter++;
            
            bSnapshot = false;
            bClick = false;
            bFirst = true;

            cam.draw(ofGetWindowWidth(),0);
            buffer = ofBufferFromFile(mydir);
            buffer.append(fileName+"\n");
            ofBufferToFile(mydir, buffer);
            typeStr.clear();
            
            stage = 2;
        }
    }

    if(bDebug){
//DEBUGGING
    ofDrawBitmapStringHighlight("stage: " + ofToString(stage), ofPoint(10,40));
    ofDrawBitmapString(ofToString(counter), ofPoint(10,ofGetWindowHeight()-70));
    ofDrawBitmapString(typeStr, ofPoint(10,ofGetWindowHeight()-50));
    ofPushMatrix();
    ofScale(0.25, 0.25);
    cam.draw(0,0);
    tracker.draw();
    ofPopMatrix();
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    cout << key << "my key" << endl;
    if(key == 'r') {
		tracker.reset();
	}
    
    if(key == OF_KEY_RETURN){
        bClick = !bClick;
        bSnapshot = true;
        counter = 0;
    }
    
    if(key == OF_KEY_UP){
        stage ++;
    } else if (key == OF_KEY_DOWN){
        stage --;
    }
    
    if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
		typeStr = typeStr.substr(0, typeStr.length()-1);
        
	}else{
		if( bFirst && key != 2305){
			typeStr.clear();
			bFirst = false;
		}
		typeStr.append(1, (char)key);
	}
    
    if(key==OF_KEY_CONTROL){
        counter = 0;
        stage = 0;
    }
    if (key==OF_KEY_ALT) bDebug = !bDebug;
    
    if(key==2305) ofToggleFullscreen();
    
    

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    textBox->setTextString("");
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
