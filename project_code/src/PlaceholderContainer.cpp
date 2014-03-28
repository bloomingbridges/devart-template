//
//  PlaceholderContainer.cpp
//  Meshwurst
//
//  Created by Florian Brueckner on 26/03/2014.
//
//

#include "PlaceholderContainer.h"

PlaceholderContainer::PlaceholderContainer(int last) : ModelContainer(last) {

    populate("plus.dae");
    model.setScale(0.05, 0.05, 0.05);
    highlightColor.g = 192;
    highlightColor.b = 192;
    highlightColor.a = 255;
    info = "SPACE Import new model";
    
}
