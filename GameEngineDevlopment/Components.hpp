#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <cstdint>

inline constexpr uint64_t VelocityKey = (1ULL << 0);
inline constexpr uint64_t PositionKey = (1ULL << 1);
inline constexpr uint64_t BitmapKey = (1ULL << 2);

struct VelocityECS {
    float dx, dy;
    float gravity = 1.0f;
};

struct PositionECS {
    float X, Y;
    PositionECS operator +(const VelocityECS& other) const {
        return { X + other.dx , Y + other.dy }; 
    }
    PositionECS& operator+=(const VelocityECS& other) {
        X += other.dx;
        Y += other.dy;
        return *this;
    }
};

struct BitmapECS {
    std::shared_ptr<SDL_Texture> texture;
};