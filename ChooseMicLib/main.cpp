//
//  main.cpp
//  ChooseMicLib
//
//  Created by Boss on 30/01/2018.
//  Copyright © 2018 Boss. All rights reserved.
//

#include <iostream>
#include "switch.hpp"

int main(int argc, const char * argv[]) {
    
    ChooseMic test;
    test.findAllInputDevices(kAudioTypeInput);
    std::string newDevice;
    
    test.initializeDeviceIterator();
    //test.advanceDeviceIterator();
    if (test.iteratorEnded() != true) newDevice = test.value();
    
    std::cout << "\nAll Devices:\n";
    test.initializeDeviceIterator();
    while(test.iteratorEnded() != true){
        std::cout << test.value();
        std::cout << "\n";
        test.advanceDeviceIterator();
    }

    std::cout << "\nCurrent:\n";
    std::cout << test.getCurrentInputDevice();
    
    std::cout << "\n\nWanted Device:\n";
    std::cout << newDevice;
    
    test.setDevice((char*)newDevice.c_str());
    
    std::cout << "\n\nCurrent:\n";
    std::cout << test.getCurrentInputDevice();
    std::cout << "\n";
    
    return 0;
}
