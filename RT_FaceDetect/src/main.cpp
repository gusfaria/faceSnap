#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
    //	ofSetupOpenGL(&window, 1920, 1200, OF_FULLSCREEN);
	ofSetupOpenGL(640,480, OF_WINDOW);			// <-------- setup the GL context
//    ofSetupOpenGL(1440,900, OF_WINDOW);			// <-------- setup the GL context

	ofRunApp(new testApp());
}
