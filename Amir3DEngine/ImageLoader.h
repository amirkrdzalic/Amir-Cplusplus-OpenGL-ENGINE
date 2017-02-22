#pragma once
#include "GLTexture.h"

#include <string>
#include<vector>

namespace Amir3DEngine {

    //Loads images into GLTextures
    class ImageLoader
    {
    public:
        static GLTexture loadPNG(std::string filePath);
    };

}