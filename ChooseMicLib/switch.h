//
//  switch.hpp
//  ChooseMicLib
//
//  Created by Boss on 30/01/2018.
//  Copyright © 2018 Boss. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>
#include <CoreServices/CoreServices.h>
#include <CoreAudio/CoreAudio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <list>

using namespace std;

typedef enum {
    kAudioTypeUnknown = 0,
    kAudioTypeInput   = 1,
} ASDeviceType;

enum {
    kFunctionSetDevice   = 1,
    kFunctionShowHelp    = 2,
    kFunctionShowAll     = 3,
    kFunctionShowCurrent = 4,
    kFunctionCycleNext   = 5
};

class Switch {
    private:
        int numberOfDevices = 0;
        int currentDeviceNameLength = 0;
        string tempdeviceName;
        list<string> namesOfDevices;
        list<string>::iterator currentDevice;
    
        AudioDeviceID currentDeviceID;
        ASDeviceType device_type;
    
    protected:
        //char* deviceTypeName(ASDeviceType device_type);
        AudioDeviceID getRequestedDeviceID(char * requestedDeviceName);
        void getDeviceName(AudioDeviceID deviceID, char * deviceName);
        bool isAnInputDevice(AudioDeviceID deviceID);
        AudioDeviceID getCurrentlySelectedDeviceID();
    
    public:
        Switch() {
            numberOfDevices = 0;
            tempdeviceName = "Hello";
            device_type = kAudioTypeUnknown;
        };
    
        void printHello(){
            printf("Hello World");
        }
    
        int getCurrentDeviceNameLength(){
            return currentDeviceNameLength;
        }
    
        //return current input device
        const char* getCurrentInputDevice();
    
        //find devices
        void findAllInputDevices();
    
        //?? find the devices again (refresh)
        //?? void refreshSystemList();
    
        // setting the Device
        void setDevice(const char * requestedDeviceName);
    
        //iterator value
        const char* value();
    
        //iterator initialize
        void initializeDeviceIterator();
    
        //iterator ++
        void advanceDeviceIterator();
    
        //iterator ended??
        bool iteratorEnded();
};



















