#pragma once
#include "Cell.h"
#include "CropData.h"
#include <string>
#include <cmath>

// ─────────────────────────────────────────────
//  Sensor base class
//  Reads from the 9x9 grid (via Cell reference)
//  and returns a float reading.
// ─────────────────────────────────────────────
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual float   read(const Cell& cell, int currentDay) const = 0;
    virtual std::string name() const = 0;
    virtual std::string unit() const = 0;
    // Returns true when reading is within optimal range for crop
    virtual bool isOptimal(float reading, const CropData* crop) const = 0;
};

// ─────────────────────────────────────────────
//  MoistureSensor — reads water level of cell
//  Optimal range: crop's optimalMoisture ±10
// ─────────────────────────────────────────────
class MoistureSensor : public Sensor {
public:
    float read(const Cell& cell, int /*currentDay*/) const override {
        // Water level (0-100) maps directly to moisture reading
        return static_cast<float>(cell.waterLevel);
    }
    std::string name() const override { return "Moisture"; }
    std::string unit() const override { return "%"; }
    bool isOptimal(float reading, const CropData* crop) const override {
        if (!crop) return false;
        return std::fabs(reading - crop->optimalMoisture) <= 10.0f;
    }
};

// ─────────────────────────────────────────────
//  TemperatureSensor — simulates ambient temp
//  Varies sinusoidally with current day
//  Optimal range: crop's optimalTemp ±3
// ─────────────────────────────────────────────
class TemperatureSensor : public Sensor {
public:
    float read(const Cell& /*cell*/, int currentDay) const override {
        // Base 22°C ± 8°C seasonal cycle
        return 22.0f + 8.0f * std::sin(currentDay * 0.15f);
    }
    std::string name() const override { return "Temperature"; }
    std::string unit() const override { return "degC"; }
    bool isOptimal(float reading, const CropData* crop) const override {
        if (!crop) return false;
        return std::fabs(reading - crop->optimalTemp) <= 3.0f;
    }
};

// ─────────────────────────────────────────────
//  HumiditySensor — reads ambient humidity
//  Influenced by surrounding water levels
//  Optimal range: crop's optimalHumidity ±10
// ─────────────────────────────────────────────
class HumiditySensor : public Sensor {
public:
    // avgNeighbourWater is passed from Plot when reading
    float read(const Cell& cell, int currentDay) const override {
        // Base 50% + contribution from cell water level + day cycle
        float base = 50.0f + (cell.waterLevel * 0.2f);
        base += 5.0f * std::sin(currentDay * 0.08f);
        if (base > 100.0f) base = 100.0f;
        if (base < 0.0f)   base = 0.0f;
        return base;
    }
    std::string name() const override { return "Humidity"; }
    std::string unit() const override { return "%"; }
    bool isOptimal(float reading, const CropData* crop) const override {
        if (!crop) return false;
        return std::fabs(reading - crop->optimalHumidity) <= 10.0f;
    }
};
