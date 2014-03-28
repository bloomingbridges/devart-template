#include "MeshwurstApp.h"
#include "ofBitmapFont.h"
#include "PlaceholderContainer.h"
#include "WurstContainer.h"

//--------------------------------------------------------------
void MeshwurstApp::setup(){
    models.push_back(new ModelContainer(0));
    models.push_back(new ModelContainer(1));
    models.push_back(new PlaceholderContainer(models.size()));
    models[0]->populate("cow.3ds");
    models[1]->populate("dog.3ds");
    models[0]->selected = true;
    selectionTitle = models[0]->getInfo();
    camera.setVFlip(true);
    cameraTargetPosition = ofVec3f(-25.0, 0.0, 200.0);
    camera.rotate(15.0, ofVec3f(0.0, -1.0, 0.0));
//    camera.setGlobalPosition(cameraTargetPosition);
    infoPosition = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 + 50.0);
    grinder = ofPlanePrimitive(1500.0, 150.0, 100, 10, OF_PRIMITIVE_TRIANGLE_STRIP);
    grinder.setGlobalPosition(500.0, 175.0, 10.0);
    ofSetLineWidth(1.0);
    ofEnableAlphaBlending();
    ofEnableDepthTest();
}

//--------------------------------------------------------------
void MeshwurstApp::update(){
    ofVec3f direction = camera.getPosition();
    direction.x += (cameraTargetPosition.x - direction.x) * 0.1;
    direction.y += (cameraTargetPosition.y - direction.y) * 0.05;
    direction.z += (cameraTargetPosition.z - direction.z) * 0.1;
    //    cout << "DIR: " << direction.x << " TARGET: " << cameraTarget.x << endl;
    camera.setGlobalPosition(direction);
}

//--------------------------------------------------------------
void MeshwurstApp::draw(){
    ofBackground(27,13,13);
    
    camera.begin();
    for(int i = 0; i < models.size(); i++){
        models[i]->draw();
    }
    ofLight();
    for(int i = 0; i < results.size(); i++){
        results[i]->draw();
    }
    drawWurster();
    camera.end();
    
    drawInfo();
}

//--------------------------------------------------------------
void MeshwurstApp::keyPressed(int key){
    if (key == ' ')
        action = true;
}

//--------------------------------------------------------------
void MeshwurstApp::keyReleased(int key){
//    cout << "KEY " << key << endl;
    switch (key) {
            
        case OF_KEY_LEFT:
            previousContainer();
            break;
            
        case OF_KEY_RIGHT:
            nextContainer();
            break;
            
        case OF_KEY_DOWN:
            if (results.size() > 0) {
                browseResults(false);
            }
            break;
            
        case OF_KEY_UP:
            if (browsingResults) {
                stopBrowsing();
            }
            break;
            
        case ' ':
            performAction();
            action = false;
            break;
            
        case 'f':
            ofToggleFullscreen();
            infoPosition = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2 + 50.0);
            break;
            
        case 'd':
            
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void MeshwurstApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void MeshwurstApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void MeshwurstApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void MeshwurstApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void MeshwurstApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void MeshwurstApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void MeshwurstApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void MeshwurstApp::drawInfo() {
    ofFill();
    ofSetColor(200, 200, 200, 128);
    ofRect(ofGetWindowWidth() - 110.0, 22.0, 120.0, 25.0);
    int alpha = (action) ? 128 : 32;
    ofSetColor(200, 200, 200, alpha);
    ofRect(ofBitmapStringGetBoundingBox(selectionTitle, infoPosition.x, infoPosition.y));
    string action = (!browsingResults && selection < models.size()-1)
        ? "SPACE Grind model"
        : "SPACE Export wurst";
    if (selection == models.size()-1) action = "";
    ofSetColor(100, 100, 100, alpha);
    ofRect(ofBitmapStringGetBoundingBox(action, infoPosition.x, infoPosition.y + 20));
    ofSetColor(255);
    ofDrawBitmapString("meshwurster", ofGetWindowWidth() -100.0,  40.0);
    ofDrawBitmapString("DAY #3", ofGetWindowWidth() -100.0,  64.0);
    ofDrawBitmapString(selectionTitle, infoPosition.x, infoPosition.y);
    ofDrawBitmapString(action, infoPosition.x, infoPosition.y + 20);
}

//--------------------------------------------------------------
void MeshwurstApp::performAction() {
    if (!browsingResults)
    {
        if (selection == models.size() - 1) {
            cout << "MORE MODELS!" << endl;
            ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a model");
            if (openFileResult.bSuccess) {
                cout << "SUCCESS! " << openFileResult.getPath() << endl;
                models.push_back(new ModelContainer(models.size()));
                models[-1]->populate(openFileResult.getPath());
                swap(models[-1], models[-2]);
            }
        }
        else {
            cout << "WURST!" << endl;
            results.push_back(new WurstContainer(results.size(), models[selection]->getWurst(), models[selection]->getInfo()));
            browseResults(true);
        }
    }
    else
    {
        cout << "EXPORTING!" << endl;
    }
}

//--------------------------------------------------------------
void MeshwurstApp::drawWurster() {
    ofSetColor(32,32,32);
    grinder.drawWireframe();
}

//--------------------------------------------------------------
void MeshwurstApp::nextContainer() {
    if (!browsingResults) {
        models[selection]->selected = false;
        selection = (selection + 1 < models.size())
        ? selection + 1 : 0;
        models[selection]->selected = true;
        selectionTitle = models[selection]->getInfo();
        //            cameraTarget.x = selection * 150;
    } else {
        results[selection]->selected = false;
        selection = (selection + 1 < results.size())
        ? selection + 1 : 0;
        results[selection]->selected = true;
        selectionTitle = results[selection]->getInfo();
    }
    cameraTargetPosition.x = (selection * 150) - 25;
}

//--------------------------------------------------------------
void MeshwurstApp::previousContainer() {
    if (!browsingResults) {
    models[selection]->selected = false;
    selection = (selection - 1 >= 0)
    ? selection - 1
    : models.size() - 1;
    models[selection]->selected = true;
    selectionTitle = models[selection]->getInfo();
    //            cameraTarget.x = selection * 150;
    } else {
        results[selection]->selected = false;
        selection = (selection - 1 >= 0)
        ? selection - 1
        : results.size() - 1;
        results[selection]->selected = true;
        selectionTitle = results[selection]->getInfo();
    }
    cameraTargetPosition.x = (selection * 150) - 25;
}

//--------------------------------------------------------------
void MeshwurstApp::browseResults(bool latest) {
    browsingResults = true;
    models[selection]->selected = false;
    if (selection > results.size() - 1) {
        selection = results.size() - 1;
        cameraTargetPosition.x = (selection * 150.0) - 25.0;
    } else if (latest) {
        cameraTargetPosition.x = (results.size() - 1) * 150.0 - 25.0;
        selection = results.size() - 1;
    }
    results[selection]->selected = true;
    selectionTitle = results[selection]->getInfo();
    cameraTargetPosition.y = 350.0;
}

//--------------------------------------------------------------
void MeshwurstApp::stopBrowsing() {
    results[selection]->selected = false;
    if (selection > models.size() - 1) {
        selection = models.size() - 1;
        cameraTargetPosition.x = (selection * 150.0) - 25.0;
    }
    models[selection]->selected = true;
    selectionTitle = models[selection]->getInfo();
    cameraTargetPosition.y = 0.0;
    browsingResults = false;
}


