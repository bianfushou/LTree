#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include<QOpenGLWidget>
#include<QOpenGLShaderProgram>
#include<QOpenGLFunctions_4_3_Core>
#include<QOpenGLContext>

class TestWidget:public QOpenGLWidget
{
    Q_OBJECT
public:
    TestWidget(QWidget *parent = 0);
    ~TestWidget();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
private:
    QOpenGLShaderProgram *m_program;
    GLuint VBO, VAO, EBO;
};

#endif // TESTWIDGET_H
