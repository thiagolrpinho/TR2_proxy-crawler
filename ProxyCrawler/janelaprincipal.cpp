#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"


JanelaPrincipal::JanelaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JanelaPrincipal)
{
    ui->setupUi(this);
    ui->label_request->setText("Iniciando Proxy.");
    proxy_socket = create_server_socket("127.0.0.1",8228);

}

JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
    shutdown(proxy_socket, SHUT_RDWR);
}


void JanelaPrincipal::on_pushButton_clicked()
{
    QString qstring_para_conversao;
    request = get_request(proxy_socket);
    qstring_para_conversao = QString::fromStdString(request);
    ui->label_request->setText(qstring_para_conversao);
}
