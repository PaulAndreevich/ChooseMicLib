//
//  switch.cpp
//  ChooseMicLib
//
//  Created by Boss on 30/01/2018.
//  Copyright © 2018 Boss. All rights reserved.
//

//#include "switchWrapHeader.h"
#include "switch.h"

    /*char* ChooseMic::deviceTypeName(ASDeviceType device_type) {
        switch(device_type) {
            case kAudioTypeInput: return (char*)"input";
            default: return (char*)"unknown";
        }
    };*/

    AudioDeviceID Switch::getCurrentlySelectedDeviceID() {
        ASDeviceType typeRequested = kAudioTypeInput;
        UInt32 propertySize;
        AudioDeviceID deviceID = kAudioDeviceUnknown;
        
        // get the default output device
        propertySize = sizeof(deviceID);
        switch(typeRequested) {
            case kAudioTypeInput:
                AudioHardwareGetProperty(kAudioHardwarePropertyDefaultInputDevice, &propertySize, &deviceID);
                break;
            default: break;
        }
        return deviceID;
    };

    const char* Switch::getCurrentInputDevice(){
        char tempdevicename2[256];
        currentDeviceID = getCurrentlySelectedDeviceID();
        getDeviceName(currentDeviceID, tempdevicename2);
        tempdeviceName = tempdevicename2;
        return tempdeviceName.c_str();
    };



    void Switch::getDeviceName(AudioDeviceID deviceID, char* deviceName) {
        UInt32 propertySize = 256;
        AudioDeviceGetProperty(deviceID, 0, false, kAudioDevicePropertyDeviceName, &propertySize, deviceName);
    };


    bool Switch::isAnInputDevice(AudioDeviceID deviceID) {
        UInt32 propertySize = 256;
        
        // if there are any input streams, then it is an input
        AudioDeviceGetPropertyInfo(deviceID, 0, true, kAudioDevicePropertyStreams, &propertySize, NULL);
        if (propertySize > 0) return kAudioTypeInput;
        return false;
    };

    void Switch::findAllInputDevices() {
        printf("In FIND\n");
        ASDeviceType typeRequested = kAudioTypeInput;
        AudioDeviceID devID_array[64];
        UInt32 propertySize;
        char deviceName[256];
        
        AudioHardwareGetPropertyInfo(kAudioHardwarePropertyDevices, &propertySize, NULL);
        AudioHardwareGetProperty(kAudioHardwarePropertyDevices, &propertySize, devID_array);
        numberOfDevices = (propertySize / sizeof(AudioDeviceID));
        
        for(int i = 0; i < numberOfDevices; ++i) {

            switch(typeRequested) {
                case kAudioTypeInput:
                    if (!isAnInputDevice(devID_array[i])) continue;
                    device_type = kAudioTypeInput;
                    break;
                case kAudioTypeUnknown:
                    std::cout << "kAudioTypeUnknown\n";
                    break;
            }
            
            getDeviceName(devID_array[i], deviceName);
            
            namesOfDevices.push_front(deviceName);
            
            //printf("%s (%s)\n",deviceName,deviceTypeName(device_type));
        }
    };

    AudioDeviceID Switch::getRequestedDeviceID(char *requestedDeviceName) {
        ASDeviceType typeRequested = kAudioTypeInput;
        //printf("InsideRequestedDevice\n");
        AudioDeviceID devID_array[64];
        UInt32 propertySize;
        char deviceName[256];
        
        AudioHardwareGetPropertyInfo(kAudioHardwarePropertyDevices, &propertySize, NULL);
        // printf("propertySize=%d\n",propertySize);
        
        AudioHardwareGetProperty(kAudioHardwarePropertyDevices, &propertySize, devID_array);
        numberOfDevices = (propertySize / sizeof(AudioDeviceID));
        // printf("numberOfDevices=%d\n",numberOfDevices);
        
        for(int i = 0; i < numberOfDevices; ++i) {
            switch(typeRequested) {
                case kAudioTypeInput:
                    if (!isAnInputDevice(devID_array[i])) continue;
                    break;
                default:
                    break;
            }
            
            getDeviceName(devID_array[i], deviceName);
            // printf("For device %d, id = %d and name is %s\n",i,dev_array[i],deviceName);
            if (strcmp(requestedDeviceName, deviceName) == 0) {
                return devID_array[i];
            }
        }
        return kAudioDeviceUnknown;
    };


    void Switch::setDevice(char *requestedDeviceName) {
        AudioDeviceID newDeviceID = getRequestedDeviceID(requestedDeviceName);
        ASDeviceType typeRequested = kAudioTypeInput;
        UInt32 propertySize = sizeof(UInt32);
        
        switch(typeRequested) {
            case kAudioTypeInput:
                AudioHardwareSetProperty(kAudioHardwarePropertyDefaultInputDevice, propertySize, &newDeviceID);
                break;
            default: break;
        }
        
    };
    
    const char* Switch::value(){
        return (*currentDevice).c_str();
    };

    void Switch::initializeDeviceIterator(){
        currentDevice = namesOfDevices.begin();
    };
    
    void Switch::advanceDeviceIterator(){
        advance(currentDevice,1);
    };
    
    bool Switch::iteratorEnded(){
        if (currentDevice == namesOfDevices.end())
            return true;
        return false;
    };
