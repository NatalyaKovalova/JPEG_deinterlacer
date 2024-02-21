#ifndef ImageProcessor_6197BC74_6B78_4433_9836_43A0E6EE712A
#define ImageProcessor_6197BC74_6B78_4433_9836_43A0E6EE712A

#include <string_view>

#include "BaseImage.h"
#include "Constants.h"

class BaseImage;

namespace JPEGDeinterlacer::Core
{

class ImageProcessor
{
public:
    ImageProcessor() = default;
    
    bool ProcessWithCommand(ImageEffects CommandID,
                            std::string_view pathToInputFile,
                            std::string_view pathToOutputFile,
                            const ImageFormat imageFormat = ImageFormat::JPEG);
    bool ProcessWithCommand(ImageEffects CommandID,
                            BaseImage&& sourceImage,
                            BaseImage&& DestinationImage,
                            const ImageFormat imageFormat = ImageFormat::JPEG);
    
    BaseImage CreateImageByType(std::string_view pathToInputFile,
                                const ImageOpenningMode imageOpenningMode = ImageOpenningMode::ReadOnly,
                                const ImageFormat imageFormat = ImageFormat::JPEG);
};

} // namespace JPEGDeinterlacer::Core
#endif // ImageProcessor_6197BC74_6B78_4433_9836_43A0E6EE712A
