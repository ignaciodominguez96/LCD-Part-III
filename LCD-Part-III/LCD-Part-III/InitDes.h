#ifndef INITDES_H
#define INITDES_H

#include <iostream>
#include <exception>
#include <list>

#include <curl.h>

#include <nlohmann/json.hpp>
#include "Tweet.h"

/*Recibe los tweets y los guarda en una lista. Devuelve un puntero a esa lista*/
list<Tweet>* InitTweets(void);

void DestroyTweets(list<Tweet>& lista);

#endif