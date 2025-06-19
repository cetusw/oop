#include "../HttpUrl.h"
#include "../UrlParsingError.h"
#include "gtest/gtest.h"

void ConstructUlrByStringTest(const std::string& stringUrl, const Protocol& expectedProtocol,
	const std::string& expectedDomain, const unsigned short expectedPort,
	const std::string& expectedDocument)
{
	const HttpUrl url(stringUrl);
	EXPECT_EQ(stringUrl, url.GetURL());
	EXPECT_EQ(expectedProtocol, url.GetProtocol());
	EXPECT_EQ(expectedDomain, url.GetDomain());
	EXPECT_EQ(expectedPort, url.GetPort());
	EXPECT_EQ(expectedDocument, url.GetDocument());
}

void ConstructUlrDefaultPortTest(const Protocol protocol, const std::string& domain,
	const std::string& document, const std::string& expectedUrl, const unsigned short expectedPort)
{
	const HttpUrl url(protocol, domain, document);
	EXPECT_EQ(expectedUrl, url.GetURL());
	EXPECT_EQ(protocol, url.GetProtocol());
	EXPECT_EQ(domain, url.GetDomain());
	EXPECT_EQ(expectedPort, url.GetPort());
	EXPECT_EQ(document, url.GetDocument());
}

void ConstructUlrCustomPortTest(const Protocol protocol, const std::string& domain,
	const unsigned short port, const std::string& document, const std::string& expectedUrl)
{
	const HttpUrl url(protocol, domain, port, document);
	EXPECT_EQ(expectedUrl, url.GetURL());
	EXPECT_EQ(protocol, url.GetProtocol());
	EXPECT_EQ(domain, url.GetDomain());
	EXPECT_EQ(port, url.GetPort());
	EXPECT_EQ(document, url.GetDocument());
}

TEST(ConstructUrlsByString, DefaultPortTest)
{
	ConstructUlrByStringTest(
		"http://www.example.com",
		Protocol::HTTP,
		"www.example.com",
		80,
		""
		);
	ConstructUlrByStringTest(
		"https://www.example.com",
		Protocol::HTTPS,
		"www.example.com",
		443,
		""
		);
}

TEST(ConstructUrlsByString, CustomPort)
{
	ConstructUlrByStringTest(
		"http://www.example.com:8080",
		Protocol::HTTP,
		"www.example.com",
		8080,
		""
		);
	ConstructUlrByStringTest(
		"http://min-port:1",
		Protocol::HTTP,
		"min-port",
		1,
		""
		);
	ConstructUlrByStringTest(
		"https://min-port:1",
		Protocol::HTTPS,
		"min-port",
		1,
		""
		);
	ConstructUlrByStringTest(
		"http://max-port:65535",
		Protocol::HTTP,
		"max-port",
		65535,
		""
		);
	ConstructUlrByStringTest(
		"https://max-port:65535",
		Protocol::HTTPS,
		"max-port",
		65535,
		""
		);
	ConstructUlrByStringTest(
		"https://www.example.com:8080",
		Protocol::HTTPS,
		"www.example.com",
		8080,
		""
		);
}

TEST(ConstructUrlsByString, DomainTest)
{
	ConstructUlrByStringTest(
		"http://www.example.com",
		Protocol::HTTP,
		"www.example.com",
		80,
		""
		);
	ConstructUlrByStringTest(
		"http://example.com",
		Protocol::HTTP,
		"example.com",
		80,
		""
		);
	ConstructUlrByStringTest(
		"http://example",
		Protocol::HTTP,
		"example",
		80,
		""
		);
}

TEST(ConstructUrlsByString, DefaultPortWithDocument)
{
	ConstructUlrByStringTest(
		"http://www.example.com",
		Protocol::HTTP,
		"www.example.com",
		80,
		""
		);
	ConstructUlrByStringTest(
		"http://www.example.com/document",
		Protocol::HTTP,
		"www.example.com",
		80,
		"/document"
		);
	ConstructUlrByStringTest(
		"http://www.example.com/document.txt",
		Protocol::HTTP,
		"www.example.com",
		80,
		"/document.txt"
		);
	ConstructUlrByStringTest(
		"http://www.example.com/document.txt/long/document",
		Protocol::HTTP,
		"www.example.com",
		80,
		"/document.txt/long/document"
		);
}

TEST(ConstructUlrDefaultPort, DefaultPortTest)
{
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"www.example.com",
		"/",
		"http://www.example.com/",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTPS,
		"www.example.com",
		"/",
		"https://www.example.com/",
		443
		);
}

TEST(ConstructUlrDefaultPort, DomainTest)
{
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"www.example.com",
		"/",
		"http://www.example.com/",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"example.com",
		"/",
		"http://example.com/",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"example",
		"/",
		"http://example/",
		80
		);
}

TEST(ConstructUlrDefaultPort, DocumentTest)
{
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"www.example.com",
		"/",
		"http://www.example.com/",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"example.com",
		"/document",
		"http://example.com/document",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"example",
		"/document.txt",
		"http://example/document.txt",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"example",
		"/document.txt/long/document",
		"http://example/document.txt/long/document",
		80
		);
}

TEST(ConstructUlrCustomPortTest, CustomPortTest)
{
	ConstructUlrCustomPortTest(
		Protocol::HTTP,
		"www.example.com",
		8080,
		"/",
		"http://www.example.com:8080/"
		);
	ConstructUlrCustomPortTest(
		Protocol::HTTP,
		"www.example.com",
		1,
		"/",
		"http://www.example.com:1/"
		);
	ConstructUlrCustomPortTest(
		Protocol::HTTP,
		"www.example.com",
		65535,
		"/",
		"http://www.example.com:65535/"
		);
}

TEST(ConstructUlrCustomPortTest, DomainTest)
{
	ConstructUlrCustomPortTest(
		Protocol::HTTP,
		"www.example.com",
		8080,
		"/",
		"http://www.example.com:8080/"
		);
	ConstructUlrCustomPortTest(
		Protocol::HTTP,
		"example.com",
		8080,
		"/",
		"http://example.com:8080/"
		);
	ConstructUlrCustomPortTest(
		Protocol::HTTP,
		"example",
		8080,
		"/",
		"http://example:8080/"
		);
}

TEST(ConstructUlrCustomPortTest, DocumentTest)
{
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"www.example.com",
		"/",
		"http://www.example.com/",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"example.com",
		"/document",
		"http://example.com/document",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"example",
		"/document.txt",
		"http://example/document.txt",
		80
		);
	ConstructUlrDefaultPortTest(
		Protocol::HTTP,
		"example",
		"/document.txt/long/document",
		"http://example/document.txt/long/document",
		80
		);
}

TEST(ConstructUrlsByString, ThrowsOnInvalidUrlParsing)
{
	EXPECT_THROW(HttpUrl("www.example.com"), UrlParsingError);
	EXPECT_THROW(HttpUrl("http//www.example.com"), UrlParsingError);
	EXPECT_THROW(HttpUrl("blabla://www.example.com"), UrlParsingError);
	EXPECT_THROW(HttpUrl("http://"), UrlParsingError);
	EXPECT_THROW(HttpUrl("https://:8080/"), UrlParsingError);
	EXPECT_THROW(HttpUrl("http://example.com:0/"), UrlParsingError);
	EXPECT_THROW(HttpUrl("http://example.com:65536/"), UrlParsingError);
}

TEST(ConstructUlrCustomPortTest, ThrowsOnInvalidConstructionParameters)
{
	EXPECT_THROW(HttpUrl(Protocol::HTTP, "", "document"), std::invalid_argument);
	EXPECT_THROW(HttpUrl(Protocol::HTTPS, "", 8080, "document"), std::invalid_argument);
	EXPECT_THROW(HttpUrl(Protocol::HTTP, "domain.com", 0, "doc"), std::out_of_range);
	EXPECT_THROW(HttpUrl(Protocol::HTTPS, "domain.com", 65536, "doc"), std::out_of_range);
}