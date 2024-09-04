cmake_minimum_required(VERSION 3.10)
project(CruiserAssistant)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(src/Assistant)
include_directories(src/Speech)
include_directories(src/Time)
include_directories(${CMAKE_SOURCE_DIR}/vosk-linux-x86_64-0.3.43)

# Define the source files
set(SOURCES
    src/Assistant/Assistant.cpp
    src/Speech/SpeechRecognition.cpp
    src/Time/TimeUtils.cpp
    main.cpp
)

add_executable(cruiser_assistant ${SOURCES})

# Link the Vosk shared library (.so)
target_link_libraries(cruiser_assistant ${CMAKE_SOURCE_DIR}/vosk-linux-x86_64-0.3.43/libvosk.so pthread asound)
