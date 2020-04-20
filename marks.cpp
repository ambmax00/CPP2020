// first name, last name, last exam, homeworks
// 1. take the three best homework marks
// 2. m_fin = 0.7 * m_exam + 0.3 * homework_mean 
// 3. if less than 3 homeworks -> final mark = 0

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>

class Student {
private:
	std::string m_first, m_last; // names
	double m_exam; // exam mark
	std::vector<double> m_hw; // homework
	double m_final;

public:

	Student() {} // default constructor
	Student(std::string t_first, std::string t_last, double t_exam, std::vector<double> t_hw) :
		m_first(t_first),
		m_last(t_last),
		m_exam(t_exam),
		m_hw(t_hw)
	{
		final_grade();
	}
       	     	       
	void final_grade() {
	
		if (this->m_hw.size() < 3) {
			m_final = 0;
			return;
		}

        	std::sort(this->m_hw.begin(),this->m_hw.end(),std::greater<double>());

        	double hw_mean = 0;

     	   	for (int i = 0; i != 3; ++i) {
       	        	 hw_mean += m_hw[i];
       	   	}

           	hw_mean /= 3;

           	this->m_final = 0.7 * m_exam + 0.3 * hw_mean;

	}

	double final() {
		return m_final;
	}

	// friend: allows function access to private members
	friend std::istream& operator>>(std::istream& in, Student& s); 
	friend std::ostream& operator<<(std::ostream& out, Student& s);
	friend bool operator<(Student& s1, Student& s2);
};

std::ostream& operator<<(std::ostream& out, Student& s) {

	out << s.m_first << " " << s.m_last << " " << s.m_final;
	return out;
}

std::istream& operator>>(std::istream& in, Student& s) {
	in >> s.m_first >> s.m_last >> s.m_exam;
	double m;
	while (in >> m) {
		s.m_hw.push_back(m);
	}

	s.final_grade();

	return in;    
}

bool operator<(Student& s1, Student& s2) {
	return s1.m_first < s2.m_first;
}

int main() {	
	
	std::string filename;

	std::cin >> filename;
	
	std::ifstream file(filename);

	std::vector<Student> students;
	std::string line;

	while (std::getline(file,line)) {
		Student s;
		std::istringstream iss(line);
		iss >> s;
		students.push_back(s);
	}


        std::sort(students.begin(),students.end(),[](Student& s1, Student& s2)
                        {
                                return s1.final() < s2.final();
                        });

	// mean grade + median grade
	// 25.5 50.3 75.2 95 -> (50.3 + 75.2)/2

	double mean = std::accumulate(students.begin(),students.end(),0.0,[](double& m, Student& s) 
			{
				return m + s.final();
			})/students.size();	


	std::cout << "MEAN: " << mean << std::endl;

	int nstudents = students.size();
	double median;

	if (nstudents % 2 == 0) {
		int idx = nstudents/2;
		median = (students[idx-1].final() + students[idx].final())/2;
	} else {
		median = students[nstudents/2].final();
	}

	std::cout << "MEDIAN: " << median << std::endl;

}

