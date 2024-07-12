#pragma once
#ifdef ALPINIST_GAME
#include "GameTypes.h"

namespace AlpinistGame
{
	    class Entity
        {
        protected:
            std::pair<int8_t, int8_t> m_pos;
        public:
            Entity(std::pair<int8_t, int8_t> pos) : m_pos(pos){}
            virtual ~Entity() {}
            std::pair<int8_t, int8_t> GetPos() const { return m_pos; }
            void SetPos(std::pair<int8_t, int8_t> pos) { m_pos = pos;}
        };
        
        class Player : public Entity
        {
        protected:
            AlpinistGame::PlayerDirection m_direction;
            
        public:
            Player(std::pair<int8_t, int8_t> pos, AlpinistGame::PlayerDirection direction) : Entity(pos), m_direction(direction){}
            
            void RotateRight(){++m_direction;}
            void RotateLeft(){--m_direction;}

            void SetDirection(const AlpinistGame::PlayerDirection& NewDirection) { m_direction = NewDirection; }
            const AlpinistGame::PlayerDirection& GetDirection() const { return m_direction;}
        };
        
        class Wall : public Entity
        {
        public:
           Wall(std::pair<int8_t, int8_t> pos) : Entity(pos){}
        };
        
        class Finish : public Entity
        {
        public:
            Finish(std::pair<int8_t, int8_t> pos) : Entity(pos){}
        };

}
#endif