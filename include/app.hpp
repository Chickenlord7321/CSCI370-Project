/**
 * Author: Caleb Bronn
 * Last Update: 10 Apr 2025
 * Title: Movie Review Database App Project
 * Class: CSCI 370
 */

#ifndef APP_H
#define APP_H

#include "../include/server.hpp"
#include <unistd.h>		// for getpass()
#include <regex>		// for string parsing
#include <iostream>
#include <string>
	using namespace std;

// TODO: Global stuff goes here

class MovieReviewApp {
private:
	Server* svr;
	string curr_user;

public:
	// Constuctor
	MovieReviewApp();

	// Destructor
	~MovieReviewApp();

	// Connect to server
	void get_credentials();

	// Sign up
	bool signUp();

	// Login
	bool login();

	void logout();

	void write_review();

	void update_review();

	void look_up_reviews();

	void look_up_movies();
};

#endif