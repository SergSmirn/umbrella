#include "main_window.hpp"
#include "setting_window.hpp"

typedef void (QWidget::*QWidgetVoidSlot)();

SettingWindow::SettingWindow(QMainWindow * parent) : QMainWindow(parent)
{
  m_centralWidget = new QWidget(this);
  setCentralWidget(m_centralWidget);
  setWindowTitle("Settings");
  setFixedSize(600, 500);

  m_sliderSound = new QSlider(Qt::Horizontal, this);
  m_sliderSound->setRange(0, 100);
  m_sliderSound->setValue(100);

  m_level = new QComboBox(this);
  m_level->addItem("Easy", static_cast<unsigned char>(GameLevel::Easy));
  m_level->addItem("Normal", static_cast<unsigned char>(GameLevel::Normal));
  m_level->addItem("Hard", static_cast<unsigned char>(GameLevel::Hard));

  m_buttonSave = new QPushButton("Save", m_centralWidget);
  m_buttonSave->move(100, 350);
  m_buttonSave->setFixedWidth(100);
  connect(m_buttonSave, SIGNAL(clicked()), this, SLOT(SaveButtonClicked()));

  m_buttonStart = new QPushButton("Start", m_centralWidget);
  m_buttonStart->move(400, 350);
  m_buttonStart->setFixedWidth(100);
  connect(m_buttonStart, SIGNAL(clicked()), this, SLOT(StartButtonClicked()));

  m_name = new QLineEdit();
  m_layout = new QFormLayout(m_centralWidget);
  m_layout->addRow("Your name", m_name);
  m_layout->addRow("Difficulty", m_level);
  m_layout->addRow("Sound", m_sliderSound);

  setFocusPolicy(Qt::StrongFocus);
}

