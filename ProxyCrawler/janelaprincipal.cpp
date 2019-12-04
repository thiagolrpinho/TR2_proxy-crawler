#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"


JanelaPrincipal::JanelaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JanelaPrincipal)
{
    ui->setupUi(this);
     ui->textEdit_request->setText("Ative o Proxy.");
     ui->textEdit_response->setText("Ative o Proxy.");
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
    browser_proxy_socket = accept(proxy_socket, NULL, NULL);
    request = get_request(browser_proxy_socket);
    qstring_para_conversao = QString::fromStdString(request);
     ui->textEdit_request->setText(qstring_para_conversao);
}

void JanelaPrincipal::on_pushButton_request_clicked()
{
    QString qstring_para_conversao;
    request = ui->textEdit_request->toPlainText().toUtf8().constData();
    request_header = extract_header(request);
    response = send_request_and_receive_response(browser_proxy_socket, request, request_header.host, request_header.porta);
    qstring_para_conversao = QString::fromStdString(response);
    ui->textEdit_response->setText(qstring_para_conversao);
}

void JanelaPrincipal::on_pushButton_response_clicked()
{
    send_back_request(browser_proxy_socket, response);
    ui->textEdit_response->setText("Response enviada");
    ui->textEdit_request->setText("Aguardando nova ativação");
}
