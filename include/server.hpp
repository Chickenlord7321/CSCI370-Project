/**
 * Author: Caleb Bronn
 * Last Update: 12 Apr 2025
 * Title: Movie Review Database App Project
 * Class: CSCI 370
 */

#ifndef SERVER_H
#define SERVER_H

#include <occi.h>  			// main header for Oracle Call Interface
	using namespace oracle::occi;
#include <iostream>
#include <string>
	using namespace std;
#include <bits/stdc++.h>	// for vector
	using std::vector;
#include <unordered_map>
	using std::unordered_map;


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
	string signup_sql;
	string submit_review_sql;
	string update_review_sql;
	string search_your_reviews_sql;
	string find_review_sql;
	string search_movies_sql;

	// Query statements
	Statement* get_user_id_query;
	Statement* signup_query;
	Statement* submit_review_query;
	Statement* update_review_query;
	Statement* search_your_reviews_query;
	Statement* find_review_query;
	Statement* search_movies_query;

	int get_next_user_id();
	int get_next_review_id();

	// List all data from movie result set
	vector<unordered_map<string, string>> list_movies(ResultSet* result);

	// List all reviews that match search term, and written by current user
	vector<unordered_map<string, string>> list_reviews(ResultSet* result);

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

	bool signup_successful(const string username, const string password);

	bool submit_review(const int movie_id, const string review, const double score);

	bool update_review(const string review_id, const string review, const double score);

	string find_review_by_curr_user(const int movie_id) const;

	// Find movies by search term
	vector<unordered_map<string, string>> search_movies(const string search_term);

	vector<unordered_map<string, string>> search_your_reviews(const string search_term);

	// vector<unordered_map<string, string>> list_reviews_by_rating(const string op, const double rating, const string sort="ASC");

	// vector<unordered_map<string, string>> list_movies_by_rating(const string op, const double rating, const string sort="ASC");
};

#endif