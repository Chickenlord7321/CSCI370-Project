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
}

// bool MovieReviewApp::signUp();

// bool MovieReviewApp::login();