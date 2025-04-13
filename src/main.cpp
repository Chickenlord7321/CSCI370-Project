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
		* TODO: write a review
		* TODO: update a review
		* TODO: look up reviews in database
			* TODO: all (no order)
			* TODO: sort by date written
			* TODO: written by you
			* TODO: having minimum/maximum stars
			* TODO: by movie
		* TODO: look up movies in database	
			* TODO: all (no order)
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
#include <iostream>
#include <string>
	using namespace std;
#include <fstream>		// for file writing/appending
	using std::ofstream;
	using std::ifstream;
	using std::ios;

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
	string input;
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
		cout << "\nSorry, that was not a valid input. Please try again\n> ";
		// Clear out the buffer
		cin.clear();
		getline(cin, throwaway);
		if (to_lower(throwaway) == "q") {
			cout << "Goodbye!" << endl;
			exit(0);
		}
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
		cout << "Sorry, that was not a valid integer. Please try again\n> ";

		// Clean out cin and the buffer.
		cin.clear();
		getline(cin, throwaway);
		if (to_lower(throwaway) == "q") {
			cout << "Goodbye!" << endl;
			exit(0);
		}
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


int main () {
	// ! intro goes here

	// Get credentials for Oracle database
	cout << "First, you will need to enter your Oracle Database credentials.\n";
	string oracle_username;
	string oracle_password;
	do {
		oracle_username = input_str("Enter Oracle username: ");
		oracle_password = input_password("Enter Oracle password: ");
	} while (!svr.connect(oracle_username, oracle_password));
	cout << "Credentials verified!\n";
	

	string command;
	while (command != "q") {
		cout << "Select one of the following commands by number.\n"
			<< "Or, type 'Q' at any time to quit:\n"
			<< "1:\tlogin\n"
			<< "2:\tlogout\n"
			<< "3:\tsign up\n"
			<< "4:\twrite a review\n"
			<< "5:\tupdate a review\n"
			<< "6:\tlook up reviews\n"
			<< "7:\tlook up movies\n";
		command = to_lower(input_str("> "));
		
		//# LOGIN
		if (command == "1") {
			string username;
			string password;
			bool logged_in;
			do {
				username = input_str("Enter your username: ");
				password = input_password("Enter your password: ");
				logged_in = svr.login_successful(username, password);
				if (logged_in) {
					cout << "\nLogin successful!\n";
				} 
				else { 
					cout << "Sorry, the username or password was incorrect.\n"; 
				}
			} while (!logged_in);
		}

		//# LOGOUT
		else if (command == "2") {
			svr.logout();
			cout << "\nLogout successful!\n";
		}

		//# SIGN UP
		else if (command == "3") {
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
		else if (command == "4") {
			string movie_name = input_str("Search for a movie to review\n> ");
			vector<unordered_map<string, string>> results = svr.search_movies(movie_name);
			for (int i = 0; i < results.size(); i++) {
				cout << i << "\n" 
					<< "\t" << results.at(i).at("title") << endl
					<< "\t" << results.at(i).at("release_date") << endl;
			}
			int num = input_int("Select one of the results by number\n> ", 0, results.size() - 1);

			double score = input_double("Give the movie a score out of 10\n> ", 0.0, 10.0);
			// do {
			// 	option = input_str("Type 1 to submit your review from a text file, or 2 to write the review in this window.\n> ");
			// 	if (option == "1") {
			// 		string filename = input_str("Enter path to the text file containg your review\n> ");
			// 		ifstream review_file(filename);
			// 		if (review_file.fail()) {
			// 			cout << "\nSorry, " << filename << " does not exist.\n";
			// 			continue;
			// 		}
					
			// 	} 
			// 	else if (option == "2") {

			// 	}
			// 	else {
			// 		cout << "\nSorry, that was not a valid option.\n";
			// 	}
			// } while (option != "q")
		}

		//# UPDATE A REVIEW
		else if (command == "5") {
			cout << "update a review\n";
		}
		//# LOOK UP REVIEWS
		else if (command == "6") {
			cout << "look up reviews\n";
		}
		//# LOOK UP MOVIES
		else if (command == "7") {
			cout << "look up movies\n";
		}
		//# INVALID COMMAND
		else {
			cout << "\nSorry, that was not a valid command.\n";
		}
	}	// end main while
	return 0;
}