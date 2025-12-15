#ifndef HANDMODEL_H
#define HANDMODEL_H

#include <QObject>
#include <QList>
#include <QAbstractListModel>
#include "card.h"

class HandModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        sourceRole = Qt::UserRole + 1,
    };

    explicit HandModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void addCard(const Card &c);
    void clearHand();
    int handTotal();
    bool revealedHand() const;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Card> m_hand;
    bool m_revealedHand{true};
};

#endif // HANDMODEL_H
