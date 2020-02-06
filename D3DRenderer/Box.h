#pragma once
#include "DrawableBase.h"
#include <random>
class Box : public DrawableBase<Box>
{
public:
	Box(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float> &aDist,
		std::uniform_real_distribution<float> &dDist,
		std::uniform_real_distribution<float> &oDist,
		std::uniform_real_distribution<float> &rDist);
	void Update(float dt) override;
	DirectX::XMMATRIX GetTransformXM() const override;
private:
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;

	float dRoll;
	float dPitch;
	float dYaw;
	float dTheta;
	float dPhi;
	float dChi;
};

