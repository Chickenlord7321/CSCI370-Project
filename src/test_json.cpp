/**
 * Author: Caleb Bronn
 * Last update: 15 Mar 2025
 * This is my test file for nlohmann JSON and C++ Requests
*/

#include <iostream>
#include <fstream>						// for writing to csv file
	using namespace std;
#include "../include/nlohmann/json.hpp"	// for JSON conversion
	using json = nlohmann::json;		// Alias for nlohmann::json class
#include <cpr/cpr.h>					// for HTTP requests

int main() {
	/** NOTE:
		This is a raw string literal. It allows you to avoid escaping characters.
		It will render everything in side the delimiters as a pure string.
		Syntax: R"(content goes here)"
		
		e.g. 
		string str1 = "Caleb\nBronn";
		// output
		Caleb
		Bronn
		
		string str2 = R"(Caleb\nBronn)"
		// output
		Caleb\nBronn
	*/

	// Create raw string literal for json data
	string test = R"(
		{ "name": "Caleb", "age": 22 }
	)";

	// Parse the data into a json object we can use
	json result = json::parse(test);
	cout << result.type_name() << endl;

	// Print
	cout << "Attempting to access json data....\n\n";

	// Process into strings/ints first
	string name = result["name"];
	int age = result["age"];
	cout << "My name is " << name << endl;
	cout << "I am " << age << " years old\n";
	// Access directly from json object
	cout << "My name is " << result["name"] << endl;	// this prints "Caleb", not Caleb
	cout << "I am " << result["age"] << " years old\n";
	cout << result["name"].type_name() << endl;

	// Now trying cpr requests
	cout << "\nNow trying cpr requests\n\n";
	string api_key = "";
	cout << "Enter API key:\n> ";
	getline(cin, api_key)
	string movie = "lord of the rings";
	string search_endpoint = "https://api.themoviedb.org/3/search/movie";
	string img_endpoint = "https://image.tmdb.org/t/p/original/";

	// Make request
	cpr::Response resp = cpr::Get(cpr::Url{search_endpoint}, 
		cpr::Parameters{
			{"api_key", api_key}, 
			{"query", movie}
	});

	// Use nlohmann to parse the json string that we get from cpr
	cout << "Attempting to turn cpr request text into nlohmann object...\n";
	json data = json::parse(resp.text)["results"];

	// Print
	cout << "Status code: " << resp.status_code << endl;
	if (resp.status_code == 200) {
		cout << data[0] << endl;
	}
	else {
		cout << data["status_message"] << endl;
	}
	return 0;
}