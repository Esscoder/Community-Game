﻿#include "VelocityComponent.h"

#include "../../util/Maths.h"

namespace Framework
{
	VelocityComponent::VelocityComponent(const sf::Vector2f& velocity)
		: velocity(velocity)
	{
	}

	VelocityComponent::VelocityComponent(nlohmann::json json) {
		velocity = sf::Vector2f(json["x"], json["y"]);
	}

	void VelocityComponent::move(float angle)
	{
		velocity.x += cos(Maths::toRadians(angle));
		velocity.y += sin(Maths::toRadians(angle));
		Maths::normalize(velocity);

		moving = true;
	}

	ComponentType* VelocityComponent::getStaticType()
	{
		static ComponentType type({ "Velocity" });
		return &type;
	}
	
	ComponentType* VelocityComponent::getType() const 
	{
		return getStaticType(); 
	}
}
