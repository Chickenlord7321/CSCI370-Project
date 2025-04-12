/**
 * Author: Caleb Bronn
 * Last Update: 12 Apr 2025
 * Title: Movie Review Database App Project
 * Class: CSCI 370

 * TODO: write header comments for each function!
 */

#include "../include/server.hpp"
#include <regex>	// for string parsing

// Constructor
Server::Server() {
	env = nullptr;
	conn = nullptr;
	// Empty curr_user represents the concept of being logged out
	curr_user = "";
	next_user_id = next_review_id = 0;

	// Init queries
	get_user_id_sql = "SELECT user_id FROM Users WHERE username = :u AND password = :p";
	signup_sql = "INSERT INTO Users VALUES (" 
				" ':id',"
				" :uname,"
				" :psswd,"
				" CURRENT_DATE"
				" )";

	// Set statements to null
	get_user_id_query = nullptr;
	signup_query = nullptr;
}

// Destructor
Server::~Server() {
	// Terminate connection only if it's not null
	// We do this in case the try-catch in connect() fails to establish a connection
	if (conn) {
		// ! Terminate statements
		conn->terminateStatement(get_user_id_query);
		conn->terminateStatement(signup_query);
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

//! Connect to the server
bool Server::connect(const string username, const string password) {
	env = Environment::createEnvironment();
	try {
		conn = env->createConnection(username, password, DB_ADDRESS);

		// Set the next available user/review IDs
		next_user_id = get_next_user_id();
		next_review_id = get_next_review_id();

		//! Create statements for each member function
		get_user_id_query = conn->createStatement(get_user_id_sql);
		signup_query = conn->createStatement(signup_sql);

		return true;	// successful connection
	} catch (SQLException & error) {
		cout << error.what();
		cout << "\nUsername or Password was incorrect, could not connect\n\n";
		return false;	// unsuccessful connection
	}
}

//! LOGIN
bool Server::login_successful(const string username, const string password) {
	get_user_id_query->setString(1, username);
	get_user_id_query->setString(2, password);
	ResultSet* result = get_user_id_query->executeQuery();
	if (result->next()) {
		curr_user = result->getString(1);
		get_user_id_query->closeResultSet(result);
		return true;
	} else {
		get_user_id_query->closeResultSet(result);
		return false;
	}
}

//! LOGOUT
void Server::logout() {
	curr_user = "";
}

//! SIGNUP 
bool Server::signup_successful(const string username, const string password) {
	// Attempting a login does the same thing as checking if the user account exists already.
	if (login_successful(username, password)) {
		cout << "\nYou have already signed up to the Movie Review App\n";
		return false;
	} 
	else {
		//! Uncomment when project complete 
		// Validate username: letters, numbers, any of !@#$%^&*_, and between 1 and 30 chars long
		// std::regex username_format("([a-z]|[A-Z]|\\d|[!@#$%^&*_]){1,30}");
		// if (!std::regex_match(username, username_format)) {
		// 	cout << "Your username is too long, or contains characters that are not acceptable. "
		// 		<< "\nPlease keep your username under 30 characters, and use only letters, numbers, and any of the following: !@#$%^&*_\n";
		// 	return false;
		// }
		// Validate password: letters, numbers, any of !@#$%^&*_, and between 1 and 100 chars long
		// std::regex password_format("([a-z]|[A-Z]|\\d|[!@#$%^&*_]){1,100}");
		// if (!std::regex_match(password, password_format)) {
		// 	cout << "Your password is too long, or contains characters that are not acceptable. "
		// 		<< "\nPlease keep your password under 100 characters, and use only letters, numbers, and any of the following: !@#$%^&*_\n";
		// 	return false;
		// }
		// If username + password passes checks, insert new user into database

		signup_query->setInt(1, next_user_id);
		signup_query->setString(2, username);
		signup_query->setString(3, password);
		cout << signup_query->getSQL() << endl;
		if (signup_query->executeUpdate()) {
			conn->commit();
			next_user_id++;
		}
		return true;
	}
}