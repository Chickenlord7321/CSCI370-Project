# Movie Review App
Database project for CSCI 370

## Setup Process

### Step 1: Clone the GitHub Directory

- `git clone https://github.com/Chickenlord7321/CSCI370-Project.git`

### Step 2: Adding data to database

Use the SQL statements in [database_design.md](./Docs/database_design.md) to create three tables: Users, Movies, and Reviews.

You can then populate the tables with the sample data found under `Data/`. There are three files there for each of the tables:

- [Users](./Data/sampleUsers.sql)
- [Movies](./Data/sampleMovies.sql)
- [Reviews](./Data/sampleReviews.sql)

### Step 3: Run the Project
- Navigate to src/ with `cd src/`.

- Run `make` to create an executable called 'MovieReviewApp' at the root level.

- Navigate back up to the root directory: `cd ../` (this is important because when the program attempts to create files, they are created using relative file paths that assume you are working from the project root directory).

- Type `./MovieReviewApp` to run the program!

## How to copy the HTML files to your machine:

All HTML output files are located under the `Output/` directory.

Follow Dave's steps for copying files with scp: http://csci.viu.ca/~wesselsd/technotes.html#TransferFromHome

## Adding more movies to the database

This must be done from the lab machines, **not from Otter!**

- Create a build directory with `mkdir build`

- Navigate to the build directory and run cmake with `cd build/; cmake ..`

- From within /build, run `make` to create an executable named `addMovies`

- Navigate back up to the root directory with `cd ../`

- Run `./addMovies`, and you will be prompted to search for a film. Any films you add will be written to 'Data/sampleMovies.sql'. You can run this SQL file to add all the movies inside it to the `Movies` table.
