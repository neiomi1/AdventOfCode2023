#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

struct CubePull {
	int red;
	int green;
	int blue;

	bool inBounds(const CubePull *bounds) const {
		return this->blue <= bounds->blue && this->green <= bounds->green && this->red <= bounds->red;
	}

	void max(CubePull& max) const {
		max.red = std::max(max.red, this->red);
		max.green = std::max(max.green, this->green);
		max.blue = std::max(max.blue, this->blue);
	}

	int power() const {
		return this->red * this->blue * this->green;
	}

	friend std::ostream& operator<< (std::ostream& os, CubePull& pull) {
		std::vector<std::string> toAdd;

		if (pull.red > 0)
			toAdd.push_back(std::to_string(pull.red) + " red");
		if (pull.green > 0)
			toAdd.push_back(std::to_string(pull.green) + " green");
		if (pull.blue > 0)
			toAdd.push_back(std::to_string(pull.blue) + " blue");

		for (auto it = begin(toAdd); it != end(toAdd); ++it) {
			if (it + 1 == end(toAdd)) {
				os << " " << *it << ";";
			}
			else {
				os << " " << *it << ",";
			}
		}

		return os;
	}
};

struct Game {
	int id;
	std::vector<CubePull> pulls;

	bool isValid(const CubePull *bounds) const {
		bool result = true;
		for (const auto pull : pulls) {
			result &= pull.inBounds(bounds);
			if (!result) {
				return result;
			}
		}
		return result;
	}

	int calculateGamePower() const {
		CubePull max{};
		for (const auto& pull : pulls) {
			pull.max(max);
		}
		return max.power();
	}

	friend std::istream& operator>>(std::istream& is, Game& g)
	{
		std::string colour;
		int amount;
		char c;

		is >> colour >> g.id >> c;

	
		auto pullComplete = false;
		auto pull = new CubePull();

		while (is.peek() != EOF) {
			is >> amount;
			is >> colour;

			if (colour[colour.length() - 1] == ';') {
				pullComplete = true;
				colour.pop_back();
			}

			if (colour[colour.length() - 1] == ',') {
				colour.pop_back();
			}

			if (colour == "red") pull->red = amount;
			else if (colour == "blue") pull->blue = amount;
			else if (colour == "green") pull->green = amount;

			if (pullComplete) {
				g.pulls.push_back(*pull);
				pull = new CubePull();
				pullComplete = false;
			}
		}
		g.pulls.push_back(*pull);
		return is;
	}

	friend std::ostream& operator<< (std::ostream& os, Game& game) {
		os << "Game " << game.id << ":";
		for (auto pull : game.pulls) {
			os << pull;
		}
		return os;
	}
};
