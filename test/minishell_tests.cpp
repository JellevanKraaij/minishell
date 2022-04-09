#include <gtest/gtest.h>
#include <gmock/gmock.h>

// #include <limits.h>

extern "C" {
	#include "minishell.h"
}

using namespace testing;

TEST(ErrorTests, perror_exit) {
	EXPECT_EXIT(perror_exit("gtest_perror", 42), ExitedWithCode(42), StartsWith("gtest_perror:"));
}

TEST(ErrorTests, null_exit)
{
	EXPECT_EQ(null_exit((void *)42), (void *)42);
	EXPECT_EQ(null_exit((void *)SIZE_MAX), (void *)SIZE_MAX);
	EXPECT_EXIT(null_exit(NULL), ExitedWithCode(1), StartsWith("minishell:"));
}