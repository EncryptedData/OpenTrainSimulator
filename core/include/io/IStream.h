
#pragma once
#include "Result.hpp"
#include <cinttypes>
#include <vector>

namespace OpenTrainSimulator::IO
{
    using FileSize_t = std::size_t;

    class IStream
    {
    public:

        virtual ~IStream() = 0;

        /**
         * @return The current position of this stream.
         */
        virtual FileSize_t get_current_position() const = 0;

        /**
         * Sets the current position of the stream. Some streams do not support this. Query get_can_seek() to check if
         * the stream supports this.
         * @param position The position to set. 0 to reset the stream to the begining.
         */
        virtual void set_current_position(FileSize_t position) = 0;

        /**
         * Attempts to query the full length of the stream
         * @return The full length of the stream if it's possible to calculate it.
         */
        virtual Result<FileSize_t> get_length() const = 0;

        /**
         * @return TRUE if the position can be changed on this stream. FALSE otherwise
         */
        virtual bool get_can_seek() const = 0;

        /**
         *
         * @return TRUE if this stream supports reading. FALSE otherwise
         */
        virtual bool get_can_read() const = 0;

        /**
         * @return TRUE if this stream supports writing, FALSE otherwise
         */
        virtual bool get_can_write() const = 0;

        /**
         * Closes the stream (closes whatever backing source of the stream).
         */
        virtual void close() = 0;

        /**
         * If the stream was being written to, this will force the stream to flush out the data to the backing source.
         */
        virtual void flush() = 0;

        /**
         * Copies data from one stream to another.
         * @param stream The stream to copy into
         */
        virtual void copy_to(IStream* stream) = 0;

        /**
         * Reads data from the stream and places it into the buffer.
         * @param buffer The buffer to copy into. Cannot be nullptr
         * @param buffer_size The size of the copy buffer. Cannot be zero.
         * @param count The amount of bytes to read. This function is a no-op if zero is passed in. This cannot be
         * negative
         * @return The number of bytes read. Zero means that count was zero OR there are no bytes left in the stream
         * (AKA the stream has ended)
         */
        virtual FileSize_t read(std::byte* buffer, FileSize_t buffer_size, FileSize_t count);

        /**
         * Reads data from the stream and places it into the buffer. The vector's size must be bigger than zero.
         * @param buffer The buffer to copy into
         * @param count The amount of bytes to read in. Zero is a no-op. Negative is not allowed.
         * @return The number of bytes read. Zero means that count was zero OR there are no bytes left in the stream
         * (AKA the stream has ended)
         */
        virtual FileSize_t read(std::vector<std::byte>& buffer, FileSize_t count);
    };
}
