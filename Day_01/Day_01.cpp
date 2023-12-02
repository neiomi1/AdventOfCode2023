#include "Day_01.h"

#include <chrono>
#include <map>



inline int part_one(const std::string& filename) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\" + filename };

	int sum = 0;
	std::string line;
	while (!file.eof()) {
		std::getline(file, line);

		char left = -1, right = -1;
		std::string numberCandidate = "";

		for (char c : line) {
			if (isdigit(c)) {
				right = c - '0';
				if (left < 0)
					left = right;
			}
			else {

			}
		}

		sum += 10 * left + right;
	}

	return sum;
}

const char* const numbers[] = {
	"one","two", "three", "four", "five", "six", "seven", "eight", "nine"
};

const std::map<std::string, int> stringNumbers =
{
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9},
};

inline int part_two(const std::string& filename) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\" + filename };

	int sum = 0;
	std::string line;
	while (!file.eof()) {
		std::getline(file, line);

		int left = -1, right = -1;
		std::vector<int> candidates = { 0,1,2,3,4,5,6,7,8 };
		int index = 0;
		std::string numberCandidate = "";

		for (char c : line) {
			if (isdigit(c)) {
				index = 0;

				right = (int) c - '0';
				if (left < 0)
					left = right;
			}
			else {
				if (index == 0) {
					candidates = { 0,1,2,3,4,5,6,7,8 };
					numberCandidate = "";
				}

				std::erase_if(candidates, [&](const int x) {return sizeof(numbers[x]) < index || numbers[x][index] != c; });
				
				numberCandidate += c;
				index++;

				// check if we hit a key
				if (stringNumbers.contains(numberCandidate)) {
					right = stringNumbers.at(numberCandidate);

					if (left < 0)
						left = right;
	
					index = 0;
				}

				// no matches remaining
				if (candidates.size() == 0 || index == 0) {
					index = 0;
					while (numberCandidate.length() > 0) {
						// take away characters from the start until we have a potential match again
						numberCandidate.erase(numberCandidate.begin());
						index = 0;
						candidates = { 0,1,2,3,4,5,6,7,8 };

						for (char cx : numberCandidate) {
							std::erase_if(candidates, [&](const int x) {return sizeof(numbers[x]) < index || numbers[x][index] != cx; });
							index++;
						}

						if (candidates.size() > 0) {
							break;
						}
					}
				}
				
			}
		}
		sum += 10 * left + right;
	}

	return sum;
}

int main() {
	std::vector<std::vector<int>> entries;



	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_01\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	auto sum = part_one("input.txt");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part One done in " << duration.count() << " microseconds.\n";
	std::cout << "Part One: Sum of all calibration values: " << sum << "\n";

	start = std::chrono::high_resolution_clock::now();
	sum = part_two("input.txt");
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part Two done in " << duration.count() << " microseconds.\n";
	std::cout << "Part Two: Sum of all calibration values: " << sum << "\n";

}
