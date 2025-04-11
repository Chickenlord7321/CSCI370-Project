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

#include "../include/app.hpp"
#include <ctype.h>		// for toupper() and tolower()

// Convert string to lowercase
void to_lower(string& s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}
}

// Convert string to uppercase
void to_upper(string& s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = toupper(s[i]);
	}
}

int main () {
	// ! intro goes here

	MovieReviewApp app;
	app.get_credentials();

	string command;
	while (command != "q") {
		cout << "Select one of the following commands by number.\n"
			<< "Or, type 'Q' to quit:\n"
			<< "1:\tlogin\n"
			<< "2:\tlogout\n"
			<< "3:\tsign up\n"
			<< "4:\twrite a review\n"
			<< "5:\tupdate a review\n"
			<< "6:\tlook up reviews\n"
			<< "7:\tlook up movies\n";
		cout << "> ";
		getline(cin, command);
		to_lower(command);

		string username;
		string password;
		
		if (command == "1") {			// login
			while(!app.login()) {
				cout << "Login failed. Please try again\n";
			};
		}
		else if (command == "2") {		// logout
			cout << "logout\n";
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
		else if (command == "q") {		// terminate program
			cout << "Goodbye!\n";
		} 
		else {
			cout << "\nSorry, that was not a valid command.\n";
		}
	}	// end while

	return 0;
}