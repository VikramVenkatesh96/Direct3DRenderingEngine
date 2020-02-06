#include "Camera.h"
#include "ImGUI/imgui.h"

DirectX::XMMATRIX Camera::GetMatrix() const
{
	const auto pos = DirectX::XMVector3Transform(
		DirectX::XMVectorSet(0.0f, 0.0f, -r, 0.0f),
		DirectX::XMMatrixRotationRollPitchYaw(phi, -theta, 0.0f)
	);

	return DirectX::XMMatrixLookAtLH(
		pos, DirectX::XMVectorZero(),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	) * DirectX::XMMatrixRotationRollPitchYaw(roll, -pitch, yaw);

}

void Camera::ControlWindow()
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("R", &r, 0.0f, 40.0f, "%.1f");
		ImGui::SliderFloat("Theta", &theta, 0.0f, 40.0f, "%.1f");
		ImGui::SliderFloat("Phi", &phi, 0.0f, 40.0f, "%.1f");

		ImGui::Text("Rotation");
		ImGui::SliderFloat("Pitch", &pitch, -180.0f, 180.0f, "%.1f");
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f, "%.1f");
		ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f, "%.1f");

		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void Camera::Reset()
{
	r = 20.0f;
	theta = 0.0f;
	phi = 0.0f;

	pitch = 0.0f;
	roll = 0.0f;
	yaw = 0.0f;
}
