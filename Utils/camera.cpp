#include "camera.h"

Camera::Camera(QVector3D position, QVector3D up ,GLfloat yaw , GLfloat pitch )
    : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
    this->Position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
    this->state = true;
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ,
               GLfloat yaw, GLfloat pitch) :
    Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
    this->Position = QVector3D(posX, posY, posZ);
    this->WorldUp = QVector3D(upX, upY, upZ);
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
    this->state = true;
}

QMatrix4x4 Camera::GetViewMatrix()
{
    QMatrix4x4 view;
    view.setToIdentity();
    view.lookAt(this->Position, this->Position + this->Front, this->Up);
    return view;
}

void Camera::StateKey(Camera_Movement state)
{
    if(state == STOP )
    {
        if(this->state )
        {
            this->state = false;
        }
    }
    else
    {
        this->state = true;
    }
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->MovementSpeed * deltaTime;
    if (direction == FORWARD)
        this->Position += this->Front * velocity;
    if (direction == BACKWARD)
        this->Position -= this->Front * velocity;
    if (direction == LEFT)
        this->Position -= this->Right * velocity;
    if (direction == RIGHT)
        this->Position += this->Right * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch )
{
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;

    this->Yaw   += xoffset;
    this->Pitch += yoffset;

    if (constrainPitch)
    {
        if (this->Pitch > 89.0f)
            this->Pitch = 89.0f;
        if (this->Pitch < -89.0f)
            this->Pitch = -89.0f;
    }

    this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
    if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
        this->Zoom -= yoffset;
    if (this->Zoom <= 1.0f)
        this->Zoom = 1.0f;
    if (this->Zoom >= 45.0f)
        this->Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    QVector3D front;
    front.setX( qCos(qDegreesToRadians(this->Yaw)) * qCos(qDegreesToRadians(this->Pitch)) );
    front.setY( qSin(qDegreesToRadians(this->Pitch)) );
    front.setZ( qSin(qDegreesToRadians(this->Yaw)) * qCos(qDegreesToRadians(this->Pitch)) );
    this->Front = front.normalized();
    this->Right = QVector3D::crossProduct(this->Front, this->WorldUp).normalized();
    this->Up = QVector3D::crossProduct(this->Right,this->Front).normalized();
}
