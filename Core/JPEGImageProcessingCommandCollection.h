#ifndef BaseJPEGImageProcessingCommandCollection_2A1DD877_73A5_4655_B22E_FB2A8B3ADCD4
#define BaseJPEGImageProcessingCommandCollection_2A1DD877_73A5_4655_B22E_FB2A8B3ADCD4

#include <map>

#include "BaseImageProcessingCommand.h"
#include "BaseImageProcessingCommandCollection.h"
#include "Constants.h"
#include "DeinterlacerJPEGProcessingCommand.h"

namespace JPEGDeinterlacer::Core
{

class JPEGImageProcessingCommandCollection : public BaseImageProcessingCommandCollection
{
public:
    JPEGImageProcessingCommandCollection() = default;;
    virtual ~JPEGImageProcessingCommandCollection() = default;
    
    virtual const BaseImageProcessingCommand& GetProcessingCommand(const ImageEffects) const;
    virtual bool IsCommandAllowed(const ImageEffects) const;
    
    //Applicable effects to spacial image type.
    //If you want to add your custom algorythms please
    //add it as static member and link it with required
    //We use statically created commands to avoid increasing of data usage
    static const DeinterlacerJPEGProcessingCommand deinterlacerJPEGProcessingCommand;
    

private:
    const static std::map<const ImageEffects, const BaseImageProcessingCommand&> m_ImageEffects;

private:
    //Disabled
    JPEGImageProcessingCommandCollection(JPEGImageProcessingCommandCollection&) = delete;
    JPEGImageProcessingCommandCollection(JPEGImageProcessingCommandCollection&&) = delete;
    JPEGImageProcessingCommandCollection& operator=(const JPEGImageProcessingCommandCollection&) = delete;
    JPEGImageProcessingCommandCollection& operator=(JPEGImageProcessingCommandCollection&&) = delete;
};

}
#endif // BaseJPEGImageProcessingCommandCollection_2A1DD877_73A5_4655_B22E_FB2A8B3ADCD4
