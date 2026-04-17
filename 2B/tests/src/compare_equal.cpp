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

int main() {

	//TESTS 1-4
	char ts1[] = "10011           01001    11010            10010            10101          01111           11110      00001       11001   10111            11011    ";
	char ts2[] = "    10010             11110        10101              11001            11011     11010  10111          01111     10011        01001          00001 ";
	int set1 = 0x1234abcd;
	int set2 = 0xa1b2c3d4;

	Emplace(ts1, &set1);
	Emplace(ts2, &set2);

	bool m1 = LessThan(set1, set2) == false;
	bool m2 = LessEqual(set1, set2) == true;
	bool m3 = GreatThan(set1, set2) == false;
	bool m4 = GreatEqual(set1, set2) == true;

	//RESULTS
	const char test_name[] = "compare_equal/";
	std::cout << (m1 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "lessthan_1\n";
	std::cout << (m2 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "less_equal_2\n";
	std::cout << (m3 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "great_than_3\n";
	std::cout << (m4 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "great_equal_4\n";

	return !(m1 && m2 && m3 && m4);
}
