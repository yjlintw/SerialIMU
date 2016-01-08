#include "SerialMQ.h"
#include <alloca.h>

// static std::queue<String> msgQueue;

// void SerialMQ::Add(std::string cmd, std::string msg) {
//     msgQueue.push(cmd + " " +msg);
//
// }

SerialMQ::SerialMQ():mReceivedString("") {
}

void SerialMQ::Send(const char* format,...) {
    va_list arg_list;
    va_start(arg_list, format);
    char short_buf[128];
    const size_t needed = vsnprintf(short_buf, sizeof short_buf, format, arg_list) + 1;
    if (needed <= sizeof short_buf) {
        Serialprint("%s\n", short_buf);
        // msgQueue.push(short_buf);
        return;
    }

    char* p = static_cast<char*>(alloca(needed));
    vsnprintf(p, needed, format, arg_list);
    va_end(arg_list);
    // msgQueue.push(p);
    Serialprint("%s\n", p);
    // Serial.println(p);

}

void SerialMQ::Update() {
    char serialByte = 0;
    String msg = "";
    while (Serial.available() > 0) {
        serialByte = Serial.read();
        if (serialByte > 1) {
            mReceivedString += serialByte;
        }
    }

    int sep = mReceivedString.indexOf('\n');
    String logString = "";
    while (sep != -1) {
        logString = mReceivedString.substring(0, sep); 
        mReceivedString = mReceivedString.substring(sep + 1);

        int sep2 = logString.indexOf(" ", 0);
        String cmd;
        String content;
        if (sep2 != -1) {
            cmd = logString.substring(0, sep2);
            content = logString.substring(sep2 + 1);
            
            std::map<String, SerialMQData>::iterator lb = msgQueue.lower_bound(cmd);
            if (lb != msgQueue.end() && !(msgQueue.key_comp()(cmd, lb->first))) {
                lb->second.setMsg(content);
            } else {
                SerialMQData data = SerialMQData();
                data.setMsg(content);
                msgQueue.insert(lb, std::map<String, SerialMQData>::value_type(cmd, data));
            }
        }
        sep = mReceivedString.indexOf('\n');
    }
}


const SerialMQData& SerialMQ::getData(String key) const {
    std::map<String, SerialMQData>::const_iterator pos = msgQueue.find(key);

    if (pos == msgQueue.end()) {
        return SerialMQData();
    } else {
        return pos->second;
    }
}
const String& SerialMQ::getValue(String key) const {
    return getData(key).getMsg();
}
const int& SerialMQ::getCounter(String key) const {
    return getData(key).getCounter();
}

// void SerialMQ::Submit() {
//     Serialprint("msgsize: %d\n", msgQueue.size());
//     while(!msgQueue.empty()) {
//         String msg = msgQueue.front();
//         msgQueue.pop(); 
//         Serialprint("%s\n", msg.c_str());
//     }
// }
