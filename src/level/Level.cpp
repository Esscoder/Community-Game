﻿#include "Level.h"
#include "LevelRenderer.h"

#include <iostream>

#include "../entity/Entity.h"
#include "../states/StatePlaying.h"
#include "../entity/component/Components.h"

namespace Level
{
	Level::Level(unsigned int width, unsigned int height)
		: m_width(width),
		m_height(height)
	{
		m_tiles.resize(width*height);

		m_renderSystem = std::make_unique<Framework::RenderSystem>();

		m_updateSystems.push_back(std::make_unique<Framework::MoveSystem>());
		m_updateSystems.push_back(std::make_unique<Framework::StatsSystem>());
		m_updateSystems.push_back(std::make_unique<Framework::AnimatorSystem>());
	}

	void Level::addEntity(Framework::Entity* entity)
	{
		m_entities.push_back(entity);
	}

	Framework::Entity * Level::getEntity(const uint64 & id)
	{
		for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
		{
			if ((*it)->getID() == id)
				return (*it);
		}
		return nullptr;
	}

	void Level::setTile(unsigned int x, unsigned int y, Tile::Tile& tile)
	{
		m_tiles[x + y * m_width] = &tile;
	}

    Tile::Tile* Level::getTile(unsigned int x, unsigned int y)
    {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height)
            return nullptr;
        return
            m_tiles[x + y * m_width];
    }

	void Level::update(const Timestep& ts)
	{
		for (uint i = 0; i < m_entities.size(); i++)
			if (m_entities[i] != nullptr)
			{
				Framework::Entity* e = m_entities[i];
				for (auto& system : m_updateSystems)
					system->update(ts, e);
	
				e->update(ts);
			}
	}

	void Level::render(sf::RenderWindow& window)
	{
		sf::View view = State::SPlaying::instance->getCamera();
		float left = view.getCenter().x - view.getSize().x / 2;
		float right = view.getCenter().x + view.getSize().x / 2;
		float top = view.getCenter().y - view.getSize().y / 2;
		float bottom = view.getCenter().y + view.getSize().y / 2;
		int x0 = (int)(left / TILE_SIZE);
		int y0 = (int)(top / TILE_SIZE);
		int x1 = (int)(right / TILE_SIZE) + 1;
		int y1 = (int)(bottom / TILE_SIZE) + 2;

		for (int x = x0; x < x1; x++)
			for (int y = y0; y < y1; y++)
			{
				if (x < 0 || x >= m_width || y < 0 || y >= m_height)
					continue;

				if (m_tiles[x + y * m_width] != nullptr)
					m_tiles[x + y * m_width]->render(x, y, *this, window);
			}
		
		for (uint i = 0; i < m_entities.size(); i++)
			if (m_entities[i] != nullptr)
			{
				Framework::Entity* e = m_entities[i];
			
				m_renderSystem->update(Timestep(0) /*Render doesn't need delta time*/, e);
			}

		LevelRenderer::drawAll();
	}
}
