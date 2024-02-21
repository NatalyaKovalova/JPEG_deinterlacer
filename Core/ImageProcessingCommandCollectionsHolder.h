#ifndef ImageProcessingCommandCollectionsHolder_1C80DEF5_B3C6_4C1A_BE0C_42A35C64C0F0
#define ImageProcessingCommandCollectionsHolder_1C80DEF5_B3C6_4C1A_BE0C_42A35C64C0F0

#include <memory>
#include <map>

#include "Constants.h"
#include "BaseImageProcessingCommandCollection.h"
#include "JPEGImageProcessingCommandCollection.h"

namespace JPEGDeinterlacer::Core
{

class ImageProcessingCommandCollectionsHolder
{
public:
    // If command is not allowed for concrete type the function do nothing.
    // There is no requirements to use IsCommandAllowed or something else.
    // It's safe
    const BaseImageProcessingCommand& GetProcessingCommand( const ImageEffects commandID,
                                                            const ImageFormat imageFormat) const;
    
    bool IsCommandAllowed( const ImageEffects commandID,
                           const ImageFormat imageFormat) const;
private:
    // if you need to add some more image formats like png ect you should:
    // 0. Add new supported image format to ImageFormat enum and all new algorythms to ImageEffects
    // 1. derive BaseImageProcessingCommandCollection and allow there algorythms for the new type
    // 2. Create static variable of created collection in this section and add it to m_formatToAlgorythmsMap.
    
    // We use static variables here to avoid reducing memory allocation and because
    // collections and command doesn't save any internal state -
    // just required command and methods to applying them
    static const JPEGImageProcessingCommandCollection jpegImageProcessingCommandCollection;
    
    static const std::map<const ImageFormat,
                          const BaseImageProcessingCommandCollection&> m_imageformatToEffectsCollectionMap;
};

}
#endif // ImageProcessingCommandCollectionsHolder_1C80DEF5_B3C6_4C1A_BE0C_42A35C64C0F0
