#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <vector>
#include "boid.hpp"

#pragma once
#include <vector>
#include "boid.hpp"

void updateBoid(Boid& boid, const std::vector<Boid>& boids, int worldWidth, int worldHeight);

#endif // BEHAVIOR_H
