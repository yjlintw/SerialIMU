#include "SerialMQData.h"

SerialMQData::SerialMQData():msg(""), counter(0) {
}

void SerialMQData::setMsg(const String msg) {
    this->msg = msg;
    counter++;
}


const String& SerialMQData::getMsg() const {
    return this->msg;
}

const int& SerialMQData::getCounter() const {
    return counter;
}

void SerialMQData::clear() {
    counter = 0;
    msg = "";
}
