#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
	// file IO
	string inFilename = "input.txt";
	string outFilename = "output.csv";
	if (argc > 1) inFilename = argv[1];
	if (argc > 2) outFilename = argv[2];
	fstream fin(inFilename.c_str(), ios::in);
	fstream fout(outFilename.c_str(), ios::out);

	// obtain a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	vector< vector< string > > rooms;
	vector< string > works;
	vector< string > dates;

	string s;
	while (fin >> s) if (s == "rooms:") break;
	vector< string > pair(2);
	while (fin >> pair[0] >> pair[1]) {
		if (pair[0] == "works:") break;
		rooms.push_back(pair);
	}
	if (pair[1] != "dates:") works.push_back(pair[1]);
	while (fin >> s) {
		if (s == "dates:") break;
		works.push_back(s);
	}
	while (fin >> s) {
		dates.push_back(s);
	}

	if (works.size() != rooms.size()) {
		cout << "Wrong number of works" << endl;
		exit(0);
	}

	// header
	fout << "人\\deadline,";
	for (int i = 0; i < dates.size() - 1; i++) fout << dates[i] << ",";
	fout << dates[dates.size() - 1] << endl;

	vector< vector< string > > table;
	for (int i = 0; i < dates.size(); i++) {
		vector< string > col;
		shuffle(works.begin(), works.end(), std::default_random_engine(seed));
		for (int j = 0; j < works.size(); j++) col.push_back(works[j]);
		table.push_back(col);
	}

	for (int i = 0; i < rooms.size(); i++) {
		fout << rooms[i][0] << " " << rooms[i][1] << ",";
		for (int j = 0; j < dates.size() - 1; j++) fout << table[j][i] << ",";
		fout << table[dates.size() - 1][i] << endl;
	}

	fout << endl;
	fout << "浴室跟廁所請選當週最髒的掃";
	for (int i = 0; i < dates.size(); i++) fout << ",";
	fout << "\n記得填一下聚會出席表";
	for (int i = 0; i < dates.size(); i++) fout << ",";

	return 0;
}