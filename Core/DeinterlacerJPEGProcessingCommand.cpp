#include "DeinterlacerJPEGProcessingCommand.h"

#include <iostream>
#include <cstdio>

#include <jpeglib.h>

#include "JPEGImage.h"

namespace DC = JPEGDeinterlacer::Core;

bool DC::DeinterlacerJPEGProcessingCommand::Apply(const BaseImage& source, BaseImage& dest) const
{
    JSAMPROW currentDataRow[1];
    currentDataRow[0] = new JSAMPLE[source.getWidthInBytes()];
    
    JSAMPROW previousDataRow = new JSAMPLE[source.getWidthInBytes()];
    
    const JPEGImage::RowDataType* const rawSource = source.getRawPointer()
                                        ? static_cast<const JPEGImage::RowDataType* const>(source.getRawPointer())
                                        :nullptr;
    if(!rawSource)
    {
        return false;
    }
    jpeg_decompress_struct inputCompresingInfo = std::get<jpeg_decompress_struct>(*rawSource);
    
    const JPEGImage::RowDataType* const rawDest = dest.getRawPointer()
                                        ? static_cast<const JPEGImage::RowDataType* const>(dest.getRawPointer())
                                        :nullptr;
    if(!rawDest)
    {
        return false;
    }
    jpeg_compress_struct outputCompresingInfo = std::get<jpeg_compress_struct>(*rawDest);
    
    

    while (inputCompresingInfo.output_scanline < source.getHeight())
    {
        jpeg_read_scanlines(&inputCompresingInfo, currentDataRow, 1);
        
        if (inputCompresingInfo.output_scanline > 1) {
            // Deinterlace: Blend current line with the previous one
            for (int i = 0; i < inputCompresingInfo.image_width * inputCompresingInfo.output_components; ++i) {
                currentDataRow[0][i] = (currentDataRow[0][i] + previousDataRow[i]) / 2;
            }
        }

        jpeg_write_scanlines(&outputCompresingInfo, currentDataRow, 1);

        std::copy(currentDataRow[0], currentDataRow[0] + inputCompresingInfo.image_width * inputCompresingInfo.output_components, previousDataRow);
    }

    delete[] currentDataRow[0];
    delete[] previousDataRow;
    return true;
}
