#include <iostream>
#include "EnemyManager.h"
#include "GameManager.h"

void EnemyManager::tick(Player& player, float deltaTime)
{
	auto game = GameManager::instance();

	//	Updating the enemies.
	for (auto it = m_enemies.begin(); it != m_enemies.end();)
	{
		(*it)->tick(deltaTime);

		///	Putting and '*' in front of a pointer like this means you're passing in the contents of the pointer,
		/// and not the pointer itself.
		if ((*it)->collidesWith(player))
		{
			//	Debug:
			std::cout << "Enemy has been hit!" << std::endl;

			//	Despawning:
			it = despawn(*(*it));

			//	Score management:
			game->score->updateScore(1);

			//	Aesthetics:
			game->camera->startShake();

			break;
		}

		//	Only iterate forward if the enemy in this iteration has not been deleted.
		it++;
	};

	//	Regulating enemy spawning
	m_spawnTimer += deltaTime;

	if (m_spawnTimer < m_maxSpawnInterval) return;
	spawn(rand() % GameManager::instance()->screenWidth);
	m_spawnTimer = 0;
}

void EnemyManager::spawn(float xPos)
{
	m_enemies.push_front(new Enemy(m_idCounter++, xPos));
}

std::list<Enemy*>::iterator EnemyManager::despawn(Enemy& enemy)
{
	auto it = m_enemies.begin();
	for (it; it != m_enemies.end(); it++)
	{
		if (enemy.id != (*it)->id) continue;
		break;
	}
	delete (*it);
	return m_enemies.erase(it);
}

void EnemyManager::draw(sf::RenderWindow& window)
{
	for (auto it = m_enemies.begin(); it != m_enemies.end(); it++)
	{
		(*it)->draw(window);
	}
}
