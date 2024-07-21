#include "App.h"
#include <QStandardItemModel>
#include <QStyleFactory>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <xlsxwriter.h>

App::App(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowIcon(QIcon(":/image/logo"));
    setWindowTitle("东莞城市学院GPA计算器");
    LoadData();
    SlotsConnect();
}

App::~App()
{
}

void App::LoadData()
{
    QVector<QString> data = {
        "数字逻辑与数字电路",
        "Web前端技术",
        "数据结构实训",
        "大学英语（一）4",
        "毛泽东思想和中国特色社会主义理论体系概论",
        "形势与政策4",
        "习近平新时代中国特色社会主义思想概论",
        "大学体育4",
        "劳动教育4",
        "电工电子实习",
        "概率论与数理统计",
        "离散数学",
        "面向对象程序设计",
        "认知实习",
        "大学英语（一）3",
        "马克思主义基本原理概论",
        "形势与政策3",
        "大学体育3",
        "劳动教育3",
        "创新创业教育"
    };
    ui.comboBox->clear();
    ui.comboBox->addItems(data);
    ui.lcdNumber_GPA->display("0.000");
    ui.lcdnumber_super_score->display("00.00");

    ui.tableWidget->clear();
    ui.tableWidget->setColumnCount(3);
    ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "课程"
                                                            << "学分"
                                                            << "成绩");
    ui.tableWidget->setColumnWidth(0, ui.tableWidget->width() - 60 * 2 - 30);
    ui.tableWidget->setColumnWidth(1, 60);
    ui.tableWidget->setColumnWidth(2, 60);
}

void App::SlotsConnect()
{
    // connect(ui.pushButton_add, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui.tableWidget, &QTableWidget::cellChanged, this, &App::self_on_tableWidget_cellChanged);
}

void App::on_pushButton_add_clicked()
{
    if (ui.comboBox->count() <= 0)
        return;

    // 先断开table的slot连接
    disconnect(ui.tableWidget, &QTableWidget::cellChanged, this, &App::self_on_tableWidget_cellChanged);

    int subject = ui.comboBox->currentIndex();
    double credit = ui.lineEdit_credit->text().toDouble();
    double score = ui.lineEdit_score->text().toDouble();
    int insert_index = ui.tableWidget->rowCount();

    QTableWidgetItem *item_subject = new QTableWidgetItem(ui.comboBox->currentText());
    QTableWidgetItem *item_credit = new QTableWidgetItem(QString::number(credit));
    QTableWidgetItem *item_score = new QTableWidgetItem(QString::number(score));

    ui.tableWidget->insertRow(insert_index);
    ui.tableWidget->setItem(insert_index, 0, item_subject);
    ui.tableWidget->setItem(insert_index, 1, item_credit);
    ui.tableWidget->setItem(insert_index, 2, item_score);

    ui.lineEdit_credit->clear();
    ui.lineEdit_score->clear();

    // 恢复连接
    connect(ui.tableWidget, &QTableWidget::cellChanged, this, &App::self_on_tableWidget_cellChanged);

    // 触发一次计算
    self_on_tableWidget_cellChanged(0, 0);
    // 删除combox的选中项
    ui.comboBox->removeItem(subject);
    // 选中最后一行
    ui.tableWidget->setCurrentCell(insert_index, ui.tableWidget->currentColumn());
}

void App::self_on_tableWidget_cellChanged(int row, int column)
{
    // 公式:平均绩点=(课程学分*课程绩点)/总学分
    // 公式:综测分=平均绩点*35*63%
    // 60分以下绩点为0
    // 60分有1绩点,之后每1分,就是0.1绩点
    // 例如:95分:4.5绩点
    // 例如:78分:2.8绩点

    // 备注:所有数据最多显示两位小数,后面的四舍五入

    double total_credit = 0;
    double total_gpa = 0;
    int count = ui.tableWidget->rowCount();
    for (int i = 0; i < count; i++)
    {
        double temp_credit = ui.tableWidget->item(i, 1)->text().toDouble();
        double temp_source = ui.tableWidget->item(i, 2)->text().toDouble();
        total_credit += temp_credit;
        if (temp_source >= 60)
        {
            double temp_gpa = (temp_source - 60) * 0.1 + 1;
            total_gpa += temp_credit * temp_gpa;
        }
        else
        {
            total_gpa += 0;
        }
    }

    double avg_gpa = total_gpa / total_credit;
    double super_score = avg_gpa * 35 * 0.63;

    ui.lcdNumber_GPA->display(QString::number(avg_gpa, 'f', 2));
    ui.lcdnumber_super_score->display(QString::number(super_score, 'f', 2));
}

// 删除
void App::on_pushButton_delete_item_clicked()
{
    int id = ui.tableWidget->currentRow();
    QString subject = ui.tableWidget->item(id, 0)->text();
    ui.tableWidget->removeRow(id);
    ui.comboBox->addItem(subject);
}

// 上移
void App::on_pushButton_move_up_clicked()
{
    disconnect(ui.tableWidget, &QTableWidget::cellChanged, this, &App::self_on_tableWidget_cellChanged);
    int id = ui.tableWidget->currentRow();

    if (id == 0)
    {
        return;
    }
    else
    {
        auto a = ui.tableWidget->takeItem(id, 0);
        auto b = ui.tableWidget->takeItem(id, 1);
        auto c = ui.tableWidget->takeItem(id, 2);
        ui.tableWidget->removeRow(id);
        ui.tableWidget->insertRow(id - 1);
        ui.tableWidget->setItem(id - 1, 0, a);
        ui.tableWidget->setItem(id - 1, 1, b);
        ui.tableWidget->setItem(id - 1, 2, c);
        ui.tableWidget->setCurrentCell(id - 1, ui.tableWidget->currentColumn());
    }

    connect(ui.tableWidget, &QTableWidget::cellChanged, this, &App::self_on_tableWidget_cellChanged);
}

// 下移
void App::on_pushButton_move_down_clicked()
{
    disconnect(ui.tableWidget, &QTableWidget::cellChanged, this, &App::self_on_tableWidget_cellChanged);
    int id = ui.tableWidget->currentRow();
    if (id == ui.tableWidget->rowCount() - 1)
    {
        return;
    }
    else
    {
        auto a = ui.tableWidget->takeItem(id, 0);
        auto b = ui.tableWidget->takeItem(id, 1);
        auto c = ui.tableWidget->takeItem(id, 2);
        ui.tableWidget->removeRow(id);
        ui.tableWidget->insertRow(id + 1);
        ui.tableWidget->setItem(id + 1, 0, a);
        ui.tableWidget->setItem(id + 1, 1, b);
        ui.tableWidget->setItem(id + 1, 2, c);
        ui.tableWidget->setCurrentCell(id + 1, ui.tableWidget->currentColumn());
    }
    connect(ui.tableWidget, &QTableWidget::cellChanged, this, &App::self_on_tableWidget_cellChanged);
}

// 导出
void App::on_pushButton_export_clicked()
{
    int xlsx_RowIndex = 0;
    QString path_export = "";
    path_export = QFileDialog::getSaveFileName(this, "导出", QDir::homePath() + "/desktop/导出.xlsx", "Excel Files (*.xlsx)");
    

    if (path_export.isEmpty())
    {
        return;
    }

    // 创建一个新的Excel文件
    lxw_workbook *workbook = workbook_new(path_export.toStdString().c_str());
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, "Sheet1");

    // 创建一组样式
    lxw_format *format = workbook_add_format(workbook);
    format_set_bold(format);
    format_set_align(format, LXW_ALIGN_CENTER);
    format_set_align(format, LXW_ALIGN_VERTICAL_CENTER);

    // 表头
    worksheet_write_string(worksheet, xlsx_RowIndex, 0, "课程", format);
    worksheet_write_string(worksheet, xlsx_RowIndex, 1, "学分", format);
    worksheet_write_string(worksheet, xlsx_RowIndex, 2, "成绩", format);

    // 设置第一列长度
    worksheet_set_column(worksheet, 0, 0, 30, NULL); // 第二第三个参数的意思:从第0列到第0列

    xlsx_RowIndex++; // 从第二行开始写入数据

    int count = ui.tableWidget->rowCount();
    for (int i = 0; i < count; i++)
    {

        worksheet_write_string(worksheet, i + xlsx_RowIndex, 0, ui.tableWidget->item(i, 0)->text().toStdString().c_str(), format);
        worksheet_write_number(worksheet, i + xlsx_RowIndex, 1, ui.tableWidget->item(i, 1)->text().toDouble(), format);
        worksheet_write_number(worksheet, i + xlsx_RowIndex, 2, ui.tableWidget->item(i, 2)->text().toDouble(), format);
    }

    // 在表的右侧添加平均绩点和综测分
    worksheet_write_string(worksheet, 0, 4, "平均绩点", format);
    worksheet_write_number(worksheet, 0, 5, ui.lcdNumber_GPA->value(), format);
    worksheet_write_string(worksheet, 1, 4, "综测分", format);
    worksheet_write_number(worksheet, 1, 5, ui.lcdnumber_super_score->value(), format);

    workbook_close(workbook);
    QMessageBox::information(this, "提示", "导出成功", QMessageBox::Ok);
}

// 清空
void App::on_pushButton_clear_clicked()
{
    ui.tableWidget->setRowCount(0);
    LoadData();
}
