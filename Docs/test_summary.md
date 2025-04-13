# Test Summary 

## Test Cases

### Login

Tested with all users in database, attempted logins with usernames / passwords that were not in database. Program responds to invalid users appropriately.

### Logout 

Very simple test case, simply logout and then attempt to update a review or write a review. Program does not allow changes to be made when user is not logged in.

### Sign up

Attempted to create test user "deleteme". "deleteme" can be viewed in the database after "deleteme" has been signed up.

### Write Review

Added test reviews from both files and terminal input. New reviews can be seen in the database.

### Update Review

Updated test reviews from both files and terminal input. Updated review content and scores can be seen in the database.

### Look Up Reviews

Selected every option one by one, all created files/terminal output is correct and display in a browser.

### Look Up Movies

Selected every option one by one, all created files/terminal output is correct and display in a browser.

### Invalid Inputs (String input, int input, double input)

All input functions have been tested with correct/incorrect passwords, usernames, integers, doubles, and invalid strings. There is currently a small bug with the initial credentials input. If the user quits the program on the first Oracle username prompt, the program quits with a segmentation fault.
