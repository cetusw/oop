#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <regex>

constexpr unsigned short HTTP_PORT = 80;
constexpr unsigned short HTTPS_PORT = 443;
constexpr unsigned short MIN_PORT = 1;
constexpr unsigned short MAX_PORT = 65535;

bool IsPortValid(const unsigned short port) { return port >= MIN_PORT && port <= MAX_PORT; }

void StringToProtocol(const std::string& stringProtocol, Protocol& protocol)
{
	if (stringProtocol == "http")
	{
		protocol = Protocol::HTTP;
	}
	else if (stringProtocol == "https")
	{
		protocol = Protocol::HTTPS;
	}
}

void StringToPort(const std::string& stringPort, unsigned short& port, const Protocol protocol)
{
	if (!stringPort.empty())
	{
		const int tempPort = std::stoi(stringPort);
		if (!IsPortValid(tempPort))
		{
			throw UrlParsingError("Invalid port number");
		}
		port = tempPort;
	}
	else if (protocol == Protocol::HTTP)
	{
		port = HTTP_PORT;
	}
	else if (protocol == Protocol::HTTPS)
	{
		port = HTTPS_PORT;
	}
}

void ParseUrl(const std::string& rawUrl, Protocol& protocol, std::string& domain,
	unsigned short& port, std::string& document)
{
	const std::regex urlRegex(
		R"((http|https)://([^/:]+)(:(\d+))?(/.*)?)", std::regex_constants::icase);

	std::smatch url;
	if (!std::regex_match(rawUrl, url, urlRegex))
	{
		throw UrlParsingError("URL doesn't match with pattern");
	}

	std::string stringProtocol = url[1];
	std::transform(stringProtocol.begin(), stringProtocol.end(), stringProtocol.begin(), tolower);
	StringToProtocol(stringProtocol, protocol);

	domain = url[2];

	const std::string stringPort = url[4];
	StringToPort(stringPort, port, protocol);

	document = url[5].length() > 0 ? url[5].str().substr(1) : "";
}

std::string AssembleUrl(const Protocol& protocol, const std::string& domain,
	const unsigned short& port, const std::string& document)
{
	std::string url = protocol == Protocol::HTTP ? "http://" : "https://";
	url += domain;
	if (port != HTTP_PORT && port != HTTPS_PORT)
	{
		url += ":" + std::to_string(port);
	}
	url += document;
	return url;
}

HttpUrl::HttpUrl(const std::string& url)
{
	Protocol protocol;
	std::string domain;
	unsigned short port;
	std::string document;

	ParseUrl(url, protocol, domain, port, document);

	m_protocol = protocol;
	m_domain = domain;
	m_port = port;
	m_document = document[0] != '/' && !document.empty() ? "/" + document : document;
	m_url = AssembleUrl(m_protocol, m_domain, m_port, m_document);
}

HttpUrl::HttpUrl(const Protocol protocol, const std::string& domain, const std::string& document)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}

	m_protocol = protocol;
	m_domain = domain;
	m_port = (protocol == Protocol::HTTP) ? HTTP_PORT : HTTPS_PORT;
	m_document = document[0] != '/' ? "/" + document : document;
	m_url = AssembleUrl(m_protocol, m_domain, m_port, m_document);
}

HttpUrl::HttpUrl(const Protocol protocol, const std::string& domain, const unsigned short port,
	const std::string& document)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}
	if (!IsPortValid(port))
	{
		throw std::out_of_range("Invalid port number");
	}

	m_protocol = protocol;
	m_domain = domain;
	m_port = port;
	m_document = document[0] == '/' ? document : "/" + document;
	m_url = AssembleUrl(m_protocol, m_domain, m_port, m_document);
}

std::string HttpUrl::GetURL() const { return m_url; }

std::string HttpUrl::GetDomain() const { return m_domain; }

std::string HttpUrl::GetDocument() const { return m_document; }

Protocol HttpUrl::GetProtocol() const { return m_protocol; }

unsigned short HttpUrl::GetPort() const { return m_port; }