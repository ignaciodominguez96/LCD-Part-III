#include "UserTwitter.h"

/*builders*/

UserTwitter::
UserTwitter(string& name, string& screen_name) {

	this->name = name;
	this->screen_name = screen_name;
}

UserTwitter::
UserTwitter(const char* name, const char* screen_name) {

	this->name = name;
	this->screen_name = screen_name;
}



/*destroyer*/

UserTwitter::
~UserTwitter() {

}



/*setters*/

void UserTwitter::
set_name(string name) {
	this->name = name;
}

void UserTwitter::
set_screen_name(string screen_name)
{
	this->screen_name = screen_name;
}


/*getters*/

string UserTwitter::
get_name(void) {

	return name;
}

string UserTwitter::
get_screen_name(void) {

	return 	this->screen_name;
	;
}

