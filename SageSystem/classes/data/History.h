#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

// =====================================================================
//  HistoryEntry  --  one logged action
// =====================================================================
struct HistoryEntry {
    int         day;
    std::string action;    // PLANT  WATER  HARVEST
    int         row;
    int         col;
    std::string cropName;
    std::string note;
};

// =====================================================================
//  History  (Class 5)
//  Track.Harvest  /  Track.Water
//  Reads from active global variable placed within class Plot
// =====================================================================
class History {
public:

    // -- Track.Harvest --
    void recordHarvest(int day, int row, int col,
                       const std::string& crop, int yield) {
        entries_.push_back({day, "HARVEST", row, col, crop,
                            "Yield: " + std::to_string(yield) + " units"});
    }

    // -- Track.Water --
    void recordWater(int day, int row, int col,
                     const std::string& crop, int newLevel) {
        entries_.push_back({day, "WATER", row, col, crop,
                            "Water level -> " + std::to_string(newLevel) + " %"});
    }

    void recordPlant(int day, int row, int col, const std::string& crop) {
        entries_.push_back({day, "PLANT", row, col, crop, ""});
    }

    // -- Display --
    void display() const {
        if (entries_.empty()) {
            std::cout << "  No history recorded yet.\n";
            return;
        }

        std::string bar(62, '-');
        std::cout << "  " << bar << "\n";
        std::cout << "  " << std::left
                  << std::setw(6)  << "Day"
                  << std::setw(10) << "Action"
                  << std::setw(8)  << "Cell"
                  << std::setw(12) << "Crop"
                  << "Details\n";
        std::cout << "  " << bar << "\n";

        for (const auto& e : entries_) {
            std::string cell = "(" + std::to_string(e.row)
                             + "," + std::to_string(e.col) + ")";
            std::cout << "  " << std::left
                      << std::setw(6)  << e.day
                      << std::setw(10) << e.action
                      << std::setw(8)  << cell
                      << std::setw(12) << e.cropName
                      << e.note << "\n";
        }
        std::cout << "  " << bar << "\n";
    }

    void clearHistory()  { entries_.clear(); }
    int  totalHarvests() const {
        int n = 0; for (auto& e : entries_) if (e.action == "HARVEST") n++; return n;
    }
    int  totalWaters() const {
        int n = 0; for (auto& e : entries_) if (e.action == "WATER") n++; return n;
    }
    const std::vector<HistoryEntry>& getEntries() const { return entries_; }

private:
    std::vector<HistoryEntry> entries_;
};
