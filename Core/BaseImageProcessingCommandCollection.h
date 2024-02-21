#ifndef BaseImageProcessingCommandCollection_F183D188_FF34_4141_BD3E_A07253ECA5DB
#define BaseImageProcessingCommandCollection_F183D188_FF34_4141_BD3E_A07253ECA5DB

#include "BaseImageProcessingCommand.h"
#include "Constants.h"
#include "DeinterlacerJPEGProcessingCommand.h"

namespace JPEGDeinterlacer::Core
{

/**
 Base abstract class to represent collection of GraphicEffects or algorithms for some type of the image.
 This class is empty and should be derived of real class for some image type.
 */
class BaseImageProcessingCommandCollection
{
public:
    BaseImageProcessingCommandCollection() = default;
    virtual ~BaseImageProcessingCommandCollection() = default;
    
    virtual const BaseImageProcessingCommand& GetProcessingCommand(const ImageEffects) const = 0;
    virtual bool IsCommandAllowed(const ImageEffects) const = 0;
    
    static constexpr const BaseImageProcessingCommand& GetEmptyCommand(){return m_emptyCommand;}
    
protected: 
    //This is empty stab which could be used as empty(invalid) value of command.
    static const BaseImageProcessingCommand m_emptyCommand;
private:
    //Disabled
    BaseImageProcessingCommandCollection(BaseImageProcessingCommandCollection&) = delete;
    BaseImageProcessingCommandCollection(BaseImageProcessingCommandCollection&&) = delete;
    BaseImageProcessingCommandCollection& operator=(const BaseImageProcessingCommandCollection&) = delete;
    BaseImageProcessingCommandCollection& operator=(BaseImageProcessingCommandCollection&&) = delete;
};

}
#endif // BaseImageProcessingCommandCollection_F183D188_FF34_4141_BD3E_A07253ECA5DB
