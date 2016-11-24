#pragma once

#include <QPushButton>
#include <QApplication>
#include <QSlider>
#include <QLineEdit>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include "setting.hpp"

class SettingWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SettingWindow(QMainWindow * parent = 0);
  void ShowMessage()
  {
    QMessageBox message;
    message.setText("Настройки сохранены!");
    message.exec();
  }

private slots:
  void StartButtonClicked()
  {
    qDebug("StartButtonClicked");

    MainWindow * mainWindow = new MainWindow();

    mainWindow->show();

    this->hide();
  }

  void SaveButtonClicked()
  {
     m_settings.SetLevel(static_cast<GameLevel>(m_level->currentIndex()));
     m_settings.SetName(m_name->text().toUtf8().constData());
     m_settings.SetSound(m_sliderSound->tickPosition());
     m_settings.Save();
     ShowMessage();
  }

private:
  Settings m_settings;
  QWidget * m_centralWidget;
  QSlider * m_sliderSound;
  QComboBox * m_level;
  QLineEdit * m_name;
  QFormLayout * m_layout;
  QPushButton * m_buttonStart;
  QPushButton * m_buttonSave;
};
