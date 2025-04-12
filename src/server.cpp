/**
 * Author: Caleb Bronn
 * Last Update: 10 Apr 2025
 * Title: Movie Review Database App Project
 * Class: CSCI 370
 */

#include "../include/server.hpp"

// Constructor
Server::Server() {
	env = nullptr;
	conn = nullptr;
	// Empty curr_user represents the concept of being logged out
	curr_user = "";
	next_user_id = "";
	next_review_id = "";

	// Init queries
	get_user_id_sql = "SELECT user_id FROM Users WHERE username = :u AND password = :p";

	// Set statements to null
	get_user_id_query = nullptr;
}

// Destructor
Server::~Server() {
	// Terminate connection only if it's not null
	// We do this in case the try-catch in connect() fails to establish a connection
	if (conn) {
		// ! Terminate statements
		conn->terminateStatement(get_user_id_query);
		env->terminateConnection(conn);
	}
	Environment::terminateEnvironment(env);
}

/****************************
 * PRIVATE SERVER FUNCTIONS *
 ****************************/

int Server::get_next_user_id() {
	string next_id_sql = "SELECT user_id FROM Users WHERE ROWNUM = 1 ORDER BY user_id DESC";
	Statement* next_id_query = conn->createStatement(next_id_sql);
	ResultSet* next_id_rs = next_id_query->executeQuery();
	next_id_rs->next();
	return next_id_rs->getInt(1);
}

int Server::get_next_review_id() {
	string next_id_sql = "SELECT review_id FROM Reviews WHERE ROWNUM = 1 ORDER BY review_id DESC";
	Statement* next_id_query = conn->createStatement(next_id_sql);
	ResultSet* next_id_rs = next_id_query->executeQuery();
	next_id_rs->next();
	return next_id_rs->getInt(1);
}

/***************************
 * PUBLIC SERVER FUNCTIONS *
 ***************************/

// Connect to the server
bool Server::connect(const string username, const string password) {
	env = Environment::createEnvironment();
	try {
		conn = env->createConnection(username, password, DB_ADDRESS);

		// Set the next available user/review IDs
		next_user_id = get_next_user_id();
		next_review_id = get_next_review_id();

		//! Create statements for each member function
		get_user_id_query = conn->createStatement(get_user_id_sql);

		return true;	// successful connection
	} catch (SQLException & error) {
		cout << error.what();
		cout << "\nUsername or Password was incorrect, could not connect\n\n";
		return false;	// unsuccessful connection
	}
}


bool Server::login_successful(const string username, const string password) {
	get_user_id_query->setString(1, username);
	get_user_id_query->setString(2, password);
	ResultSet* result = get_user_id_query->executeQuery();
	if (result->next()) {
		curr_user = result->getString(1);
		get_user_id_query->closeResultSet(result);
		cout << "Login successful!\n";
		return true;
	} else {
		get_user_id_query->closeResultSet(result);
		cout << "Sorry, the username or password was incorrect.\n";
		return false;
	}
}


void Server::logout() {
	curr_user = "";
}