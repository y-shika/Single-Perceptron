#ifndef __SINGLEPERCEPTRON_H_INCLUDED__
#define __SINGLEPERCEPTRON_H_INCLUDED__

#include "csvFile.h"

#include <random>

class SinglePerceptron : public csvFile
{
private:
	Eigen::Vector2d in;
	double out;
	Eigen::Vector2d w;

	double theta;
	double alpha;
	double delta;
	double p;

	double calc_p(Eigen::Vector2d tmp_w);

public:
	std::vector<Eigen::Vector2d> w_log;
	std::vector<double> theta_log;
	std::vector<double> p_log;

	SinglePerceptron();
	~SinglePerceptron();

	void learn();
};

#endif
