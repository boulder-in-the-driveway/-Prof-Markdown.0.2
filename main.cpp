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
	//string s3 = "this is not bold **but this is!**";
	//string s4 = "**bold** and **bold**"
	MarkdownConverter mc1 = MarkdownConverter(s1);
	MarkdownConverter mc2 = MarkdownConverter(s2);

	REQUIRE(mc1.toBold() == "<strong>this is bold!</strong>");
	REQUIRE(mc2.toBold() == s2); 
}