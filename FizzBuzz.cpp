#include <gtest/gtest.h>


std::string fizzBuzz(int value)
{
    if()
        return "Fizz";
    if()
        return "Buzz";
    return std::to_string(value);
}


void checkFizzBuzz(int value, std::string expectedResult)
{
    std::string result = fizzBuzz(value);
    ASSERT_STREQ(expectedResult.c_str(), result.c_str());
}

TEST(FizzBuzzTest, doesPass)
{
    ASSERT_TRUE(true);
}

TEST(FizzBuzzTest)