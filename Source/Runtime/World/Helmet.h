#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/World/GameObject.h>

class Helmet : public GameObject
{
public:
	Helmet();
	~Helmet() = default;

	void Update() override;
};
