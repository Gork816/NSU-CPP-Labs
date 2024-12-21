#pragma once

#include <stdexcept>

class CommandLineException : public std::runtime_error {
public:
    explicit CommandLineException(const std::string& message) : std::runtime_error(message) {}
};

class ConfigException : public std::runtime_error {
public:
    explicit ConfigException(const std::string& message) : std::runtime_error(message) {}
};

class ProcessingException : public std::runtime_error {
public:
    explicit ProcessingException(const std::string& message) : std::runtime_error(message) {}
};
