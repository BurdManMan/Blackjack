#include <algorithm>
#include <vector>
#include "card.h"
#include "deck.h"
#include "random.h"

Deck::Deck(bool shuffled)
{
    for(int i{0}; i < 4; i++)
    {
        for(int j{0}; j < 13; j++)
        {
            Card c{static_cast<Suit>(i), static_cast<Value>(j)};
            m_deck.push_back(c);
        }
    }

    if(shuffled) shuffle();
}

Card Deck::draw(bool flip)
{
    Card last{ m_deck.back() };
    m_deck.pop_back();
    if(flip)
        last.flip();
    return last;
}

void Deck::shuffle()
{
    std::shuffle(m_deck.begin(), m_deck.end(), Random::mt);
}
