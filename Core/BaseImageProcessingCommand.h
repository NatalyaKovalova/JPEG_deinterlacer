#ifndef BaseImageProcessingCommand_160B107B_DF84_4A85_89F1_B5ACF9F8489E
#define BaseImageProcessingCommand_160B107B_DF84_4A85_89F1_B5ACF9F8489E

#include <stdio.h>

#include "BaseImage.h"

namespace JPEGDeinterlacer::Core
{
class BaseImageProcessingCommand
{
public:
    BaseImageProcessingCommand() = default;
    virtual ~BaseImageProcessingCommand() = default;
    
    virtual bool Apply(const BaseImage& source, BaseImage& dest) const {return false;};

private:
    //Disabled
    BaseImageProcessingCommand(BaseImageProcessingCommand&) = delete;
    BaseImageProcessingCommand(BaseImageProcessingCommand&&) = delete;
    BaseImageProcessingCommand& operator=(const BaseImageProcessingCommand&) = delete;
    BaseImageProcessingCommand& operator=(BaseImageProcessingCommand&&) = delete;
};

}
#endif // BaseImageProcessingCommand_160B107B_DF84_4A85_89F1_B5ACF9F8489E
