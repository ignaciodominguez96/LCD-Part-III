/*

#pragma once


#ifndef TWITTER_API_H

#define TWITTER_API_H

#include "HttpRequest.h"
#include "Tweet.h"
#include "UserTwitter.h"

#define TWITTER_PAGE_NOT_FOUND 34

enum class Twitter_Code : unsigned int {
	TWEETS_FOUND,
	ERROR_USER_NOT_FOUND,
	ERROR_TWEETS_NOT_FOUND,
	ERROR_CURL,
	NONE
};

enum class Tweet_Status : unsigned int {
	PREPARE,
	REQUEST,
	BUILD
};


class Twitter_API : public HttpRequest {
public:


	Twitter_API(string& apiKey, string& apiSecret);
	Twitter_API(const char* apiKey, const char* apiSecret);
	~Twitter_API();

	
	bool isConnected(void);


	bool getTweet(
		string screenName,
		unsigned int count,
		list<Tweet>& tweet
	);

	
	Twitter_Code getTweetCode(void);

	
	virtual bool hasFinished(void);

private:

	
	bool connect(void);

	
	bool _prepare_getTweet(
		string screenName,
		unsigned int count
	);


	bool _request_getTweet(void);


	bool _build_getTweet(list<Tweet>& tweet);

	string apiKey;
	string apiSecret;
	string token;
	bool connected;

	bool twitterFinished;

	Twitter_Code tweetCode;
	Tweet_Status getTweetStatus;
};

#endif // !TWITTER_API_H

*/