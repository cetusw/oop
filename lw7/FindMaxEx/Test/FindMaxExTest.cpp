#include "../FindMaxExTest.h"
#include "../Sportsman.h"
#include <gtest/gtest.h>

void FindMaxExTest(const std::vector<Sportsman>& sportsmen,
	const Sportsman& expectedHighestSportsman, const Sportsman& expectedHeaviestSportsman,
	const Sportsman& expectedShortestSportsman, const Sportsman& expectedLightestSportsman)
{
	Sportsman highestSportsman;
	Sportsman heaviestSportsman;
	Sportsman shortestSportsman;
	Sportsman lightestSportsman;

	auto returnHighest = [](const Sportsman& a, const Sportsman& b) { return a.height < b.height; };
	auto returnHeaviest
		= [](const Sportsman& a, const Sportsman& b) { return a.weight < b.weight; };
	auto returnShortest
		= [](const Sportsman& a, const Sportsman& b) { return a.height > b.height; };
	auto returnLightest
		= [](const Sportsman& a, const Sportsman& b) { return a.weight > b.weight; };

	FindMaxEx<Sportsman>(sportsmen, highestSportsman, returnHighest);
	FindMaxEx<Sportsman>(sportsmen, heaviestSportsman, returnHeaviest);
	FindMaxEx<Sportsman>(sportsmen, shortestSportsman, returnShortest);
	FindMaxEx<Sportsman>(sportsmen, lightestSportsman, returnLightest);

	EXPECT_EQ(highestSportsman.name, expectedHighestSportsman.name);
	EXPECT_EQ(heaviestSportsman.name, expectedHeaviestSportsman.name);
	EXPECT_EQ(shortestSportsman.name, expectedShortestSportsman.name);
	EXPECT_EQ(lightestSportsman.name, expectedLightestSportsman.name);
}


TEST(FindMaxExTest, SingleSportsman) {
    Sportsman s = {"John", 185, 90};
    FindMaxExTest({s}, s, s, s, s);
}

TEST(FindMaxExTest, ZeroSingleSportsman) {
	Sportsman s = {"John", 0, 0};
	FindMaxExTest({s}, s, s, s, s);
}

TEST(FindMaxExTest, ZeroMultipleSportsmen) {
	Sportsman s1 = {"A", 0, 0};
	Sportsman s2 = {"B", 0, 0};
	Sportsman s3 = {"C", 0, 0};
	FindMaxExTest({s1, s2, s3},
				 s1,
				 s1,
				 s1,
				 s1);
}

TEST(FindMaxExTest, MultipleSportsmen) {
    Sportsman s1 = {"A", 180, 80};
    Sportsman s2 = {"B", 190, 75};
    Sportsman s3 = {"C", 170, 85};
    FindMaxExTest({s1, s2, s3},
                 s2,
                 s3,
                 s3,
                 s2);
}

TEST(FindMaxExTest, NegativeMultipleSportsmen) {
	Sportsman s1 = {"A", -180, -80};
	Sportsman s2 = {"B", -190, -75};
	Sportsman s3 = {"C", -170, -85};
	FindMaxExTest({s1, s2, s3},
				 s3,
				 s2,
				 s2,
				 s3);
}

TEST(FindMaxExTest, NegativeAndPositiveMultipleSportsmen) {
	Sportsman s1 = {"A", -180, 80};
	Sportsman s2 = {"B", 190, -75};
	Sportsman s3 = {"C", -170, 85};
	FindMaxExTest({s1, s2, s3},
				 s2,
				 s3,
				 s1,
				 s2);
}

TEST(FindMaxExTest, SameHeight) {
    Sportsman s1 = {"A", 180, 80};
    Sportsman s2 = {"B", 180, 85};
    FindMaxExTest({s1, s2},
                 s1,
                 s2,
                 s1,
                 s1);
}

TEST(FindMaxExTest, SameHeightReversed) {
	Sportsman s1 = {"A", 180, 80};
	Sportsman s2 = {"B", 180, 85};
	FindMaxExTest({s2, s1},
				 s2,
				 s2,
				 s2,
				 s1);
}

TEST(FindMaxExTest, SameWeight) {
	Sportsman s1 = {"A", 170, 80};
	Sportsman s2 = {"B", 175, 80};
	FindMaxExTest({s1, s2},
				 s2,
				 s1,
				 s1,
				 s1);
}

TEST(FindMaxExTest, SameWeightReversed) {
	Sportsman s1 = {"A", 170, 80};
	Sportsman s2 = {"B", 175, 80};
	FindMaxExTest({s2, s1},
				 s2,
				 s2,
				 s1,
				 s2);
}

TEST(FindMaxExTest, SameHeightAndWeight) {
	Sportsman s1 = {"A", 170, 80};
	Sportsman s2 = {"B", 170, 80};
	FindMaxExTest({s1, s2},
				 s1,
				 s1,
				 s1,
				 s1);
}

TEST(FindMaxExTest, SameHeightAndWeightReversed) {
	Sportsman s1 = {"A", 170, 80};
	Sportsman s2 = {"B", 170, 80};
	FindMaxExTest({s2, s1},
				 s2,
				 s2,
				 s2,
				 s2);
}

TEST(FindMaxExTest, HeaviestNotHighest) {
    Sportsman s1 = {"A", 180, 90};
    Sportsman s2 = {"B", 190, 80};
    FindMaxExTest({s1, s2},
                 s2,
                 s1,
                 s1,
                 s2);
}

TEST(FindMaxExTest, HighestNotHeaviest) {
	Sportsman s1 = {"A", 190, 80};
	Sportsman s2 = {"B", 180, 90};
	FindMaxExTest({s1, s2},
				 s1,
				 s2,
				 s2,
				 s1);
}

TEST(FindMaxExTest, BoundHeight) {
	Sportsman s1 = {"A", 190, 80};
	Sportsman s2 = {"B", 189, 90};
	FindMaxExTest({s1, s2},
				 s1,
				 s2,
				 s2,
				 s1);
}

TEST(FindMaxExTest, BoundHeightReversed) {
	Sportsman s1 = {"A", 189, 80};
	Sportsman s2 = {"B", 190, 90};
	FindMaxExTest({s1, s2},
				 s2,
				 s2,
				 s1,
				 s1);
}

TEST(FindMaxExTest, BoundWeight) {
	Sportsman s1 = {"A", 189, 89};
	Sportsman s2 = {"B", 190, 90};
	FindMaxExTest({s1, s2},
				 s2,
				 s2,
				 s1,
				 s1);
}

TEST(FindMaxExTest, BoundWeightReversed) {
	Sportsman s1 = {"A", 189, 90};
	Sportsman s2 = {"B", 190, 89};
	FindMaxExTest({s1, s2},
				 s2,
				 s1,
				 s1,
				 s2);
}

