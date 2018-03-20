#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool simple_comment(istream&fin) {
	char sym;
	while (fin.get(sym))
		if (sym == '\n')
			return false;
	return true;
}

bool heavy_comment(istream&fin) {
	char sym;
	while (fin.get(sym))	
		if (sym == '*') {
			if (!fin.get(sym))
				break;
			if (sym == '/')
				return false;
		}
	return true;
}

void write(ofstream&fout, string&line) {
	static bool prev_empry_line = false;
	for (int i = 0; i < line.length(); ++i) {
		if (!isspace(line[i])) {
			prev_empry_line = true;
			fout.write(line.c_str(), line.length());
			line = "";
			return;
		}
	}
	if (!prev_empry_line) {
		fout.put('\n');
		prev_empry_line = true;
	}
	line = "";
}

int start(string nFile) {
	
	ifstream fin(nFile.c_str());
	if (!fin) return 1;

	nFile += "_answer.cpp";
	ofstream fout(nFile.c_str());
	if (!fout) return 1;
	
	bool in_str, in_ch, end;
	string line;
	char sym;

	in_str = in_ch = false;
	end = true;

	while (fin.get(sym))
	{
		if (in_ch || in_str || sym != '/') {
			line += sym;
			if (sym == '\n') write(fout, line);
			else if (sym == '\"') in_str = !in_str;
			else if (sym == '\'') in_ch = !in_ch;
			continue;
		}
		if (!fin.get(sym)) break;

		switch (sym)
		{
		case '/':
			end = simple_comment(fin);
			line += '\n';
			write(fout, line);
			break;
		case '*':
			end = heavy_comment(fin);
			line += ' ';
			break;
		default:
			line += '/';
			line += sym;
			break;
		}

		if (end) break;
	}
	write(fout, line);
	fin.close();
	fout.close();
	return 0;
}

int main()
{
	switch (start("code.cpp")) {
	case 1: cout << "error\n"; break;
	case 0: cout << "success\n"; break;
	}
	system("pause");
	return EXIT_SUCCESS;
}