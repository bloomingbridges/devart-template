//
//  WurstContainer.h
//  Meshwurst
//
//  Created by Florian Brueckner on 26/03/2014.
//
//

#ifndef __Meshwurst__WurstContainer__
#define __Meshwurst__WurstContainer__

#include <iostream>
#include <ModelContainer.h>

class WurstContainer : public ModelContainer {

    public:
    
        void drop(ofMesh mesh);
        void draw();
        void upload();
    
        WurstContainer(int offset, Wurst wurst, string meat);
    
    private:
    
        void drawMesh();
    
        Wurst model;
        string origin;
};

#endif /* defined(__Meshwurst__WurstContainer__) */
