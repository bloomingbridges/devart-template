#pragma once

#include "ofMain.h"
#include "ModelContainer.h"
#include "WurstContainer.h"

class MeshwurstApp : public ofBaseApp {

	public:
		void setup();
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
    
        vector<ModelContainer *> models;
        vector<WurstContainer *> results;
        int selection;
        bool action;
        string selectionTitle;
        ofVec2f infoPosition;
        ofVec2f cameraTarget;
        ofVec3f cameraTargetPosition;
        ofCamera camera;
        ofPlanePrimitive grinder;
    
    private:
        void drawInfo();
        void drawWurster();
        void performAction();
        void nextContainer();
        void previousContainer();
        void browseResults(bool latest);
        void stopBrowsing();
    
        bool browsingResults;
		
};
