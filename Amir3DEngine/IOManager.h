#pragma once

#include <vector>

namespace Amir3DEngine {

    class IOManager
    {
    public:
        static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
    };

}