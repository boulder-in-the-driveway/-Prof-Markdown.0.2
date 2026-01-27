#include <iostream>
#define CATCH_CONFIG_NO_POSIX_SIGNALS
#define CATCH_CONFIG_MAIN   
#include "catch.hpp"
#include "MarkdownConverter.h"
#include "fileFormatter.h"
using namespace std;


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
	string s2 = "this is not code";

	MarkdownConverter mc1 = MarkdownConverter(s1);
	MarkdownConverter mc2 = MarkdownConverter(s2);
	
	REQUIRE(mc1.toOneLineCode() == "<code>this is code!</code>");
	REQUIRE(mc2.toOneLineCode() == s2);
}


 
TEST_CASE("toList Unordered Test")
{
	string s1 = "- This is a list item!";
	string s2 = "this is not a list item";

	MarkdownConverter mc1 = MarkdownConverter(s1);
	MarkdownConverter mc2 = MarkdownConverter(s2);
	MarkdownConverter mc1_1 = MarkdownConverter(s1, s2, s2);
	MarkdownConverter mc1_2 = MarkdownConverter(s1, s1, s1);
	MarkdownConverter mc1_3 = MarkdownConverter(s1, s1, s2);
	MarkdownConverter mc1_4 = MarkdownConverter(s1, s2, s1);

	REQUIRE(mc1.toList() == "<ul>\n<li> This is a list item!</li>\n</ul>");
	REQUIRE(mc2.toList() == s2);
	REQUIRE(mc1_1.toList() == "<ul>\n<li> This is a list item!</li>\n</ul>");
	REQUIRE(mc1_2.toList() == "<li> This is a list item!</li>");
	REQUIRE(mc1_3.toList() == "<li> This is a list item!</li>\n</ul>");
	REQUIRE(mc1_4.toList() == "<ul>\n<li> This is a list item!</li>");
}
TEST_CASE("toList Ordered Test")
{
	string s0 = "- This is a list item!";
	string s = "this is not a list item";
	string s1 = "1. This is the first item!";
	string s2 = "2. This is the second item!";
	string s3 = "3. This is the third item!";
	string s4 = "4. Item 4";

	MarkdownConverter mc1 = MarkdownConverter(s0);
	MarkdownConverter mc2 = MarkdownConverter(s);
	MarkdownConverter mc3 = MarkdownConverter(s1);
	MarkdownConverter mc3_1 = MarkdownConverter(s1, s, s2);
	MarkdownConverter mc4 = MarkdownConverter (s2, s1, s3);
	MarkdownConverter mc5 = MarkdownConverter (s3, s2, s);
	MarkdownConverter mc6 = MarkdownConverter (s4, s3,s );

	REQUIRE(mc1.toList() == "<ul>\n<li> This is a list item!</li>\n</ul>");
	REQUIRE(mc2.toList() == s);
	REQUIRE(mc3.toList() == "<ol>\n<li> This is the first item!</li>\n</ol>");
	REQUIRE(mc3_1.toList() == "<ol>\n<li> This is the first item!</li>");
	REQUIRE(mc4.toList() == "<li> This is the second item!</li>");
	REQUIRE(mc5.toList() == "<li> This is the third item!</li>\n</ol>");
	REQUIRE(mc6.toList() == "<li> Item 4</li>\n</ol>");
}




TEST_CASE("toLink Test")  
{ 
	string s1 = "this is a link! [Google](https://google.com)";
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

TEST_CASE("toHeader Test")
{
	string s1 = "#this will be a header";
	string s2 = "##this will be a h2 header";
	string s3 = "######this will be a h6 header";

	MarkdownConverter mc1 = MarkdownConverter(s1);
	MarkdownConverter mc2 = MarkdownConverter(s2);
	MarkdownConverter mc3 = MarkdownConverter(s3);

	REQUIRE(mc1.toHeader() == "<h1>this will be a header</h1>");
	REQUIRE(mc2.toHeader() == "<h2>this will be a h2 header</h2>");
	REQUIRE(mc3.toHeader() == "<h6>this will be a h6 header</h6>");
}

TEST_CASE("toHors Test")
{
	string s1 = "---";


	MarkdownConverter mc1 = MarkdownConverter(s1);


	REQUIRE(mc1.toHorsLine() == "<hr>");

}

TEST_CASE ("fileFormatter Test")
{
	fileFormatter file1 = fileFormatter("/workspaces/-Prof-Markdown.0.2/-Prof-Markdown.txt");
	REQUIRE(file1.getLine(2) == "This is some basic, sample markdown.");
	REQUIRE(file1.getLine(0) == "# Sample Markdown");
}