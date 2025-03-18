# Movie Review Database Application

- Author: Caleb Bronn
- Last Update: 27 Feb 2025

## Overview

This application will allow users to sign-in to their account, write reviews of movies, and read reviews left by other users. It is designed for people who are fans of movies and anyone who is looking for a new movie to watch. If a movie doesn't exist in the database yet, users will be able to add any movie they like by simply searching for it by title, selecting the movie they want to review, and clicking "add" to add the movie to the database. In this way, the database can be expanded by the users themselves through a secure and easy-to-use interface.

### Assumed Domain Knowledge

All a user needs to know is the name of the movie they want to review! The rest of the content (movie covers, year released, etc.) is handled internally through the use of the [TMDB API]("https://developer.themoviedb.org/docs/getting-started") and SQL queries to manage the database. This makes the application very user-friendly and easy to operate.

## Data Relationships

There are three major data categories in this application: Users, Movies, and Reviews. The primary relationship between these three categories is that users are able to search for a specific movie and write a review for it. This trifecta relationship is the core idea behind the project.

Additionally, users can also view movies or reviews through a web page. These are examples of relationships between users and movies or users and reviews.

The final important relationship in this database is that each review is associated with a single movie, but a given movie can have many reviews by many different users.

## Database Application Functionalities

Users will be able to do all of the following:

### 1. Login to or create an account

Users do not need an account to read movie reviews, but they do need an account in order to write their own reviews and add movies to the database.

### 2. Add a review for a movie

Once logged in, users can search for a movie they want to review, write a review, give the movie a rating, and upload their review to the database.

### 3. Update a review they have written

Users can update their reviews if they have more they want to add or their opinions have changed. Users can login to their account, search for one of the movies they have reviewed, and update the rating and/or the review text.

### 4. View movies they have reviewed 

Users can view their account page which lists all the movies they have written reviews for. This allows users to read their previous reviews and update them if they so wish.

### 5. View movies that match given criteria

Users can view the homepage which lists all movies in the database. From there, they can filter the list by selecting one or more options from drop-down menus. For example, the user could sort the movies list by rating to find the highest-rated movies. As another example, if the user wanted to find out which new releases are most popular right now, they could select movies that were released in 2025 and have a rating greater than 4 stars.

These drop-down options will allow users to filter movies by rating, year released, number of reviews, and more.
