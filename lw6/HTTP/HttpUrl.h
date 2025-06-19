#ifndef HTTPURL_H
#define HTTPURL_H
#include "Protocol.h"

#include <string>

class HttpUrl
{
public:
	explicit HttpUrl(std::string const& url);

	explicit HttpUrl(
		Protocol protocol, const std::string& domain, const std::string& document);

	HttpUrl(Protocol protocol, const std::string& domain, unsigned short port,
		const std::string& document);

	[[nodiscard]] std::string GetURL() const;

	[[nodiscard]] std::string GetDomain() const;

	[[nodiscard]] std::string GetDocument() const;

	[[nodiscard]] Protocol GetProtocol() const;

	[[nodiscard]] unsigned short GetPort() const;
private:
	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};

#endif // HTTPURL_H
