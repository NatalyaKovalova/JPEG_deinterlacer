#include "File.h"
#include <iostream>

namespace DC = JPEGDeinterlacer::Core;

DC::File::File(std::string_view pathToFile, std::string_view openningMode)
{
    m_file = fopen(pathToFile.data(), openningMode.data());
    
    if (m_file == nullptr) {
        std::cerr << "Error opening input file: " << pathToFile << std::endl;
        return;
    }
}

DC::File::~File()
{
    if(m_file != nullptr)
    {
        fclose(m_file);
    }
}
