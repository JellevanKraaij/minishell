#include <gtest/gtest.h>
#include <gmock/gmock.h>

// #include <limits.h>

extern "C" {
	#include "minishell.h"
}

using namespace testing;


// Demonstrate some basic assertions.
TEST(ErrorTests, exit) {
	// Expect two strings not to be equal.
	EXPECT_EXIT(perror_exit("gtest_perror", 42), ExitedWithCode(42), StartsWith("gtest_perror:"));
	EXPECT_EXIT(null_exit(NULL), ExitedWithCode(1), StartsWith("minishell:"));
}
TEST(ErrorTests, basic)
{
	EXPECT_TRUE((null_exit(42) == (void *)42));
}