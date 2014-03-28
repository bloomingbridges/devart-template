//
//  WurstContainer.cpp
//  Meshwurst
//
//  Created by Florian Brueckner on 26/03/2014.
//
//

#include "WurstContainer.h"

WurstContainer::WurstContainer(int offset, Wurst wurst, string meat) : ModelContainer(offset)
{

    highlightColor = ofColor(255,0,128,200);
    position.x = offset * 150.0;
    position.y = 350;
    model = wurst;
    origin = meat;
    info = meat + "~";
//    cout << model.scale << endl;
    
}

void WurstContainer::draw() {
        drawMesh();
        ofNoFill();
        ofDrawBox(position.x, position.y, position.z, 100.0);
}

void WurstContainer::drawMesh() {
    if (selected) {
        ofSetColor(highlightColor);
        rotation += (TWO_PI / 360) * 5.0;
    }
    else
        ofSetColor(200, 200, 200, 128);
    
    ofPushMatrix();
    ofTranslate(position.x, position.y, position.z);
    float scaleFactor;
    if (model.scale > 1.0) {
        scaleFactor = model.scale / ( model.mesh.getNumVertices() / 1000.0 );
    } else {
        scaleFactor = 3.0 / model.scale;
        ofMultMatrix(model.matrix);
    }
    ofScale(scaleFactor, scaleFactor, scaleFactor);
    ofRotate(rotation, 0.0, 1.0, 0.0);
    model.mesh.draw(OF_MESH_FILL);
    ofPopMatrix();
}
