#ifndef URLPARSINGERROR_H
#define URLPARSINGERROR_H
#include <stdexcept>

class UrlParsingError final : public std::invalid_argument
{
public:
	explicit UrlParsingError(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};

#endif // URLPARSINGERROR_H
