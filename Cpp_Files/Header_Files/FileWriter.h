#pragma once
#include "seedingBot.h"
#include "SprayerBot.h"
#include "HarvestBot.h"
#include <string>

void writeLogsToFile(const SeedingBot&    seeder,
                     const SprayerBot&    sprayer,
                     const HarvestingBot& harvester);