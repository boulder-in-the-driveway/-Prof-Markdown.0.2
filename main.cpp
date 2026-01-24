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

TEST_CASE("toParagraph Test")
{
	string s1 = "this will be a paragraph\n\n"; //needs to be directly connected to the sentence
	string s2 = "this will not be a paragraph";
	string s3 = "this will be a paragraph\n\n and this will not be";
	//string s4 = "this will be a paragraph\n\n and this will be another one\n\n";

	MarkdownConverter mc1 = MarkdownConverter(s1);
	MarkdownConverter mc2 = MarkdownConverter(s2);
	MarkdownConverter mc3 = MarkdownConverter(s3);
	//MarkdownConverter mc4 = MarkdownConverter(s4);

	REQUIRE(mc1.toParagraph() == "<p>this will be a paragraph</p>");
	REQUIRE(mc2.toParagraph() == "this will not be a paragraph");
	REQUIRE(mc3.toParagraph() == "<p>this will be a paragraph</p> and this will not be");
	//REQUIRE(mc4.toParagraph() == "<p>this will be a paragraph</p> <p>and this will be another one</p>");
}

TEST_CASE("toImage Test")  
{ 
	string s1 = "![this is an image](/path/to/img.jpg)";
	string s2 = "![this is not an image]/path/to/img.jpg";
	string s3 = "![this is an image](/path/to/img.jpg) **but this italics!**";
	string s4 = "![this is an image](/path/to/img.jpg) and ![this is an image](/path/to/img.jpg)";
	string s5 = "[this is a not an image](/path/to/img.jpg) and ![this is an image](/path/to/img.jpg)";
	

	MarkdownConverter mc1 = MarkdownConverter(s1);
	
	MarkdownConverter mc2 = MarkdownConverter(s2);
	MarkdownConverter mc3 = MarkdownConverter(s3);
	MarkdownConverter mc4 = MarkdownConverter(s4);
	MarkdownConverter mc5 = MarkdownConverter(s5);
	

	
	REQUIRE(mc1.toImage() == "<img src=\"/path/to/img.jpg\" alt=\"this is an image\">");
	
	REQUIRE(mc2.toImage() == "![this is not an image]/path/to/img.jpg"); 
	REQUIRE(mc3.toImage() == "<img src=\"/path/to/img.jpg\" alt=\"this is an image\"> **but this italics!**");
	REQUIRE(mc4.toImage() == "<img src=\"/path/to/img.jpg\" alt=\"this is an image\"> and <img src=\"/path/to/img.jpg\" alt=\"this is an image\">");
	REQUIRE(mc5.toImage() == "[this is a not an image](/path/to/img.jpg) and <img src=\"/path/to/img.jpg\" alt=\"this is an image\">");
	
}