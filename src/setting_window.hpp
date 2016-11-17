#pragma once

#include <QDialog>
#include <QMainWindow>

class SettingWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SettingWindow(QMainWindow * parent = 0);
};
