#include "SinglePerceptron.h"

int main(int argc, char * argv[]) {
	SinglePerceptron SinglePer;
	SinglePer.learn();

	for (int i = 0; i < SinglePer.w_log.size(); i++)
		std::cout << SinglePer.w_log[i][0] << ", " << SinglePer.w_log[i][1] << ", " << SinglePer.p_log[i] << std::endl;

	system("pause");

	return 0;
}