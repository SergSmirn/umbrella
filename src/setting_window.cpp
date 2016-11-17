#include "setting_window.hpp"
#include <QPushButton>
#include <QApplication>
#include <QSlider>
#include <QLineEdit>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialog>

typedef void (QWidget::*QWidgetVoidSlot)();

SettingWindow::SettingWindow(QMainWindow * parent) : QMainWindow(parent)
{
  QWidget * centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  setWindowTitle("Setting");
  setFixedSize(600, 500);

  QSlider * sliderSound = new QSlider(Qt::Horizontal, this);
  sliderSound->setRange(0, 100);
  sliderSound->setValue(100);

  QSlider * sliderComp = new QSlider(Qt::Horizontal, this);
  sliderComp->setRange(0, 8);
  sliderComp->setValue(4);

  QSpinBox * spinAlien = new QSpinBox(this);
  spinAlien->setRange(50, 300);
  spinAlien->setValue(100);


  QPushButton * buttonClose = new QPushButton("Close", centralWidget);
  buttonClose->move(100, 350);
  buttonClose->setFixedWidth(100);
  connect(buttonClose, SIGNAL(clicked()), this, SLOT(close()));

  QPushButton * buttonSave = new QPushButton("Save", centralWidget);
  buttonSave->move(400, 350);
  buttonSave->setFixedWidth(100);
  connect(buttonSave, SIGNAL(clicked()), this, SLOT(close()));

  QLineEdit * name = new QLineEdit();
  QFormLayout * layout = new QFormLayout(centralWidget);
  layout->addRow("Your name", name);
  layout->addRow("Сomplexity", sliderComp);
  layout->addRow("Allien ammount", spinAlien);
  layout->addRow("Sound", sliderSound);

  setFocusPolicy(Qt::StrongFocus);

}
