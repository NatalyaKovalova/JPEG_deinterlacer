#include <iostream>
#include <cstdio>

#include <jpeglib.h>

#include "File.h"

namespace DC = JPEGDeinterlacer::Core;

int deinterlace(const char* inputPath, const char* outputPath) {
    
    //TODO in nect commits
    //ImageProcessor().RegisterCommandsByDefault().ProcessWithCommand( "Deinterlacer", inputPath, outputPath );
    
    DC::File inputFile(inputPath, "rb");
    DC::File outputFile(outputPath, "wb");
    
    if (!inputFile.isValid() || !outputFile.isValid())
    {
        std::cerr << "Exit with code: " << EXIT_FAILURE << "because filde does not exist." << std::endl;
        return (EXIT_FAILURE);
    }

    struct jpeg_decompress_struct inputCompresingInfo;
    struct jpeg_error_mgr errorManager;

    inputCompresingInfo.err = jpeg_std_error(&errorManager);
    jpeg_create_decompress(&inputCompresingInfo);
    jpeg_stdio_src(&inputCompresingInfo, inputFile.GetRaw());
    
    if( jpeg_read_header(&inputCompresingInfo, TRUE) != 1)
    {
        std::cerr << "Corrupted JPEG - " << inputPath << std::endl;
        return (EXIT_FAILURE);
    }
    inputCompresingInfo.out_color_space = JCS_YCbCr;
    if(jpeg_start_decompress(&inputCompresingInfo) == false)
    {
        std::cerr << "Corrupted JPEG - " << inputPath << std::endl;
        return (EXIT_FAILURE);
    }
    
    struct jpeg_compress_struct outputCompresingInfo;
    outputCompresingInfo.err = jpeg_std_error(&errorManager);
    jpeg_create_compress(&outputCompresingInfo);

    jpeg_stdio_dest(&outputCompresingInfo, outputFile.GetRaw());

    outputCompresingInfo.image_width = inputCompresingInfo.image_width;
    outputCompresingInfo.image_height = inputCompresingInfo.image_height;
    outputCompresingInfo.input_components = inputCompresingInfo.output_components;
    outputCompresingInfo.in_color_space = JCS_YCbCr;

    jpeg_set_defaults(&outputCompresingInfo);
    jpeg_start_compress(&outputCompresingInfo, TRUE);

    JSAMPROW currentDataRow[1];
    currentDataRow[0] = new JSAMPLE[inputCompresingInfo.image_width * inputCompresingInfo.output_components];

    JSAMPROW previousDataRow = new JSAMPLE[inputCompresingInfo.image_width * inputCompresingInfo.output_components];

    while (inputCompresingInfo.output_scanline < inputCompresingInfo.output_height) {
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

    jpeg_finish_compress(&outputCompresingInfo);
    jpeg_destroy_compress(&outputCompresingInfo);
    jpeg_finish_decompress(&inputCompresingInfo);
    
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Please, use with arguments: " << argv[0] << " <input_path> <output_path>" << std::endl;
        return 1;
    }

    const char* inputPath = argv[1];
    const char* outputPath = argv[2];

    return deinterlace(inputPath, outputPath);
}
