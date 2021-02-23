#ifndef HW2_ERROR_H
#define HW2_ERROR_H
 
#include <string>
#include <exception>
#include <iostream>

#ifndef FUNCSUPPORT
#define FUNCSUPPORT 1
#endif
#if(FUNCSUPPORT)
#define hw2Error(myMessage) {hw2::hw2Error_M(myMessage, __LINE__, __FILE__, __PRETTY_FUNCTION__);}
#else
#define hw2Error(myMessage) {hw2::hw2Error_M(myMessage, __LINE__, __FILE__);}
#endif
namespace hw2
{
    struct hw2Exception : public std::exception
    {
        const char* what() const throw()
        {
        	return "(hw2 Exception)";
        }
    };
#if(FUNCSUPPORT)
    static inline void hw2Error_M(std::string message, const int line, const char* file, const char* func)
#else
    static inline void hw2Error_M(std::string message, const int line, const char* file)
#endif
    {
        std::cout << "------------------------------------------------------" << std::endl;
        std::cout << "hw2 Error Thrown.\nFile: " << file << "\nLine: " << line << std::endl;
#if(FUNCSUPPORT)
        std::cout << "Function: " << func << std::endl;
#endif
        std::cout << message << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
        throw hw2Exception();
    }
}

#endif