#include "SpeechRecognition.h"
#include <iostream>
#include <sstream>

SpeechRecognition::SpeechRecognition() : model_path("/opt/vosk_model/model") {
    // Initialize Vosk model
    model = vosk_model_new(model_path.c_str());
    if (model == nullptr) {
        std::cerr << "Failed to load model from " << model_path << std::endl;
        exit(1);
    }

    // Initialize ALSA for audio capture
    if (snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_CAPTURE, 0) < 0) {
        std::cerr << "Error opening PCM device" << std::endl;
        exit(1);
    }

    if (snd_pcm_set_params(pcm_handle,
                           SND_PCM_FORMAT_S16_LE,
                           SND_PCM_ACCESS_RW_INTERLEAVED,
                           1,
                           16000,
                           1,
                           500000) < 0) {
        std::cerr << "Error setting PCM parameters" << std::endl;
        exit(1);
    }

    // Initialize Vosk recognizer
    recognizer = vosk_recognizer_new(model, 16000.0);
}

SpeechRecognition::~SpeechRecognition() {
    // Clean up Vosk and ALSA resources
    vosk_recognizer_free(recognizer);
    vosk_model_free(model);
    snd_pcm_close(pcm_handle);
}

std::string SpeechRecognition::recognize_speech() {
    // Buffer size for audio data
    const int BUFFER_SIZE = 4096;  // Adjust this as needed
    int16_t buffer[BUFFER_SIZE];

    std::ostringstream result_stream;

    while (true) {
        // Capture audio from ALSA
        int frames = snd_pcm_readi(pcm_handle, buffer, BUFFER_SIZE);
        if (frames < 0) {
            frames = snd_pcm_recover(pcm_handle, frames, 0);
        }
        if (frames < 0) {
            std::cerr << "Error reading from PCM device" << std::endl;
            break;
        }

        // Convert int16_t buffer to const char* for Vosk recognizer
        const char* char_buffer = reinterpret_cast<const char*>(buffer);
        int buffer_size = frames * sizeof(int16_t);  // The size of the audio data in bytes

        // Pass audio to Vosk recognizer
        if (vosk_recognizer_accept_waveform(recognizer, char_buffer, buffer_size)) {
            const char* result = vosk_recognizer_result(recognizer);
            result_stream << result;
            break;  // End after receiving a complete result
        } else {
            const char* partial_result = vosk_recognizer_partial_result(recognizer);
            std::cout << partial_result << std::endl;  // For debugging partial results
        }
    }

    return result_stream.str();
}
