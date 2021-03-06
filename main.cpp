#include <iostream>
#include <vector>

#include "main.h"

struct prime_struct {
    int coefficient;
    int power;
};


void fillArray(int *arr, int size) // fills the array with a list of numbers from 2 - (number chosen minus 1)
{
    for (int i = 0; i < size; i++) {
        arr[i] = i + 2;
    }
}

int primeList(int *arr, int &size) // makes the array a list of prime numbers from 2 - num
{

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (arr[j + 1] % arr[i] ==
                0) // sorts for primes by seeing if there is a remainder when divided by other values in the array
            {
                for (int k = j + 1; k < size; k++) // gets rid of the non-primes and fixes the array
                {
                    arr[k] = arr[k + 1];
                }
                size = size - 1; // resizes the array because a non-prime was taken out
            }
        }
    }

    return 0;
}


void askForPrimeList(std::vector<std::string> &primeList);

prime_struct delimitString(std::string str, const std::string &delimiter);

void symbolNum(std::vector<prime_struct> primeStuff) {
	std::string thing[] = {"null", "0", "null", "f", "null", "¬", "null", "∨", "null", "∀", "null", "(", "null", ")",
						   "null", "∧", "null", "∃", "null", "=", "null", "x", "null", "y"};

	//2^3 3^3 5^3 7^1 == f f f 0
	for (prime_struct x : primeStuff) {
		if (x.power > (sizeof(thing) / sizeof(thing[0])) || x.power % 2 == 0) {
			std::cout << "list of primes is unacceptable" << std::endl;
			exit(-1);
		} else
			std::cout << thing[x.power] << " ";
	}
}

int main() {
    int size = 0;

    int *arr = nullptr;
    arr = new int[size]{};

    std::vector<std::string> primeInputList;
    askForPrimeList(primeInputList);

    std::vector<prime_struct> primeStuff;

    for (std::string curStr : primeInputList) {
        prime_struct structThing = delimitString(curStr, "^");
        primeStuff.push_back(structThing);
        size = structThing.coefficient + 1;
        // std::cout << structThing.coefficient << std::endl << structThing.power << std::endl;
    }


    fillArray(arr, size);
    primeList(arr, size);


	int i = 0;
    for (prime_struct x : primeStuff) {
        if (x.coefficient != arr[i]) {
            std::cout << "list of primes is unacceptable" << std::endl;
            std::cout << "Expected " << arr[i] << " but got " << x.coefficient << std::endl;

            return -1;
        }
        i++;
    }

    symbolNum(primeStuff);

    delete[] arr;
    return 0;
}

void askForPrimeList(std::vector<std::string> &primeList) {
    std::string receivedInput = "0";

    std::cout << "Input a number (e.g. 2^3) to add to the list of primes, or -1 when you're done: ";
    for (;;) { // Loop infinitely until input -1 is received
        std::cin >> receivedInput;

        if (receivedInput != "-1")
            primeList.push_back(receivedInput);
        else
            break;
    }
}

prime_struct delimitString(std::string str, const std::string &delimiter) {
	prime_struct returningPrime{};
	unsigned int position;
	std::string curToken;

	if (str.find(delimiter) != std::string::npos)
		while ((position = str.find(delimiter)) != std::string::npos) {
			returningPrime.coefficient = std::stoi(str.substr(0, position));
			str.erase(0, position + delimiter.length());
			returningPrime.power = std::stoi(str);
		}

	return returningPrime;
}