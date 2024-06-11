#pragma once
#ifdef ALPINIST_GAME
namespace AlpinistGame
{
    enum Condition
    {
        C_WALL_FORWARD,
        C_WALL_RIGHT,
        C_WALL_LEFT
    };

    enum MoveResult
    {
        MR_SUCCESS,
        MR_ERROR,
        MR_FINISH
    };

    enum PlayerDirection
    {
        PD_UP = 4,
        PD_RIGHT = 2,
        PD_DOWN = 8,
        PD_LEFT = 1
    };

    inline AlpinistGame::PlayerDirection& operator++(AlpinistGame::PlayerDirection& direction)
    {
        if (direction % 4 == 0)
        {
            direction = static_cast<AlpinistGame::PlayerDirection>(~(direction >> 2) & 3);
            return direction;
        }
        direction = static_cast<AlpinistGame::PlayerDirection>(direction << 2);
        return direction;
    }

    inline AlpinistGame::PlayerDirection& operator--(AlpinistGame::PlayerDirection& direction)
    {
        if (direction % 4 == 0)
        {
            direction = static_cast<AlpinistGame::PlayerDirection>(direction >> 2);
            return direction;
        }
        direction = static_cast<AlpinistGame::PlayerDirection>(~(direction << 2) & 12);
        return direction;
    }
    
    inline uint8_t GetBit(int8_t num, int i)
    {
        return (num >> i) & 1u;
    }

    inline std::pair<int, int> GetDirectionFromByteCode(const AlpinistGame::PlayerDirection& direction)
    {
        return std::make_pair(GetBit(direction, 3) + GetBit(direction, 2) * -1,
                              GetBit(direction, 1) + GetBit(direction, 0) * -1);
    }
}

#endif