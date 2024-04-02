#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/World/GameObject.h>

class Lantern : public GameObject
{
public:
	Lantern();
	~Lantern() = default;

	void Update() override;
};
