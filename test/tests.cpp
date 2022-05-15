// Copyright 2022 GHA Test Team
#include <gtest/gtest.h>
#include "../include/task.h"

TEST(task1, test1) {
	Shop shop(3, 10, 10);
	shop.Start();
	shop.Stop();
	int result = shop.stats.served + shop.stats.rejected;
	EXPECT_EQ(113, result);
}

TEST(task2, test2) {
	Shop shop(4, 10, 20);
	shop.Start();
	shop.Stop();
	int result = shop.stats.rejected;
	EXPECT_EQ(81, result);
}

TEST(task3, test3) {
	Shop shop(1, 4, 100);
	shop.Start();
	shop.Stop();
	int result = 0;
	if (shop.stats.rejected > 100)
		result = 1;
	EXPECT_EQ(1, result);
}
