//
//  ModelContainer.h
//  Meshwurst
//
//  Created by Florian Brueckner on 25/03/2014.
//
//

#ifndef __Meshwurst__ModelContainer__
#define __Meshwurst__ModelContainer__

#include <iostream>
#include "ofxAssimpModelLoader.h"
#include "Wurst.h"

class ModelContainer {
    
    public:
    
        void populate(string file);
        void draw();
        string getInfo();
        Wurst getWurst();
    
        ofVec3f position;
        float rotation;
        bool selected;
    
        ModelContainer(int offset);

    protected:
    
        void drawMesh();
        void drawOutline();
        ofMesh wurst(ofMesh mesh);
    
        ofxAssimpModelLoader model;
        string info;
        ofColor highlightColor;
    
};

#endif /* defined(__Meshwurst__ModelContainer__) */
