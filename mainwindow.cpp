#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , searchEngine(new SearchEngine(this))
{
    ui->setupUi(this);

    // 仅连接searchButton（selectDirectoryButton已在UI文件中自动连接）
    connect(ui->searchButton, &QPushButton::clicked,
            this, &MainWindow::on_searchButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_selectDirectoryButton_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "选择目录");
    if (!dir.isEmpty()) {
        currentDir.setPath(dir);
        ui->directoryLineEdit->setText(dir);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        searchEngine->buildIndex(currentDir);
        QApplication::restoreOverrideCursor();
    }
}

void MainWindow::on_searchButton_clicked() {
    if (currentDir.path().isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择目录");
        return;
    }

    QString queryText = ui->queryTextEdit->toPlainText().trimmed();
    if (queryText.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入查询内容");
        return;
    }

    QStringList queries = queryText.split('\n', Qt::SkipEmptyParts);
    if (queries.size() < 2) {
        QMessageBox::warning(this, "警告", "请输入至少一个查询");
        return;
    }
    // 第一行是查询数量
    bool ok;
    int queryCount = queries.first().toInt(&ok);
    if (!ok || queryCount <= 0 || queryCount > 100000) {
        QMessageBox::warning(this, "警告", "第一行请输入有效的查询数目(1-100000)");
        return;
    }

    // 移除数量行
    queries.removeFirst();

    QProgressDialog progress("正在搜索...", "取消", 0, queries.size(), this);
    progress.setWindowModality(Qt::WindowModal);

    ui->resultTextEdit->clear();
    ui->resultTextEdit->setUpdatesEnabled(false);

    QStringList results;
    results.reserve(queries.size());

    for (int i = 0; i < queries.size(); ++i) {
        if (progress.wasCanceled()) break;

        results.append(searchEngine->search(queries[i]));
        results.append("");

        if (i % 10 == 0) {
            progress.setValue(i);
            QApplication::processEvents();
        }
    }

    ui->resultTextEdit->setPlainText(results.join('\n'));
    ui->resultTextEdit->setUpdatesEnabled(true);
    progress.setValue(queries.size());
}
