#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_App.h"

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget *parent = nullptr);
    ~App();

private:
    Ui::AppClass ui;
    void LoadData();
    void SlotsConnect();
private slots:
	void on_pushButton_add_clicked();

    void self_on_tableWidget_cellChanged(int row, int column);
    void on_pushButton_delete_item_clicked();
    void on_pushButton_move_up_clicked();
    void on_pushButton_move_down_clicked();
    void on_pushButton_export_clicked();
    void on_pushButton_clear_clicked();
};
