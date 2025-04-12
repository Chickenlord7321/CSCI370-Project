/**
 * Author: Caleb Bronn
 * Last Update: 10 Apr 2025
 * Title: Movie Review Database App Project
 * Class: CSCI 370
 */

#ifndef SERVER_H
#define SERVER_H

#include <occi.h>  // main header for Oracle Call Interface
	using namespace oracle::occi;
#include <iostream>
#include <string>
#include <bits/stdc++.h>	// for vector
#include <unordered_map>
	using namespace std;


/**
 * ServerException is a very simple exception class that is thrown 
 * when something goes wrong in the Heap. All the implementation
 * for this class is done inline.
 */
class ServerException {
private:
	string location;
	string message;
	
public:

	/**
 	* Creates a ServerException object.
 	* @param where_thrown The origin of the member function that threw the exception.
 	* @param msg An indication of what the problem was that triggered the exception.
 	*/
	ServerException(const string& where_thrown, const string& msg) {
		location = where_thrown;
		message = msg;
	}

	/** 
	 * Provides a string version of the ServerException object.
	 * @return A debug message providing you with the location and a description of the 
	 * problem.
 	*/
	string to_string() const {
		return "*** ServerException in "+ location + ": "+ message;
	}

	/**
 	* Allows for a direct stream of the error message using the << operator.
 	* @param out The ostream object.
 	* @param he The ServerException to pass into the output stream.
 	* @return The ostream object that will print the debug info to the console.
 	*/
 	friend ostream& operator << (ostream& out, const ServerException& e) {
 		out << e.to_string();
		return out;
	}
}; // end of ServerException


/**
 * This Server class connects to the CSCI Oracle database and allows
 * users to place orders and unsubscribe from the Food Sharing program.
 */
class Server {
private:
	Environment* env;
	Connection* conn;

	// Default format for dates
	const string DATE_FORMAT = "YYYY-MM-DD";
	// Location of the Oracle database on CSCI servers
	const string DB_ADDRESS = "sunfire.csci.viu.ca";

	string curr_user;	// stores user ID of current logged-in user
	int next_user_id;
	int next_review_id;

	// SQL Queries
	string get_user_id_sql;

	// Query statements
	Statement* get_user_id_query;

	// Helper
	bool user_in_db(string username);

	int get_next_user_id();
	int get_next_review_id();

public:
	// Constructor
	Server();
	// Destructor
	~Server();

	/**
	 * @brief Connect to the database
	 * @param username Your username on Oracle
	 * @param password Your Oracle password
	 */
	bool connect(const string username, const string password);

	bool login_successful(const string username, const string password);

	void logout();

	void add_user(const string username, const string password);

	void add_review(const string review);

	void update_review(const string review);

	vector<unordered_map<string, string>> list_reviews_by_rating(const string op, const double rating, const string sort="ASC");

	vector<unordered_map<string, string>> list_movies_by_rating(const string op, const double rating, const string sort="ASC");
};

#endif