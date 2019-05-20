#include "Twit.h"

int month_number(string month);

Twit::Twit()
{
	name = nullptr;
	date = nullptr;
	time = nullptr;
	text = nullptr;
}
Twit::Twit(string j)
{
	json parsed_j = json::parse(j);

	string name_aux = parsed_j["screen_name"];
	name = "@" + name_aux;

	string date_aux = parsed_j["created_at"];		//"Mon May 06 20:01:29 +0000 2019" --> dd/mm/aa y hh:mm
	time = date_aux.substr(10, 5);
	int num = month_number(date_aux.substr(4, 3));
	if (num != 0)
	{
		date = date_aux.substr(7, 2) + "/" + to_string(num) + "/" + date_aux.substr(27);
	}
	else
	{
		date = nullptr;
	}
	
	string text_aux = parsed_j["text"];
	text = text_aux;
}

string
Twit::get_date()
{
	return date;
}

string
Twit::get_name()
{
	return name;
}

string
Twit::get_time()
{
	return time;
}

string
Twit::get_text()
{
	return text;
}

void
Twit::set_date(string date)
{
	this->date = date;
}

void
Twit::set_name(string name)
{
	this->name = name;
}

void
Twit::set_text(string text)
{
	this->text = text;
}

void
Twit::set_time(string time)
{
	this->time = time;
}

int month_number(string month)
{
	if (month == "Jan")
	{
		return 1;
	}
	else if (month == "Feb")
	{
		return 2;
	}
	else if (month == "Mar")
	{
		return 3;
	}
	else if (month == "Apr")
	{
		return 4;
	}
	else if (month == "May")
	{
		return 5;
	}
	else if (month == "Jun")
	{
		return 6;
	}
	else if (month == "Jul")
	{
		return 7;
	}
	else if (month == "Aug")
	{
		return 8;
	}
	else if (month == "Sep")
	{
		return 9;
	}
	else if (month == "Oct")
	{
		return 10;
	}
	else if (month == "Nov")
	{
		return 11;
	}
	else if (month == "Dec")
	{
		return 12;
	}
	else
	{
		return 0;
	}
}