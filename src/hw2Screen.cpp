#include "hw2Screen.h"
#include "hw2.h"
namespace hw2
{
    void WriteLine_WithFileAndLine(int debugLevel, std::string message, int line, const char* file)
    {
        if (globalSettings.globalOutputEnabledHere && (debugLevel<=globalSettings.debugLevel))
        {
            std::cout << "hw2 :: " << message;
            if (globalSettings.trackOutputOrigins) std::cout << "\n >> (debug " << debugLevel << " from file " << file << ", line " << line << ")";
            std::cout << std::endl;
        }
    }
    
    void WriteLineStd_WithFileAndLine(int debugLevel, std::string message, int line, const char* file)
    {
        if (globalSettings.globalOutputEnabledHere && (debugLevel<=globalSettings.debugLevel))
        {
            std::cout << "hw2 :: " << message;
            if (globalSettings.trackOutputOrigins) std::cout << "\n >> (debug " << debugLevel << " from file " << file << ", line " << line << ")";
            std::cout << std::endl;
        }
    }
    
    void ParWriteLine_WithFileAndLine(int debugLevel, std::string message, int line, const char* file)
    {
        if ((debugLevel<=globalSettings.debugLevel))
        {
            std::cout << "hw2 :: " << message;
            if (globalSettings.trackOutputOrigins) std::cout << "\n >> (debug " << debugLevel << " from file " << file << ", line " << line << ")";
            std::cout << std::endl;
        }
    }
    
    void ParWriteLineStd_WithFileAndLine(int debugLevel, std::string message, int line, const char* file)
    {
        if ((debugLevel<=globalSettings.debugLevel))
        {
            std::cout << "hw2 :: " << message;
            if (globalSettings.trackOutputOrigins) std::cout << "\n >> (debug " << debugLevel << " from file " << file << ", line " << line << ")";
            std::cout << std::endl;
        }
    }
}