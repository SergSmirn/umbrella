#include "main_window.hpp"

#include <QApplication>
#include "gl_widget.hpp"
#include "setting_window.hpp"

typedef void (QWidget::*QWidgetVoidSlot)();

MainWindow::MainWindow()
{

  m_glWidget = new GLWidget(this, qRgb(20, 20, 50));
  m_timer = new QTimer(this);

  QPushButton * settingsButton = new QPushButton("Settings",this);
  settingsButton->move(10,10);
  connect(settingsButton, SIGNAL(clicked()), this, SLOT(openSettingsWindow()));
  QPushButton * buttonClose = new QPushButton("Close", this);
  buttonClose->move(10,60);
  connect(buttonClose, SIGNAL(clicked()), this, SLOT(close()));

  m_timer->setInterval(10);
  connect(m_timer, &QTimer::timeout, this, static_cast<QWidgetVoidSlot>(&QWidget::update));
  m_timer->start();
  setFocusPolicy(Qt::StrongFocus);
}

void MainWindow::openSettingsWindow()
{
  SettingWindow * settingWindow = new SettingWindow(this);
  settingWindow->show();
}
