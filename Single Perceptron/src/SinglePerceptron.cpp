#include "SinglePerceptron.h"

SinglePerceptron::SinglePerceptron() {
	// ���������� [-1.0, 1.0)
	std::random_device rnd;
	std::mt19937_64 mt(rnd());
	std::uniform_real_distribution<> rand100(-1.0, 1.0);

	w[0] = rand100(mt);
	w[1] = rand100(mt);

	theta = rand100(mt);

	alpha = 0.05;

	delta = 0;
	p = 0;

	read();
}

SinglePerceptron::~SinglePerceptron() {
	write(w_log, theta_log, p_log);
}

void SinglePerceptron::learn() {
	// �����_���Ɍ��܂鐔(w, theta)����ł̓��[�v�ɓ���Ȃ��\�������邽��, ���[�v�O�Ɉ�x���������v�Z����.
	p = calc_p(w);

	w_log.push_back(w);
	theta_log.push_back(theta);
	p_log.push_back(p);

	while (p != 100) {
		for (int i = 0; i < Teach_in.size(); i++) {
			in[0] = Teach_in[i][0];
			in[1] = Teach_in[i][1];

			double tmp_out = in[0] * w[0] + in[1] * w[1] - theta;
			// ?? out�̌��ʂɂ���, ���Ȃ�1, ���Ȃ�0�Ƃ��邪, 0�̂Ƃ��͂ǂ�����̂�?
			if (tmp_out >= 0) out = 1;
			else out = 0;

			// �����I�Ȋw�K
			if (out != Teach_out[i]) {
				delta = out - Teach_out[i];
				w[0] = w[0] - alpha * delta * in[0];
				w[1] = w[1] - alpha * delta * in[1];
				theta = theta + alpha * delta;

				p = calc_p(w);

				w_log.push_back(w);
				theta_log.push_back(theta);
				p_log.push_back(p);

				std::cout << w[0] << ", " << w[1] << "," << p << std::endl;
			}

			if (p == 100) break;
		}
	}
}

// SinglePerceptron�N���X�̃����o�ϐ�, w���Ӑ}�������삳���̂���������, �����Ƃ��ēn��.
// private�֐��ł�, p�����������Ȃ邾���ꎞ�I�ȕϐ�����ēn���悤�ɂ���. (�\�t�g�E�F�A�H�w�I�ɗL�ӂȂ��Ƃ��͂킩��Ȃ��c)
double SinglePerceptron::calc_p(Eigen::Vector2d tmp_w) {
	int correctCount = 0;

	for (int i = 0; i < Teach_in.size(); i++) {
		Eigen::Vector2d tmp_in;
		double tmp_out;

		tmp_in[0] = Teach_in[i][0];
		tmp_in[1] = Teach_in[i][1];

		double _tmp_out = tmp_in[0] * tmp_w[0] + tmp_in[1] * tmp_w[1] - theta;
		if (_tmp_out >= 0) tmp_out = 1;
		else tmp_out = 0;

		if (tmp_out == Teach_out[i]) correctCount++;
	}

	// %�\�L (0 - 100)
	double tmp_p = correctCount * 100 / Teach_out.size();

	return tmp_p;
}