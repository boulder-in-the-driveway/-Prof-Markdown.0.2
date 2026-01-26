#include <iostream>
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#define CATCH_CONFIG_MAIN   
#include "catch.hpp"
#include "MarkdownConverter.h"
using namespace std;

//--
TEST_CASE("toBold Test")  
{ 
	string s1 = "**this is bold!**";
	string s2 = "this is not bold";
	string s3 = "this is not bold **but this is!**";
	string s4 = "**bold** and **bold**";
	string s5 = "*this is italics* **and this is bold!**";

	MarkdownConverter mc1 = MarkdownConverter(s1);
	MarkdownConverter mc2 = MarkdownConverter(s2);
	MarkdownConverter mc3 = MarkdownConverter(s3);
	MarkdownConverter mc4 = MarkdownConverter(s4);
	MarkdownConverter mc5 = MarkdownConverter(s5);

	REQUIRE(mc1.toBold() == "<strong>this is bold!</strong>");
	REQUIRE(mc2.toBold() == s2); 
	REQUIRE(mc3.toBold() == "this is not bold <strong>but this is!</strong>");
	REQUIRE(mc4.toBold() == "<strong>bold</strong> and <strong>bold</strong>");
	REQUIRE(mc5.toBold() == "*this is italics* <strong>and this is bold!</strong>");
}
TEST_CASE("toItalics Test")  
{ 
	string s1 = "*this is italic!*";
	string s2 = "this is not italic";
	string s3 = "this is not italic *but this is!*";
	string s4 = "*italic* and *italic*";
	string s5 = "*this is italics* **and this is bold!**";

	MarkdownConverter mc1 = MarkdownConverter(s1);
	MarkdownConverter mc2 = MarkdownConverter(s2);
	MarkdownConverter mc3 = MarkdownConverter(s3);
	MarkdownConverter mc4 = MarkdownConverter(s4);
	MarkdownConverter mc5 = MarkdownConverter(s5);
	string s5_1 = mc5.toBold();
	MarkdownConverter mc5_1 = MarkdownConverter(s5_1);

	REQUIRE(mc1.toItalic() == "<em>this is italic!</em>");
	REQUIRE(mc2.toItalic() == s2); 
	REQUIRE(mc3.toItalic() == "this is not italic <em>but this is!</em>");
	REQUIRE(mc4.toItalic() == "<em>italic</em> and <em>italic</em>");
	REQUIRE(mc5_1.toItalic() == "<em>this is italics</em> <strong>and this is bold!</strong>");
}

TEST_CASE("toCode Test")  
{ 
	string s1 = "`this is code!`";
	/*string s2 = "this is not bold";
	string s3 = "this is not bold **but this is!**";
	string s4 = "**bold** and **bold**";
	string s5 = "*this is italics* **and this is bold!**";
	*/

	MarkdownConverter mc1 = MarkdownConverter(s1);
	/*
	MarkdownConverter mc2 = MarkdownConverter(s2);
	MarkdownConverter mc3 = MarkdownConverter(s3);
	MarkdownConverter mc4 = MarkdownConverter(s4);
	MarkdownConverter mc5 = MarkdownConverter(s5);
	*/

	REQUIRE(mc1.toOneLineCode() == "<code>this is code!</code>");
	/*
	REQUIRE(mc2.toBold() == s2); 
	REQUIRE(mc3.toBold() == "this is not bold <strong>but this is!</strong>");
	REQUIRE(mc4.toBold() == "<strong>bold</strong> and <strong>bold</strong>");
	REQUIRE(mc5.toBold() == "*this is italics* <strong>and this is bold!</strong>");
	*/
}

TEST_CASE("toLink Test")  
{ 
	string s1 = "`this is a link [Google](https://google.com)";
	string s2 = "this is not a link";
	string s3 = "this is not a link [but this is!](https://link.com)";
	string s4 = "[Google](https://google.com) and [gitHub](https://github.com)";
	string s5 = "[this is a link](https://google.com) ![and this is an image](data:image/jpeg;base64)";
	string s6 = "![this is an image](data:image/jpeg;base64) [and this is a link](https://google.com)";


	MarkdownConverter mc1 = MarkdownConverter(s1);
	MarkdownConverter mc2 = MarkdownConverter(s2);
	MarkdownConverter mc3 = MarkdownConverter(s3);
	MarkdownConverter mc4 = MarkdownConverter(s4);
	MarkdownConverter mc5 = MarkdownConverter(s5);
	MarkdownConverter mc6 = MarkdownConverter(s6);

	
	REQUIRE(mc1.toLink() == "this is a link! <a href=\"https://google.com\">Google</a>");
	REQUIRE(mc2.toLink() == s2); 
	REQUIRE(mc3.toLink() == "this is not a link <a href=\"https://link.com\">but this is!</a>");
	REQUIRE(mc4.toLink() == "<a href=\"https://google.com\">Google</a> and <a href=\"https://github.com\">gitHub</a>");
	REQUIRE(mc5.toLink() == "<a href=\"https://google.com\">this is a link</a> ![and this is an image](data:image/jpeg;base64)");
	REQUIRE(mc6.toLink() == "![this is an image](data:image/jpeg;base64) <a href=\"https://google.com\">and this is a link</a>");

}