#ifndef __SINGLEPERCEPTRON_H_INCLUDED__
#define __SINGLEPERCEPTRON_H_INCLUDED__

#include "csvFile.h"

#include <random>

class SinglePerceptron : public csvFile
{
private:
	std::vector<double> in;
	double out;
	std::vector<double> w;

	double theta;
	double alpha;
	double delta;
	double p;

	double calc_p(double w0, double w1);

public:
	// TODO learn()を実装する. またmain関数にてある程度の実装を行うのか, クラス内にてほぼ題意を満たすコードを作るのか考える.
	std::vector<std::vector<double>> w_log;
	std::vector<double> theta_log;
	std::vector<double> p_log;

	SinglePerceptron();
	~SinglePerceptron();

	void learn();
};

#endif
