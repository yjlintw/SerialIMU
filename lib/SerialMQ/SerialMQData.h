#ifndef SerialMQData_h
#define SerialMQData_h

#include "Arduino.h"

class SerialMQData {
    public:
        SerialMQData();
        void setMsg(const String msg);
        const String& getMsg() const;
        const int& getCounter() const;
        void clear();

    private:
        String msg;
        int counter;
};

#endif
