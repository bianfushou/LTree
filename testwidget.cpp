#include "testwidget.h"
#include "system/openglfunction.h"

TestWidget::TestWidget(QWidget *parent):
QOpenGLWidget(parent),
m_program(0)
{

}

TestWidget::~TestWidget()
{
    makeCurrent();

    delete m_program;
    m_program = 0;
    doneCurrent();
}

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void TestWidget::initializeGL()
{
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
    f->initializeOpenGLFunctions();
    f->glClearColor(1.0f,1.0f,1.0f,1.0f);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentShaderSource);
    GLfloat vertices[] = {
             0.5f,  0.5f, 0.0f,  // Top Right
             0.5f, -0.5f, 0.0f,  // Bottom Right
            -0.5f, -0.5f, 0.0f,  // Bottom Left
            -0.5f,  0.5f, 0.0f   // Top Left
        };
        GLuint indices[] = {  // Note that we start from 0!
            0, 1, 3,  // First Triangle
            1, 2, 3   // Second Triangle
        };

        f->glGenVertexArrays(1, &VAO);
        f->glGenBuffers(1, &VBO);
        f->glGenBuffers(1, &EBO);
        // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
        f->glBindVertexArray(VAO);

        f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
        f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        f->glEnableVertexAttribArray(0);

        f->glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

        f->glBindVertexArray(0);
}

void TestWidget::paintGL()
{
    QOpenGLFunctions_4_3_Core *f = OpenGLFunction::getOpenGLFunction();
    f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            f->glClear(GL_COLOR_BUFFER_BIT);

            // Draw our first triangle
            m_program->bind();
            f->glBindVertexArray(VAO);
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            f->glBindVertexArray(0);
            m_program->release();
}
void TestWidget::resizeGL(int width, int height)
{
    QOpenGLWidget::resizeGL(width,height);
}
