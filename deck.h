#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Deck
{
public:
    Deck(bool shuffled=false);

    Card draw(bool flip=false);
    void shuffle();
private:
    std::vector<Card> m_deck{};
};

#endif // DECK_H
