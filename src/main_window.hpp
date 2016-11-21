#pragma once
#pragma once

#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QtOpenGL/QGLWidget>
#include <QPushButton>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
private slots:
  void openSettingsWindow();
private:
  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  QGLWidget * m_glWidget = nullptr;
  QPushButton * m_settingsButton = nullptr;
};
