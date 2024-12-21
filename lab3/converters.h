#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <cstdint>

// Base Converter class
class Converter {
public:
    virtual ~Converter() = default;
    virtual void process(std::vector<int16_t>& samples, int sampleRate) = 0;
};

// MuteConverter class
class MuteConverter : public Converter {
    double startTime;
    double endTime;

public:
    MuteConverter(double startTime, double endTime);
    void process(std::vector<int16_t>& samples, int sampleRate) override;
};

// MixConverter class
class MixConverter : public Converter {
    std::vector<int16_t> additionalSamples;
    double startTime;

public:
    MixConverter(const std::vector<int16_t>& additionalSamples, double startTime);
    void process(std::vector<int16_t>& samples, int sampleRate) override;
};

// VolumeConverter class (example)
class VolumeConverter : public Converter {
    double factor;

public:
    explicit VolumeConverter(double factor);
    void process(std::vector<int16_t>& samples, int sampleRate) override;
};

// ConverterFactory class
class ConverterFactory {
    using CreatorFunction = std::function<std::unique_ptr<Converter>(const std::vector<std::string>&)>;
    static std::map<std::string, CreatorFunction> converters;

public:
    static void registerConverter(const std::string& name, CreatorFunction creator);
    static std::unique_ptr<Converter> createConverter(const std::string& name, const std::vector<std::string>& args);
    static std::map<std::string, std::string> getAvailableConverters();
};

// Register all converters
void registerDefaultConverters();
