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

	// Init queries
	get_user_id_sql = "SELECT user_id FROM Users WHERE username = :u AND password = :p";

	// Set statements to null
	get_user_id_query = nullptr;
}

// Destructor
Server::~Server() {
	// Terminate connection only if it's not null
	// We do this in case the try-catch fails to establish a connection in the constructor.
	if (conn) {
		// ! Terminate statements
		conn->terminateStatement(get_user_id_query);
		env->terminateConnection(conn);
	}
	Environment::terminateEnvironment(env);
}

// Connect to the server
bool Server::connect(const string username, const string password) {
	env = Environment::createEnvironment();
	try {
		conn = env->createConnection(username, password, DB_ADDRESS);

		//! Create statements for each member function
		get_user_id_query = conn->createStatement(get_user_id_sql);
		return true;	// successful connection
	} catch (SQLException & error) {
		cout << error.what();
		cout << "\nUsername or Password was incorrect, could not connect\n\n";
		return false;	// unsuccessful connection
	}
}

string get_user_id(const string username, const string password) const{
	get_user_id_query->setString(1, username);
	get_user_id_query->setString(2, password);
	ResultSet* result = get_user_id_query->executeQuery();
	if (result->next()) {
		return result->getString(1);
	} else {
		throw ServerException("get_user_id", "user not in DB");
	}
}