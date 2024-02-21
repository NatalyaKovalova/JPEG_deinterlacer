#include "JPEGImage.h"

#include <iostream>

#include "File.h"

namespace DC = JPEGDeinterlacer::Core;

struct jpeg_error_mgr DC::JPEGImage::m_errorManager;

DC::JPEGImage::JPEGImage(std::string_view pathToInputFile, std::string_view fileMode):
                         BaseImage(pathToInputFile, fileMode),
                         m_fileMode(fileMode)
{
    assert(fileMode == "rb" || fileMode == "wb");
    
    if(fileMode !="rb" || fileMode!="wb")
    {
        std::cerr << "Error opening file mode: " << fileMode << " is not sutable for" << pathToInputFile << std::endl;
        return;
    }
    
    m_file = std::make_shared<File>(pathToInputFile, fileMode);
}

DC::JPEGImage::~JPEGImage()
{
    Close();
}

bool DC::JPEGImage::Open()
{
    return false;
}

bool DC::JPEGImage::Close()
{
    try
    {
        if(m_fileMode == "rb") // TODO: std::holds_alternative
        {
            jpeg_decompress_struct data = std::get<jpeg_decompress_struct>(m_compressionData);
            jpeg_finish_decompress(&data);
        }
        if(m_fileMode == "wb")
        {
            jpeg_compress_struct data = std::get<jpeg_compress_struct>(m_compressionData);
            jpeg_finish_compress(&data);
            jpeg_destroy_compress(&data);
        }
        return true;
    }
    catch(const std::bad_variant_access& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return false;
}

void DC::JPEGImage::ReadFromFile(std::string_view pathToFile)
{
    m_file = std::make_shared<DC::File>(pathToFile, "rb");

    if (!m_file || !m_file->isValid() )
    {
        std::cerr << "Exit with code: " << EXIT_FAILURE << "because file does not exist." << std::endl;
        return;
    }

    try
    {
        struct jpeg_decompress_struct inputCompresingInfo;
        inputCompresingInfo.err = jpeg_std_error(&m_errorManager);
        jpeg_create_decompress(&inputCompresingInfo);
        jpeg_stdio_src(&inputCompresingInfo, m_file->GetRaw());
        
        if( jpeg_read_header(&inputCompresingInfo, TRUE) != 1)
        {
            std::cerr << "Corrupted JPEG - " << pathToFile << std::endl;
            return;
        }
        inputCompresingInfo.out_color_space = JCS_YCbCr;
        if(jpeg_start_decompress(&inputCompresingInfo) == false)
        {
            std::cerr << "Corrupted JPEG - " << pathToFile << std::endl;
            return;
        }
        m_compressionData = inputCompresingInfo;
    }
    catch(const std::bad_variant_access& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

void DC::JPEGImage::CreateNewImage(std::string_view pathToFile,const JPEGImage& copyStyleFrom)
{
    m_file = std::make_shared<DC::File>(pathToFile, "wb");

    if (!m_file || !m_file->isValid() )
    {
        std::cerr << "Exit with code: " << EXIT_FAILURE << "because file does not exist." << std::endl;
        return;
    }
    
    struct jpeg_compress_struct outputCompresingInfo;
    outputCompresingInfo.err = jpeg_std_error(&m_errorManager);
    jpeg_create_compress(&outputCompresingInfo);

    jpeg_stdio_dest(&outputCompresingInfo, m_file->GetRaw());

    try
    {
        if(copyStyleFrom.m_fileMode == "rb") // TODO: std::holds_alternative
        {
            jpeg_decompress_struct data = std::get<jpeg_decompress_struct>(copyStyleFrom.m_compressionData);
            outputCompresingInfo.image_width = data.image_width;
            outputCompresingInfo.image_height = data.image_height;
            outputCompresingInfo.input_components = data.output_components;
        }
        if(copyStyleFrom.m_fileMode == "wb")
        {
            jpeg_compress_struct data = std::get<jpeg_compress_struct>(copyStyleFrom.m_compressionData);
            outputCompresingInfo.image_width = data.image_width;
            outputCompresingInfo.image_height = data.image_height;
            outputCompresingInfo.input_components = data.input_components;
        }
    }
    catch(const std::bad_variant_access& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    
    outputCompresingInfo.in_color_space = JCS_YCbCr;

    jpeg_set_defaults(&outputCompresingInfo);
    jpeg_start_compress(&outputCompresingInfo, TRUE);
}

unsigned int DC::JPEGImage::getWidthInBytes() const
{
    try
    {
        if(m_fileMode == "rb") // TODO: std::holds_alternative
        {
            jpeg_decompress_struct data = std::get<jpeg_decompress_struct>(m_compressionData);
            return data.image_width * data.output_components;
        }
        if(m_fileMode == "wb")
        {
            jpeg_compress_struct data = std::get<jpeg_compress_struct>(m_compressionData);
            return data.image_width * data.input_components;
        }
    }
    catch(const std::bad_variant_access& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}

unsigned int DC::JPEGImage::getHeight() const
{
    try
    {
        if(m_fileMode == "rb") // TODO: std::holds_alternative
        {
            jpeg_decompress_struct data = std::get<jpeg_decompress_struct>(m_compressionData);
            return data.output_height;
        }
        if(m_fileMode == "wb")
        {
            jpeg_compress_struct data = std::get<jpeg_compress_struct>(m_compressionData);
            return data.jpeg_height;
        }
    }
    catch(const std::bad_variant_access& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}

void* DC::JPEGImage::getRawPointer()
{
    return &m_compressionData;
}

const void* const DC::JPEGImage::getRawPointer() const
{
    return &m_compressionData;
}
