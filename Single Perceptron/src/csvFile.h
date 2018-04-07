#ifndef __CSVFILE_H_INCLUDED__
#define __CSVFILE_H_INCLUDED__

#include <Eigen\Eigen>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class csvFile
{
// SinglePerceptron(Œp³ƒNƒ‰ƒX) ‚Åprivate•Ï”Žg‚¢‚½‚¢‚È‚ç, private -> protected‚É‚·‚é.
private:
	std::string inputFileName;
	std::string outputFileName;
	void split(std::string& line);

public:
	std::vector<Eigen::Vector2d> Teach_in;
	std::vector<double> Teach_out;

	csvFile();
	//~csvFile();

	void read();
	void write(std::vector<Eigen::Vector2d> w_log, std::vector<double> theta_log, std::vector<double> p_log);
};

#endif