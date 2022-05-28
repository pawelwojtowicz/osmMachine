# osmMachine 
  C++ library for handling the geo location powered by the osm data.

## Input data
  Open Streep Maps can be downloaded from: https://www.openstreetmap.org ( with some restrictions )

  and without the data size restrictions from: https://download.geofabrik.de/ 

## Environment preparation
### src
  gtest installation:
  
  ```
    sudo apt-get install libgtest-dev
    sudo apt-get install cmake
    cd /usr/src/gtest
    sudo cmake CMakeLists.txt
    sudo make
    #copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
    sudo cp *.a /usr/lib

  ```
### Python tools
  Installing the tooling scripts dependencies, based on the requirements file
  ```
     pip install -r requirements.txt
  ```
