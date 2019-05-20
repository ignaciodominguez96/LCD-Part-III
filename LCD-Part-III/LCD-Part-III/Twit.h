#include <nlohmann/json.hpp> 
#include <string>

using json = nlohmann::json;
using namespace std;
class Twit
{
public:
	Twit();
	Twit(string j);
	string get_name();
	string get_date();
	string get_time();
	string get_text();

	void set_name(string name);
	void set_date(string date);
	void set_time(string time);
	void set_text(string text);
private:
	string name;
	string date;
	string time;
	string text;
};
