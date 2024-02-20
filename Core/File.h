#ifndef File_60E71F68_C04B_46A1_8037_DD765E6CB510
#define File_60E71F68_C04B_46A1_8037_DD765E6CB510

#include <stdio.h>
#include <string_view>

namespace JPEGDeinterlacer::Core
{
/**
 This is RTTI adapter arount the c-file
 */
class File
{
public:
    File(std::string_view pathToFile, std::string_view openningMode);
    inline bool isValid() const{return m_file != nullptr;};
    FILE* GetRaw() {return m_file;}
    
    ~File();
private:
    FILE* m_file;
    
    //Disabled
    File(File&) = delete;
    File(File&&) = delete;
    File& operator=(const File& other) = delete;
    File& operator=(File&& other) = delete;
};
}
#endif //#define File_60E71F68_C04B_46A1_8037_DD765E6CB510
