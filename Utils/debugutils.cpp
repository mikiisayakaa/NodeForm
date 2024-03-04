#include "debugutils.h"

#include <iostream>

void NF::assertion(bool judgement, const char *file, const char *func, int line, const QString &info)
{
    if (judgement == false){
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "[NF Assertion Error]" << std::endl;
        std::cout << "   file: " << file << std::endl;
        std::cout << "   func: " << func << std::endl;
        std::cout << "   line: " << line << std::endl;
        std::cout << "   info: " << info.toStdString().c_str() << std::endl;
        std::cout << std::endl << std::flush;

        abort();
    }
}

