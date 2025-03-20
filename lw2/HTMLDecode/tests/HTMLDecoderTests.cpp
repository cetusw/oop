#include <fstream>
#include "../HTMLDecoder.h"
#include "../HTMLDecoderUtils.h"
#include "catch2/catch_all.hpp"

struct TestData
{
    const std::map<std::string, std::string> testHTMLEntity = {
        {"&quot;", "\""},
        {"&apos;", "'"},
        {"&lt;", "<"},
        {"&gt;", ">"},
        {"&amp;", "&"},
        {"&unknown;", "&unknown;"},
        {"&Quot;", "&Quot;"},
        {"abc&lt;def", "abc<def"},
        {"abc&lt;", "abc<"},
        {"   &lt;   ", "   <   "},
        {"&lt;&gt;", "<>"},
        {"&amp", "&amp"},
        {"   &amp  ", "   &amp  "},
        {"&;", "&;"},
        {"  &amp ; ", "  &amp ; "},
        {"  & amp; ", "  & amp; "},
        {"&quot;&apos;&lt;&gt;&amp;", "\"'<>&"},
        {"", ""},
        {"&", "&"}
    };
};

void RunDecodeStringTests(const std::map<std::string, std::string> &testCases)
{
    int testCount = 0;
    for (const auto &section: testCases)
    {
        testCount++;
        SECTION("Тест #" + std::to_string(testCount))
        {
            REQUIRE(DecodeString(section.first) == section.second);
        }
    }
}

TEST_CASE("DecodeString")
{
    const TestData testData;
    RunDecodeStringTests(testData.testHTMLEntity);
}
