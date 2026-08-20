#include "gtest/gtest.h"
#include "Exception.hpp"

TEST(ExceptionTest, TestGetters)
{
	observability::Exception exception(L"Test message", L"ExceptionTest.cpp", L"TestGetters");
	EXPECT_EQ(exception.getMessage(), L"Test message");
	EXPECT_EQ(exception.getFileName(), L"ExceptionTest.cpp");
	EXPECT_EQ(exception.getLocation(), L"TestGetters");
}

TEST(ExceptionTest, TestWhat)
{
	observability::Exception exception(L"Test message", L"ExceptionTest.cpp", L"TestGetters");
	EXPECT_EQ(exception.what(), L"Exception in 'TestGetters' (ExceptionTest.cpp): Test message");
}
