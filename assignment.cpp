#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
	// file IO
	string inFilename = "input.txt";
	string outFilename = "output.csv";
	if (argc > 1) inFilename = argv[1];
	if (argc > 2) outFilename = argv[2];
	fstream fin(inFilename.c_str(), ios::in);
	fstream fout(outFilename.c_str(), ios::out);

	// set random seed:
  srand((unsigned)time(NULL));

	vector< vector< string > > rooms;
	vector< string > works;
	vector< string > dates;
	string header;
	vector< string > notes;

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
		if (s == "header:") break;
		dates.push_back(s);
	}
	while (fin >> s) {
		if (s == "notes:") break;
		header = s;
	}
	while (fin >> s) {
		notes.push_back(s);
	}

	if (works.size() != rooms.size()) {
		cout << "Wrong number of works" << endl;
		exit(0);
	}

	// header
	fout << header << ",";
	for (int i = 0; i < dates.size() - 1; i++) fout << dates[i] << ",";
	fout << dates[dates.size() - 1] << endl;

	vector< vector< string > > table;
	for (int i = 0; i < dates.size(); i++) {
		vector< string > col;
		vector< bool > visited;
		for (int j = 0; j < works.size(); j++) visited.push_back(false);
		// random	
		int n = 0, j;
		while (n < works.size()) {
			do {
				j = rand() % works.size();
			} while (visited[j]);
			col.push_back(works[j]);
			visited[j] = true;
			n++;
		}
		table.push_back(col);
	}

	for (int i = 0; i < rooms.size(); i++) {
		fout << rooms[i][0] << " " << rooms[i][1] << ",";
		for (int j = 0; j < dates.size() - 1; j++) fout << table[j][i] << ",";
		fout << table[dates.size() - 1][i] << endl;
	}

	for (int i = 0; i < notes.size(); i++) {
		fout << endl;
		fout << notes[i];
		for (int j = 0; j < dates.size(); j++) fout << ",";
	}

	return 0;
}