#ifndef JPEGImage_847A7823_E46B_4584_8C4B_35757C96A1C4
#define JPEGImage_847A7823_E46B_4584_8C4B_35757C96A1C4

#include <memory>
#include <string_view>

#include <jpeglib.h>

#include "BaseImage.h"
#include "File.h"

namespace JPEGDeinterlacer::Core
{

//Adapter for libJPEG, support RTTI
class JPEGImage : public BaseImage
{
public:
    JPEGImage(std::string_view pathToInputFile, std::string_view fileMode);
    ~JPEGImage() override;
    bool Open() override;
    bool Close() override;
    
    const void* const getRawPointer() const override;
    void* getRawPointer() override;
    
    // void setRawPointer (unsigned int*) override;
    unsigned int getWidthInBytes() const override;
    unsigned int getHeight() const override;
    
    using RowDataType = std::variant<struct jpeg_decompress_struct, struct jpeg_compress_struct>;
protected:
    void ReadFromFile(std::string_view pathToFile);
    void CreateNewImage(std::string_view pathToFile,const JPEGImage& copyStyleFrom);
    RowDataType m_compressionData;
    std::string_view m_fileMode;
    std::shared_ptr<JPEGDeinterlacer::Core::File> m_file = nullptr;
    
    static struct jpeg_error_mgr m_errorManager;
};

}
#endif // JPEGImage_847A7823_E46B_4584_8C4B_35757C96A1C4
