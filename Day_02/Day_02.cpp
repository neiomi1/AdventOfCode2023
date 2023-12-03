#include "Day_02.h"

#include <chrono>
#include <map>

inline void readEntries(const std::string& filename, std::vector<Game>& games) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_02\\" + filename };

	std::string line;
	while (!file.eof()) {
		std::getline(file, line);

		std::stringstream ss;
		ss.str(line);
		Game game;
		ss >> game;

		std::cout << game << "\n";
		games.push_back(game);
	}
}

inline int part_one(const std::vector<Game>& games, const CubePull& bounds) {
	int sum = 0;
	for (const auto& game : games) {
		sum += game.isValid(&bounds) ? game.id : 0;
	}
	return sum;
}

inline int part_two(const std::vector<Game>& games) {
	int result = 0;
	for (const auto& game : games) {
		result += game.calculateGamePower();
	}
	return result;
}

int main() {
	std::vector<Game> entries;
	CubePull bounds;

	bounds.red = 12;
	bounds.green = 13;
	bounds.blue = 14;

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_02\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	readEntries("input.txt", entries);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Read Entries in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	auto result = part_one(entries, bounds);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Sum of valid Game IDs: " << result << "\n";
	file_time << "Calculated Part One in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	result = part_two(entries);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Sum of all Game Powers: " << result << "\n";
	file_time << "Calculated Part Two in " << duration.count() << " microseconds.\n";
}