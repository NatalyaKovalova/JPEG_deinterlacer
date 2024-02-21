#include "JPEGImageProcessingCommandCollection.h"
namespace DC = JPEGDeinterlacer::Core;

const DC::DeinterlacerJPEGProcessingCommand DC::JPEGImageProcessingCommandCollection::deinterlacerJPEGProcessingCommand;

const std::map<const JPEGDeinterlacer::ImageEffects,
               const DC::BaseImageProcessingCommand&> DC::JPEGImageProcessingCommandCollection::m_ImageEffects
{
    {JPEGDeinterlacer::ImageEffects::Deinterlacer, deinterlacerJPEGProcessingCommand}
};

const DC::BaseImageProcessingCommand& DC::JPEGImageProcessingCommandCollection::GetProcessingCommand(const ImageEffects imageEffects) const
{
    if( m_ImageEffects.contains(imageEffects))
    {
        return m_ImageEffects.at(imageEffects);
    };
    return BaseImageProcessingCommandCollection::GetEmptyCommand();
}

bool DC::JPEGImageProcessingCommandCollection::IsCommandAllowed(const ImageEffects imageEffects) const
{
    return m_ImageEffects.contains(imageEffects);
}
