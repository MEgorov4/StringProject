#include "../nstring/nstring.h"
#include "gtest/gtest.h"

TEST(NStringTest, test)
{
    using namespace str_lib;
    String string;
    ASSERT_TRUE(1 == 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
