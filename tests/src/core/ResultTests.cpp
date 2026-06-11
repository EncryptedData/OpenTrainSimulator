#include <catch2/catch_all.hpp>

#include <Result.hpp>

TEST_CASE("Result constructed without value should return no value")
{
    OpenTrainSimulator::Result<int> result;

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("Result constructed with value should return the value")
{
    OpenTrainSimulator::Result<int> result(0);

    REQUIRE(result.has_value());
    REQUIRE(result.value() == 0);
}

TEST_CASE("Result can be constructed with non-builtin types")
{
    struct Data
    {
    };

    OpenTrainSimulator::Result<Data> result(Data{});

    REQUIRE(result.has_value());
}

