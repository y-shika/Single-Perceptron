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
// SinglePerceptron(�p���N���X) ��private�ϐ��g�������Ȃ�, private -> protected�ɂ���.
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