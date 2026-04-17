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

	//TEST EMPTY 1-2
	char t12s[] = "";
	int set12 = 0x1234abcd;

	Emplace(t12s, &set12);

	bool m1 = Emptiness(set12) == true;
	bool m2 = Nonempty(set12) == false;

	//TEST EMPTY 3-4
	char t34s[] = "      ";
	int set34 = 0xa1b2c3d4;

	Emplace(t34s, &set34);

	bool m3 = Emptiness(set34) == true;
	bool m4 = Nonempty(set34) == false;

	//TEST 5-6
	char t56s[] = " 00000     ";
	int set56 = 0xa1b2c3d4;

	Emplace(t56s, &set56);

	bool m5 = Emptiness(set56) == false;
	bool m6 = Nonempty(set56) == true;


	//RESULTS
	const char test_name[] = "empty_nonempty/";
	std::cout << (m1 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "empty_1\n";
	std::cout << (m2 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "nonempty_2\n";
	std::cout << (m3 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "empty_3\n";
	std::cout << (m4 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "nonempty_4\n";
	std::cout << (m5 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "empty_5\n";
	std::cout << (m6 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "nonempty_6\n";

	return !(m1 && m2 && m3 && m4 && m5 && m6);
}
