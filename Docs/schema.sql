CREATE TABLE Users (
	user_id CHAR(6) NOT NULL PRIMARY KEY,
	username VARCHAR(30) NOT NULL,
	email VARCHAR(254) NOT NULL,	-- 254 chars is the max length for an email
	sign_up_date DATE DEFAULT TO_DATE(CURRENT_DATE, 'YYYY-MM-DD')
);

CREATE TABLE Reviews (
	review_id CHAR(9) NOT NULL PRIMARY KEY,
	user_id CHAR(6) FOREIGN KEY REFERENCES Users(user_id),
	movie_id INT FOREIGN KEY REFERENCES Movies(movie_id),
	review_text VARCHAR(4000) NOT NULL, --4,000 chars is the max length for varchar
	your_score NUMBER(4, 2) CHECK(score <= 10.00),
	written DATE DEFAULT TO_DATE(CURRENT_DATE, 'YYYY-MM-DD'),
	last_update DATE CHECK(last_update >= written)					-- same as 'written' if review has never been updated
);

CREATE TABLE Movies (
	movie_id INT NOT NULL PRIMARY KEY,	-- TMDB movie IDs are integers
	title VARCHAR(213),			-- longest movie title ever is 213 chars long
	overview VARCHAR(4000),		-- 4,000 chars is the max length for varchar
	lang CHAR(2),				-- 2-letter language code
	bg_path VARCHAR(100),		-- relative path for movie background image
	poster_path VARCHAR(100),	-- relative path for movie poster image
	tmdb_score NUMBER(4, 2) CHECK(score <= 10.00),	-- scores are stored as decimal percentages on TMDB
	user_avg_score NUMBER(4, 2) CHECK(score <= 10.00),	-- average score from users on this app
	release_date DATE,
);
