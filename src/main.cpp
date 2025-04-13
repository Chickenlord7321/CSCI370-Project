/**
 * Author: Caleb Bronn
 * Last Update: 10 Apr 2025
 * Title: Movie Review Database App Project
 * Class: CSCI 370

 *! TODO: UPDATE THIS!!!
 */

/**
 * TODO: Create separate file for adding movies to database. Use csv insert file as a template

 * TODO: Top-level structure:
 *	# Server 
		* connects to Oracle and does all the SQL stuff
		* Contains pre-written SQL statements that can be added onto/filled out.
		* Gives user options for using the application
		* Features:
			*? Writes results to html file? 
			* Only problem is they're not directly accessible from Otter. 
			* Users will have to scp the html files to their own machines for viewing.
			*? Also possible to write results to markdown file? Same issues tho.
			* On top of that, not everyone has a markdown extension.

		* Commands:
		* //TODO: login
		* //TODO: logout
		* //TODO: sign up
		* //TODO: write a review
		* //TODO: update a review
		* TODO: look up reviews in database
			* TODO: all
			* TODO: recent reviews
			* TODO: written by you
			* TODO: having minimum/maximum stars
			* TODO: by search term
		* TODO: look up movies in database	
			* TODO: all
			* TODO: by search term
			* TODO: recently released
			* TODO: having minimum/maximum stars
			* TODO: have reviews
			* TODO: have no reviews
 *	# Main 
		* Provides access to the app
		* Manages user input
*/

#include "../include/server.hpp"
#include <unistd.h>		// for getpass()
#include <ctype.h>		// for toupper() and tolower()
#include <cstdlib>		// for exit()
#include <limits>		// for max streamsize
#include <iostream>
#include <string>
	using namespace std;
#include <fstream>		// for file writing/appending
	using std::ofstream;
	using std::ifstream;
	using std::ios;

// HMLT stuff
string HTML_HEADER = "<!DOCTYPE html>"
					"<html lang='en'>"
					"<head><meta charset='utf-8'><title>Movie Review App</title>"
					"<link rel='stylesheet' href='css/style.css'></head>"
					"<body><h1>Movie Review App</h1>";
string HTML_CLOSE = "</body></html>";

// Global Server
Server svr;


/***************************
 * STRING HELPER FUNCTIONS *
 ***************************/

// Convert string to lowercase
string to_lower(string s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}
	return s;
}

// Convert string to uppercase
string to_upper(string s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = toupper(s[i]);
	}
	return s;
}

/****************************
 * MOVIE REVIEW APP COMMAND *
 *  INPUT HELPER FUNCTIONS  *
 ****************************/

string input_str(const string msg) {
	string input = "";
	cout << msg;
	getline(cin, input);
	if (to_lower(input) == "q") {
		cout << "Goodbye!" << endl;
		exit(0);
	}
	return input;
}

double input_double(const string msg, const double min, const double max) {
	double answer = 0.0;
	string throwaway;
	cout << msg;

	// cin has a flag that reads as false if the user input is not of the correct data type.
	// We exploit that flag in this while loop. Credit to Prof. Bette Bultena for showing me 
	// this trick in CSCI 159!
	while (!(cin >> answer) || answer < min || answer > max) {
		// Clear out the buffer
		cin.clear();
		getline(cin, throwaway);

		// Quit if user types 'Q'
		if (to_lower(throwaway) == "q") {
			cout << "Goodbye!" << endl;
			exit(0);
		}
		cout << "\nSorry, that was not a valid input. Please try again\n> ";
	}
	// Clear out buffer again for the next time this function is called.
	cin.clear();
	getline(cin, throwaway);
	return answer;
}


int input_int(const string msg, const int min, const int max) {
	int answer;
	string throwaway;
	cout << msg;

	// if the user does not input an integer, prompt them to try again.
	while (!(cin >> answer) || answer < min || answer > max) {
		// Clean out cin and the buffer.
		cin.clear();
		getline(cin, throwaway);

		// Quit if user types 'Q'
		if (to_lower(throwaway) == "q") {
			cout << "Goodbye!" << endl;
			exit(0);
		}
		cout << "Sorry, that was not a valid integer. Please try again\n> ";
	}
	// Clean out buffer again.
	cin.clear();
	getline(cin, throwaway);
	return answer;
}


string input_password(const char* msg) {
	return string(getpass(msg));
}


/****************************
 * MORE HELPER FUNCTION FOR *
 *   LARGE BLOCKS OF CODE   *
 ****************************/

string write_review_from_file() {
	ifstream review_file;
	do {
		string filename = input_str("Enter file path (relative or absolute)\n> ");
		try {
			review_file.open(filename);
		} 
		catch (ifstream::failure& fail) {
			cout << "Sorry, that file doesn't seem to exist. Please try again.\n";
		}
	} while (!review_file.is_open());

	// Dump contents of file into this string.
	string new_review;
	getline(review_file, new_review, static_cast<char>(EOF));	// EOF is End Of File
	review_file.close();
	return new_review;
}

string write_review_in_terminal(const string original_review = "") {
	if (original_review != "") {
		cout << "Here is your original review:\n";
		cout << original_review << endl << endl;
	}
	cout << "Write your review here. Press Enter twice to end the review:\n";

	// Here we get use a while loop to get multiple lines of input. I struggled with this a lot,
	// why on earth does cin have to be such a bitch.....
	// Anyway, the code is based on this GeeksForGeeks article:
	// https://www.geeksforgeeks.org/take-multiple-line-string-input-in-cpp/
	string new_review;
	string line;
	while (getline(cin, line)) {
		if (line.empty()) {
			break;
		}
		new_review += line;
	}
	return new_review;
}


void write_reviews_to_html(vector<unordered_map<string, string>> results, const string filename) {
	ofstream file;
	string file_path = "../Output/" + filename;
	file.open(file_path);
	if (!file.is_open() || file.fail()) {
		cout << "Could not open file\n";
	}
	file << HTML_HEADER;
	for (int i = 0; i < results.size(); i++) {
		file << "<h2 class='title'>" << results.at(i).at("title") << "</h2>"
			<< "<h3 class='date'>" << results.at(i).at("written") << "</h3>"
			<< "<h3 class='author'>" << results.at(i).at("username") << "</h3>"
			<< "<p class='score'>" << results.at(i).at("your_score") << "</p>"
			<< "<p class='score'>" << results.at(i).at("user_avg_score") << "</p>"
			<< "<p class='score'>" << results.at(i).at("tmdb_score") << "</p>"
			<< "<p class='review'>" << results.at(i).at("review_text") << "</p>"
			<< "<img src='" << results.at(i).at("poster_path") << "'>";
	}
	file << HTML_CLOSE;
	file.close();
}

void write_movies_to_html(vector<unordered_map<string, string>> results, const string filename) {
	ofstream file;
	string file_path = "../Output/" + filename;
	file.open(file_path);
	if (!file.is_open() || file.fail()) {
		cout << "Could not open file\n";
	}
	file << HTML_HEADER;
	for (int i = 0; i < results.size(); i++) {
		file << "<h2 class='title'>" << results.at(i).at("title") << "</h2>"
			<< "<h3 class='date'>" << results.at(i).at("release_date") << "</h3>"
			<< "<h3 class='original_lang'>" << results.at(i).at("lang") << "</h3>"
			<< "<p class='score'>" << results.at(i).at("user_avg_score") << "</p>"
			<< "<p class='score'>" << results.at(i).at("tmdb_score") << "</p>"
			<< "<p class='overview'>" << results.at(i).at("overview") << "</p>"
			<< "<img src='" << results.at(i).at("poster_path") << "'>";
	}
	file << HTML_CLOSE;
	file.close();
}



int main () {
	cout << "Welcome to the Movie Review App!\n\n";

	// Get credentials for Oracle database
	cout << "First, you will need to enter your Oracle Database credentials.\n";
	string oracle_username;
	string oracle_password;
	do {
		oracle_username = input_str("Enter Oracle username: ");
		oracle_password = input_password("Enter Oracle password: ");
	} while (!svr.connect(oracle_username, oracle_password));
	cout << "Credentials verified!\n";
	

	int command;
	bool app_running = true;
	while (app_running) {
		cout << "\nSelect one of the following commands by number.\n"
			<< "Or, type 'Q' at any time to quit:\n"
			<< "\t1: login\n"
			<< "\t2: logout\n"
			<< "\t3: sign up\n"
			<< "\t4: write a review\n"
			<< "\t5: update a review\n"
			<< "\t6: look up reviews\n"
			<< "\t7: look up movies\n";
		command = input_int("> ", 1, 7);
		
		//# LOGIN
		if (command == 1) {
			string username;
			string password;
			bool logged_in;
			do {
				username = input_str("Enter your username: ");
				password = input_password("Enter your password: ");
				logged_in = svr.login_successful(username, password);
				if (logged_in) {
					cout << "Login successful!\n";
				} 
				else { 
					cout << "Sorry, the username or password was incorrect.\n"; 
				}
			} while (!logged_in);
		}

		//# LOGOUT
		else if (command == 2) {
			svr.logout();
			cout << "\nLogout successful!\n";
		}

		//# SIGN UP
		else if (command == 3) {
			string username;
			string password;
			bool signed_up;
			do {
				username = input_str("Choose a username: ");
				password = input_password("Choose a password: ");
			} while (!svr.signup_successful(username, password));
			cout << "\nYou've been successfully signed up, " << username << "!\n";
		}

		//# WRITE A REVIEW
		else if (command == 4) {
			// Step 1: search for a movie to review
			string movie_name = input_str("Search for a movie to review\n> ");
			vector<unordered_map<string, string>> results;
			try {
				results = svr.search_movies(movie_name);
				// No search results
				if (results.size() <= 0) {
					cout << "There were no results for your search. Perhaps it was misspelled?\n";
					continue;
				}
			} 
			// User was not logged in
			catch (ServerException& e) {
				cout << "Sorry, please log in first.\n";
				continue;
			}

			// Print out all movies that match the search term
			for (int i = 0; i < results.size(); i++) {
				cout << i << "\n" 
					<< "\tMovie Title: " << results.at(i).at("title") << endl
					<< "\tRelease Date: " << results.at(i).at("release_date") << endl
					<< "\tMovie Poster: " << results.at(i).at("poster_path") << endl;
			}
			int num = input_int("Select one of the results by number\n> ", 0, results.size() - 1);

			// Step 2: give movie a score
			double score = input_double("Give the movie a score out of 10\n> ", 0.0, 10.0);

			// Step 3: write and submit review
			int option;
			string review;
			option = input_int("Type 1 to submit your review from a text file, or 2 to write the review in this window.\n> ", 1, 2);
			if (option == 1) {
				review = write_review_from_file();
			} 
			else {
				review = write_review_in_terminal();
			}

			// Submit review. If user has already written a review for this movie, ask them if they want to update their review instead.
			int movie_id = stoi(results.at(num).at("movie_id"));
			if (!svr.submit_review(movie_id, review, score)) {
				string update_instead = to_lower(input_str("Would you like to update your review instead? Y/N\n> "));
				if (update_instead == "y" || update_instead == "yes") {
					svr.update_review(svr.find_review_by_curr_user(movie_id), review, score, movie_id);
				}
			}

			cout << "Thank you for uploading a review!\n";
		}

		//# UPDATE A REVIEW
		else if (command == 5) {
			string search_term = input_str("Search your reviews by movie title or phrase\n> ");
			vector<unordered_map<string, string>> results;
			try {
				results = svr.search_your_reviews(search_term);
				// If no search results
				if (results.size() <= 0) {
					cout << "There were no results for your search. Perhaps it was misspelled?\n";
					continue;
				}
			} 
			// User was not logged in
			catch (ServerException& e) {
				cout << "Sorry, please log in first.\n";
				continue;
			}

			// Print out all reviews that match the search term
			for (int i = 0; i < results.size(); i++) {
				cout << i << "\n" 
					<< "\tMovie Title: " << results.at(i).at("title") << endl
					<< "\tYour Score: " << results.at(i).at("your_score") << endl
					<< "\tYour Review: \n" << results.at(i).at("review_text") << endl;
			}
			int num = input_int("Select one of the results by number\n> ", 0, results.size() - 1);

			// Step 2: give movie a score
			double score = input_double("Give the movie a new score out of 10\n> ", 0.0, 10.0);

			// Step 3: write and submit review
			int option;
			string review;
			option = input_int("Type 1 to submit your review from a text file, or 2 to write the review in this window.\n> ", 1, 2);
			if (option == 1) {
				review = write_review_from_file();
			} 
			else {
				review = write_review_in_terminal(results.at(num).at("review_text"));
			}

			// Finally, update the review
			svr.update_review(
				results.at(num).at("review_id"), 
				review, 
				score, 
				stoi(results.at(num).at("movie_id"))
			);
		}

		//# LOOK UP REVIEWS
		else if (command == 6) {
			cout << "Select one of the following options by number:\n"
				<< "\t1: view all reviews\n"
				<< "\t2: view reviews written by you\n"
				<< "\t3: view reviews by search term\n";
			int option = input_int("> ", 1, 5);
			string filename;
			switch (option) {
				case 1:
					filename = "all.html";
					write_reviews_to_html(svr.list_all_reviews(), filename);
					break;
				case 2:
					string search_term = input_str("Enter your search term:\n> ");
					filename = "your_reviews.html";
					write_reviews_to_html(svr.search_your_reviews(search_term));
					break;
				case 3:
					string search_term = input_str("Enter your search term:\n> ");
					filename = search_term + ".html";
					write_reviews_to_html(svr.search_all_reviews(search_term));
					break;
			}
			cout << "Output written to: Output/" << filename
				<< "\nTo view the output, copy the 'Output' folder to your machine and drag " 
				<< filename << " into your web browser!\n";
		}

		//# LOOK UP MOVIES
		else if (command == 7) {
			// cout << "Select one of the following options by number:\n"
			// 	<< "\t1: all movies\n"
			// 	<< "\t2: recently released\n"
			// 	<< "\t3: having minimum/maximum stars\n"
			// 	<< "\t4: have no reviews\n"
			// 	<< "\t5: by search term\n";
			// int option = input_int("> ", 1, 5);
			// string filename;
			// switch (option) {
			// 	case 1:
			// 		filename = "all.html";
			// 		write_reviews_to_html(svr.list_all_reviews(), "all.html");
			// 		break;
			// 	case 2:
			// 		break;
			// 	case 3:
			// 		break;
			// 	case 4:
			// 		break;
			// 	case 5:
			// 		break;
			// }
			// cout << "Output written to: Output/" << filename
			// 	<< "\nTo view the output, copy the 'Output' folder to your machine and drag " 
			// 	<< filename << " into your web browser!\n";
		}
		//# INVALID COMMAND
		else {
			cout << "\nSorry, that was not a valid command.\n";
		}
	}	// end main while
	return 0;
}