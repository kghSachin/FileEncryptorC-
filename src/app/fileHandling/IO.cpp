#include <iostream>
#include "IO.hpp"
#include <fstream>

IO::IO(const std::string &filePath)
{
    file_stream.open(filePath, std::ios::in | std::ios::out | std::ios::app);
    if (!file_stream.is_open())
    {
        std::cout << "Error opening file: " << filePath << std::endl;
    }
}

std::fstream IO::getFileStream()
{
    return std::move(file_stream);
}

IO::~IO()
{
    if (file_stream.is_open())
    {
        file_stream.close();
    }
}