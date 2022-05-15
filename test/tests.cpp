// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "../include/task.h"

TEST(task1, test1) {
	Shop shop(2, 30, 200);
	int result = shop.stats.served + shop.stats.rejected;
	EXPECT_EQ(30, result);
}

TEST(task2, test2) {
	Shop shop(4, 60, 200);
	int result = shop.stats.rejected;
	EXPECT_EQ(0, result);
}

TEST(task3, test3) {
	Shop shop(2, 60, 250);
	int result = 0;
	if (shop.stats.rejected > 0)
		result = 1;
	EXPECT_EQ(1, result);
}
