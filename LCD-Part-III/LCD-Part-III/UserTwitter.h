#ifndef USER_TWITTER_H
#define USER_TWITTER_H


#include <string>

using namespace std;

class UserTwitter {
public:

	UserTwitter(string& name, string& screen_name);
	UserTwitter(const char* name, const char* screen_name);
	~UserTwitter();

	void set_name(string name);
	void set_screen_name(string name);
	string get_name(void);
	string get_screen_name(void);

private:

	string name;
	string screen_name;

};





#endif // !USER_TWITTER_H

