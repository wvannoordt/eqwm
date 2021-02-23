#ifndef HW2_SCREEN_H
#define HW2_SCREEN_H
#include "hw2.h"
#include <string>
#define WriteLine(mylevel, mymessage) {hw2::WriteLine_WithFileAndLine((mylevel), (mymessage), __LINE__, __FILE__);}
#define WriteLineStd(mylevel, mymessage) {hw2::WriteLineStd_WithFileAndLine((mylevel), (mymessage), __LINE__, __FILE__);}
#define ParWriteLine(mylevel, mymessage) {hw2::WriteLine_WithFileAndLine((mylevel), (mymessage), __LINE__, __FILE__);}
#define ParWriteLineStd(mylevel, mymessage) {hw2::WriteLineStd_WithFileAndLine((mylevel), (mymessage), __LINE__, __FILE__);}

namespace hw2
{
    void WriteLine_WithFileAndLine(int debugLevel, std::string message, int line, const char* file);
        
    void WriteLineStd_WithFileAndLine(int debugLevel, std::string message, int line, const char* file);
        
    void ParWriteLine_WithFileAndLine(int debugLevel, std::string message, int line, const char* file);

    void ParWriteLineStd_WithFileAndLine(int debugLevel, std::string message, int line, const char* file);
}

#endif