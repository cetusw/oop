#include "Date.h"

#include <iostream>
#include <vector>

constexpr unsigned DAYS_IN_ERA = 146097;
constexpr unsigned BEGIN_OFFSET = 719468;
constexpr unsigned YEARS_IN_ERA = 400;
constexpr unsigned DAYS_IN_YEAR = 365;
constexpr unsigned MIN_YEAR = 1970;
constexpr unsigned MAX_YEAR = 9999;
constexpr char LAST_DAY_OF_MONTH_COMMON_YEAR[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
constexpr unsigned MAX_TIMESTAMP = 2932896;

bool IsLeap(const unsigned year) { return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; }

unsigned GetLastDayInMonth(const unsigned month, const unsigned year)
{
	return month != 2 || !IsLeap(year) ? LAST_DAY_OF_MONTH_COMMON_YEAR[month - 1] : 29u;
}

bool ValidateDate(const unsigned day, const unsigned month, const unsigned year)
{
	if (month < 1 || month > 12)
	{
		return false;
	}
	const unsigned lastDayOfMonth = GetLastDayInMonth(month, year);
	if (day < 1 || day > lastDayOfMonth || year < MIN_YEAR || year > MAX_YEAR)
	{
		return false;
	}
	return true;
}

bool ValidateTimestamp(const unsigned timestamp) { return timestamp <= MAX_TIMESTAMP; }

unsigned DateToTimestamp(const unsigned day, const unsigned month, unsigned year)
{
	if (!ValidateDate(day, month, year))
	{
		return 0;
	}

	// Алгоритм: https://howardhinnant.github.io/date_algorithms.html#weekday_from_days
	year -= month <= 2;
	const unsigned era = year / YEARS_IN_ERA;
	const unsigned yearOfEra = year - era * YEARS_IN_ERA;
	const unsigned dayOfYear = (153 * (month > 2 ? month - 3 : month + 9) + 2) / 5 + day - 1;
	const unsigned dayOfEra
		= yearOfEra * DAYS_IN_YEAR + yearOfEra / 4 - yearOfEra / 100 + dayOfYear;

	return era * DAYS_IN_ERA + dayOfEra - BEGIN_OFFSET;
}

Date::Date(const unsigned day, Month month, const unsigned year)
{
	const auto monthNumber = static_cast<unsigned>(month);

	m_timestamp = DateToTimestamp(day, monthNumber, year);
}

Date::Date(const unsigned timestamp)
	: m_timestamp(timestamp)
{
	if (!ValidateTimestamp(timestamp))
	{
		m_timestamp = 0;
	}
}

Date::Date() { m_timestamp = 0; }

unsigned Date::GetDay() const { return std::get<0>(GetCivil()); }

Month Date::GetMonth() const { return std::get<1>(GetCivil()); }

unsigned Date::GetYear() const { return std::get<2>(GetCivil()); }

WeekDay Date::GetWeekDay() const
{
	return static_cast<WeekDay>(m_timestamp % 7 + 4);
}

Date& Date::operator++()
{
	if (ValidateTimestamp(m_timestamp + 1))
	{
		m_timestamp++;
	}
	return *this;
}
Date Date::operator++(int)
{
	const Date temp = *this;
	++*this;
	return temp;
}
Date& Date::operator--()
{
	if (ValidateTimestamp(m_timestamp - 1))
	{
		m_timestamp--;
	}
	return *this;
}

Date Date::operator--(int)
{
	const Date temp = *this;
	--*this;
	return temp;
}

Date Date::operator+(const unsigned days) const { return Date(m_timestamp + days); }

Date Date::operator-(const unsigned days) const { return Date(m_timestamp - days); }

Date& Date::operator+=(const unsigned days)
{
	if (ValidateTimestamp(m_timestamp + days))
	{
		m_timestamp += days;
	}
	return *this;
}

Date& Date::operator-=(const unsigned days)
{
	if (ValidateTimestamp(m_timestamp - days))
	{
		m_timestamp -= days;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	const unsigned day = date.GetDay();
	const auto month = static_cast<unsigned>(date.GetMonth());
	const unsigned year = date.GetYear();
	const auto dayPrefix = day < 10 ? "0" : "";
	const auto monthPrefix = month < 10 ? "0" : "";
	os << dayPrefix << day << '.' << monthPrefix << month << '.' << year << std::endl;

	return os;
}

std::istream& operator>>(std::istream& is, Date& date)
{
	unsigned day;
	unsigned month;
	unsigned year;
	char separator1;
	char separator2;

	if (is >> day >> separator1 >> month >> separator2 >> year)
	{
		if (separator1 == '.' && separator2 == '.')
		{
			date.m_timestamp = DateToTimestamp(day, month, year);
		}
		else
		{
			is.setstate(std::ios::failbit);
		}
	}
	return is;
}

bool Date::operator==(const Date& date) const { return m_timestamp == date.m_timestamp; }

bool Date::operator!=(const Date& date) const { return !(*this == date); }

bool Date::operator<(const Date& date) const { return m_timestamp < date.m_timestamp; }

bool Date::operator>(const Date& date) const { return m_timestamp > date.m_timestamp; }

bool Date::operator<=(const Date& date) const { return *this < date || *this == date; }

bool Date::operator>=(const Date& date) const { return *this > date || *this == date; }

std::tuple<unsigned, Month, unsigned> Date::GetCivil() const
{
	unsigned timestamp = m_timestamp;

	timestamp += 719468;
	const unsigned era = timestamp / 146097;
	const unsigned dayOfEra = timestamp - era * 146097;
	const unsigned yearOfEra
		= (dayOfEra - dayOfEra / 1460 + dayOfEra / 36524 - dayOfEra / 146096) / 365;
	const unsigned year = yearOfEra + era * 400;
	const unsigned dayOfYear = dayOfEra - (365 * yearOfEra + yearOfEra / 4 - yearOfEra / 100);
	const unsigned monthPeriod = (5 * dayOfYear + 2) / 153;
	const unsigned day = dayOfYear - (153 * monthPeriod + 2) / 5 + 1;
	const unsigned monthNumber = monthPeriod < 10 ? monthPeriod + 3 : monthPeriod - 9;
	auto month = static_cast<Month>(monthNumber);
	return { day, month, year + (monthNumber <= 2) };
}