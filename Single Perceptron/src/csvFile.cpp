#include "csvFile.h"

csvFile::csvFile() {
	// 相対パスで指定している. "data"フォルダにcsvファイルを置いておく.
	inputFileName = "data\\教師信号.csv";
	outputFileName = "data\\DataLog.csv";
}

void csvFile::read() {
	std::ifstream inputFile(inputFileName);
	if (inputFile.fail()) {
		std::cout << "ファイルを開けません.\n";

		// キー入力待ち
		getchar();

		exit(0);
	}
	else std::cout << "ファイルを開きました.\n";

	std::string line;

	// 入力を一行ごとに分割
	while (getline(inputFile, line)) {
		split(line);
	}
	inputFile.close();
}

// 行中での分割
// ?? 教師信号.csvから入力されるデータから, 桁落ちしてしまうがそれはいいのか?
// TODO : データの桁落ちを回避する.
void csvFile::split(std::string& line) {
	std::istringstream lineStream(line);

	int inoutCount = 0;
	Eigen::Vector2d inData;
	std::string field;
	while (getline(lineStream, field, ',')) {
		switch (inoutCount)
		{
		case 0:
			inData[0] = std::stod(field);
			inoutCount++;
			break;

		case 1:
			inData[1] = std::stod(field);
			Teach_in.push_back(inData);
			inoutCount++;
			break;

		case 2:
			Teach_out.push_back(std::stod(field));
			inoutCount++;
			break;

		default:
			break;
		}
	}
}

void csvFile::write(std::vector<Eigen::Vector2d> w_log, std::vector<double> theta_log, std::vector<double> p_log) {
	std::ofstream outputFile(outputFileName);
	outputFile << "w_log[0], w_log[1], theta_log, p_log" << std::endl;

	for (int i = 0; i < w_log.size(); i++)
		outputFile << w_log[i][0] << ", " << w_log[i][1] << ", " << theta_log[i] << ", " << p_log[i] << std::endl;

	outputFile.close();
}