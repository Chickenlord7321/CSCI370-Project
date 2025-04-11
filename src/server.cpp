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
	sql = "";

	// Set statements to null
	query = nullptr;
}

// Destructor
Server::~Server() {
	// Terminate connection only if it's not null
	// We do this in case the try-catch fails to establish a connection in the constructor.
	if (conn) {
		conn->terminateStatement(query);
		env->terminateConnection(conn);
	}
	Environment::terminateEnvironment(env);
}

// Connect to the server
bool Server::connect(const string username, const string password) {
	env = Environment::createEnvironment();
	try {
		conn = env->createConnection(username, password, DB_ADDRESS);
		cout << "\nSuccessfully connected to the database!\n\n";

		// Create statements for each member function
		query = conn->createStatement(sql);
		return true;	// successful connection
	} catch (SQLException & error) {
		cout << error.what();
		cout << "\nUsername or Password was incorrect, could not connect\n\n";
		return false;	// unsuccessful connection
	}
}