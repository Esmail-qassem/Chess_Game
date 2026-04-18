#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStatusBar>
#include <QWidget>
#include "ChessBoardWidget.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Chess");

    // central widget holds the board + history panel side by side
    QWidget* central = new QWidget(&window);
    QHBoxLayout* layout = new QHBoxLayout(central);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(12);

    ChessBoardWidget* board = new ChessBoardWidget(central);
    layout->addWidget(board);

    // move history panel
    QListWidget* historyList = new QListWidget(central);
    historyList->setFixedWidth(160);
    historyList->setStyleSheet("font-size: 13px;");
    layout->addWidget(historyList);

    window.setCentralWidget(central);

    // status bar shows turn / check messages
    QObject::connect(board, &ChessBoardWidget::statusChanged,
                     [&window](const QString& msg){ window.statusBar()->showMessage(msg); });

    // history panel gets each move appended
    QObject::connect(board, &ChessBoardWidget::historyUpdated,
                     [historyList](const QString& entry){ historyList->addItem(entry); });

    window.statusBar()->showMessage("White's turn");
    window.adjustSize();
    window.show();

    return app.exec();
}
