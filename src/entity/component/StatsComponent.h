﻿#pragma once

#include <vector>
#include <memory>

#include "../Stats.h"

#include "Component.h"
#include "../../util/json.hpp"

namespace Framework
{
	class StatsComponent : public Component
	{
	public:
		Stats stats;
		std::vector<std::shared_ptr<StatusEffect>> active_effects;
	public:
		StatsComponent();
		StatsComponent(nlohmann::json json);

		void addEffect(std::shared_ptr<StatusEffect> effect);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
