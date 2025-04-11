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

public:
	// Constuctor
	MovieReviewApp();

	// Destructor
	~MovieReviewApp();

	// Connect to server
	void get_credentials();

	// Sign up
	bool signUp(string username, string password);

	// Login
	bool login(string username, string password);

	void write_review(string username);

	void update_review(string username);

	void look_up_reviews();

	void look_up_movies();
};

#endif