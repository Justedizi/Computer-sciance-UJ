#include <iostream>
#include "../include/config.hpp"
#include "../source.cpp"
#include <cstdio>
#include <cstring>
#include <string>


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

	//TEST 1
	char t1s[] = "   ";
	int set1 = 0x1234abcd;
	char t1r[6] = {'a', 'b', 'c', 'd', 'e', 'f'}; //explicit no null byte to check if user sets it

	Emplace(t1s, &set1);
	Print(set1, t1r);

	bool m1 = !strcmp("empty", t1r);

	//TEST 2
	char t2s[] = " 00000     11111 ";
	int set2 = 0xa1b2c3d4;
	char t2r[13] = {'A', 'B', 'C', 'D', 'E', 'F', 'A', 'B', 'C', 'D', 'E', 'F', 'X'}; //explicit no null byte to check if user sets it

	Emplace(t2s, &set2);
	Print(set2, t2r);

	bool m2 = !strcmp("11111 00000 ", t2r);


	//RESULTS
	const char test_name[] = "print_null_byte/";
	std::cout << (m1 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "test_1\n";
	std::cout << (m2 ? "[\033[32mOK\033[0m]    " : "[\033[31mANS\033[0m] ! ") << test_name << "test_2\n";

	return !(m1 && m2);
}
