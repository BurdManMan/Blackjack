#include <string_view>
#include <QDebug>
#include "card.h"

Card::Card(Suit suit, Value value, bool faceUp)
    : m_suit{suit}, m_value{value}, m_faceUp{faceUp}
{
}

Suit Card::suit() const
{
    return m_suit;
}

Value Card::value() const
{
    return m_value;
}

bool Card::faceUp() const
{
    return m_faceUp;
}

int Card::intValue()
{
    switch(m_value)
    {
    case Value::ace: return 1;
    case Value::two: return 2;
    case Value::three: return 3;
    case Value::four: return 4;
    case Value::five: return 5;
    case Value::six: return 6;
    case Value::seven: return 7;
    case Value::eight: return 8;
    case Value::nine: return 9;
    case Value::ten:
    case Value::jack:
    case Value::queen:
    case Value::king: return 10;
    }
}

void Card::flip()
{
    m_faceUp = !m_faceUp;
}

QUrl Card::cardImageSource() const
{
    if(!m_faceUp)
    {
        qDebug() << "[Card] cardImageSource() -> QUrl(\"qrc:/assets/cards/back_light.png\")";
        return QUrl{"qrc:/assets/cards/back_light.png"};
    }

    QUrl url{"qrc:/assets/cards/" + suitToString(m_suit) + "s_" + valueToString(m_value) + ".png"};
    qDebug() << "[Card] cardImageSource() -> " << url;
    return url;
}

//"qrc:/assets/cards/diamonds_A.png"

std::string_view suitToString(Suit suit)
{
    switch(suit)
    {
    case Suit::diamond: return "diamond";
    case Suit::heart: return "heart";
    case Suit::club: return "club";
    case Suit::spade: return "spade";
    default: return "???";
    }
}

std::string_view valueToString(Value value)
{
    switch(value)
    {
    case Value::ace: return "A";
    case Value::two: return "2";
    case Value::three: return "3";
    case Value::four: return "4";
    case Value::five: return "5";
    case Value::six: return "6";
    case Value::seven: return "7";
    case Value::eight: return "8";
    case Value::nine: return "9";
    case Value::ten: return "10";
    case Value::jack: return "J";
    case Value::queen: return "Q";
    case Value::king: return "K";
    }
}
