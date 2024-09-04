#include "Assistant.h"
#include <iostream>
#include <chrono>
#include <thread> // For std::this_thread::sleep_for

Assistant::Assistant() : recognizer() {}

bool Assistant::isWakeWordDetected(const std::string& text) {
    return text.find("hey cruiser") != std::string::npos;
}

void Assistant::listenForCommand() {
    auto last_speech_time = std::chrono::steady_clock::now();

    while (true) {
        std::string command = recognizer.recognize_speech();

        if (!command.empty()) {
            last_speech_time = std::chrono::steady_clock::now();  // Reset the timeout

            if (command == "What time is it?" || command == "What is the time?") {
                std::string current_time = get_current_time();
                std::cout << "Current time: " << current_time << std::endl;
                break;
            } else if (command == "What is the date today?" || command == "What day is today?") {
                std::string current_date = get_current_time();
                std::cout << "Today's date: " << current_date << std::endl;
                break;
            } else {
                std::cout << "Command not recognized" << std::endl;
                break;
            }
        }

        // Calculate time since the last speech was detected
        auto elapsed_time = std::chrono::steady_clock::now() - last_speech_time;
        // End conversation after 10 seconds of inactivity
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed_time).count() >= 10) {
            std::cout << "Closing the conversation." << std::endl;
            break;
        }

        // Sleep briefly to prevent busy-waiting
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Assistant::run() {
    while (true) {
        std::string text = recognizer.recognize_speech();
        std::cout << "Recognized text: " << text << std::endl;
        if (isWakeWordDetected(text)) {
            std::cout << "Wake word detected: Hey Cruiser!" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait before listening for commands
            listenForCommand();
        }
    }
}
