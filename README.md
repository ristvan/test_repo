# test_repo
First test repository

This is my first test repository in github.

You can clone it to your machine by the follow command:
git clone https://github.com/ristvan/test_repo


Compile with CMake:
You need to install google test and copy it's include directory to your home directory into apps/include directory.
You need to copy libgtest.a into app/lib directory

Start CMake with the following command:
mkdir bin
cd bin
cmake -DHOME=${HOME} ..
