#ifndef CARD_H
#define CARD_H

#include <QUrl>
#include <string_view>

enum class Suit{
    diamond,
    heart,
    club,
    spade,
};

enum class Value{
    ace,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
};

class Card
{
public:
    Card(Suit suit, Value value, bool faceUp=true);
    Suit suit() const;
    Value value() const;
    bool faceUp() const;
    int intValue();
    void flip();
    QUrl cardImageSource() const;

signals:
    void cardImageSourceChanged();

private:
    Suit m_suit;
    Value m_value;
    bool m_faceUp{true};
};

// helper functions
std::string_view suitToString(Suit suit);
std::string_view valueToString(Value value);

#endif // CARD_H
