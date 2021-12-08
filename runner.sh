#!/bin/bash

## * Function Declarations * ##

## Just a simple way to do a print
function PrintStatement() {
    echo ""
    echo $1
    echo ""
}


## Since I use mobaxterm, i need to specifically give it the 
## version that I wish to use.
export MESA_GL_VERSION_OVERRIDE=4.5

# Gets the arguments
args=("$@")

## Gets into the build directory to build the program, then 
## runs the program
PrintStatement "Building the project: "
cd build
make build

## Runs the project
PrintStatement "Running the project: "
./project


## Cleans up after the run
PrintStatement "Cleaning up: "
if [ "$1" != "shader_test" ]
then
    make clean
else
    make clean_project
fi

## returns back to the directory state we are used to
cd ..