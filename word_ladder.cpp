#include "word_ladder.h"
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <queue>

// Reads in the file from the given path and returns an unordered_set containing all
// words in the file
auto word_ladder::read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
	auto lexicon = std::unordered_set<std::string>();
	auto word = std::string();
	std::fstream in(path);
	while (in >> word) {
		lexicon.insert(word);
	}
	return lexicon;
}

// Returns an unordered_set of all words adjacent to cur
auto find_adjacent_words(
	std::string &cur,
	const std::unordered_set<std::string> &lexicon
) -> std::unordered_set<std::string> {
	auto adjacent = std::unordered_set<std::string>();
	const auto len = cur.length();
	for (auto j = 0u; j < len; j++) {
		const auto letter = cur[j];
		for (auto k = 'a'; k <= 'z'; k++) {
			cur[j] = k;
			if (lexicon.contains(cur)) {
				adjacent.insert(cur);
			}
		}
		cur[j] = letter;
	}
	return adjacent;
}

// Returns all paths by recursively backtracking inside the set of parents vectors
auto build_paths(
	std::vector<std::vector<std::string>> &paths,
	std::vector<std::string> path,
	std::unordered_map<std::string, std::vector<std::string>> &parents,
	const std::string &from,
	const std::string &cur
) -> void {
	if (cur == from) {
		path.push_back(cur);
		paths.push_back(path);
		return;
	}
	for (const auto &parent : parents[cur]) {
		path.push_back(cur);
		build_paths(paths, path, parents, from, parent);
		path.pop_back();
	}
}

// Performs the BFS traversal algorithm from the starting word to dest
auto run_bfs(
	std::queue<std::string> &queue,
	const std::string &dest,
	const std::unordered_set<std::string> &lexicon,
	std::unordered_map<std::string, int> &dist,
	std::unordered_map<std::string, std::vector<std::string>> &parents
) -> void {
	while(!queue.empty()) {
		auto cur = queue.front();
		queue.pop();
		if (cur == dest) {
			break;
		}
		const auto adjacentNodes = find_adjacent_words(cur, lexicon);
		for (const auto &node : adjacentNodes) {
			if (dist[node] > dist[cur] + 1) {
				// If we have found a new shortest path, remove all previous 
				// paths and replace with new shortest path
				dist[node] = dist[cur] + 1;
				queue.push(node);
				parents[node].clear();
				parents[node].push_back(cur);
			} else if (dist[node] == dist[cur] + 1) {
				// If path is of equal length, add cur to the existing set of parents
				parents[node].push_back(cur);
			}
		}
	}
}

auto word_ladder::generate(
	const std::string &from,
	const std::string &to,
	const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
	// Reverse the start and end since our backtracking algorithm will return
	// the paths in reverse order
	const auto start = to;
	const auto dest = from;
	auto queue = std::queue<std::string>();
	auto dist = std::unordered_map<std::string, int>();
	auto parents = std::unordered_map<std::string, std::vector<std::string>>();
	for (auto vertex : lexicon) {
		// Set all entries in dist to maximum possible value
		dist[vertex] = INT32_MAX;
	}
	dist[start] = 0;
	queue.push(start);
	run_bfs(queue, dest, lexicon, dist, parents);
	auto paths = std::vector<std::vector<std::string>>();
	build_paths(paths, {}, parents, start, dest);
	std::sort(paths.begin(), paths.end());
	return paths;
}
