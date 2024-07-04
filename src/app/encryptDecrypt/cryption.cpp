#include "cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"

int executeCryption(std::string &taskData)
{
    Task task = Task::fromString(taskData);
    ReadEnv env;
    std::string envKey = env.getEnv();
    // converts the string to an integer
    int key = std::stoi(envKey);
    if (task.action == Action::ENCRYPT)
    {
        // encrypt the file
        char ch;
        while (task.f_stream.get(ch))
        {
            ch = (ch + key) % 256;
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    else
    {
        char ch;
        while (task.f_stream.get(ch))
        {
            ch = (ch - key + 256) % 256;
            task.f_stream.seekp(-1, std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    return 0;
}
