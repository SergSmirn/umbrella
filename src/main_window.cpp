
#include "main_window.hpp"

#include <QApplication>
#include "gl_widget.hpp"
#include "setting_window.hpp"

typedef void (QWidget::*QWidgetVoidSlot)();

MainWindow::MainWindow()
{
  m_glWidget = new GLWidget(this, qRgb(20, 20, 50));
  m_timer = new QTimer(this);
  //m_settingsButton = new QPushButton("Settings",m_glWidget);
  //m_settingsButton->move(15,50);
  m_timer->setInterval(10);
  setCentralWidget(m_glWidget);
  connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
  //connect(m_settingsButton, SIGNAL(clicked()), this, SLOT(openSettingsWindow()));
  m_timer->start();
  setFocusPolicy(Qt::StrongFocus);
}


void MainWindow::openSettingsWindow()
{
  SettingWindow * settingWindow = new SettingWindow(this);
  settingWindow->show();
}

