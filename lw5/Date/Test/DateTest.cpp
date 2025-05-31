#include "../Date.h"
#include <gtest/gtest.h>

void IsLeapTest(const unsigned year, const bool isLeap) { EXPECT_EQ(IsLeap(year), isLeap); }

void ValidateDateTest(
	const unsigned day, const unsigned month, const unsigned year, const bool isValid)
{
	EXPECT_EQ(ValidateDate(day, month, year), isValid);
}

void ValidateTimestampTest(const unsigned timestamp, const bool isValid)
{
	EXPECT_EQ(ValidateTimestamp(timestamp), isValid);
}

void DateToTimestampTest(
	const unsigned day, const unsigned month, const unsigned year, const unsigned expectedTimestamp)
{
	const unsigned timestamp = DateToTimestamp(day, month, year);
	EXPECT_EQ(timestamp, expectedTimestamp);
}

void CreateDateByCivilTest(
	const unsigned day, const Month month, const unsigned year, const WeekDay expectedWeekDay)
{
	const Date date(day, month, year);
	EXPECT_EQ(date.GetDay(), day);
	EXPECT_EQ(date.GetMonth(), month);
	EXPECT_EQ(date.GetYear(), year);
	EXPECT_EQ(date.GetWeekDay(), expectedWeekDay);
}

void CreateDateByTimestampTest(const unsigned timestamp, const unsigned expectedDay,
	const Month expectedMonth, const unsigned expectedYear, const WeekDay expectedWeekDay)
{
	const Date date(timestamp);
	EXPECT_EQ(date.GetDay(), expectedDay);
	EXPECT_EQ(date.GetMonth(), expectedMonth);
	EXPECT_EQ(date.GetYear(), expectedYear);
	EXPECT_EQ(date.GetWeekDay(), expectedWeekDay);
}

void CreateDefaultDateTest()
{
	const Date date;
	EXPECT_EQ(date.GetDay(), 1);
	EXPECT_EQ(static_cast<unsigned>(date.GetMonth()), 1);
	EXPECT_EQ(date.GetYear(), 1970);
}

void PrefixIncrementTest(const Date& initial, const Date& expected)
{
	Date date = initial;
	Date& result = ++date;
	EXPECT_EQ(result, expected);
	EXPECT_EQ(&result, &date);
}

void PostfixIncrementTest(
	const Date& initial, const Date& expectedAfter, const Date& expectedReturn)
{
	Date date = initial;
	const Date result = date++;
	EXPECT_EQ(date, expectedAfter);
	EXPECT_EQ(result, expectedReturn);
}

void PrefixDecrementTest(const Date& initial, const Date& expected)
{
	Date date = initial;
	Date& result = --date;
	EXPECT_EQ(result, expected);
	EXPECT_EQ(&result, &date);
}

void PostfixDecrementTest(
	const Date& initial, const Date& expectedAfter, const Date& expectedReturn)
{
	Date date = initial;
	const Date result = date--;
	EXPECT_EQ(date, expectedAfter);
	EXPECT_EQ(result, expectedReturn);
}

void AdditionOperatorTest(const Date& initial, const unsigned days, const Date& expected)
{
	const Date result = initial + days;
	EXPECT_EQ(result, expected);
}

void SubtractionOperatorTest(const Date& initial, const unsigned days, const Date& expected)
{
	const Date result = initial - days;
	EXPECT_EQ(result, expected);
}

void AdditionAssignmentTest(Date initial, const unsigned days, const Date& expected)
{
	Date& result = (initial += days);
	EXPECT_EQ(initial, expected);
	EXPECT_EQ(&result, &initial);
}

void SubtractionAssignmentTest(Date initial, const unsigned days, const Date& expected)
{
	Date& result = (initial -= days);
	EXPECT_EQ(initial, expected);
	EXPECT_EQ(&result, &initial);
}

void EqualityOperatorTest(const Date& date1, const Date& date2, const bool expected)
{
	EXPECT_EQ(date1 == date2, expected);
}

void InequalityOperatorTest(const Date& date1, const Date& date2, const bool expected)
{
	EXPECT_EQ(date1 != date2, expected);
}

void LessThanOperatorTest(const Date& date1, const Date& date2, const bool expected)
{
	EXPECT_EQ(date1 < date2, expected);
}

void GreaterThanOperatorTest(const Date& date1, const Date& date2, const bool expected)
{
	EXPECT_EQ(date1 > date2, expected);
}

void LessOrEqualOperatorTest(const Date& date1, const Date& date2, const bool expected)
{
	EXPECT_EQ(date1 <= date2, expected);
}

void GreaterOrEqualOperatorTest(const Date& date1, const Date& date2, const bool expected)
{
	EXPECT_EQ(date1 >= date2, expected);
}

void OutputOperatorTest(const Date& date, const std::string& expected)
{
	std::ostringstream os;
	os << date;
	EXPECT_EQ(os.str(), expected);
}

void InputOperatorTest(const std::string& input, const bool shouldSucceed, const Date& expected)
{
	std::istringstream is(input);
	Date date;
	is >> date;

	if (shouldSucceed)
	{
		EXPECT_FALSE(is.fail());
		EXPECT_EQ(date, expected);
	}
	else
	{
		EXPECT_TRUE(is.fail());
	}
}

TEST(IsLeapTest, LeapYears)
{
	IsLeapTest(2000, true);
	IsLeapTest(2020, true);
	IsLeapTest(2400, true);
}

TEST(IsLeapTest, NonLeapYears)
{
	IsLeapTest(1900, false);
	IsLeapTest(2021, false);
	IsLeapTest(2100, false);
}

TEST(ValidateDateTest, ValidDates)
{
	ValidateDateTest(1, 1, 1970, true);
	ValidateDateTest(31, 12, 9999, true);
	ValidateDateTest(29, 2, 2020, true);
}

TEST(ValidateDateTest, InvalidDates)
{
	ValidateDateTest(0, 1, 1970, false);
	ValidateDateTest(32, 1, 1970, false);
	ValidateDateTest(29, 2, 2021, false);
	ValidateDateTest(31, 4, 2023, false);
	ValidateDateTest(1, 0, 1970, false);
	ValidateDateTest(1, 13, 1970, false);
	ValidateDateTest(1, 1, 1969, false);
	ValidateDateTest(1, 1, 10000, false);
}

TEST(ValidateTimestampTest, ValidTimestamps)
{
	ValidateTimestampTest(0, true);
	ValidateTimestampTest(2932896, true);
	ValidateTimestampTest(10000, true);
}

TEST(ValidateTimestampTest, InvalidTimestamps)
{
	ValidateTimestampTest(-1, false);
	ValidateTimestampTest(2932897, false);
}

TEST(DateToTimestampTest, ValidConversions)
{
	DateToTimestampTest(1, 1, 1970, 0);
	DateToTimestampTest(2, 1, 1970, 1);
	DateToTimestampTest(1, 1, 1971, 365);
	DateToTimestampTest(1, 1, 2000, 10957);
	DateToTimestampTest(31, 12, 9999, 2932896);
}

TEST(DateToTimestampTest, InvalidConversions) { DateToTimestampTest(29, 2, 1970, 0); }

TEST(CreateDateByCivilTest, ValidDates)
{
	CreateDateByCivilTest(1, Month::JANUARY, 1970, WeekDay::THURSDAY);
	CreateDateByCivilTest(31, Month::DECEMBER, 9999, WeekDay::FRIDAY);
	CreateDateByCivilTest(29, Month::FEBRUARY, 2020, WeekDay::SATURDAY);
}

TEST(CreateDateByTimestampTest, ValidTimestamps)
{
	CreateDateByTimestampTest(0, 1, Month::JANUARY, 1970, WeekDay::THURSDAY);
	CreateDateByTimestampTest(1, 2, Month::JANUARY, 1970, WeekDay::FRIDAY);
	CreateDateByTimestampTest(2932896, 31, Month::DECEMBER, 9999, WeekDay::FRIDAY);
}

TEST(IncrementDecrementTest, BasicOperations)
{
	const Date currentDate(1, Month::JANUARY, 1970);
	const Date nextDate(2, Month::JANUARY, 1970);

	PrefixIncrementTest(currentDate, nextDate);
	PostfixIncrementTest(currentDate, nextDate, currentDate);
	PrefixDecrementTest(nextDate, currentDate);
	PostfixDecrementTest(nextDate, currentDate, nextDate);
}

TEST(IncrementDecrementTest, MonthBoundaries)
{
	const Date lastJan(31, Month::JANUARY, 2023);
	const Date firstFeb(1, Month::FEBRUARY, 2023);

	PrefixIncrementTest(lastJan, firstFeb);
	PostfixDecrementTest(firstFeb, lastJan, firstFeb);
}

TEST(IncrementDecrementTest, YearBoundaries)
{
	const Date lastDate(31, Month::DECEMBER, 2023);
	const Date firstDate(1, Month::JANUARY, 2024);

	PrefixIncrementTest(lastDate, firstDate);
	PostfixDecrementTest(firstDate, lastDate, firstDate);
}

TEST(ArithmeticTest, AdditionSubtractionLessThanMonth)
{
	const Date currentDate(1, Month::JANUARY, 1970);
	const Date afterTenDays(11, Month::JANUARY, 1970);
	const Date beforeTenDays(22, Month::DECEMBER, 1969);

	AdditionOperatorTest(currentDate, 10, afterTenDays);
	SubtractionOperatorTest(currentDate, 10, beforeTenDays);
	AdditionAssignmentTest(currentDate, 10, afterTenDays);
	SubtractionAssignmentTest(currentDate, 10, beforeTenDays);
}

TEST(ArithmeticTest, AdditionSubtractionMoreThanMonth)
{
	const Date currentDate(1, Month::JANUARY, 1970);
	const Date after60Days(02, Month::MARCH, 1970);
	const Date before60Days(22, Month::DECEMBER, 1969);

	AdditionOperatorTest(currentDate, 60, after60Days);
	SubtractionOperatorTest(currentDate, 60, before60Days);
	AdditionAssignmentTest(currentDate, 60, after60Days);
	SubtractionAssignmentTest(currentDate, 60, before60Days);
}

TEST(ArithmeticTest, AdditionSubtractionMoreThanYear)
{
	const Date currentDate(1, Month::JANUARY, 1970);
	const Date after400Days(05, Month::FEBRUARY, 1971);
	const Date before400Days(22, Month::DECEMBER, 1969);

	AdditionOperatorTest(currentDate, 400, after400Days);
	SubtractionOperatorTest(currentDate, 400, before400Days);
	AdditionAssignmentTest(currentDate, 400, after400Days);
	SubtractionAssignmentTest(currentDate, 400, before400Days);
}

TEST(ArithmeticTest, LeapYearAddition)
{
	const Date preLeap(28, Month::FEBRUARY, 2020);
	const Date leapDay(29, Month::FEBRUARY, 2020);
	const Date postLeap(1, Month::MARCH, 2020);

	AdditionOperatorTest(preLeap, 1, leapDay);
	AdditionOperatorTest(leapDay, 1, postLeap);
}


TEST(ArithmeticTest, NonLeapYearAddition)
{
	const Date preNonLeap(27, Month::FEBRUARY, 2021);
	const Date nonLeapDay(28, Month::FEBRUARY, 2021);
	const Date postNonLeap(1, Month::MARCH, 2021);

	AdditionOperatorTest(preNonLeap, 1, nonLeapDay);
	AdditionOperatorTest(nonLeapDay, 1, postNonLeap);
}

TEST(ComparisonTest, BasicComparisons)
{
	const Date date1(1, Month::JANUARY, 1970);
	const Date date2(2, Month::JANUARY, 1970);
	const Date date3(1, Month::JANUARY, 1970);

	EqualityOperatorTest(date1, date3, true);
	InequalityOperatorTest(date1, date2, true);
	LessThanOperatorTest(date1, date2, true);
	GreaterThanOperatorTest(date2, date1, true);
	LessOrEqualOperatorTest(date1, date2, true);
	GreaterOrEqualOperatorTest(date2, date1, true);
	LessOrEqualOperatorTest(date1, date3, true);
	GreaterOrEqualOperatorTest(date1, date3, true);
}

TEST(InputOutputTest, Formatting)
{
	const Date singleDigits(9, Month::AUGUST, 2023);
	OutputOperatorTest(singleDigits, "09.08.2023\n");

	const Date singleDigitDay(1, Month::DECEMBER, 1970);
	OutputOperatorTest(singleDigitDay, "01.12.1970\n");

	const Date singleDigitMonth(10, Month::JANUARY, 1970);
	OutputOperatorTest(singleDigitMonth, "10.01.1970\n");

	const Date maxDate(31, Month::DECEMBER, 9999);
	OutputOperatorTest(maxDate, "31.12.9999\n");
}

TEST(InputOutputTest, ValidInput)
{
	InputOperatorTest("15.09.2023", true, Date(15, Month::SEPTEMBER, 2023));
	InputOperatorTest("01.01.1970", true, Date(1, Month::JANUARY, 1970));
	InputOperatorTest("31.12.9999", true, Date(31, Month::DECEMBER, 9999));
}

TEST(InputOutputTest, InvalidDateInput)
{
	InputOperatorTest("32.01.2023", true, Date());
	InputOperatorTest("00.01.2023", true, Date());
	InputOperatorTest("15.13.2023", true, Date());
	InputOperatorTest("15.00.2023", true, Date());
	InputOperatorTest("15.09.1969", true, Date());
	InputOperatorTest("15.09.10000", true, Date());
	InputOperatorTest("29.02.2023", true, Date());
}

TEST(InputOutputTest, InvalidInputFormatting)
{
	InputOperatorTest("15-09-2023", false, Date());
	InputOperatorTest("Invalid", false, Date());
}

TEST(BoundaryTest, BeginOfTimestamp)
{
	CreateDefaultDateTest();
	CreateDateByCivilTest(1, Month::JANUARY, 1970, WeekDay::THURSDAY);
	CreateDateByTimestampTest(0, 1, Month::JANUARY, 1970, WeekDay::THURSDAY);
}

TEST(BoundaryTest, MaxDate)
{
	CreateDateByCivilTest(31, Month::DECEMBER, 9999, WeekDay::FRIDAY);
	CreateDateByTimestampTest(2932896, 31, Month::DECEMBER, 9999, WeekDay::FRIDAY);
}

TEST(BoundaryTest, YearEnd)
{
	const Date lastDate(31, Month::DECEMBER, 2023);
	const Date nextDate = lastDate + 1;
	EXPECT_EQ(nextDate.GetDay(), 1);
	EXPECT_EQ(nextDate.GetMonth(), Month::JANUARY);
	EXPECT_EQ(nextDate.GetYear(), 2024);
}

TEST(InvalidValueTest, InvalidDateConstruction)
{
	const Date invalidDate(31, Month::FEBRUARY, 2023);
	EXPECT_EQ(invalidDate.GetDay(), 1);
	EXPECT_EQ(invalidDate.GetMonth(), Month::JANUARY);
	EXPECT_EQ(invalidDate.GetYear(), 1970);
}

TEST(InvalidValueTest, InvalidTimestampConstruction)
{
	const Date invalidDate(2932898);
	EXPECT_EQ(invalidDate.GetDay(), 1);
	EXPECT_EQ(invalidDate.GetMonth(), Month::JANUARY);
	EXPECT_EQ(invalidDate.GetYear(), 1970);
}