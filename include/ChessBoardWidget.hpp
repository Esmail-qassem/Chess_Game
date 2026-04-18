#ifndef CHESS_BOARD_WIDGET_HPP
#define CHESS_BOARD_WIDGET_HPP

#include <QWidget>
#include <QString>
#include <vector>
#include <string>
#include "Board.hpp"
#include "Types.hpp"

class ChessBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChessBoardWidget(QWidget* parent = nullptr);

signals:
    void statusChanged(const QString& message);
    void historyUpdated(const QString& entry);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    static constexpr int SQUARE_SIZE = 80;

    Board        m_board;
    color_t      m_currentTurn;
    bool         m_hasSelection;
    Position_t   m_selectedPos;
    std::vector<Position_t> m_validMoves;
    bool         m_inCheck;
    int          m_moveCounter;

    Position_t   m_whiteKing;
    Position_t   m_blackKing;

    Position_t pixelToPos(int x, int y) const;
    bool       isInValidMoves(const Position_t& pos) const;
    QString    pieceToUnicode(const Piece* piece) const;

    void       findKings();
    bool       detectCheck() const;
    void       switchTurn();
};

#endif
