#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "SpeechRecognition.h"
#include "TimeUtils.h"
#include <string>

class Assistant {
public:
    Assistant();
    void run();
private:
    SpeechRecognition recognizer;
    bool isWakeWordDetected(const std::string& text);
    void listenForCommand();
};

#endif // ASSISTANT_H
