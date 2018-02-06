//
//  switch.hpp
//  ChooseMicLib
//
//  Created by Boss on 30/01/2018.
//  Copyright © 2018 Boss. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
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

class ChooseMic {
    private:
        int numberOfDevices = 0;
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
        ChooseMic(){
            numberOfDevices = 0;
            device_type = kAudioTypeUnknown;
        }

        //return current input device
        const char* getCurrentInputDevice();
    
        //find devices
        void findAllInputDevices(ASDeviceType typeRequested);
    
        //?? find the devices again (refresh)
        //?? void refreshSystemList();
    
        // setting the Device
        void setDevice(char *requestedDeviceName);
    
        //iterator value
        const char* value();
    
        //iterator initialize
        void initializeDeviceIterator();
    
        //iterator ++
        void advanceDeviceIterator();
    
        //iterator ended??
        bool iteratorEnded();
};



















