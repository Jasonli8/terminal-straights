#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <memory>
#include "deck.h"

// Big 5 //////////////////////////////

Deck::Deck(std::vector<char> * ranks, std::vector<char> * suites, int seed) : cards{}, seed{seed} {
	for (auto &i : *ranks) {
		for (auto &j : *suites) {
			cards.emplace_back(std::make_unique<Card> (i, j, ranks, suites));
		}
	}
}

Deck::~Deck() {}

// Functions ///////////////////////////////
void Deck::shuffle() {
	std::default_random_engine shuffler{seed};
	std::shuffle(cards.begin(), cards.end(), shuffler);
}

// FOR DEBUGGING AND MARKING
void Deck::printDeck() {
	int count = 0;
	for (int i = 0; i < cards.size(); i++) {
		Card * card = cards[i].get();
		std::cout<<*card<<" ";
		count++;
		if (count == 13) {
			std::cout<<std::endl;
			count = 0;
		}
	}
}

// Getters

Card * Deck::cardAt(int ind) {
	return cards[ind].get();
}
