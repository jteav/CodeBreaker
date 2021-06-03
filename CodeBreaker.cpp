/* This program randomly generates a four-digit code. Each digit is unique.
 * The user has 8 tries to guess the code.
 * The program will tell the user if they got a number right or if they got a number right but in the wrong place.
 * At the end, the program will ask the user if they would like to play again.
 */
#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

int main() {
    //This loop will continue until the user declines to play again.
    while (true) {
        //Generate a code by initializing a vector with unique digits, shuffle it, resize it to 4 elements.
        std::vector<int> nums = { 0,1,2,3,4,5,6,7,8,9 };
        shuffle(nums.begin(), nums.end(), std::default_random_engine(time(0)));

        std::string code = "";
        for (int i = 0; i < 4; i++) {
            code += std::to_string(nums.at(i));
        }

        std::cout << "Guess the four digit code! Each digit is unique. You have 8 tries.\n";
        std::string input;

        //The for loop loops 8 times for the 8 attempts.
        //It starts at 7 and decrements to keep track of how many attempts are left.
        for (int i = 7; i > -1; i--) {
            std::cin >> input;

            //Check if the input only contains 4 digits.
            bool isValid;
            if (input.size() == 4) {
                for (int j = 0; j < input.size(); j++) {
                    if (isdigit(input[j]))
                        isValid = true;
                    else {
                        isValid = false;
                        break;
                    }
                }
            }
            else
                isValid = false;

            //If the input is valid, then continue with the game.
            if (isValid == true) {
                if (input == code) {
                    std::cout << "You guessed correctly!\n";
                    break;
                }
                else {
                    //See if any digits in the input match any digits in the code and if they are in the right spot.
                    int rightSpot = 0;
                    int wrongSpot = 0;
                    for (int j = 0; j < code.size(); j++) {
                        for (int k = 0; k < input.size(); k++) {
                            if (code[j] == input[k] && j == k) {
                                rightSpot++;
                            }
                            else if (code[j] == input[k]) {
                                wrongSpot++;
                            }
                        }
                    }
                    std::cout << "Numbers correct: " << rightSpot << "\t Numbers correct but in the wrong spot: " << wrongSpot << "\t Tries remaining: " << i << std::endl;
                }

                if (i == 0) {
                    std::cout << "You ran out of tries. The code was: " << code << std::endl;
                }
            }
            //If the input is invalid, do not use up an attempt.
            else {
                std::cout << "Invalid input!\n";
                i += 1;
            }
        }

        //Ask the user if they would like to play again.
        bool replay;
        //This loop will continue until it receives a valid input.
        while (true) {
            std::cout << "Would you like to play again (y or n)? ";
            std::string response;
            std::cin >> response;

            //Change their response to lowercase incase the user enters 'Y' or 'N'
            std::string responseLowercase = "";
            for (int i = 0; i < response.size(); i++) {
                responseLowercase += tolower(response[i]);
            }

            //Check their response.
            if (responseLowercase == "y") {
                replay = true;
                break;
            }
            else if (responseLowercase == "n") {
                replay = false;
                break;
            }
            else {
                std::cout << "Invalid response!\n";
            }
        }

        //If the user wants to play again, then the program will loop back to the beginning.
        if (replay == true)
            continue;
        else
            break;
    }
    return 0;
}