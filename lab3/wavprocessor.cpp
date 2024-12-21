#include "WavProcessor.h"
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iostream>

WavProcessor::WavProcessor(const std::string& filePath) : filePath(filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open WAV file: " + filePath);
    }

    // Parse WAV header
    char header[44];
    file.read(header, 44);
    if (std::strncmp(header, "RIFF", 4) != 0 || std::strncmp(header + 8, "WAVE", 4) != 0) {
        throw std::runtime_error("Unsupported WAV file format.");
    }
    sampleRate = *reinterpret_cast<int*>(header + 24);
    int dataSize = *reinterpret_cast<int*>(header + 40);

    // Read samples
    samples.resize(dataSize / 2);
    file.read(reinterpret_cast<char*>(samples.data()), dataSize);
}

const std::vector<int16_t>& WavProcessor::getSamples() const {
    return samples;
}

std::vector<int16_t>& WavProcessor::getSamples() {
    return samples;
}

int WavProcessor::getSampleRate() const {
    return sampleRate;
}

void WavProcessor::save(const std::string& outputPath) const {
    std::ofstream file(outputPath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputPath);
    }

    // Write WAV header
    int dataSize = samples.size() * 2;
    char header[44] = {};
    std::memcpy(header, "RIFF", 4);
    *reinterpret_cast<int*>(header + 4) = 36 + dataSize;
    std::memcpy(header + 8, "WAVE", 4);
    std::memcpy(header + 12, "fmt ", 4);
    *reinterpret_cast<int*>(header + 16) = 16;
    *reinterpret_cast<short*>(header + 20) = 1;
    *reinterpret_cast<short*>(header + 22) = 1;
    *reinterpret_cast<int*>(header + 24) = sampleRate;
    *reinterpret_cast<int*>(header + 28) = sampleRate * 2;
    *reinterpret_cast<short*>(header + 32) = 2;
    *reinterpret_cast<short*>(header + 34) = 16;
    std::memcpy(header + 36, "data", 4);
    *reinterpret_cast<int*>(header + 40) = dataSize;

    file.write(header, 44);
    file.write(reinterpret_cast<const char*>(samples.data()), dataSize);
}

void WavProcessor::printInfo() const {
    std::cout << "WAV File Info:" << std::endl;
    std::cout << "File Path: " << filePath << std::endl;
    std::cout << "Sample Rate: " << sampleRate << " Hz" << std::endl;
    std::cout << "Number of Samples: " << samples.size() << std::endl;
    std::cout << "First 10 Samples (if available): ";

    // Печатаем первые 10 сэмплов (если они есть)
    for (size_t i = 0; i < std::min(samples.size(), size_t(10)); ++i) {
        std::cout << samples[i] << " ";
    }
    std::cout << std::endl;
}