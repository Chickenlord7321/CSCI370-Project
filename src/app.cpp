#include "../include/app.hpp"

MovieReviewApp::MovieReviewApp() {
	svr = new Server();
}

MovieReviewApp::~MovieReviewApp() {
	delete svr;
}

void MovieReviewApp::get_credentials() {
	cout << "First, you will need to enter your Oracle Database credentials.\n";
	bool connected;
	do {
		// Prompt for username
		cout << "Enter Oracle username: ";
		string username;
		getline(cin, username);

		// Prompt for password
		char* passwd_char = getpass("Enter Oracle password: ");
		string password(passwd_char);

		connected = svr->connect(username, password);
	} while (!connected);
	cout << "Credentials verified!\n";
}

// bool MovieReviewApp::signUp();

bool MovieReviewApp::login() {
	try {
		string username;
		string password;
		cout << "Enter your username:\n> ";
		getline(cin, username);
		password = string(getpass("Enter your password:\n> "));
		curr_user = svr->get_user_id(username, password);
	} catch (ServerException& error) {
		cout << "Sorry, it seems that username is not correct.\n";
		return false;
	}
	return true;
};

void MovieReviewApp::logout() {
	curr_user = "";
}