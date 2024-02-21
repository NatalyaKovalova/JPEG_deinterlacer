#include "ImageProcessingCommandCollectionsHolder.h"

#include "JPEGImageProcessingCommandCollection.h"

namespace DC = JPEGDeinterlacer::Core;

const DC::JPEGImageProcessingCommandCollection DC::ImageProcessingCommandCollectionsHolder::jpegImageProcessingCommandCollection;

const std::map<const JPEGDeinterlacer::ImageFormat,
               const DC::BaseImageProcessingCommandCollection&>
                          DC::ImageProcessingCommandCollectionsHolder::m_imageformatToEffectsCollectionMap =
{
    {JPEGDeinterlacer::ImageFormat::JPEG, jpegImageProcessingCommandCollection },
};


const DC::BaseImageProcessingCommand&
             DC::ImageProcessingCommandCollectionsHolder::GetProcessingCommand( const ImageEffects commandID,
                                                                                const ImageFormat imageFormat) const
{
    if( m_imageformatToEffectsCollectionMap.contains(imageFormat))
    {
        const BaseImageProcessingCommandCollection& commandCollection = m_imageformatToEffectsCollectionMap.at(imageFormat);
        if(commandCollection.IsCommandAllowed(commandID))
        {
            return commandCollection.GetProcessingCommand(commandID);
        }
    };
    
    return BaseImageProcessingCommandCollection::GetEmptyCommand();
}

bool DC::ImageProcessingCommandCollectionsHolder::IsCommandAllowed( const ImageEffects commandID,
                                                                    const ImageFormat imageFormat) const
{
    if( m_imageformatToEffectsCollectionMap.contains(imageFormat))
    {
        const BaseImageProcessingCommandCollection& commandCollection = m_imageformatToEffectsCollectionMap.at(imageFormat);
        return commandCollection.IsCommandAllowed(commandID);
    };
    return false;
}
