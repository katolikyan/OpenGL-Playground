#ifndef __OBJ_VIEWER_INCLUDE_CAMERA_CLASS_HPP__
# define __OBJ_VIEWER_INCLUDE_CAMERA_CLASS_HPP__

#include "../glm/glm.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/matrix_transform.hpp"

class Camera {
  public:
    Camera();
    Camera(float width, float height);
    ~Camera();
    Camera(Camera const &other);
    Camera& operator=(Camera const &other);

    void SetPosition(float x, float y, float z);
    void SetFront(float x, float y, float z);
    void SetUp(float x, float y, float z);
    void SetLookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
    void SetProjection(glm::mat4 proj);
    void SetProjection(float fov, float ratio, float znear, float zfar);
    void SwapLock();
    bool IsLocked() const;
    glm::mat4 GetProj() const;
    glm::mat4 GetView() const;

    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);
    void MoveForward(float deltaTime);
    void MoveBack(float deltaTime);
    void MoveViewDirection(float xoffset, float yoffset, bool constrainPitch = true);

  private:

    void UpdateCameraFront();

    glm::vec3 m_CameraPos;
    glm::vec3 m_CameraFront;
    glm::vec3 m_CameraUp;
    glm::vec3 m_CameraRight;
    glm::vec3 m_WorldUp;
    glm::mat4 m_Projection;
    float m_Yaw;
    float m_Pitch;

    // camera options
    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;
    bool  m_Lock;
};

#endif