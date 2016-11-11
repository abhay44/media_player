#include <QFileDialog>
#include <QInputDialog>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Enums.h>
#include <add_dialog.h>
#include "SimplePlayer.h"
#include "ui_SimplePlayer.h"

SimplePlayer::SimplePlayer(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::SimplePlayer),
      _media(0)

{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);

    ui->video->setMediaPlayer(_player);
    ui->volume->setMediaPlayer(_player);
    ui->volume->setVolume(50);
    ui->seek->setMediaPlayer(_player);

    connect(ui->actionOpenLocal, &QAction::triggered, this, &SimplePlayer::openLocal);
    connect(ui->stop, &QPushButton::clicked, _player, &VlcMediaPlayer::stop);

    connect(ui->actionPause, &QAction::toggled, _player, &VlcMediaPlayer::togglePause);

    connect(ui->openLocal, &QPushButton::clicked, this, &SimplePlayer::openLocal);
    connect(ui->pause, &QPushButton::toggled, ui->actionPause, &QAction::toggle);
    connect(ui->stop, &QPushButton::clicked, _player, &VlcMediaPlayer::stop);
    connect(ui->actionStop, &QAction::triggered, _player, &VlcMediaPlayer::stop);
    QIcon icon;
    icon.addPixmap(QPixmap("://icons/play.png"),QIcon::Normal,QIcon::On);
    icon.addPixmap(QPixmap("://icons/pause.png"),QIcon::Normal,QIcon::Off);
    ui->pause->setIcon(icon);
    ui->pause->setCheckable(true);

}
SimplePlayer::~SimplePlayer()
{
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
}

void SimplePlayer::openLocal()
{
    QString file =
            QFileDialog::getOpenFileName(this, tr("Open file"),
                                         QDir::homePath(),
                                         tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media = new VlcMedia(file, true, _instance);

    _player->open(_media);
}

void VlcWidgetVolumeSlider::mousePressEvent(QMouseEvent *event)
{
   // ...
    QSlider::mousePressEvent(event);
   // ...
}
void VlcWidgetVolumeSlider::mouseReleaseEvent(QMouseEvent *event)
{
    // ...
    QSlider::mouseReleaseEvent(event);
   // ...
}


void SimplePlayer::on_fullscreen_clicked(bool checked)
{

    isFullScreen() ? showNormal() : showFullScreen();
    QIcon ico;
    ico.addPixmap(QPixmap("://icons/full_in.png"),QIcon::Normal,QIcon::On);
    ico.addPixmap(QPixmap("://icons/full_out.png"),QIcon::Normal,QIcon::Off);
//    setWindowState(windowState() | Qt::WindowFullScreen);
    ui->fullscreen->setIcon(ico);
    ui->fullscreen->setCheckable(true);
    ui->video->setCursor(Qt::BlankCursor);
}

void SimplePlayer::on_pause_clicked(bool checked)
{

    if(ui->pause->isChecked()){
         _player->pause();
        }
        else{
        _player->play();
        }
}

