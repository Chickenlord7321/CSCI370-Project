/**
 * Author: Caleb Bronn
 * Last update: 15 Mar 2025
*/

#include <iostream>
#include <fstream>						// for writing to csv file
	using namespace std;
#include "../include/nlohmann/json.hpp"	// for JSON conversion
	using json = nlohmann::json;		// Alias for nlohmann::json class
#include <cpr/cpr.h>					// for HTTP requests

// Get integer input from user
int get_int(string question, int max = INT_MAX) {
	int answer;
	string throwaway;

	// Ask the question to the user.
	cout << question;

	// if the user does not input an integer, prompt them to try again.
	while (!(cin >> answer) || answer > max) {
		cout << "Sorry, that was not a valid integer. Please enter a number: ";

		// Clean out cin and the buffer.
		cin.clear();
		getline(cin, throwaway);
	}
	// Clean out buffer again.
	cin.clear();
	getline(cin, throwaway);

	return answer;
}


int main() {
	// API stuff
	string api_key = "ad870395164b3e4a76c9da7a495fd4ee";
	const string SEARCH_ENDPOINT = "https://api.themoviedb.org/3/search/movie";
	const string IMG_ENDPOINT = "https://image.tmdb.org/t/p/original";

	ofstream file;
	// Open sample.csv (and create it if it doesn't exist)
	// using ios::out allows us to read from the file, whereas ios::app allows us to append to the file
	file.open("Data/sampleMovies.csv", ios::out | ios::app);

	string input = "";
	while (input != "q") {
		// Prompt user
		cout << "Search for movie (or type q to quit): \n> ";
		getline(cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);

		// Check for quit
		if (input == "q") {
			continue;
		}
		// Make HTTP request
		cpr::Response resp = cpr::Get(cpr::Url{SEARCH_ENDPOINT}, 
			cpr::Parameters{
				{"api_key", api_key}, 
				{"query", input}
		});
		json data = json::parse(resp.text);

		// Check status code
		if (resp.status_code != 200) {
			cout << "Status error: " << resp.status_code << endl;
			cout << data["status_message"] << endl;
			continue;
		}

		// Present all options to user
		int max_options = 0;
		for (auto& item : data["results"].items()) {
			cout << item.key() << endl;
			// In case there is a null value, we use a try-catch block
			try {
				cout << "\t" << item.value()["original_title"].get<string>() << endl;
				cout << "\t(" << item.value()["release_date"].get<string>() << ")\n";
				cout << "\t" << IMG_ENDPOINT + item.value()["poster_path"].get<string>() << endl;
			} catch (nlohmann::detail::type_error& e) {
				cout << "\t" << e.what() << endl;
			}
			max_options++;
		}
		// Promt user for number
		int num = get_int("Select a movie by number: \n> ", max_options);

		// Input all relevant data from selection into csv file
		cout << "Inserting data into csv...\n";
		json info = data["results"][num];
		file << info["id"] << ","								// movie_id
			<< info["title"] << ","								// title
			<< info["overview"] << ","							// overview
			<< info["original_language"].get<string>() << ","	// lang
			<< IMG_ENDPOINT << info["backdrop_path"].get<string>() << ","	// bg_path
			<< IMG_ENDPOINT << info["poster_path"].get<string>() << ","		// poster_path
			<< info["vote_average"] << ","						// tmdb_score
			<< "NULL" << ","									// user_avg_score
			<< info["release_date"].get<string>()				// release_date
			<< "\n";
		
		cout << "Movie successfully added!\n\n";
	}
	file.close();
	return 0;
}