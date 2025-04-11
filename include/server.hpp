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

	// Helper
	bool user_in_db(string username);

	void add_review(string review);

	void update_review(string review);

	
};

#endif