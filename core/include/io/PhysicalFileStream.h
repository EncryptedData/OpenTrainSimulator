
#pragma once
#include <filesystem>
#include <string_view>

#include "IStream.h"
#include "IFilesystem.h"

namespace OpenTrainSimulator::IO
{
    class PhysicalFileStream : public IStream
    {
        FileOpenModes _mode;
        //std::ifstream _backing_stream;

    public:
        PhysicalFileStream(std::filesystem::path file_path, FileOpenModes mode);

        ~PhysicalFileStream() override;

        FileSize_t get_current_position() const override;

        void set_current_position(FileSize_t position) override;

        Result<FileSize_t> get_length() const override;

        bool get_can_seek() const override;

        bool get_can_read() const override;

        bool get_can_write() const override;

        void close() override;

        void flush() override;

        void copy_to(IStream *stream) override;

        FileSize_t read(std::byte *buffer, FileSize_t buffer_size, FileSize_t count) override;

        FileSize_t read(std::vector<std::byte> &buffer, FileSize_t count) override;
    };
}
