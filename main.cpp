#include <iostream>

#include "ImageProcessor.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Please, use with arguments: " << argv[0] << " <input_path> <output_path>" << std::endl;
        return 1;
    }

    const char* inputPath = argv[1]; //TODO - Add parcer, add log system
    const char* outputPath = argv[2];

    return !JPEGDeinterlacer::Core::ImageProcessor()
                            .ProcessWithCommand(JPEGDeinterlacer::ImageEffects::Deinterlacer,
                                                inputPath,
                                                outputPath);
}
