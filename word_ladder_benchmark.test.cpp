#include "word_ladder.h"

#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("atlases -> cabaret") {
	auto const english_lexicon = word_ladder::read_lexicon("src/english.txt");
	auto const ladders = word_ladder::generate("atlases", "cabaret", english_lexicon);
	const auto expected = std::vector<std::vector<std::string>>{};
	std::cout << std::size(ladders[0]) << '\n';
	std::cout << std::size(ladders) << '\n';
	CHECK(std::size(ladders) != 0);
	// CHECK(ladders == expected);
}
