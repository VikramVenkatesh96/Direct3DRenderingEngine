#pragma once
#include "DrawableBase.h"

class Sheet: public DrawableBase<Sheet>
{
public:
	Sheet(Graphics& gfx,std::wstring fileName,float xScale, float yScale, float yVel, float dRoll);
	void Update(float dt) override;
	DirectX::XMMATRIX GetTransformXM() const override;

private:
	std::wstring fileName;
	float xScale;
	float yScale;
	float r;
	float y;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;

	float yVel;
	float dRoll;
	float dPitch;
	float dYaw;
	float dTheta;
	float dPhi;
	float dChi;
};

