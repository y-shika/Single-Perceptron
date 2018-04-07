#include "SinglePerceptron.h"

SinglePerceptron::SinglePerceptron() {
	// vectorはresizeなどで, 大きさ指定しないと配列のような代入は不具合を起こす.
	in.resize(2);
	w.resize(2);

	// 乱数生成器 [-1.0, 1.0)
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
	// ランダムに決まる数(w, theta)次第ではループに入らない可能性もあるため, ループ前に一度正答率を計算する.
	p = calc_p(w[0], w[1]);

	w_log.push_back(w);
	theta_log.push_back(theta);
	p_log.push_back(p);

	while (p != 100) {
		for (int i = 0; i < Teach_in.size(); i++) {
			in[0] = Teach_in[i][0];
			in[1] = Teach_in[i][1];

			double tmp_out = in[0] * w[0] + in[1] * w[1] - theta;
			// ?? outの結果について, 正なら1, 負なら0とあるが, 0のときはどうするのか?
			if (tmp_out >= 0) out = 1;
			else out = 0;

			// 実質的な学習
			if (out != Teach_out[i]) {
				delta = out - Teach_out[i];
				w[0] = w[0] - alpha * delta * in[0];
				w[1] = w[1] - alpha * delta * in[1];
				theta = theta + alpha * delta;

				p = calc_p(w[0], w[1]);

				w_log.push_back(w);
				theta_log.push_back(theta);
				p_log.push_back(p);

				std::cout << w[0] << ", " << w[1] << "," << p << std::endl;
			}

			if (p == 100) break;
		}
	}
}

// SinglePerceptronクラスのメンバ変数, w[]が意図せず操作されるのを嫌うため, 引数として渡す.
// private関数では, pもそうだがなるだけ一時的な変数を介して渡すようにした. (ソフトウェア工学的に有意なことかはわからない…)
double SinglePerceptron::calc_p(double w0, double w1) {
	int correctCount = 0;

	for (int i = 0; i < Teach_in.size(); i++) {
		std::vector<double> tmp_in;
		tmp_in.resize(2);
		double tmp_out;

		tmp_in[0] = Teach_in[i][0];
		tmp_in[1] = Teach_in[i][1];

		double _tmp_out = tmp_in[0] * w0 + tmp_in[1] * w1 - theta;
		if (_tmp_out >= 0) tmp_out = 1;
		else tmp_out = 0;

		if (tmp_out == Teach_out[i]) correctCount++;
	}

	// %表記 (0 - 100)
	double tmp_p = correctCount * 100 / Teach_out.size();

	return tmp_p;
}