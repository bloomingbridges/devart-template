#include "ofMain.h"
#include "MeshwurstApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,640,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new MeshwurstApp());

}