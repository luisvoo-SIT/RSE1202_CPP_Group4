// ═══════════════════════════════════════════════════════════════
//  S.A.G.E — Smart Agricultural Grid Environment
//  main.cpp
//
//  Architecture (from whiteboard design):
//    Classes: UserInterface | Plot | Sensor | Robots | History
//    Data:    data/crops.csv (crop data + simulated sensor env)
// ═══════════════════════════════════════════════════════════════

#include "classes/CropData.h"
#include "classes/History.h"
#include "classes/Plot.h"
#include "classes/Robots.h"
#include "classes/UserInterface.h"
#include <iostream>
#include <filesystem>

int main() {
    // ── Load crop data from CSV (reads from data/crops.csv) ──
    // Try multiple paths so it works from any working directory
    bool loaded = false;
    for (const auto& path : {"data/crops.csv", "../data/crops.csv", "./sage/data/crops.csv"}) {
        if (CropRegistry::instance().load(path)) {
            loaded = true;
            break;
        }
    }
    if (!loaded) {
        std::cerr << "[SAGE] Warning: Could not load crops.csv."
                  << " Falling back to built-in defaults.\n";

        // Inline fallback so the game still works without the file
        // (We parse a small inline CSV string)
        std::istringstream fallback(
            "name,symbol,growth_days,water_need_days,harvest_yield,water_per_session,"
            "optimal_moisture,optimal_temp,optimal_humidity\n"
            "Wheat,WH,7,3,10,20,60.0,22.0,55.0\n"
            "Corn,CO,10,2,15,25,70.0,26.0,60.0\n"
            "Tomato,TM,5,1,8,15,75.0,24.0,65.0\n"
            "Potato,PT,8,3,12,20,65.0,20.0,60.0\n"
        );
        // Note: CropRegistry::load() takes a filepath string, so we
        // handle the fallback by writing a temp file:
        {
            std::ofstream tmp("/tmp/sage_crops.csv");
            tmp << "name,symbol,growth_days,water_need_days,harvest_yield,"
                   "water_per_session,optimal_moisture,optimal_temp,optimal_humidity\n"
                   "Wheat,WH,7,3,10,20,60.0,22.0,55.0\n"
                   "Corn,CO,10,2,15,25,70.0,26.0,60.0\n"
                   "Tomato,TM,5,1,8,15,75.0,24.0,65.0\n"
                   "Potato,PT,8,3,12,20,65.0,20.0,60.0\n";
        }
        CropRegistry::instance().load("/tmp/sage_crops.csv");
    }

    if (CropRegistry::instance().all().empty()) {
        std::cerr << "[SAGE] Fatal: No crop data available. Exiting.\n";
        return 1;
    }

    std::cout << "[SAGE] Loaded " << CropRegistry::instance().all().size()
              << " crop types from database.\n";

    // ── Instantiate system components ────────────────────────
    History       history;                  // Class 5: History
    Plot          plot(history);            // Class 2: Plot (9×9 grid)
    UserInterface ui(plot, history);        // Class 1: UserInterface

    // ── Run the UI loop ──────────────────────────────────────
    ui.run();

    return 0;
}
