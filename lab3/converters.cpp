#include "converters.h"
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "wavprocessor.h"

std::map<std::string, ConverterFactory::CreatorFunction> ConverterFactory::converters;

void ConverterFactory::registerConverter(const std::string& name, CreatorFunction creator) {
    converters[name] = std::move(creator);
}

std::unique_ptr<Converter> ConverterFactory::createConverter(const std::string& name, const std::vector<std::string>& args) {
    auto it = converters.find(name);
    if (it == converters.end()) {
        throw std::runtime_error("Unknown converter: " + name);
    }
    return it->second(args);
}

std::map<std::string, std::string> ConverterFactory::getAvailableConverters() {
    return {
        {"mute", "Mute a specified time interval. Args: <startTime> <endTime> (seconds)"},
        {"mix", "Mix with another sample stream. Args: <additionalFile> <startTime> (seconds)"},
        {"volume", "Apply a volume transformation. Args: <factor> (multiplier for sample amplitude)"}
    };
}

void registerDefaultConverters() {
    ConverterFactory::registerConverter("mute", [](const std::vector<std::string>& args) {
        if (args.size() != 2) {
            throw std::runtime_error("MuteConverter requires 2 arguments: <startTime> <endTime>");
        }
        double startTime = std::stod(args[0]);
        double endTime = std::stod(args[1]);
        return std::make_unique<MuteConverter>(startTime, endTime);
        });

    ConverterFactory::registerConverter("mix", [](const std::vector<std::string>& args) {
        if (args.size() != 2) {
            throw std::runtime_error("MixConverter requires 2 arguments: <additionalFile> <startTime>");
        }
        const std::string& additionalFile = args[0];
        double startTime = std::stod(args[1]);

        WavProcessor addFile(additionalFile);
        std::vector<int16_t> additionalSamples = addFile.getSamples();

        return std::make_unique<MixConverter>(additionalSamples, startTime);
        });

    ConverterFactory::registerConverter("volume", [](const std::vector<std::string>& args) {
        if (args.size() != 1) {
            throw std::runtime_error("VolumeConverter requires 1 argument: <factor>");
        }
        double factor = std::stod(args[0]);
        return std::make_unique<VolumeConverter>(factor);
        });
}

MuteConverter::MuteConverter(double startTime, double endTime)
    : startTime(startTime), endTime(endTime) {}

void MuteConverter::process(std::vector<int16_t>& samples, int sampleRate) {
    int startSample = static_cast<int>(startTime * sampleRate);
    int endSample = static_cast<int>(endTime * sampleRate);

    for (int i = startSample; i < endSample && i < samples.size(); ++i) {
        samples[i] = 0;
    }
}

MixConverter::MixConverter(const std::vector<int16_t>& additionalSamples, double startTime)
    : additionalSamples(additionalSamples), startTime(startTime) {}

void MixConverter::process(std::vector<int16_t>& samples, int sampleRate) {
    int startSample = static_cast<int>(startTime * sampleRate);

    for (size_t i = 0; i < additionalSamples.size() && (startSample + i) < samples.size(); ++i) {
        int mixedSample = (samples[startSample + i] + additionalSamples[i]) / 2;
        samples[startSample + i] = static_cast<int16_t>(std::clamp(mixedSample, -32768, 32767));
    }
}

VolumeConverter::VolumeConverter(double factor)
    : factor(factor) {}

void VolumeConverter::process(std::vector<int16_t>& samples, int sampleRate) {
    for (auto& sample : samples) {
        int adjustedSample = static_cast<int>(sample * factor);
        sample = static_cast<int16_t>(std::clamp(adjustedSample, -32768, 32767));
    }
}
