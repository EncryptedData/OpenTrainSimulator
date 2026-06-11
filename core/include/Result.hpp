#pragma once

namespace OpenTrainSimulator
{
    /**
     * Type to represent operations that might fail and need to be handled by the caller
     * @tparam T The result type when there is a value
     */
    template<typename T>
    class Result
    {
        bool _has_value;
        T _value;

    public:

        explicit Result() :
            _has_value{false},
            _value{}
        {
        }

        explicit Result(const T& t) :
            _has_value{true},
            _value{t}
        {
        }

        explicit operator bool() const
        {
            return _has_value;
        }

        bool has_value() const
        {
            return _has_value;
        };

        T value() const
        {
            return _value;
        };
    };
}