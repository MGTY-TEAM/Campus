#pragma once

namespace AlpinistGame
{
    enum Condition
    {
        WALL_FORWARD,
        WALL_RIGHT,
        WALL_LEFT
    };

    enum MoveResult
    {
        SUCCESS,
        ERROR,
        FINISH
    };

    enum PlayerDirection
    {
        UP = 4,
        RIGHT = 2,
        DOWN = 8,
        LEFT = 1
    };

    inline PlayerDirection& operator++(PlayerDirection& direction)
    {
        if (direction % 4 == 0)
        {
            direction = static_cast<PlayerDirection>(~(direction >> 2) & 3);
            return direction;
        }
        direction = static_cast<PlayerDirection>(direction << 2);
        return direction;
    }

    inline PlayerDirection& operator--(PlayerDirection& direction)
    {
        if (direction % 4 == 0)
        {
            direction = static_cast<PlayerDirection>(direction >> 2);
            return direction;
        }
        direction = static_cast<PlayerDirection>(~(direction << 2) & 12);
        return direction;
    }
    
    inline uint8_t GetBit(int8_t num, int i)
    {
        return (num >> i) & 1u;
    }

    inline std::pair<int, int> GetDirectionFromByteCode(const PlayerDirection& direction)
    {
        return std::make_pair(GetBit(direction, 3) + GetBit(direction, 2) * -1,
                              GetBit(direction, 1) + GetBit(direction, 0) * -1);
    }
}

