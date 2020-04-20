#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <string>
#include <cmath>
#include <map>

int main() {

	std::ifstream first("first.txt");
	std::ifstream second("second.txt");

	std::vector<std::string> firstnames;
	std::vector<std::string> lastnames;

	std::string line;
	while (std::getline(first,line)) {
		firstnames.push_back(line);
	}
	while (std::getline(second,line)) {
		lastnames.push_back(line);
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randname1(0,firstnames.size()-1);
	std::uniform_int_distribution<> randname2(0,lastnames.size()-1);
	std::lognormal_distribution<> marks(4.1, 0.23);
	std::lognormal_distribution<> rand_nhw(1.6,0.25);

	std::uniform_int_distribution<> rand_lim(3,10);

	std::map<int,int> m;
	std::map<int,int> mhw;

	int size;
	std::cin >> size;

	for (int i = 0; i != size; ++i) {
		double d;
		while (true) {
		 d = marks(gen);
		 if (d <= 100 && d >= 0) break;
		}

		int mean = std::round(d);

		++m[std::round(d/10)];
	
		int r1 = randname1(gen);
		int r2 = randname2(gen);

		std::uniform_int_distribution<> rand_hw(mean - rand_lim(gen),mean + rand_lim(gen));

		std::cout << firstnames[r1] << " " << lastnames[r2] << " " << mean << " ";
		
		int nhw = rand_nhw(gen);
		if (nhw < 0) nhw = 0;
		if (nhw > 6) nhw = 6;
	
		++mhw[nhw];

		for (int i = 0; i != nhw; ++i) {
			int dhw = std::min(rand_hw(gen),100);
			dhw = std::max(dhw,0);
			std::cout << dhw << " ";
		} std::cout << std::endl;

	}

	/*
	for (auto p : m) {
		std::string s(p.second,'*');
		std::cout << p.first << "\t" << s << std::endl;
	}	

	for (auto p : mhw) {
                std::string s(p.second,'*');
                std::cout << p.first << "\t" << s << std::endl;
        }
	*/


}
