#include "csvFile.h"

csvFile::csvFile() {
	// ���΃p�X�Ŏw�肵�Ă���. "data"�t�H���_��csv�t�@�C����u���Ă���.
	inputFileName = "data\\���t�M��.csv";
	outputFileName = "data\\DataLog.csv";
}

void csvFile::read() {
	std::ifstream inputFile(inputFileName);
	if (inputFile.fail()) {
		std::cout << "�t�@�C�����J���܂���.\n";

		// �L�[���͑҂�
		getchar();

		exit(0);
	}
	else std::cout << "�t�@�C�����J���܂���.\n";

	std::string line;

	// ���͂���s���Ƃɕ���
	while (getline(inputFile, line)) {
		split(line);
	}
	inputFile.close();
}

// �s���ł̕���
// ?? ���t�M��.csv������͂����f�[�^����, ���������Ă��܂�������͂����̂�?
// TODO : �f�[�^�̌��������������.
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