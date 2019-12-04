#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"


JanelaPrincipal::JanelaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JanelaPrincipal)
{
    ui->setupUi(this);

}

JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
}


void JanelaPrincipal::on_pushButton_clicked()
{
    ui->label_request->setText("Iniciando Proxy.");
    proxy_socket = create_server_socket("127.0.0.1",8228);
}


void JanelaPrincipal::on_pushButton_2_clicked()
{
    string texto = to_string(proxy_socket);
    QString qstr = QString::fromStdString(texto);
    ui->label_request->setText(qstr);
    request_header = get_request(proxy_socket);
    texto = request_header.host;
    qstr = QString::fromStdString(texto);
    QString::fromStdString(texto);
    ui->label_request->setText(qstr);
}
