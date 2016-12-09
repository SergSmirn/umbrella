#include "gl_widget.hpp"
#include "space.hpp"
#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QGuiApplication>
#include <cmath>
#include <iostream>
#include "iobstacle.hpp"
#include "ialien.hpp"
//#include "aintesection.hpp"


#include "main_window.hpp"

namespace
{

int constexpr kLeftDirection = 0;
int constexpr kRightDirection = 1;
int constexpr kUpDirection = 2;
int constexpr kDownDirection = 3;

bool IsLeftButton(Qt::MouseButtons buttons)
{
  return buttons & Qt::LeftButton;
}
bool IsLeftButton(QMouseEvent const * const e)
{
  return IsLeftButton(e->button()) || IsLeftButton(e->buttons());
}

bool IsRightButton(Qt::MouseButtons buttons)
{
  return buttons & Qt::RightButton;
}
bool IsRightButton(QMouseEvent const * const e)
{
  return IsRightButton(e->button()) || IsRightButton(e->buttons());
}

} // namespace


std::shared_ptr<Space> m_space = nullptr;


GLWidget::GLWidget(MainWindow * mw, QColor const & background)
  : m_mainWindow(mw)
  , m_background(background)
{
  setMinimumSize(800, 800);
  setFocusPolicy(Qt::StrongFocus);
  m_space = std::make_shared<Space>();
}

GLWidget::~GLWidget()
{
  makeCurrent();
  delete m_textureStar;
  delete m_textureShip;
  delete m_textureObstacle;
  delete m_texturedRect;
  doneCurrent();
}

void GLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  m_texturedRect = new TexturedRect();
  m_texturedRect->Initialize(this);
  m_textureStar = new QOpenGLTexture(QImage("data/star.png"));
  m_textureObstacle = new QOpenGLTexture(QImage("data/aestroid_dark.png"));
  m_textureShip = new QOpenGLTexture(QImage("data/ship.png"));
  m_textureAlien1 = new QOpenGLTexture(QImage("data/Alien1.png"));
  m_textureAlien2 = new QOpenGLTexture(QImage("data/Alien2.png"));
  m_textureAlien3 = new QOpenGLTexture(QImage("data/Alien3.png"));
  m_textureShipBullet = new QOpenGLTexture(QImage("data/shipbullet.png"));
  m_textureGameOver = new QOpenGLTexture(QImage("data/gameover.png"));
  m_space->SetShip(std::make_shared<Gun>(Point2D {400.0, 100.0}, Point2D {400.0, 400.0}, 100, 2, 2));

  m_time.start();
}

void GLWidget::paintGL()
{
  int const elapsed = m_time.elapsed();
  Update(elapsed / 1000.0f);

  QPainter painter;
  painter.begin(this);
  painter.beginNativePainting();
  if (m_iniall)
  {
    IniObsatacle(m_space->GetObstacle());
    IniAlien(m_space->GetAlien());
    m_iniall = false;
  }

  glClearColor(m_background.redF(), m_background.greenF(), m_background.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Render();

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);
  painter.endNativePainting();

  if (elapsed != 0)
  {
    QString framesPerSecond;
    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
    painter.setPen(Qt::white);
    painter.drawText(20, 60, framesPerSecond + " fps");;
  }
  QString hp;
  hp.setNum(m_space->GetShip()->GetHealth());
  painter.setPen(Qt::red);
  painter.drawText(680, 40, "Your health: " + hp);
  QString sc;
  sc.setNum(m_score);
  painter.setPen(Qt::yellow);
  painter.drawText(20, 40, "Your score: " + sc);

  painter.end();

  if (!(m_frames % 500))
  {
    m_time.start();
    m_frames = 0;
  }
  ++m_frames;

  update();
}

void GLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);
}

void GLWidget::Update(float elapsedSeconds)
{
  float const kSpeed = 3.0f; // pixels per second.
  static float lastShot = 0.0f;
  if (m_shipShot && (fabs(elapsedSeconds - lastShot) > 0.5f))
  {
    m_space->AddShipBullet(std::make_shared<Bullet>(m_space->GetShip()->LeftBot() , 5));
    lastShot = elapsedSeconds;
  }

  if (m_directions[kUpDirection])
  {
    m_space->GetShip()->MoveY(kSpeed );
  }
  if (m_directions[kDownDirection])
  {
    m_space->GetShip()->MoveY(-kSpeed );
  }
  if (m_directions[kLeftDirection])
  {
    m_space->GetShip()->MoveX(-kSpeed );
  }
  if (m_directions[kRightDirection])
  {
    m_space->GetShip()->MoveX(kSpeed );
  }
}

void GLWidget::RenderStar()
{
  static bool flag = true;
  static QVector2D coordinates[32];
  static float clarity[32];
  for (int i = 0; i < 31; i++)
    {
      clarity[i] = fabs(sin(M_PI * m_frames / 250 + M_PI * i/20)) ;
      if (clarity[i] < 0.01 || flag)
        {
          coordinates[i].setX(rand() % 800);
          coordinates[i].setY(rand() % 800);
          flag = false;
        }
      m_texturedRect->Render(m_textureStar, coordinates[i], QSize(20, 20), m_screenSize, clarity[i]);
    }
}

void GLWidget::RenderShip()
{
  m_texturedRect->Render(m_textureShip, QVector2D(m_space->GetShip()->LeftBot().x(),
                         m_space->GetShip()->LeftBot().y()), QSize(60, 60), m_screenSize, 1.0);
}

void GLWidget::RenderObstacle()
{
  for (std::vector<Obstacle>::iterator it = m_space->GetObstacle().begin(); it != m_space->GetObstacle().end(); ++it)
  {
    if (it->GetIni())
      m_texturedRect->Render(m_textureObstacle, QVector2D(-25 + 50 * it->GetCoordinateX(), 175 + 50 * it->GetCoordinateY()), QSize(50, 50), m_screenSize, 1.0);
  }
}

void GLWidget::RenderAlien()
{
  int i = 0;
  for (std::vector<Alien>::iterator it = m_space->GetAlien().begin() ; it!=m_space->GetAlien().end() ; ++it)
  {
    if (i < 22)
      m_texturedRect->Render(m_textureAlien1, QVector2D(50 + 50 * it->GetCoordinateX(), 550 + 50 * it->GetCoordinateY()), QSize(50, 50), m_screenSize, 1.0);
    else if (i >= 44)
      m_texturedRect->Render(m_textureAlien2, QVector2D(50 + 50 * it->GetCoordinateX(), 550 + 50 * it->GetCoordinateY()), QSize(50, 50), m_screenSize, 1.0);
    else
      m_texturedRect->Render(m_textureAlien3, QVector2D(50 + 50 * it->GetCoordinateX(), 550 + 50 * it->GetCoordinateY()), QSize(50, 50), m_screenSize, 1.0);
    i++;
  }
}

void GLWidget::RenderShipBullet()
{
  for (auto bullet : m_space->GetShipBulletList())
  {
    m_texturedRect->Render(m_textureShipBullet, QVector2D(bullet->LeftBot().x(),
                  bullet->LeftBot().y() + 30), QSize (20, 20), m_screenSize, 1.0);
    bullet->MoveY(2);
  }
}

void GLWidget::RenderGameOver()
{
  m_texturedRect->Render(m_textureGameOver, QVector2D(400, 450), QSize(300, 300), m_screenSize, 1.0);
}

void GLWidget::Render()
{
  GLWidget::RenderStar();
  if (m_space->GetShip()->GetHealth() != 0)
  {
    GLWidget::RenderShip();
    GLWidget::RenderObstacle();
    GLWidget::RenderAlien();
    GLWidget::RenderShipBullet();
  }
  else RenderGameOver();
}



void GLWidget::mousePressEvent(QMouseEvent * e)
{
  QGLWidget::mousePressEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    // ...
  }
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
  QGLWidget::mouseDoubleClickEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsRightButton(e))
  {
    // ...
  }
}

void GLWidget::mouseMoveEvent(QMouseEvent * e)
{
  QGLWidget::mouseMoveEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    // ...
  }
}

void GLWidget::mouseReleaseEvent(QMouseEvent * e)
{
  QGLWidget::mouseReleaseEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    // ...
  }
}

void GLWidget::wheelEvent(QWheelEvent * e)
{
  QGLWidget::wheelEvent(e);

  int const delta = e->delta();
  int const px = L2D(e->x());
  int const py = L2D(e->y());
  // ...
}

void GLWidget::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Space)
     m_shipShot = true;
  if (e->key() == Qt::Key_Up)
    m_directions[kUpDirection] = true;
  else if (e->key() == Qt::Key_Down)
    m_directions[kDownDirection] = true;
  else if (e->key() == Qt::Key_Left)
    m_directions[kLeftDirection] = true;
  else if (e->key() == Qt::Key_Right)
    m_directions[kRightDirection] = true;
}

void GLWidget::keyReleaseEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Space)
     m_shipShot = false;
  if (e->key() == Qt::Key_Up)
    m_directions[kUpDirection] = false;
  else if (e->key() == Qt::Key_Down)
    m_directions[kDownDirection] = false;
  else if (e->key() == Qt::Key_Left)
    m_directions[kLeftDirection] = false;
  else if (e->key() == Qt::Key_Right)
    m_directions[kRightDirection] = false;
}
