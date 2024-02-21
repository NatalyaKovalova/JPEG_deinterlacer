#ifndef Constants_29C63A79_D592_46AF_85A9_D0E70AA72E47
#define Constants_29C63A79_D592_46AF_85A9_D0E70AA72E47

namespace JPEGDeinterlacer
{

enum class ImageFormat
{
    None = 0,
    JPEG,
    // Add here some other format of images to support them,
    // derive you own Image class from BaseImage class and complete "CreateImageByType" method of ImageProcessor.
};

enum class ImageOpenningMode
{
    None = 0,
    ReadOnly,
    Write,
    //You can add other modes here. Currently we use here only these two
};


// Not all images can support some effects. To add some support of command,
// please, derive from BaseImageProcessingCommand and override Apply method
// in specific way to concrete image format(JPEG,PNG,SVG ect)
enum class ImageEffects
{
    None = 0,
    Deinterlacer,
};

}
#endif //Constants_29C63A79_D592_46AF_85A9_D0E70AA72E47
