#ifndef TWEET_H
#define TWEET_H


#include <string>
#include "UserTwitter.h"

using namespace std;


class Tweet {
public:

	Tweet();
	Tweet(string user_name,	string screen_name, string text, string time_birth, bool is_trunc);
	~Tweet();


	void set_tweet(string user_name, string screen_name, string text, string time_birth, bool is_trunc);




	string get_text(void);
	string get_text_pos_protocol(void);
	string get_time_birth(void);
	UserTwitter get_user(void);


private:

	void set_text(string text);
	void set_time_birth(string time_birth);
	void set_is_trunc(bool is_trunc);



	UserTwitter user;
	string text;
	string time_birth;
	bool is_trunc;
};




#endif // !TWEET_H
