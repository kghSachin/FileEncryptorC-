#ifndef TASK_HPP
#define TASK_HPP
#include <fstream>
#include <string>

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
    
};

#endif