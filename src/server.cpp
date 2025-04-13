/**
 * Author: Caleb Bronn
 * Last Update: 12 Apr 2025
 * Title: Movie Review Database App Project
 * Class: CSCI 370

 * TODO: write header comments for each function!
 */

#include "../include/server.hpp"
// #include <regex>	// for string parsing

// Constructor
Server::Server() {
	env = nullptr;
	conn = nullptr;
	// Empty curr_user represents the concept of being logged out
	curr_user = "";
	next_user_id = next_review_id = 0;

	// Init queries
	get_user_id_sql = "SELECT user_id FROM Users WHERE username = :u AND password = :p";
	signup_sql = "INSERT INTO Users VALUES(" 
				" :u_id,"
				" :uname,"
				" :psswd,"
				" CURRENT_DATE"
				" )";
	submit_review_sql = "INSERT INTO Reviews VALUES("
						" :r_id,"
						" :u_id,"
						" :m_id,"
						" :r_text,"
						" :your_score,"
						" CURRENT_DATE,"
						" CURRENT_DATE"
						")";
	update_review_sql = "UPDATE Reviews"
						" SET review_text = :r_text,"
						" your_score = :your_score,"
						" last_update = CURRENT_DATE"
						" WHERE review_id = :review_id";
	search_your_reviews_sql = "SELECT review_id, user_id, R.movie_id, review_text, your_score, written, last_update, title, tmdb_score, user_avg_score"
						" FROM Movies M JOIN Reviews R ON (M.movie_id = R.movie_id)"
						" WHERE LOWER(title) LIKE LOWER( ':search_term' )"
						" OR LOWER(review_text) LIKE LOWER( ':search_term' )" 
						" AND user_id = :u_id"
						" ORDER BY title DESC";
	find_review_sql = "SELECT review_id FROM Reviews WHERE user_id = :u_id AND movie_id = :m_id";
	search_movies_sql = "SELECT * "
						" FROM Movies"
						" WHERE LOWER(title) LIKE LOWER( ':search_term' ) "
						" AND LOWER(overview) LIKE LOWER( ':search_term' )"
						" ORDER BY movie_id DESC";

	// Set statements to null
	get_user_id_query = nullptr;
	signup_query = nullptr;
	submit_review_query = nullptr;
	update_review_query = nullptr;
	search_your_reviews_query= nullptr;
	find_review_query = nullptr;
	search_movies_query = nullptr;
}

// Destructor
Server::~Server() {
	// Terminate connection only if it's not null
	// We do this in case the try-catch in connect() fails to establish a connection
	if (conn) {
		// ! Terminate statements
		conn->terminateStatement(get_user_id_query);
		conn->terminateStatement(signup_query);
		conn->terminateStatement(submit_review_query);
		conn->terminateStatement(update_review_query);
		conn->terminateStatement(search_your_reviews_query);
		conn->terminateStatement(find_review_query);
		conn->terminateStatement(search_movies_query);
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


vector<unordered_map<string, string>> Server::list_movies(ResultSet* result) {
	vector<unordered_map<string, string>> data;
	while (result->next()) {
		unordered_map<string, string> entry = {
			{"movie_id", result->getString(1)},
			{"title", result->getString(2)},
			{"overview", result->getString(3)},
			{"lang", result->getString(4)},
			{"bg_path", result->getString(5)},
			{"poster_path", result->getString(6)},
			{"tmdb_score", result->getString(7)},
			{"user_avg_score", result->getString(8)},
			{"release_date", result->getDate(9).toText("YYYY-MON-DD")}
		};
		data.push_back(entry);
	}
	return data;
}


vector<unordered_map<string, string>> Server::list_reviews(ResultSet* result) {
	vector<unordered_map<string, string>> data;
	while (result->next()) {
		unordered_map<string, string> entry = {
			{"review_id", result->getString(1)},
			{"user_id", result->getString(2)},
			{"movie_id", result->getString(3)},
			{"review_text", result->getString(4)},
			{"your_score", result->getString(5)},
			{"written", result->getString(6)},
			{"last_update", result->getString(7)},
			{"title", result->getString(8)},
			{"tmdb_score", result->getString(9)},
			{"user_avg_score", result->getString(10)}
		};
		data.push_back(entry);
	}
	return data;
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
		next_user_id = 1 + get_next_user_id();
		next_review_id = 1 + get_next_review_id();

		//! Create statements for each member function
		get_user_id_query = conn->createStatement(get_user_id_sql);
		signup_query = conn->createStatement(signup_sql);
		submit_review_query = conn->createStatement(submit_review_sql);
		update_review_query = conn->createStatement(update_review_sql);
		search_your_reviews_query = conn->createStatement(search_your_reviews_sql);
		find_review_query = conn->createStatement(find_review_sql);
		search_movies_query = conn->createStatement(search_movies_sql);

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

		string uid = to_string(next_user_id);
		uid.insert(0, 6 - uid.length(), '0');
		signup_query->setString(1, uid);
		signup_query->setString(2, username);
		signup_query->setString(3, password);
		if (signup_query->executeUpdate()) {
			conn->commit();
			next_user_id++;
		}
		return true;
	}
}

//! SUBMIT REVIEW
bool Server::submit_review(const int movie_id, const string review, const double score) {
	if (curr_user == "") {
		cout << "\nYou are not logged in. Please login first.\n";
		return false;
	} 
	else if (find_review_by_curr_user(movie_id) == "") {
		cout << "\nYou have already written a review for this movie.\n";
		return false;
	}
	string rid = to_string(next_review_id);
	rid.insert(0, 9 - rid.length(), '0');
	submit_review_query->setString(1, rid);
	submit_review_query->setString(2, curr_user);
	submit_review_query->setInt(3, movie_id);
	submit_review_query->setString(4, review);
	submit_review_query->setDouble(5, score);
	if (submit_review_query->executeUpdate()) {
		conn->commit();
		next_review_id++;
	}
	return true;
}

//! UPDATE REVIEW
bool Server::update_review(const string review_id, const string review, const double score) {
	if (curr_user == "") {
		cout << "\nYou are not logged in. Please login first.\n";
		return false;
	}
	update_review_query->setString(1, review);
	update_review_query->setDouble(2, score);
	update_review_query->setString(3, review_id);
	if (update_review_query->executeUpdate()) {
		conn->commit();
	}
	return true;
}


string Server::find_review_by_curr_user(const int movie_id) const {
	if (curr_user == "") {
		return "";
	}
	find_review_query->setString(1, curr_user);
	find_review_query->setInt(2, movie_id);
	ResultSet* result = find_review_query->executeQuery();
	string review_id = "";
	if (result->next()) {
		review_id = result->getString(1);
	}
	find_review_query->closeResultSet(result);
	return review_id;
}


//! SEARCH MOVIES BY MOVIE NAME
vector<unordered_map<string, string>> Server::search_movies(const string search_term) {
	if (curr_user == "") {
		throw ServerException("search_movies", "user not logged in");
	}
	string match = "%" + search_term + "%";

	//! DEBUG 
	cout << "search term is:" << match << endl;

	search_movies_query->setString(1, match);
	search_movies_query->setString(2, match);
	ResultSet* result = search_movies_query->executeQuery();
	vector<unordered_map<string, string>> search_result = list_movies(result);

	cout << "SQL:" << search_movies_query->getSQL() << endl;

	search_movies_query->closeResultSet(result);
	return search_result;
}

//! SEARCH YOUR REVIEWS BY SEARCH TERM
vector<unordered_map<string, string>> Server::search_your_reviews(const string search_term) {
	if (curr_user == "") {
		throw ServerException("search_your_reviews", "user not logged in");
	}
	string match = "%" + search_term + "%";

	//! DEBUG 
	cout << "search term is:" << match << endl;

	search_your_reviews_query->setString(1, match);
	search_your_reviews_query->setString(2, match);
	search_your_reviews_query->setString(3, curr_user);
	ResultSet* result = search_your_reviews_query->executeQuery();


	//! DEBUG
	cout << "SQL:" << search_your_reviews_query->getSQL() << endl;

	vector<unordered_map<string, string>> search_result = list_reviews(result);
	search_your_reviews_query->closeResultSet(result);
	return search_result;
}