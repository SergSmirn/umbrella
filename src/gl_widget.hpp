#pragma once

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include "textured_rect.hpp"
#include <QVector2D>
#include <array>


class MainWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GLWidget(MainWindow * mw, QColor const & background);
  ~GLWidget();

protected:
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initializeGL() override;

  void Update(float elapsedSeconds);
  void RenderStar();
  void RenderShip();
  void RenderObstacle();
  void RenderAlien();
  void RenderShipBullet();
  void RenderGameOver();
  void Render();
  void mousePressEvent(QMouseEvent * e) override;
  void mouseDoubleClickEvent(QMouseEvent * e) override;
  void mouseMoveEvent(QMouseEvent * e) override;
  void mouseReleaseEvent(QMouseEvent * e) override;
  void wheelEvent(QWheelEvent * e) override;
  void keyPressEvent(QKeyEvent * e) override;
  void keyReleaseEvent(QKeyEvent * e) override;

private:
  int L2D(int px) const { return px * devicePixelRatio(); }

  MainWindow * m_mainWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QColor m_background;
  QSize m_screenSize;

  QOpenGLTexture * m_textureShipBullet = nullptr;
  QOpenGLTexture * m_textureGameOver = nullptr;
  QOpenGLTexture * m_textureShip = nullptr;
  QOpenGLTexture * m_textureObstacle = nullptr;
  TexturedRect * m_texturedRect = nullptr;
  QOpenGLTexture * m_textureAlien1 = nullptr;
  QOpenGLTexture * m_textureAlien2 = nullptr;
  QOpenGLTexture * m_textureAlien3 = nullptr;
  QOpenGLTexture * m_textureStar = nullptr;
  QVector2D m_position = QVector2D(200, 200);

  std::array<bool, 4> m_directions = {{ false, false, false, false }};
  bool m_iniall = true;

  bool m_shipShot = false;
  unsigned m_score = 0;

};
