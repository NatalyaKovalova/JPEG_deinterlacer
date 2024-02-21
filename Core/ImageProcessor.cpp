#include "ImageProcessor.h"

#include <iostream>

#include "BaseImageProcessingCommand.h"
#include "JPEGImage.h"
#include "ImageProcessingCommandCollectionsHolder.h"

namespace DC = JPEGDeinterlacer::Core;

bool DC::ImageProcessor::ProcessWithCommand(ImageEffects commandID,
                                            std::string_view pathToInputFile,
                                            std::string_view pathToOutputFile,
                                            const ImageFormat imageFormat)
{
    return ProcessWithCommand(commandID,
                              CreateImageByType(pathToInputFile),
                              CreateImageByType(pathToOutputFile, ImageOpenningMode::Write),
                              imageFormat);
}

bool DC::ImageProcessor::ProcessWithCommand(ImageEffects commandID,
                                            BaseImage&& sourceImage,
                                            BaseImage&& destinationImage,
                                            const ImageFormat imageFormat)
{
    if( !sourceImage.isValid() || destinationImage.isValid() )
    {
        std::cerr << "Verbose: processing is stopped because one or two images are invalid.\
                      Please, be sure you are not working with an empty type: BaseImage \
                      and use some derived real image.\
                      Also, please check if the image format is supported \
                      in the app(ImageFormat enum)."
                  << std::endl;
        return false;
    }
    if( commandID == ImageEffects::None || imageFormat == ImageFormat::None)
    {
        std::cerr << "Verbose: Please check if the image format and ImageEffect\
                      are supported in the app(Not None. Should be real value of\
                      ImageFormat and ImageEffect from \"Constants.h\")."
                  << std::endl;
        
        return false;
    }
        
    const BaseImageProcessingCommand& command = DC::ImageProcessingCommandCollectionsHolder()
                                                           .GetProcessingCommand(commandID, imageFormat);
 
    return command.Apply(sourceImage, destinationImage);
}

DC::BaseImage DC::ImageProcessor::CreateImageByType(std::string_view pathToFile,
                                                    ImageOpenningMode imageOpenningMode,
                                                    ImageFormat imageFormat)
{
    switch(imageFormat)
    {
        case ImageFormat::JPEG:
        {
            std::string_view openningCFileMode = "rb";
            if(imageOpenningMode == ImageOpenningMode::Write)
            {
                openningCFileMode = "wb";
            }
            
            return DC::JPEGImage(pathToFile, openningCFileMode);
        }
        default: std::cerr << "Unsupported image format" << pathToFile << std::endl;
    }
    
    return DC::BaseImage("","");
}
