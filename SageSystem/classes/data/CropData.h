#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

// ─────────────────────────────────────────────
//  CropData — holds static data loaded from
//             data/crops.csv
// ─────────────────────────────────────────────
struct CropData {
    std::string name;
    std::string symbol;        // 2-char display token
    int         growthDays;    // days to maturity
    int         waterNeedDays; // re-water every N days
    int         harvestYield;  // units produced on harvest
    int         waterPerSession; // water level added per watering (+)
    float       optimalMoisture;
    float       optimalTemp;
    float       optimalHumidity;
};

// ─────────────────────────────────────────────
//  CropRegistry — singleton that loads and
//                 stores all crop definitions
// ─────────────────────────────────────────────
class CropRegistry {
public:
    static CropRegistry& instance() {
        static CropRegistry inst;
        return inst;
    }

    bool load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "[CropRegistry] Cannot open: " << filepath << "\n";
            return false;
        }
        std::string line;
        std::getline(file, line); // skip header
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string tok;
            CropData c;
            std::getline(ss, c.name,            ',');
            std::getline(ss, c.symbol,           ',');
            std::getline(ss, tok, ','); c.growthDays       = std::stoi(tok);
            std::getline(ss, tok, ','); c.waterNeedDays    = std::stoi(tok);
            std::getline(ss, tok, ','); c.harvestYield     = std::stoi(tok);
            std::getline(ss, tok, ','); c.waterPerSession  = std::stoi(tok);
            std::getline(ss, tok, ','); c.optimalMoisture  = std::stof(tok);
            std::getline(ss, tok, ','); c.optimalTemp      = std::stof(tok);
            std::getline(ss, tok, ','); c.optimalHumidity  = std::stof(tok);
            crops_.push_back(c);
        }
        return true;
    }

    const std::vector<CropData>& all() const { return crops_; }

    const CropData* find(const std::string& name) const {
        for (auto& c : crops_)
            if (c.name == name) return &c;
        return nullptr;
    }

private:
    CropRegistry() = default;
    std::vector<CropData> crops_;
};
