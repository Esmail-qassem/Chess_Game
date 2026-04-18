#include "ChessBoardWidget.hpp"
#include <QPainter>
#include <QMouseEvent>
#include <QFont>

static const QColor LIGHT_SQUARE  = QColor(240, 217, 181);
static const QColor DARK_SQUARE   = QColor(181, 136,  99);
static const QColor SELECT_COLOR  = QColor(100, 200, 100, 180);
static const QColor MOVE_COLOR    = QColor(100, 200, 100, 120);
static const QColor CHECK_COLOR   = QColor(220,  50,  50, 180);

ChessBoardWidget::ChessBoardWidget(QWidget* parent)
    : QWidget(parent)
    , m_currentTurn(color_t::white)
    , m_hasSelection(false)
    , m_selectedPos({0, 0})
    , m_inCheck(false)
    , m_moveCounter(0)
{
    setFixedSize(SQUARE_SIZE * 8, SQUARE_SIZE * 8);
    m_board.initialize();
    findKings();
    emit statusChanged("White's turn");
}

// ── coordinate helpers ────────────────────────────────────────────────────────

Position_t ChessBoardWidget::pixelToPos(int x, int y) const
{
    // row 0 is displayed at the bottom (rank 1)
    int col = x / SQUARE_SIZE;
    int row = 7 - (y / SQUARE_SIZE);
    return {row, col};
}

bool ChessBoardWidget::isInValidMoves(const Position_t& pos) const
{
    for (const auto& m : m_validMoves)
        if (m.row == pos.row && m.col == pos.col)
            return true;
    return false;
}

// ── piece → unicode glyph ─────────────────────────────────────────────────────

QString ChessBoardWidget::pieceToUnicode(const Piece* piece) const
{
    if (!piece) return "";
    bool white = piece->getColor() == color_t::white;
    switch (piece->getType())
    {
        case PieceType_t::King:   return white ? "♔" : "♚";
        case PieceType_t::Queen:  return white ? "♕" : "♛";
        case PieceType_t::Rook:   return white ? "♖" : "♜";
        case PieceType_t::Bishop: return white ? "♗" : "♝";
        case PieceType_t::Knight: return white ? "♘" : "♞";
        case PieceType_t::Pawn:   return white ? "♙" : "♟";
    }
    return "";
}

// ── find both kings on the board ──────────────────────────────────────────────

void ChessBoardWidget::findKings()
{
    for (int r = 0; r < BOARD_ROWS; r++)
    {
        for (int c = 0; c < BOARD_COLS; c++)
        {
            Position_t pos = {r, c};
            const Piece* p = m_board.getPieceAt(pos);
            if (!p) continue;
            if (p->getSymbol() == 'K') m_whiteKing = pos;
            if (p->getSymbol() == 'k') m_blackKing = pos;
        }
    }
}

// ── check detection: any enemy piece attacks the current player's king? ───────

bool ChessBoardWidget::detectCheck() const
{
    const Position_t& kingPos = (m_currentTurn == color_t::white) ? m_whiteKing : m_blackKing;

    for (int r = 0; r < BOARD_ROWS; r++)
    {
        for (int c = 0; c < BOARD_COLS; c++)
        {
            Position_t pos = {r, c};
            const Piece* p = m_board.getPieceAt(pos);
            if (!p) continue;
            if (p->getColor() == m_currentTurn) continue; // skip friendly pieces

            auto attackMoves = p->getValidMoves(pos, m_board);
            for (const auto& m : attackMoves)
                if (m.row == kingPos.row && m.col == kingPos.col)
                    return true;
        }
    }
    return false;
}

// ── switch turn and update status ─────────────────────────────────────────────

void ChessBoardWidget::switchTurn()
{
    m_currentTurn = (m_currentTurn == color_t::white) ? color_t::black : color_t::white;
    findKings();
    m_inCheck = detectCheck();

    QString status;
    if (m_inCheck)
        status = (m_currentTurn == color_t::white) ? "White is in CHECK!" : "Black is in CHECK!";
    else
        status = (m_currentTurn == color_t::white) ? "White's turn" : "Black's turn";

    emit statusChanged(status);
}

// ── paint ─────────────────────────────────────────────────────────────────────

void ChessBoardWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont pieceFont("Arial", 44);
    painter.setFont(pieceFont);

    const Position_t& kingPos = (m_currentTurn == color_t::white) ? m_whiteKing : m_blackKing;

    for (int row = 0; row < BOARD_ROWS; row++)
    {
        for (int col = 0; col < BOARD_COLS; col++)
        {
            // display: row 7 at top, row 0 at bottom
            int screenRow = 7 - row;
            int x = col * SQUARE_SIZE;
            int y = screenRow * SQUARE_SIZE;

            // base square color
            QColor squareColor = ((row + col) % 2 == 0) ? LIGHT_SQUARE : DARK_SQUARE;
            painter.fillRect(x, y, SQUARE_SIZE, SQUARE_SIZE, squareColor);

            // highlight: king in check
            if (m_inCheck && row == kingPos.row && col == kingPos.col)
                painter.fillRect(x, y, SQUARE_SIZE, SQUARE_SIZE, CHECK_COLOR);

            // highlight: selected square
            if (m_hasSelection && row == m_selectedPos.row && col == m_selectedPos.col)
                painter.fillRect(x, y, SQUARE_SIZE, SQUARE_SIZE, SELECT_COLOR);

            // highlight: valid move targets
            Position_t here = {row, col};
            if (isInValidMoves(here))
            {
                if (m_board.getPieceAt(here))
                {
                    // enemy piece on valid move square — draw a ring
                    painter.setPen(QPen(QColor(80, 180, 80), 5));
                    painter.setBrush(Qt::NoBrush);
                    painter.drawEllipse(x + 4, y + 4, SQUARE_SIZE - 8, SQUARE_SIZE - 8);
                    painter.setPen(Qt::NoPen);
                }
                else
                {
                    // empty square — draw a dot
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(MOVE_COLOR);
                    int dotSize = SQUARE_SIZE / 3;
                    int offset  = (SQUARE_SIZE - dotSize) / 2;
                    painter.drawEllipse(x + offset, y + offset, dotSize, dotSize);
                }
            }

            // draw piece
            const Piece* piece = m_board.getPieceAt(here);
            if (piece)
            {
                painter.setPen(piece->getColor() == color_t::white ? Qt::white : Qt::black);
                painter.drawText(QRect(x, y, SQUARE_SIZE, SQUARE_SIZE),
                                 Qt::AlignCenter,
                                 pieceToUnicode(piece));
            }
        }
    }

    // rank/file labels
    QFont labelFont("Arial", 10);
    painter.setFont(labelFont);
    painter.setPen(QColor(100, 100, 100));
    for (int i = 0; i < 8; i++)
    {
        // rank numbers (1-8) on left edge
        int screenRow = 7 - i;
        painter.drawText(2, screenRow * SQUARE_SIZE + 14, QString::number(i + 1));
        // file letters (a-h) on bottom edge
        painter.drawText(i * SQUARE_SIZE + SQUARE_SIZE - 14,
                         BOARD_ROWS * SQUARE_SIZE - 2,
                         QString(QChar('a' + i)));
    }
}

// ── mouse click ───────────────────────────────────────────────────────────────

void ChessBoardWidget::mousePressEvent(QMouseEvent* event)
{
    Position_t clicked = pixelToPos(event->pos().x(), event->pos().y());

    if (clicked.row < 0 || clicked.row >= BOARD_ROWS ||
        clicked.col < 0 || clicked.col >= BOARD_COLS)
        return;

    if (!m_hasSelection)
    {
        // first click — select a piece
        const Piece* piece = m_board.getPieceAt(clicked);
        if (!piece || piece->getColor() != m_currentTurn)
        {
            emit statusChanged(piece ? "Not your piece" : "No piece there");
            return;
        }

        // if in check, only allow selecting the king
        if (m_inCheck)
        {
            const Position_t& kingPos = (m_currentTurn == color_t::white) ? m_whiteKing : m_blackKing;
            if (clicked.row != kingPos.row || clicked.col != kingPos.col)
            {
                emit statusChanged("You are in check! Move your king.");
                return;
            }
        }

        m_hasSelection  = true;
        m_selectedPos   = clicked;
        m_validMoves    = piece->getValidMoves(clicked, m_board);
    }
    else
    {
        // second click — attempt move
        if (isInValidMoves(clicked))
        {
            m_board.movePiece(m_selectedPos, clicked);

            // record history
            m_moveCounter++;
            QString entry = QString::number(m_moveCounter) + ". " +
                            QChar('a' + m_selectedPos.col) +
                            QString::number(m_selectedPos.row + 1) + " " +
                            QChar('a' + clicked.col) +
                            QString::number(clicked.row + 1);
            emit historyUpdated(entry);

            m_hasSelection = false;
            m_validMoves.clear();
            switchTurn();
        }
        else
        {
            // clicked a different friendly piece — reselect
            const Piece* piece = m_board.getPieceAt(clicked);
            if (piece && piece->getColor() == m_currentTurn)
            {
                if (m_inCheck)
                {
                    const Position_t& kingPos = (m_currentTurn == color_t::white) ? m_whiteKing : m_blackKing;
                    if (clicked.row != kingPos.row || clicked.col != kingPos.col)
                    {
                        emit statusChanged("You are in check! Move your king.");
                        return;
                    }
                }
                m_selectedPos = clicked;
                m_validMoves  = piece->getValidMoves(clicked, m_board);
            }
            else
            {
                m_hasSelection = false;
                m_validMoves.clear();
            }
        }
    }

    update();
}
