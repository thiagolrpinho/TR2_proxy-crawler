#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QMainWindow>
#include "proxy.hpp"
QT_BEGIN_NAMESPACE
namespace Ui { class JanelaPrincipal; }
QT_END_NAMESPACE

class JanelaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    JanelaPrincipal(QWidget *parent = nullptr);
    ~JanelaPrincipal();
    int proxy_socket, browser_proxy_socket;
    estrutura_request request_header;
    string request, response;

private slots:
    void on_pushButton_clicked();



    void on_pushButton_request_clicked();

    void on_pushButton_response_clicked();


private:
    Ui::JanelaPrincipal *ui;
};
#endif // JANELAPRINCIPAL_H
