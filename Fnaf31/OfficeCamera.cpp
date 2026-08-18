#include "OfficeCamera.h"
#include <algorithm>

void OfficeCamera::init()
{
    m_officeCamera.position = Vector3{ 0.0f, 4.2f, 24.172f };  // Camera position
    m_officeCamera.target = Vector3{ 0.0f, 4.2f, 14.2351f };
    m_officeCamera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    m_officeCamera.fovy = 32.0f;                                // Camera field-of-view Y
    m_officeCamera.projection = CAMERA_PERSPECTIVE;
	// Initialize camera parameters here

	m_baseDirection = m_baseDirection = Vector3Subtract(m_officeCamera.target,m_officeCamera.position);

}

void OfficeCamera::update(float dt)
{
	panCamera(dt);
	// Update camera target based on yaw


}

void OfficeCamera::draw() const
{
}

void OfficeCamera::panCamera(float dt)
{
    if (GetMouseX() < GetScreenWidth() * 0.35f)
    {
		m_yaw += m_panSpeed * dt;
		//rotate camera to the left
		if (GetMouseX() < GetScreenWidth() * 0.15f)
		{
			m_yaw += m_panSpeed * dt * 1.4f;
		}
	}
	else if (GetMouseX() > GetScreenWidth() * 0.65f)
	{

		m_yaw -= m_panSpeed * dt;
		//rotate camera to the right
		if (GetMouseX() > GetScreenWidth() * 0.85f)
		{
			m_yaw -= m_panSpeed * dt * 1.4f;
		}
	}

	m_yaw = Clamp(m_yaw, m_minYaw, m_maxYaw);

	Vector3 rotatedDirection = Vector3RotateByAxisAngle(
		m_baseDirection,
		m_officeCamera.up,
		m_yaw
	);

	m_officeCamera.target = Vector3Add(
		m_officeCamera.position,
		rotatedDirection
	);

}
