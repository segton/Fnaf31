#pragma once
#include "raylib.h"

#include "raymath.h"

struct MousePosition
{
	int x;
	int y;
};

class OfficeCamera
{
public:
	OfficeCamera() = default;
	void init();
	void update(float dt);
	void draw() const;

	const Camera3D& getCamera() const { return m_officeCamera; }

private:
	void panCamera(float dt);

private:
	Camera3D m_officeCamera{};
	Vector3 m_baseDirection{};

	float m_yaw = 0.0f;

	float m_minYaw = -20.0f * DEG2RAD;
	float m_maxYaw = 20.0f * DEG2RAD;

	float m_panSpeed = 35.0f * DEG2RAD;

};

