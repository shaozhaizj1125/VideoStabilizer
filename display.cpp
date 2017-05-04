#include "display.h"
#include "ui_display.h"
#include "image_converter.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videostab.hpp>

#include <QDebug>
#include <QImage>
#include <QPixmap>

Display::Display(QWidget *parent) : QWidget(parent),
    ui          {   new Ui::Display             },
    mediaPlayer {   new QMediaPlayer(this)      },
    videoArea   {   new QVideoWidget(this)      },
    model       {   new QFileSystemModel(this)  }
{
    ui->setupUi(this);
    ui->fileExplorer->setModel(model);
    ui->fileExplorer->hideColumn(1);
    ui->fileExplorer->hideColumn(2);
    ui->fileExplorer->hideColumn(3);

    model->setRootPath(QDir::currentPath());
    mediaPlayer->setVideoOutput(videoArea);
    videoArea->setMinimumWidth(800);
    static_cast<QHBoxLayout*>(layout())->insertWidget(0, videoArea);

    connect(this, &Display::itemProcessed, this, &Display::onItemProcessed);
    connect(ui->fileExplorer, &QTreeView::clicked, [&] (const QModelIndex& index)
    {
        current_item = model->fileInfo(index);
        if(current_item.suffix() == "mp4" || current_item.suffix() == "avi")
        {
            qDebug() << QUrl::fromLocalFile(current_item.absoluteFilePath());
            mediaPlayer->setMedia(QUrl::fromLocalFile(current_item.absoluteFilePath().toStdString().c_str()));
            mediaPlayer->play();
        }
    });
    connect(ui->stabVideoButton, &QPushButton::clicked, [&] () {
        if(current_item.suffix() == "mp4" || current_item.suffix() == "avi")
        {
            qDebug() << current_item.absoluteFilePath();
            QString result_absolute_path =
                    current_item.absolutePath() + '/' +
                    current_item.baseName() +
                    "_stabilized."  +
                    current_item.completeSuffix();
            stabilizer.Process(current_item.absoluteFilePath().toStdString());
            stabilizer.SaveResult(result_absolute_path.toStdString());
            emit Display::itemProcessed(result_absolute_path);
        }
    });
}

Display::~Display()
{
    delete ui;
}

void Display::onItemProcessed(const QString& item_path)
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(item_path));
    mediaPlayer->play();
}


