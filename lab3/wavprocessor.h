#pragma once

#include <string>
#include <vector>
#include <cstdint>

class WavProcessor {
    std::string filePath;
    std::vector<int16_t> samples;
    int sampleRate;

public:
    WavProcessor(const std::string& filePath);
    const std::vector<int16_t>& getSamples() const;
    std::vector<int16_t>& getSamples();
    int getSampleRate() const;
    void save(const std::string& outputPath) const;
    void printInfo() const;
};
