#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QSize>
#include <QVector2D>

class TexturedRect
{
public:
  TexturedRect() = default;
  ~TexturedRect();

  bool Initialize(QOpenGLFunctions * functions);
  void Render(QOpenGLTexture * texture, QVector2D const & position,
              QSize const & size, QSize const & screenSize, const float clarity);


  void ChangeClarity(unsigned int p)
  {
    m_clarity = 0.5 - 0.5 * cos(M_PI * 0.004 * p);
  }

  void ChangeCoordinates (unsigned int p)
  {
     for (int i = 1; i < 16; i++ )
     m_coordinates[i] = rand()%20;
  }

  float GetClarity() const
  {
    return m_clarity;
  }

  int GetCoordinates (unsigned int i) const
  {
     return m_coordinates[i];
  }

private:
  QOpenGLFunctions * m_functions = nullptr;

  QOpenGLShader * m_vertexShader = nullptr;
  QOpenGLShader * m_fragmentShader = nullptr;
  QOpenGLShaderProgram * m_program = nullptr;

  QOpenGLBuffer m_vbo;

  int m_positionAttr = 0;
  int m_clarityAttr = 0;
  int m_texCoordAttr = 0;
  int m_modelViewProjectionUniform = 0;
  int m_textureUniform = 0;
  int m_coordinates[16];
  float m_clarity = 0;
};
