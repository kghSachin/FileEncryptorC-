#ifndef TASK_HPP
#define TASK_HPP
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "../fileHandling/IO.hpp"

enum class Action
{
    ENCRYPT,
    DECRYPT
};
struct Task
{
    std::string filePath;
    std::fstream f_stream;
    Action action;
    Task(std::string filePath, Action act, std::fstream &&stream) : filePath(filePath), action(act), f_stream(std::move(stream)) {}
    std::string toString()
    {
        std::ostringstream oss;
        oss << filePath << ',' << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");
    }
    static Task fromString(std::string &taskData)
    {
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;
        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr))
        {
            Action action = actionStr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT;
            IO io(filePath);
            std::fstream f_stream = std::move(io.getFileStream());
            if (f_stream.is_open())
            {
                return Task(filePath, action, std::move(f_stream));
            }
            else
            {
                throw std::runtime_error("Failed to open file: " + filePath + " for " + actionStr + "ion.");
            }
        }
        else
        {
            throw std::runtime_error("Failed to parse task data: " + taskData);
        }
    }
};

#endif