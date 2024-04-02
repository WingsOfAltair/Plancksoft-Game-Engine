#pragma once

#include <Runtime/Core/Core.h>

#include <Runtime/World/GameObject.h>

class Fox : public GameObject
{
public:
	Fox();
	~Fox() = default;

	void Update() override;
};
