#pragma once
#include <memory>
#include <string_view>

#include "Result.hpp"
#include "IStream.h"

namespace OpenTrainSimulator::IO
{
    enum FileOpenModes
    {
        Read,
        Write
    };

    class IFilesystem
    {
    public:

        virtual ~IFilesystem() = 0;

        virtual Result<std::shared_ptr<IStream>> open(const std::string_view& file_path, FileOpenModes mode) = 0;

    };
}
