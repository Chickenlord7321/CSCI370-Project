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
 *	# App 
		* Gives user options for using the application:
		* Features:
			*? Writes results to html file? 
			* Only problem is they're not directly accessible from Otter. 
			* Users will have to scp the html files to their own machines for viewing.
			*? Also possible to write results to markdown file? Same issues tho.
			* On top of that, not everyone has a markdown extension.

		* Commands:
		* TODO: login
		* TODO: logout
		* TODO: sign up
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
			* TODO: recently released
			* TODO: having minimum/maximum stars
			* TODO: have reviews
			* TODO: have no reviews
 *	# Main 
		* Provides access to the app
*/

#include "../include/server.hpp"
#include <unistd.h>		// for getpass()
#include <regex>		// for string parsing
#include <ctype.h>		// for toupper() and tolower()
#include <cstdlib>		// for exit()
#include <iostream>
#include <string>
	using namespace std;

// Global Server
Server svr;


/***************************
 * STRING HELPER FUNCTIONS *
 ***************************/

// Convert string to lowercase
string to_lower(string& s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}
	return s;
}

// Convert string to uppercase
string to_upper(string& s) {
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
		svr.disconnect();
		cout << "Goodbye!" << endl;
		exit(0);
	}
	return input;
}

string input_password(const string msg) {
	return string(getpass(msg));
}


int main () {
	// ! intro goes here

	// Get credentials for Oracle database
	cout << "First, you will need to enter your Oracle Database credentials.\n";
	do {
		string username = input_str("Enter Oracle username: ");
		string password = input_password("Enter Oracle password: ");
	} while (!svr.connect(username, password););
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
		
		if (command == "1") {			// login
			string username;
			string password;
			do {
				username = input_str("Enter your username: ");
				password = input_password("Enter your password: ");
			} while (!svr.login_successful(username, password));
		}
		else if (command == "2") {		// logout
			svr.logout();
			cout << "Logout successful!\n";
		}
		else if (command == "3") {		// sign up
			cout << "sign up\n";
		}
		else if (command == "4") {		// write review
			cout << "write a review\n";
		}
		else if (command == "5") {		// update review
			cout << "update a review\n";
		}
		else if (command == "6") {		// look up reviews
			cout << "look up reviews\n";
		}
		else if (command == "7") {		// look up movies
			cout << "look up movies\n";
		}
		else {
			cout << "\nSorry, that was not a valid command.\n";
		}
	}	// end while command != "q"

	svr.disconnect();
	return 0;
}