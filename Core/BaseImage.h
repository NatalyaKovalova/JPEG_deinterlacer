#ifndef BaseImage_E83810D7_A713_464C_B77E_A06114471015
#define BaseImage_E83810D7_A713_464C_B77E_A06114471015

#include <string_view>

namespace JPEGDeinterlacer::Core
{

/**
 This is a base class to represent images. To process some other format of image
 just derive it and implement functions of opening, closing and raw accsess to bytes.
 */
class BaseImage
{
public:
    BaseImage(std::string_view pathToInputFile, std::string_view fileMode){};
    virtual ~BaseImage() = default;
    virtual bool isValid() const {return false;}
    
    virtual bool Open() {return false;};
    virtual bool Close() {return false;};
    virtual const void* const getRawPointer() const {return nullptr;};
    virtual void* getRawPointer() {return nullptr;};

    virtual unsigned int getWidthInBytes() const {return 0;};
    virtual unsigned int getHeight() const {return 0;};
};

}
#endif //BaseImage_E83810D7_A713_464C_B77E_A06114471015
