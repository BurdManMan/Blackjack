#include <QDebug>
#include "card.h"
#include "handmodel.h"

HandModel::HandModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int HandModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return m_hand.size();
}

QVariant HandModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= m_hand.size())
        return {};

    const Card &c = m_hand[index.row()];

    switch (role)
    {
    case sourceRole:
        return c.cardImageSource();
    }

    return {};
}

void HandModel::addCard(const Card &c)
{
    qDebug() << "Card added to hand";
    beginInsertRows(QModelIndex(), m_hand.size(), m_hand.size());
    m_hand.append(c);
    if(!c.faceUp()) m_revealedHand = false;
    endInsertRows();
}

void HandModel::clearHand()
{
    qDebug() << "Hand cleared";
    beginResetModel();
    m_hand.clear();
    endResetModel();
}

int HandModel::handTotal()
{
    int total{ 0 };
    int aces{ 0 };
    bool faceDownFound{false};
    for(Card card : m_hand)
    {
        if(!card.faceUp()) faceDownFound = true;
        if(card.value() == Value::ace)
        {
            aces++;
        }
        else
        {
            total += card.intValue();
        }
    }

    for(int i{0}; i < aces; i++)
    {
        if(total + 11 > 21) total += 1;
        else total += 11;
    }

    faceDownFound ? m_revealedHand = true : m_revealedHand = false;

    return total;
}

bool HandModel::revealedHand() const
{
    return m_revealedHand;
}


QHash<int, QByteArray> HandModel::roleNames() const
{
    return {{sourceRole, "source"}};
}
