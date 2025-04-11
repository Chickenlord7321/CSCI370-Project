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

	// Queries
	string sql;

	// Query statements
	Statement* query;

	// Helper
	bool user_in_db(string username);

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

	void add_user(const string username, const string password);

	void add_review(const string review);

	void update_review(const string review);

	vector<unordered_map<string, string>> list_reviews_by_rating(const string op, const double rating, const string sort="ASC");

	vector<unordered_map<string, string>> list_movies_by_rating(const string op, const double rating, const string sort="ASC");
};

#endif