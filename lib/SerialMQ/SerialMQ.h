#ifndef SerialMQ_h
#define SerialMQ_h

#include "StandardCplusplus.h"
#include "map"
// #include <iostream>
// 
#include <stdarg.h>
#include "SerialPrint.h"
#include "SerialMQData.h"
#include "Arduino.h"

class SerialMQ {
    public:
        // static void Add(std::string cmd, std::string msg);
        SerialMQ();
        void Send(const char* format,...);
        void Update();
        
        const SerialMQData& getData(String key) const;
        const String& getValue(String key) const;
        const int& getCounter(String key) const;

        // TODO:: implement receive part
    private:
        std::map< String, SerialMQData> msgQueue;
        String mReceivedString;
};

#endif
