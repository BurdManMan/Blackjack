#include <QDebug>
#include "blackjackcontroller.h"

BlackjackController::BlackjackController(QObject *parent)
    : QObject{parent}
{
    m_playerHand = new HandModel(this);
    qDebug() << "m_playerHand created";
    m_dealerHand = new HandModel(this);
    qDebug() << "m_dealerHand created";
    reset();
}

HandModel* BlackjackController::playerHand() const
{
    return m_playerHand;
}

HandModel* BlackjackController::dealerHand() const
{
    return m_dealerHand;
}

int BlackjackController::playerTotal() const
{
    return m_playerHand->handTotal();
}

int BlackjackController::dealerTotal() const
{
    return m_dealerHand->handTotal();
}

bool BlackjackController::revealedDealerHand() const
{
    qDebug() << "[BlackjackController] reavealedDealerHand() -> " << m_dealerHand->revealedHand();
    return m_dealerHand->revealedHand();
}

bool BlackjackController::dealerBust() const
{
    return m_dealerBust;
}

bool BlackjackController::playerWin() const
{
    return m_playerWin;
}

bool BlackjackController::playerLose() const
{
    return m_playerLose;
}

bool BlackjackController::draw() const
{
    return m_draw;
}

void BlackjackController::hit()
{
    m_playerHand->addCard(m_deck.draw());
    if(playerTotal() > 21) m_playerLose = true;
    emit gameStateChanged();
}

void BlackjackController::stand()
{
    dealersTurn();
    if(m_dealerBust){
        m_playerWin = true;
        emit gameStateChanged();
    }
    else if(m_dealerStand)
    {
        int dealerTotal {m_dealerHand->handTotal()};
        int playerTotal {m_playerHand->handTotal()};

        if(dealerTotal > playerTotal)
        {
            m_playerLose = true;
            emit gameStateChanged();
        }
        else if(dealerTotal < playerTotal)
        {
            m_playerWin =  true;
            emit gameStateChanged();
        }
        else
        {
            m_draw = true;
            emit gameStateChanged();
        }
    }
}

void BlackjackController::reset()
{
    m_deck = Deck{true};

    m_playerBust = false;
    m_playerWin = false;
    m_playerLose = false;
    m_draw = false;
    m_dealerBust = false;
    m_dealerStand = false;


    m_playerHand->clearHand();
    m_dealerHand->clearHand();

    m_playerHand->addCard(m_deck.draw());
    m_playerHand->addCard(m_deck.draw());

    m_dealerHand->addCard(m_deck.draw(true));
    m_dealerHand->addCard(m_deck.draw());

    emit gameStateChanged();
}

void BlackjackController::dealersTurn()
{
    while(!m_dealerBust && !m_dealerStand)
    {
        if(m_dealerHand->handTotal() < 17) // dealer hits
        {
            m_dealerHand->addCard(m_deck.draw());
            emit gameStateChanged();
            if(m_dealerHand->handTotal() > 21)
            {
                m_dealerBust = true;
                emit gameStateChanged();
                break;
            }
        }
        else // dealer stands
        {
            m_dealerStand = true;
            emit gameStateChanged();
            break;
        }
    }
}
