#include "word_ladder.h"

#include <catch2/catch.hpp>

TEST_CASE("work->play using english.txt") {
	const auto lexicon = word_ladder::read_lexicon("english.txt");
	const auto expected = std::vector<std::vector<std::string>>{
		{"work", "fork", "form", "foam", "flam", "flay", "play"},
		{"work", "pork", "perk", "peak", "pean", "plan", "play"},
		{"work", "pork", "perk", "peak", "peat", "plat", "play"},
		{"work", "pork", "perk", "pert", "peat", "plat", "play"},
		{"work", "pork", "porn", "pirn", "pian", "plan", "play"},
		{"work", "pork", "port", "pert", "peat", "plat", "play"},
		{"work", "word", "wood", "pood", "plod", "ploy", "play"},
		{"work", "worm", "form", "foam", "flam", "flay", "play"},
		{"work", "worn", "porn", "pirn", "pian", "plan", "play"},
		{"work", "wort", "bort", "boat", "blat", "plat", "play"},
		{"work", "wort", "port", "pert", "peat", "plat", "play"},
		{"work", "wort", "wert", "pert", "peat", "plat", "play"}
	};

	const auto ladders = word_ladder::generate("work", "play", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("ate->bee using english.txt") {
	const auto lexicon = word_ladder::read_lexicon("english.txt");
	const auto expected = std::vector<std::vector<std::string>>{
		{"ate", "aye", "bye", "bee"}
	};

	const auto ladders = word_ladder::generate("ate", "bee", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("at->be using english.txt") {
	const auto lexicon = word_ladder::read_lexicon("english.txt");
	const auto expected = std::vector<std::vector<std::string>>{
		{"at", "ae", "be"}
	};

	const auto ladders = word_ladder::generate("at", "be", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("a->b") {
			const auto lexicon = std::unordered_set<std::string>{
		"a", "b", "c", "d", "e"
		};

		const auto expected = std::vector<std::vector<std::string>>{
			{"a", "b"}
		};

		const auto ladders = word_ladder::generate("a", "b", lexicon);

		CHECK(ladders == expected);
	}

TEST_CASE("at->to: single path") {
		const auto lexicon = std::unordered_set<std::string>{
	"at", "bt", "et", "tt", "to"
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"at", "tt", "to"}
	};

	const auto ladders = word_ladder::generate("at", "to", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("at->to: multiple paths") {
		const auto lexicon = std::unordered_set<std::string>{
	"at", "bt", "et", "tt", "to", "ao"
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"at", "ao", "to"},
		{"at", "tt", "to"}
	};

	const auto ladders = word_ladder::generate("at", "to", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("ate->pay: single path") {
	const auto lexicon = std::unordered_set<std::string>{
		"ate", "pay", "ade", "bte", "ata", "pey", "pav", "pte", "aty", "pae"
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"ate", "pte", "pae", "pay"}
	};

	const auto ladders = word_ladder::generate("ate", "pay", lexicon);

	CHECK(ladders == expected);
}


TEST_CASE("ate->pay: multiple paths") {
	const auto lexicon = std::unordered_set<std::string>{
		"ate", "pay", "ade", "bte", "ata", "pey", "pav", "pte", "pae", "aty", "pty"
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"ate", "aty", "pty", "pay"},
		{"ate", "pte", "pae", "pay"},
		{"ate", "pte", "pty", "pay"}
	};

	const auto ladders = word_ladder::generate("ate", "pay", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("adam->acai: single path") {
	const auto lexicon = std::unordered_set<std::string>{
		"adam", "adan", "bdam", "bdan", "adai", "acai"
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"adam", "adai", "acai"}
	};

	const auto ladders = word_ladder::generate("adam", "acai", lexicon);

	CHECK(expected == ladders);
}

TEST_CASE("adam->acai: multiple paths") {
	const auto lexicon = std::unordered_set<std::string>{
		"adam", "adan", "bdam", "bdan", "adai", "acai", "acam" 
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"adam", "acam", "acai"},
		{"adam", "adai", "acai"},
	};

	const auto ladders = word_ladder::generate("adam", "acai", lexicon);

	CHECK(expected == ladders);
}

TEST_CASE("adam->chen: multiple paths") {
	const auto lexicon = std::unordered_set<std::string>{
		"adam", "bdam", "cdam", "ddam", "aham", "apam", "aham", "cham",
		"adem", "chem", "cdem", "ahen", "cden", "chen" 
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{ "adam", "adem", "cdem", "cden", "chen" },
		{ "adam", "adem", "cdem", "chem", "chen" },
		{ "adam", "aham", "cham", "chem", "chen" },
		{ "adam", "cdam", "cdem", "cden", "chen" },
		{ "adam", "cdam", "cdem", "chem", "chen" },
		{ "adam", "cdam", "cham", "chem", "chen" }
	};

	const auto ladders = word_ladder::generate("adam", "chen", lexicon);

	CHECK(expected == ladders);
}

TEST_CASE("no path from start to destination") {
	const auto lexicon = std::unordered_set<std::string>{
		"adam", "bdam", "cdam", "ddam", "aham", "apam", "aham", "cham",
		"adem", "cdem", "ahen", "chen" 
	};

	const auto expected = std::vector<std::vector<std::string>>{};

	const auto ladders = word_ladder::generate("adam", "chen", lexicon);

	CHECK(expected == ladders);
}

