#include <random>
#include <iostream>
#include "../include/config.hpp"
#include "../source.cpp"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>


void Emplace(char* buff, int* set);
void Insert(char* buff, int* set);
void Erase(char* buff, int* set);
bool Emptiness(int set);
bool Nonempty(int set);
void Print(int set, char* target);
bool Member(char* buff, int set);
bool Disjoint(int set1, int set2);
bool Conjunctive(int set1, int set2);
bool Equality(int set1, int set2);
bool Inclusion(int set1, int set2);
void Union(int set1, int set2, int* target);
void Intersection(int set1, int set2, int* target);
void Symmetric(int set1, int set2, int* target);
void Difference(int set1, int set2, int* target);
void Complement(int set, int* target);
int Cardinality(int set);
bool LessThan(int set1, int set2);
bool LessEqual(int set1, int set2);
bool GreatEqual(int set1, int set2);
bool GreatThan(int set1, int set2);

int randint() {
	static FILE* randFile = fopen("/dev/random", "rb");

	if (!randFile) {
		std::cerr << "Error: Unable to open /dev/random\n";
		throw 1;
	}

	int randomValue = 0;
	size_t bytesRead = fread(&randomValue, sizeof(randomValue), 1, randFile);

	if (bytesRead != 1) {
		std::cerr << "Error: Failed to read from /dev/random\n";
		throw 1;
	}

	return randomValue;
}

std::string conv(int num) {
	std::string res = "";

	for(int i = 0; i < 5; i = i + 1)
		res.push_back(!((num >> i) & 1) + '0');

	reverse(res.begin(), res.end());

	return res;
}

std::string stringify_set(int set, bool randomize) {
	std::vector <std::string> elements;

	for(int k = 0; k < 32; k = k + 1)
		if((set >> k) & 1)
			elements.push_back(conv(k));

	if(randomize) {
		std::random_device rd;
		std::mt19937 g(rd());

		shuffle(elements.begin(), elements.end(), g);
	}

	std::string result = "";
	for(unsigned short i = 0; i < elements.size(); i = i + 1) {
		if(randomize)
			result = result + std::string((randint() & 3), ' ');

		result = result + elements[i] + " ";

		if(randomize)
			result = result + std::string((randint() & 3), ' ');
	}
	return result;
}

int main() {
	const char test_name[] = "disjoint_false/";

	//RANDOM TESTS
	bool rand_result = true;
	for(int i = 0; i < random_test_size; i = i + 1) {
		//generate random set for that test
		int mask = randint();
		int root_set1 = randint();
		int root_set2 = ~root_set1;

		int set1 = mask | root_set1;
		int set2 = mask | root_set2;

		//generate correct and shuffled output
		bool correct_result = false;

		std::string emplace_string1 = stringify_set(set1, false);
		std::string emplace_string2 = stringify_set(set2, false);

		//garbage for the user;
		int user_set1 = randint();
		int user_set2 = randint();

		//run
		Emplace((char*)emplace_string1.c_str(), &user_set1);
		Emplace((char*)emplace_string2.c_str(), &user_set2);

		bool user_result = Disjoint(user_set1, user_set2);

		//check
		bool result = user_result == correct_result;

		if(!result) {
			std::cerr << "[\033[33mDEBUG\033[0m] FAILED FOR SET1: >" << emplace_string1 << "<\n";
			std::cerr << "[\033[33mDEBUG\033[0m]            SET2: >" << emplace_string2 << "<\n";
			std::cerr << "[\033[33mDEBUG\033[0m] CORRECT OUTPUT: " << correct_result << "\n";
			std::cerr << "[\033[33mDEBUG\033[0m] YOUR OUTPUT:    " << user_result << "\n";
			std::cerr << "[\033[33mDEBUG\033[0m] > AND < SYMBOLS ARE ADDED TO SEE WHITESPACE\n";
		}

		//report
		rand_result = rand_result && result;
		std::cout << (result ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "random_" << i << '\n';
	}

	return !rand_result;
}
