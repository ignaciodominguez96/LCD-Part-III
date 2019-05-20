#ifndef INITDES_H
#define INITDES_H

#include <iostream>
#include <exception>
#include <list>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "Tweet.h"

/*Recibe los tweets y los guarda en una lista. Devuelve un punteroa esa lista*/
list<Tweet>* Init(void);
void Destroy(list<Tweet>& lista);

#endif