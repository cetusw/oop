#ifndef DATE_H
#define DATE_H
#include <tuple>

#include "Month.h"
#include "WeekDay.h"

#include <istream>

bool IsLeap(unsigned year);

unsigned GetLastDayInMonth(unsigned month, unsigned year);

bool ValidateDate(unsigned day, unsigned month, unsigned year);

bool ValidateTimestamp(unsigned timestamp);

unsigned DateToTimestamp(unsigned day, unsigned month, unsigned year);

class Date
{
public:
	explicit Date(unsigned day, Month month, unsigned year);

	explicit Date(unsigned timestamp);

	Date();

	[[nodiscard]] unsigned GetDay() const;

	[[nodiscard]] Month GetMonth() const;

	[[nodiscard]] unsigned GetYear() const;

	[[nodiscard]] WeekDay GetWeekDay() const;

	Date& operator++();
	Date operator++(int);

	Date& operator--();
	Date operator--(int);

	Date operator+(unsigned days) const;
	Date operator-(unsigned days) const;

	Date& operator+=(unsigned days);
	Date& operator-=(unsigned days);

	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend std::istream& operator>>(std::istream& is, Date& date);

	bool operator==(const Date& date) const;
	bool operator!=(const Date& date) const;

	bool operator<(const Date& date) const;
	bool operator>(const Date& date) const;

	bool operator<=(const Date& date) const;
	bool operator>=(const Date& date) const;

private:
	[[nodiscard]] std::tuple<unsigned, Month, unsigned> GetCivil() const;

	unsigned m_timestamp;
};

#endif // DATE_H
