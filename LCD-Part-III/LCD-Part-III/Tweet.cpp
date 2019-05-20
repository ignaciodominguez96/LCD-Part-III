#include "Tweet.h"

#include <time.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

#define EMPTY_FIELD_STRING	""
#define PROTOCOL_STRING		"https"

#define FORMAT_IN_TIME	"%a %b %d %H:%M:%S %Y"
#define FORMAT_OUT_TIME	"%e/%m/%G - %R"
#define CHAR_TOKEN_FORMAT_TIME	'+'
#define CANT_SKIP_AFTER_TOKEN	5

#define MAX_SIZE_TIME_TEXT 50

/*auxiliar functions*/

string format_birth_time(string time, const char * format_in, const char * format_out);
string remove_substring(string str, char token, unsigned int skip_after_token);

/*builders*/

Tweet::
Tweet() : user(EMPTY_FIELD_STRING, EMPTY_FIELD_STRING) {

}

Tweet::
Tweet(string user_name, string screen_name, string text, string time_birth, bool is_trunc) : user(user_name, screen_name) {

	this->text = text;
	this->time_birth = format_birth_time(time_birth, FORMAT_IN_TIME, FORMAT_OUT_TIME);
	this->is_trunc = is_trunc;

}


/*destroyers*/

Tweet::
~Tweet() {
	
}



/*setters*/

void Tweet::
set_tweet(string user_name, string screen_name, string text, string time_birth, bool is_trunc) {

	user.set_name(user_name);
	user.set_screen_name(screen_name);

	this->set_text(text);
	this->set_time_birth(time_birth);
	this->set_is_trunc(is_trunc);

}

void Tweet::
set_text(string text)
{
	this->text = text;
}

void Tweet::
set_time_birth(string time_birth)
{
	this->time_birth = time_birth;
}

void Tweet::
set_is_trunc(bool is_trunc)
{
	this->is_trunc = is_trunc;
}


/*getters*/

string Tweet::
get_text(void) {
	return this->text;
}

string Tweet::
get_text_pos_protocol(void) {
	return this->text.substr(0, text.find(PROTOCOL_STRING));
}

string Tweet::
get_time_birth(void) {

	return this->time_birth;
}

UserTwitter Tweet::
get_user(void) {

	return this->user;
}




/*auxiliar functions*/

/*
pasar de:

Thu Apr 06 15:28:43 (TOKEN_FORMAT_TIME)0000 2017

a:

Thu Apr 06 15:28:43 2017

*/

string remove_substring(string str, char token, unsigned int skip_after_token) {

	string result = str.substr(0, str.find_first_of(token));

	result += str.substr(str.find_first_of(token) + skip_after_token);

	return result;
}


string format_birth_time(string time, const char * format_in, const char * format_out){

	tm time_object = {};

	std::istringstream in_stream(remove_substring(time, CHAR_TOKEN_FORMAT_TIME, CANT_SKIP_AFTER_TOKEN));

	in_stream >> get_time(&time_object, format_in);

	char aux_time_array[MAX_SIZE_TIME_TEXT];

	strftime(aux_time_array, MAX_SIZE_TIME_TEXT, format_out, &time_object);

	return string(aux_time_array);
}