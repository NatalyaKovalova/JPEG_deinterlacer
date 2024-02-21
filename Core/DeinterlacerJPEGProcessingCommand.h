#ifndef DeinterlacerJPEGProcessingCommand_968414AC_1041_4064_89D4_ACFACAE04709
#define DeinterlacerJPEGProcessingCommand_968414AC_1041_4064_89D4_ACFACAE04709

#include "BaseImageProcessingCommand.h"

namespace JPEGDeinterlacer::Core
{
class DeinterlacerJPEGProcessingCommand: public BaseImageProcessingCommand
{
public:
    DeinterlacerJPEGProcessingCommand() = default;
    ~DeinterlacerJPEGProcessingCommand() = default;
    virtual bool Apply(const BaseImage& source, BaseImage& dest) const override;
    
private:
    //Disabled
    DeinterlacerJPEGProcessingCommand(DeinterlacerJPEGProcessingCommand&) = delete;
    DeinterlacerJPEGProcessingCommand(DeinterlacerJPEGProcessingCommand&&) = delete;
    DeinterlacerJPEGProcessingCommand& operator=(const DeinterlacerJPEGProcessingCommand&) = delete;
    DeinterlacerJPEGProcessingCommand& operator=(DeinterlacerJPEGProcessingCommand&&) = delete;
};

}
#endif // DeinterlacerJPEGProcessingCommand_968414AC_1041_4064_89D4_ACFACAE04709
