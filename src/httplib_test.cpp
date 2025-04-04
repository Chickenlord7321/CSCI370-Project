//! Header comment

// Enable HTTPS support
// #ifndef CPPHTTPLIB_OPENSSL_SUPPORT
// 	#define CPPHTTPLIB_OPENSSL_SUPPORT
// #endif

#include "../include/httplib.h"		// library for HTTPS requests
#include <iostream>
#include <fstream>						// for writing to csv file
	using namespace std;
#include "../include/nlohmann/json.hpp"	// for JSON conversion
	using json = nlohmann::json;		// Alias for nlohmann::json class

int main () {
	// API stuff
	const string API_KEY = "ad870395164b3e4a76c9da7a495fd4ee";
	const string TMDB_SEARCH_URL = "http://api.themoviedb.org";
	const string SEARCH_ENDPOINT = "/3/search/movie";
	const string TMDB_IMG_URL = "http://image.tmdb.org";
	const string IMG_ENDPOINT = "/t/p/original";
	
	// HTTP server for requests
	httplib::Client SearchClient(TMDB_SEARCH_URL);
	httplib::Client ImgClient(TMDB_IMG_URL);

	string input = "";
	while (input != "q") {
		// Prompt user
		cout << "Search for movie (or type q to quit): \n> ";
		getline(cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);

		// Check for quit
		if (input == "q") {
			break;
		}
		// Make HTTP request
		string url = TMDB_SEARCH_URL + SEARCH_ENDPOINT + "?api_key=" + API_KEY + "&query=" + input;
		cout << url << endl;
		auto res = SearchClient.Get(url);

		if(res) {
			cout << "Status: " << res->status << endl;
		}
		else {
			cout << "Get request failed :(\n";
		}
	}

	return 0;
}
