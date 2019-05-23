#include "InitDes.h"
#include "Tweet.h"
#include "EventGen.h"
#include "Timer.h"

using namespace std;

int main(void)
{
	EventGen evs;
	Timer timer;
	list<Tweet>* tuits = InitTweets();
	if (tuits != nullptr)
	{
		timer.set_timer();
		while (!evs.stop())
		{
			if (evs.hay_evento(*tuits, timer))
			{
				evs.dispatcher();
			}
		}
	}
	DestroyTweets(*tuits);
	/*
	if (tuits != nullptr)
	{
		for (list<Tweet>::iterator itr = tuits->begin(); itr != tuits->end(); ++itr)
		{
			cout << itr->get_text() << endl;
		}
	}*/
	getchar();
	return 0;
}