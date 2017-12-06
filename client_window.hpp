#ifndef CLIENT_WINDOW_HPP
#define CLIENT_WINDOW_HPP

#include <QMainWindow>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = 0);
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;
};

#endif // CLIENT_WINDOW_HPP
