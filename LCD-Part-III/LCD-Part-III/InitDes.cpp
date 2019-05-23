#include "InitDes.h"

#define QUERY "https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name=lanacion&count=10"
#define API_KEY "HCB39Q15wIoH61KIkY5faRDf6"
#define API_SECRET_KEY "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6"

static size_t myCallback(void *contents, size_t size, size_t nmemb, void *userp);


using json = nlohmann::json;
using namespace std;

list<Tweet>* InitTweets(void)
{
	json j; 

	CURL *curl;					//Variable donde vamos a guardar las configuraciones de una transferencia
	CURLM *multiHandle;			//Variable donde vamos a atachear los easy handles
	CURLcode res;
	string readString, token;

	// Query es la dirección de Twitter que vamos a consultar.
	string query = QUERY;

	string API_key = API_KEY;
	string API_SecretKey = API_SECRET_KEY;


	list<Tweet>* tweets = new list<Tweet>;

	/************************************************************************************
	*                      Get Bearer Token from the Twitter API						*
	************************************************************************************/

	// Primero realizamos la inicialización de curl para obtener el token de Twitter el cual vamos
	// a utilizar luego para realizar la autenticación por Oauth2.
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.twitter.com/oauth2/token");

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);

		//Preparamos el password para la autenticación
		string userPwd = API_key + ":" + API_SecretKey;
		//Se lo seteamos a CURL.
		curl_easy_setopt(curl, CURLOPT_USERPWD, userPwd.c_str());

		struct curl_slist *list = NULL;

		//Le decimos a CURL que vamos a mandar URLs codificadas y además en formato UTF8.
		list = curl_slist_append(list, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

		//Le decimos a CURL que trabaje con credentials.
		string data = "grant_type=client_credentials";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

		//Le decimos a curl que cuando haya que escribir llame a myCallback
		//y que use al string readString como user data.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readString);

		// Con lo de abajo le decimos a curl que intente conectarse a la página
		res = curl_easy_perform(curl);

		// Nos fijamos si hubo algún error
		if (res != CURLE_OK)
		{
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			//Hacemos un clean up de curl antes de salir.
			curl_easy_cleanup(curl);
			return nullptr;
		}
	

		// Si no hubo errores hago un clean up antes de realizar un nuevo query.
		curl_easy_cleanup(curl);

		//Si el request de CURL fue exitoso entonces twitter devuelve un JSON
		//Abajo busco el token en el JSON para luego acceder a los twits.
		j = json::parse(readString);

		try
		{
			//Tratamos de acceder al campo acces_token del JSON
			std::string aux = j["access_token"];
			token = aux;
			std::cout << "Bearer Token get from Twitter API: \n" << token << std::endl;
		}
		catch (std::exception& e)
		{
			//Si hubo algun error, se muestra el error que devuelve la libreria
			std::cerr << e.what() << std::endl;
			return nullptr;
		}
	}
	else
	{
		cout << "Unable to get token. Unable to start cURL" << endl;
		return nullptr;
	}

	//Una vez obtenido el Token, voy a buscar los Twits

	/************************************************************************************
	*                        Get Tweets from the Twitter API							*
	************************************************************************************/

	curl = curl_easy_init();
	multiHandle = curl_multi_init();
	readString = "";
	int stillRunning = 0;
	if ((curl != NULL) & (multiHandle != NULL))
	{
		//Attacheo el easy handle para manejar una coneccion no bloqueante.
		curl_multi_add_handle(multiHandle, curl);

		//Seteamos URL FOLLOWLOCATION y los protocolos a utilizar igual que antes.
		curl_easy_setopt(curl, CURLOPT_URL, query.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);

		//Construimos el Header de autenticacion como lo especifica la API
		//usando el token que obtuvimos antes
		struct curl_slist *list = NULL;
		std::string aux = "Authorization: Bearer ";
		aux = aux + token;
		list = curl_slist_append(list, aux.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

		//Seteamos los callback igual que antes
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readString);

		//Realizamos ahora un perform no bloqueante
		curl_multi_perform(multiHandle, &stillRunning);
		while (stillRunning)
		{
			curl_multi_perform(multiHandle, &stillRunning);
			//loading();
																						//ACA IRIA EL "LOADING..."
		}

		//Checkeamos errores
		if (res != CURLE_OK)
		{
			cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
			//Hacemos un clean up de curl antes de salir.
			curl_easy_cleanup(curl);
			return nullptr;
		}

		//Siempre realizamos el cleanup al final
		curl_easy_cleanup(curl);

		//Si el request de CURL fue exitoso entonces twitter devuelve un JSON
		//con toda la informacion de los tweets que le pedimos
		j = json::parse(readString);
		try
		{
			//Al ser el JSON un arreglo de objetos JSON guardo cada tweet en la lista de tweets
			for (auto element : j)
			{																									//SI VAN A CAMBIAR ALGO, SE CAMBIA ACA.
				tweets->push_back(Tweet(element["name"], element["screen_name"], element["text"], element["created_at"], true));
			}
			std::cout << "Tweets retrieved from Twitter account " << std::endl;
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			delete tweets;
		}
	}
	else
	{
		cout << "Cannot download tweets. Unable to start cURL" << endl;
		delete tweets;
	}

	return tweets;
}

void DestroyTweets(list<Tweet>& lista)
{
	delete &lista;
}


//Concatena lo recibido en content a s
static size_t myCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	char* data = (char *)contents;
	string* s = (string*)userp;
	s->append(data, realsize);
	return realsize;
}
