#pragma once

#include <string>
#include <vector>

/// Check if the given string contains the given token
[[nodiscard]] bool contains(std::string const &input, std::string const &searchToken);

/// Check if the given string starts with the given token
[[nodiscard]] bool startsWith(std::string const &input, std::string const &searchToken);

/// Check if the given string ends with the given token
[[nodiscard]] bool endsWith(std::string const &input, std::string const &searchToken);

/// Cut characters off either end of a string
[[nodiscard]] std::string subString(std::string const &input, unsigned int const &distFromStart, unsigned int const &distFromEnd);

/// Trim leading and trailing whitespace
[[nodiscard]] std::string trim(std::string const &input);

/// Remove all occurences of the given character from the input string
[[nodiscard]] std::string remove(std::string const &input, char const &remove);

/// Remove all occurences of any of the given characters from the input string
[[nodiscard]] std::string removeMult(std::string const &input, std::vector<char> const &remove);

/// Split a string on the given character
[[nodiscard]] std::vector<std::string> split(std::string const &input, char const &splitOn, bool const removeMatches);

/// Split a string on any of the given characters
[[nodiscard]] std::vector<std::string> splitMult(std::string const &input, std::vector<char> const &splitOn, bool const removeMatches);

/// Split a string on the given word
[[nodiscard]] std::vector<std::string> splitSeq(std::string const &input, std::string const &splitOn, bool const removeMatches);

/// Split a string on any of the given words
[[nodiscard]] std::vector<std::string> splitSeqMult(std::string const &input, std::vector<std::string> const &splitOn, bool const removeMatches);

/// Replace all instances of a character with another
[[nodiscard]] std::string replaceAll(std::string const &input, char const &searchFor, char const &replaceWith);
