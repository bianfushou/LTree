#ifndef CAMERA_H
#define CAMERA_H


#include <QVector>
#include <QOpenGLFunctions_3_3_Core>
#include <QVector3D>
#include <QMatrix4x4>
#include<time.h>
#include<qmath.h>
#include "model/mesh.h"
#include "mark.h"

#define YAW         -90.0f
#define PITCH        0.0f
#define SPEED        2.0f
#define SENSITIVTY   0.25f
#define ZOOM         45.0f

struct Camera_Pos
{
    QPoint lastPos;
    bool firstPos;
    GLfloat deltaTime = 0.0f;
    time_t lastFrame = 0.0f;
};

class Camera
{
public:

    QVector3D Position;
    QVector3D Front;
    QVector3D Up;
    QVector3D Right;
    QVector3D WorldUp;

    GLfloat Yaw;
    GLfloat Pitch;

    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;
    QMatrix4x4 stopView;
    bool state;
    Mark mark;

    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        STOP,
        OPEN
    };

    Camera(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f),
           GLfloat yaw = YAW, GLfloat pitch = PITCH);

    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ,
           GLfloat yaw, GLfloat pitch) ;

    QMatrix4x4 GetViewMatrix();

    void StateKey(Camera_Movement state);
    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yoffset);

private:
    void updateCameraVectors();
};

#endif // CAMERA_H
