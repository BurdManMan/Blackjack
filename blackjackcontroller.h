#ifndef BLACKJACKCONTROLLER_H
#define BLACKJACKCONTROLLER_H

#include <QObject>
#include "deck.h"
#include "handmodel.h"

class BlackjackController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(HandModel* playerHand READ playerHand NOTIFY gameStateChanged)
    Q_PROPERTY(HandModel* dealerHand READ dealerHand NOTIFY gameStateChanged)
    Q_PROPERTY(int playerTotal READ playerTotal NOTIFY gameStateChanged)
    Q_PROPERTY(int dealerTotal READ dealerTotal NOTIFY gameStateChanged)
    Q_PROPERTY(bool revealedDealerHand READ revealedDealerHand NOTIFY gameStateChanged)
    Q_PROPERTY(bool dealerBust READ dealerBust NOTIFY gameStateChanged)
    Q_PROPERTY(bool playerWin READ playerWin NOTIFY gameStateChanged)
    Q_PROPERTY(bool playerLose READ playerLose NOTIFY gameStateChanged)
    Q_PROPERTY(bool draw READ draw NOTIFY gameStateChanged)

public:
    explicit BlackjackController(QObject *parent = nullptr);

    HandModel* playerHand() const;
    HandModel* dealerHand() const;
    int playerTotal() const;
    int dealerTotal() const;
    bool revealedDealerHand() const;
    bool dealerBust() const;
    bool playerWin() const;
    bool playerLose() const;
    bool draw() const;

public slots:
    void hit();
    void stand();
    void reset();

signals:
    void gameStateChanged();

private:
    // data members
    Deck m_deck{true};
    HandModel *m_playerHand;
    HandModel *m_dealerHand;
    bool m_playerBust{false};
    bool m_playerWin{false};
    bool m_playerLose{false};
    bool m_draw{false};
    bool m_dealerBust{false};
    bool m_dealerStand{false};

    // member functions
    void dealersTurn();
};

#endif // BLACKJACKCONTROLLER_H
