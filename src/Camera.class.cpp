#include "Camera.class.hpp"

Camera::Camera() {
  m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f); 
  m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  m_WorldUp = m_CameraUp;
  m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
  m_Yaw = -90.0f;
  m_Pitch = 0.0f;
  m_MovementSpeed = 2.5f;
  m_MouseSensitivity = 0.1f;
  m_Zoom = 45.0f;
  m_Lock = false;
  m_Projection = glm::perspective(\
                 glm::radians(45.0f), 1000.0f / 1000.0f, 0.1f, 100.0f);
}
              
Camera::Camera(float width, float height) {
  m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f); 
  m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  m_WorldUp = m_CameraUp;
  m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
  m_Yaw = -90.0f;
  m_Pitch = 0.0f;
  m_MovementSpeed = 2.5f;
  m_MouseSensitivity = 0.1f;
  m_Zoom = 45.0f;
  m_Lock = false;
  m_Projection = glm::perspective(\
                 glm::radians(45.0f), width / height, 0.1f, 100.0f);
}

Camera::Camera(Camera const &other) {
  m_CameraFront = other.m_CameraFront;
  m_CameraPos = other.m_CameraPos;
  m_CameraUp = other.m_CameraUp;
  m_Projection = other.m_Projection;
  m_WorldUp = other.m_WorldUp;
  m_CameraRight = other.m_CameraRight;
  m_Yaw = other.m_Yaw;
  m_Pitch = other.m_Pitch;
  m_MovementSpeed = other.m_MovementSpeed;
  m_MouseSensitivity = other.m_MouseSensitivity;
  m_Zoom = other.m_Zoom;
  m_Lock = other.m_Lock;
}

Camera::~Camera() {}

Camera& Camera::operator=(Camera const &other) {
  m_CameraFront = other.m_CameraFront;
  m_CameraPos = other.m_CameraPos;
  m_CameraUp = other.m_CameraUp;
  m_Projection = other.m_Projection;
  m_WorldUp = other.m_WorldUp;
  m_CameraRight = other.m_CameraRight;
  m_Yaw = other.m_Yaw;
  m_Pitch = other.m_Pitch;
  m_MovementSpeed = other.m_MovementSpeed;
  m_MouseSensitivity = other.m_MouseSensitivity;
  m_Zoom = other.m_Zoom;
  m_Lock = other.m_Lock;
  return *this;
}

void Camera::SetPosition(float x, float y, float z) {
  m_CameraPos = glm::vec3(x, y, z);
}
void Camera::SetFront(float x, float y, float z) {
  m_CameraFront = glm::vec3(x, y, z);
}
void Camera::SetUp(float x, float y, float z) {
  m_CameraUp = glm::vec3(x, y, z);
}

void Camera::SetLookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
  m_CameraPos = pos;
  m_CameraFront = target;
  m_CameraUp = up;
}

void Camera::SetProjection(glm::mat4 proj) {
  m_Projection = proj;
}

void Camera::SetProjection(float fov, float ratio, float znear, float zfar) {
  m_Projection = glm::perspective(glm::radians(fov), 
                                  ratio,
                                  znear,
                                  zfar);
}

glm::mat4 Camera::GetProj() const {
  return m_Projection;
}

glm::mat4 Camera::GetView() const {
  return glm::lookAt( m_CameraPos, 
                      m_CameraPos + m_CameraFront,
                      m_CameraUp);
}

void  Camera::MoveLeft(float deltaTime) {
  m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * \
                                m_MovementSpeed * deltaTime;
}

void  Camera::MoveRight(float deltaTime) {
  m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * \
                                m_MovementSpeed * deltaTime;
}

void  Camera::MoveForward(float deltaTime) {
  m_CameraPos += m_MovementSpeed * deltaTime * m_CameraFront;
}

void  Camera::MoveBack(float deltaTime) {
  m_CameraPos -= m_MovementSpeed * deltaTime * m_CameraFront;
}

void  Camera::SwapLock() {
  m_Lock = (m_Lock ^ 0x1);
}

bool  Camera::IsLocked() const {
  return m_Lock;
}

void Camera::MoveViewDirection(float xoffset, float yoffset, bool constrainPitch) {
  xoffset *= m_MouseSensitivity;
  yoffset *= m_MouseSensitivity;

  m_Yaw   += xoffset;
  m_Pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (m_Pitch > 89.0f)
      m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
      m_Pitch = -89.0f;
  }

  UpdateCameraFront();
}

void Camera::UpdateCameraFront() {
  glm::vec3 front;
  front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
  front.y = sin(glm::radians(m_Pitch));
  front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
  m_CameraFront = glm::normalize(front);
  m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
  m_CameraUp    = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
}