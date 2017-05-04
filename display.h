#pragma once

#include <QWidget>
#include <QTreeWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileSystemModel>

#include "video_stabilizer.h"

namespace Ui {
    class Display;
}

class Display : public QWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0);
    ~Display();

private:
    Ui::Display *ui             = nullptr;
    QVideoWidget* videoArea     = nullptr;
    QFileSystemModel* model     = nullptr;
    QMediaPlayer* mediaPlayer   = nullptr;

    QFileInfo current_item;
    VideoStabilizer stabilizer;

signals:
    void itemProcessed(const QString&);

private slots:
    void onItemProcessed(const QString& item_path);
};

