#include "FileAccess.h"

FileAccess::FileAccess(std::string path) {
	std::fstream fs(path);

	if (!fs.is_open()) { return; }

	std::string line;
	while (std::getline(fs, line)) {
		m_list.push_back(line);
	}

	fs.close();
}

FileAccess::FileAccess(std::string path, FAO option) {
	std::fstream fs(path);

	if (!fs.is_open()) { return; }

	std::string line;
	bool slas = false;
	while (std::getline(fs, line)) {
		if (option != FAO::rc_all) {
			if (option == FAO::rc_slash) {
				line = line.find("//") != std::string::npos ? line.substr(0, line.find("//")) : line;
			}
			else if (option == FAO::rc_sharp) {
				line = line.find("#") != std::string::npos ? line.substr(0, line.find("#")) : line;
			}
			else if (option == FAO::rc_slas) {
				if (line.find("/*") != std::string::npos) {
					line = line.substr(0, line.find("#"));
					slas = true;
				}
				else if (line.find("*/") != std::string::npos) {
					line = line.substr(line.find("*/") + 2, line.size() - (line.find("*/") + 2) - 1);
					slas = false;
				}
				else if (slas) {
					line = "";
				}
			}
		}
		else {
			line = line.find("//") != std::string::npos ? line.substr(0, line.find("//")) : line;
			line = line.find("#") != std::string::npos ? line.substr(0, line.find("#")) : line;
			if (line.find("/*") != std::string::npos) {
				line = line.substr(0, line.find("#"));
				slas = true;
			}
			else if (line.find("*/") != std::string::npos) {
				line = line.substr(line.find("*/") + 2, line.size() - (line.find("*/") + 2) - 1);
				slas = false;
			}
			else if (slas) {
				line = "";
			}
		}
		m_list.push_back(line);
	}

	fs.close();
}

FileAccess::~FileAccess() {

}

std::string FileAccess::operator[](size_t index) {
	return m_list[index];
}
