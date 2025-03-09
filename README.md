# CSCI370-Project
Database project for CSCI 370

## Setup Process

### Step 1: Clone the GitHub Directory

- `git clone https://github.com/Chickenlord7321/CSCI370-Project.git`

### Step 2: Install Asio

**On Ubuntu:**
- `sudo apt-get install libasio-dev`

**On Other OSes:**

https://app.studyraid.com/en/read/12426/401280/installing-and-configuring-asio-library

### Step 3: Build Crow Environment

- Navigate to the "Crow" directory, which is located at the root level of the project

- Run `mkdir build; cd build`

- Run `cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF` from within the Crow/build directory. 
(You can ignore the `-DCROW...` options and just run `cmake ..` if you want to build the examples and unit tests)

- Finally, run `sudo make install`
