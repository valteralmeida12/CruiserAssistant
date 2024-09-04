#ifndef SPEECH_RECOGNITION_H
#define SPEECH_RECOGNITION_H

#include <vector>
#include <sstream>
#include <iostream>
#include <cstring>  // For std::memcpy
#include <alsa/asoundlib.h>
#include <vosk_api.h>

class SpeechRecognition {
public:
    SpeechRecognition();
    ~SpeechRecognition();
    std::string recognize_speech();
private:
    const std::string model_path;
    VoskModel* model;
    VoskRecognizer* recognizer;
    snd_pcm_t* pcm_handle;
};

#endif // SPEECH_RECOGNITION_H
