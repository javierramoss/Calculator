# Calculator
A simple calculator entirely on C++ and CMake capable of performing the most fundamental arithmetic operations using the Elements C++ GUI library

![calc](https://user-images.githubusercontent.com/65036152/166814225-6b80fc90-1b7f-444e-a58b-2f6f8082729f.JPG)

## Features
* Addition, subtraction, multiplication, division, power, and nth root
* Nested parentheses support
* Integers and decimals

## Requirements
* CMake
* Windows SDK Version 10
* Visual Studio 16 2019
* Elements C++ GUI library https://github.com/cycfi/elements

## Build
1. Clone the repo:
```
git clone https://github.com/BigBeakPenguin/Calculator.git
```
2. cd to the Calculator folder and create a `build` folder.
3. cd to the `build` folder and open the command prompt.
4. Compile using (change the `DELEMENTS_ROOT` path to where the elements library resides):
```
cmake -G"Visual Studio 16 2019" -DELEMENTS_ROOT=”../elements” ../
```
5. cd to the lib folder and use the following commands to import the LinkedLib library to the project:
```
git submodule init
git submodule update
```
6. Go back to the main folder and open the `Calculator.sln` in Visual Studio.
7. Add the calculator.cpp file to the solution under source files if not present.
8. Remove all the solutions in Visual Studio excepts for `elements` and `calculator`.
9. Build all.

## Usage
Press the buttons or type directly into the display to write an arithmetic operation. To compute the answer simply press the `=` button.

## Contributing
Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b NewBranch`)
3. Commit your Changes (`git commit -m 'Add x'`)
4. Push to the Branch (`git push origin NewBranch`)
5. Open a Pull Request

## License

Distributed under the MIT License. See `LICENSE` for more information.
