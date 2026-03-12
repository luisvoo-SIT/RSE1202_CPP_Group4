#pragma once
#include "Plot.h"
#include "Robots.h"
#include "History.h"
#include "CropData.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

// =====================================================================
//  UserInterface  (Class 1)
//
//  The field is a 3x3 grid of PLOTS  (Plot rows 1-3, Plot cols 1-3).
//  Each Plot renders as a 3x3 sub-grid of 9 identical cells.
//  All 9 cells in a Plot always hold the same crop.
//  Every operation (plant/water/harvest/clear) acts on a whole Plot.
//
//  Below each Plot two lines show:
//    Line 1 : crop name  (or "(empty)")
//    Line 2 : status     (weeks to mature / Mature / Thirsty / Withered)
// =====================================================================
class UserInterface {
public:
    explicit UserInterface(Plot& plot, History& history)
        : plot_(plot), history_(history) {}

    void run() {
        while (running_) {
            clearScreen();
            printBanner();
            printDayBar();
            printField();
            printMainMenu();
            handleMainChoice();
        }
        std::cout << "\n  Goodbye from S.A.G.E!\n\n";
    }

private:
    Plot&    plot_;
    History& history_;
    bool     running_ = true;

    // ── Layout constants ──────────────────────────────────────────────
    // Sub-cell slot width (content only, not borders)
    static constexpr int SW  = 5;
    // Full plot width incl. borders: 1 + 3*(SW+1) = 19
    static constexpr int PW  = 1 + 3*(SW+1);   // = 19
    // Gap between plots
    static constexpr int GAP = 4;
    // Column width used for label lines: PW + GAP
    static constexpr int LW  = PW + GAP;        // = 23

    // =================================================================
    //  UTILITIES
    // =================================================================
    void sep(char ch='-', int w=68) const {
        std::cout << "  " << std::string(w, ch) << "\n";
    }
    void box(char ch='-', int w=52) const {
        std::cout << "  +" << std::string(w-2, ch) << "+\n";
    }
    void clearScreen() const {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    void pauseForEnter() {
        std::cout << "\n  Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    int readInt() {
        int val = 0;
        while (!(std::cin >> val)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  Enter a number: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return val;
    }

    // 1-based plot index -> 0-based global top-left row or col
    int pg(int plotIdx) const { return (plotIdx - 1) * 3; }

    // Representative cell for a plot (all 9 are identical)
    const Cell& plotCell(int pRow, int pCol) const {
        return plot_.getCell(pg(pRow), pg(pCol));
    }

    // =================================================================
    //  APPLY TO WHOLE PLOT  (silent — no per-cell robot output)
    //  Returns count of successful operations.
    // =================================================================
    int applyToPlot(int pRow, int pCol, char action,
                    const std::string& cropName = "") {
        int r0 = pg(pRow), c0 = pg(pCol);
        int ok = 0;
        for (int dr = 0; dr < 3; dr++)
            for (int dc = 0; dc < 3; dc++) {
                bool res = false;
                int r = r0+dr, c = c0+dc;
                if      (action == 'p') res = plot_.plantCrop(r, c, cropName);
                else if (action == 'w') res = plot_.waterCrop(r, c);
                else if (action == 'h') res = (plot_.harvestCrop(r, c) >= 0);
                else if (action == 'c') res = plot_.clearCell(r, c);
                if (res) ok++;
            }
        return ok;
    }

    // =================================================================
    //  SUB-CELL SYMBOL  (SW chars, centred)
    //  Every sub-cell in a plot shows the same symbol.
    // =================================================================
    std::string subCellSym(int pRow, int pCol) const {
        const Cell& c = plotCell(pRow, pCol);
        std::string sym;
        if (!c.isPlanted)           sym = "";
        else if (c.isWithered)      sym = "W";
        else if (c.isMature)        sym = "M";
        else if (c.waterLevel < 20) sym = "!";
        else {
            const CropData* cd = CropRegistry::instance().find(c.cropName);
            int dl = 0;
            if (cd) { dl = (c.plantedDay + cd->growthDays) - plot_.getCurrentDay(); if (dl<0) dl=0; }
            sym = std::to_string((dl+6)/7) + "w";
        }
        int pad = SW - (int)sym.size();
        return std::string(pad/2,' ') + sym + std::string(pad-pad/2,' ');
    }

    // =================================================================
    //  PLOT LABEL LINES  (two lines printed below the sub-grid)
    // =================================================================
    std::string plotLabelName(int pRow, int pCol) const {
        const Cell& c = plotCell(pRow, pCol);
        return c.isPlanted ? c.cropName : "(empty)";
    }
    std::string plotLabelStatus(int pRow, int pCol) const {
        const Cell& c = plotCell(pRow, pCol);
        if (!c.isPlanted)           return "";
        if (c.isWithered)           return "Withered";
        if (c.isMature)             return "Mature  -- harvest now";
        if (c.waterLevel < 20)      return "Thirsty -- needs water";
        const CropData* cd = CropRegistry::instance().find(c.cropName);
        int dl = 0;
        if (cd) { dl = (c.plantedDay + cd->growthDays) - plot_.getCurrentDay(); if (dl<0) dl=0; }
        int wk = (dl+6)/7;
        return std::to_string(wk) + " week(s) to mature";
    }

    // Single plot horizontal border:  +-----+-----+-----+
    std::string hline() const {
        std::string s = "+";
        for (int i=0;i<3;i++) s += std::string(SW,'-') + "+";
        return s;   // 19 chars
    }

    // =================================================================
    //  PRINT FIELD  --  3x3 arrangement of mini-plots
    // =================================================================
    void printField() const {
        const std::string hl  = hline();
        const std::string gap = std::string(GAP, ' ');

        std::cout << "  +-----  S.A.G.E FIELD  [ 3 x 3 Plots ]  -----+\n\n";

        for (int pRow = 1; pRow <= 3; pRow++) {

            // Plot header labels
            std::cout << "  ";
            for (int pCol = 1; pCol <= 3; pCol++) {
                std::string hdr = "Plot (" + std::to_string(pRow)
                                + "," + std::to_string(pCol) + ")";
                // centre in PW
                int pad = PW - (int)hdr.size();
                std::cout << std::string(pad/2,' ') << hdr << std::string(pad-pad/2,' ');
                if (pCol < 3) std::cout << gap;
            }
            std::cout << "\n";

            // Top border
            std::cout << "  ";
            for (int pCol=1;pCol<=3;pCol++) {
                std::cout << hl;
                if (pCol<3) std::cout << gap;
            }
            std::cout << "\n";

            // 3 sub-rows of cells
            for (int sr=0; sr<3; sr++) {
                // Cell content row
                std::cout << "  ";
                for (int pCol=1;pCol<=3;pCol++) {
                    std::string s = subCellSym(pRow, pCol);
                    std::cout << "|" << s << "|" << s << "|" << s << "|";
                    if (pCol<3) std::cout << gap;
                }
                std::cout << "\n";
                // Row separator
                std::cout << "  ";
                for (int pCol=1;pCol<=3;pCol++) {
                    std::cout << hl;
                    if (pCol<3) std::cout << gap;
                }
                std::cout << "\n";
            }

            // Label line 1: crop name
            std::cout << "  ";
            for (int pCol=1;pCol<=3;pCol++) {
                std::cout << std::left << std::setw(pCol<3 ? LW : PW)
                          << plotLabelName(pRow, pCol);
            }
            std::cout << "\n";

            // Label line 2: status
            std::cout << "  ";
            for (int pCol=1;pCol<=3;pCol++) {
                std::cout << std::left << std::setw(pCol<3 ? LW : PW)
                          << plotLabelStatus(pRow, pCol);
            }
            std::cout << "\n\n";
        }

        // Legend
        sep('-', 68);
        std::cout << "  SYMBOLS :  Nw = N weeks to mature    "
                     "M = Mature    ! = Thirsty    W = Withered\n";
        sep('-', 68);
        std::cout << "\n";
    }

    // =================================================================
    //  BANNER
    // =================================================================
    void printBanner() const {
        sep('=', 68);
        std::cout << "  |      S.A.G.E  --  Smart Agricultural Grid Environment        |\n";
        sep('=', 68);
        std::cout << "\n";
    }

    // =================================================================
    //  DAY / STATS BAR
    // =================================================================
    void printDayBar() const {
        std::cout << "  Day  : " << std::left << std::setw(6) << plot_.getCurrentDay()
                  << " | Harvests  : " << std::setw(4) << history_.totalHarvests()
                  << " | Waterings : " << history_.totalWaters() << "\n\n";
    }

    // =================================================================
    //  MAIN MENU
    // =================================================================
    void printMainMenu() const {
        box('-', 52);
        std::cout << "  |                 S.A.G.E  MENU                   |\n";
        box('-', 52);
        std::cout << "  |  1.  View Plot Info                              |\n";
        std::cout << "  |  2.  Plant Crop                                  |\n";
        std::cout << "  |  3.  Water Plot                                  |\n";
        std::cout << "  |  4.  Harvest Plot                                |\n";
        std::cout << "  |  5.  Clear Withered Plot                         |\n";
        std::cout << "  |  6.  Time Skip                                   |\n";
        std::cout << "  |  7.  View History                                |\n";
        std::cout << "  |  0.  Exit                                        |\n";
        box('-', 52);
        std::cout << "  Choice: ";
    }

    void handleMainChoice() {
        int ch = readInt();
        switch (ch) {
            case 1: doViewPlot();    break;
            case 2: doPlant();       break;
            case 3: doWater();       break;
            case 4: doHarvest();     break;
            case 5: doClear();       break;
            case 6: doTimeSkip();    break;
            case 7: doViewHistory(); break;
            case 0: running_ = false; break;
            default:
                std::cout << "  Invalid choice.\n";
                pauseForEnter();
        }
    }

    // =================================================================
    //  SHARED: show field then prompt for a plot
    //  Returns 1-based {pRow, pCol} or {-1,-1} on bad input
    // =================================================================
    std::pair<int,int> selectPlot(const std::string& action) {
        printField();
        std::cout << "  " << action << "  --  Plot Row (1-3): ";
        int pRow = readInt();
        std::cout << "  " << action << "  --  Plot Col (1-3): ";
        int pCol = readInt();
        if (pRow<1||pRow>3||pCol<1||pCol>3) {
            std::cout << "  Invalid. Row and Col must be 1-3.\n";
            pauseForEnter();
            return {-1,-1};
        }
        return {pRow, pCol};
    }

    // =================================================================
    //  SHARED: "Select a Plot" / "All Plots" sub-menu
    // =================================================================
    int showSubMenu(const std::string& title) {
        clearScreen();
        printBanner();
        box('-', 52);
        std::cout << "  |  " << std::left << std::setw(48) << title << "|\n";
        box('-', 52);
        std::cout << "  |  1.  Select a Plot                               |\n";
        std::cout << "  |  2.  All Plots                                   |\n";
        std::cout << "  |  0.  Back                                        |\n";
        box('-', 52);
        std::cout << "  Choice: ";
        return readInt();
    }

    // =================================================================
    //  SHARED: crop chooser
    // =================================================================
    int chooseCrop() {
        const auto& crops = CropRegistry::instance().all();
        std::cout << "\n";
        sep('-', 64);
        std::cout << "  Available Crops\n";
        sep('-', 64);
        std::cout << "  " << std::left
                  << std::setw(4)  << "#"
                  << std::setw(12) << "Name"
                  << std::setw(14) << "Matures in"
                  << std::setw(12) << "Yield"
                  << "Water/session\n";
        sep('-', 64);
        for (int i=0;i<(int)crops.size();i++) {
            std::cout << "  " << std::left
                      << std::setw(4)  << (i+1)
                      << std::setw(12) << crops[i].name
                      << std::setw(14) << (std::to_string(crops[i].growthDays/7)+" weeks")
                      << std::setw(12) << (std::to_string(crops[i].harvestYield)+" units")
                      << "+" << crops[i].waterPerSession << "%\n";
        }
        sep('-', 64);
        std::cout << "  Select (1-" << crops.size() << ", or 0 to cancel): ";
        int idx = readInt()-1;
        if (idx<0||idx>=(int)crops.size()) {
            std::cout << "  Cancelled.\n";
            pauseForEnter();
            return -1;
        }
        return idx;
    }

    // =================================================================
    //  1.  VIEW PLOT INFO
    // =================================================================
    void doViewPlot() {
        auto [pRow, pCol] = selectPlot("View");
        if (pRow<0) return;

        const Cell& c = plotCell(pRow, pCol);
        std::cout << "\n";
        sep('-', 52);
        std::cout << "  Plot (" << pRow << "," << pCol << ")  --  Details\n";
        sep('-', 52);
        if (!c.isPlanted) {
            std::cout << "  Status        : Empty\n";
        } else {
            const CropData* cd = CropRegistry::instance().find(c.cropName);
            int age = plot_.getCurrentDay() - c.plantedDay;
            std::cout << "  Crop          : " << c.cropName    << "\n";
            std::cout << "  Age           : " << age           << " day(s)\n";
            std::cout << "  Water Level   : " << c.waterLevel  << "%\n";
            std::cout << "  Drought Days  : " << c.droughtDays << " day(s)  (withers at 3)\n";
            if (c.isWithered)      std::cout << "  Status        : WITHERED -- clear it (option 5)\n";
            else if (c.isMature)   std::cout << "  Status        : MATURE -- ready to harvest\n";
            else {
                std::cout << "  Status        : Growing\n";
                if (cd) {
                    int dl = (c.plantedDay+cd->growthDays) - plot_.getCurrentDay();
                    if (dl>0) std::cout << "  Time to ripe  : " << dl
                                        << " day(s)  (" << (dl+6)/7 << " week(s))\n";
                }
            }
            if (cd) std::cout << "  Base yield    : " << cd->harvestYield << " units/cell  (x9 total)\n";
        }
        sep('-', 52);
        std::cout << "  Sensor Readings\n";
        sep('-', 52);
        plot_.readSensors(pg(pRow), pg(pCol));
        pauseForEnter();
    }

    // =================================================================
    //  2.  PLANT
    // =================================================================
    void doPlant() {
        int ch = showSubMenu("PLANT CROP");
        if (ch==0) return;

        int cropIdx = chooseCrop();
        if (cropIdx<0) return;
        const std::string& name = CropRegistry::instance().all()[cropIdx].name;

        if (ch==1) {
            auto [pRow, pCol] = selectPlot("Plant");
            if (pRow<0) return;
            if (plotCell(pRow,pCol).isPlanted) {
                std::cout << "  Plot (" << pRow << "," << pCol
                          << ") is already occupied. Harvest or clear it first.\n";
                pauseForEnter();
                return;
            }
            applyToPlot(pRow, pCol, 'p', name);
            std::cout << "\n  Planted " << name
                      << " in Plot (" << pRow << "," << pCol << ").\n";
            pauseForEnter();

        } else if (ch==2) {
            std::cout << "\n  Planting " << name << " in all empty plots...\n\n";
            int done=0;
            for (int r=1;r<=3;r++) for (int c=1;c<=3;c++) {
                if (plotCell(r,c).isPlanted) {
                    std::cout << "  Plot (" << r << "," << c << ")  skipped  (occupied)\n";
                } else {
                    applyToPlot(r, c, 'p', name);
                    std::cout << "  Plot (" << r << "," << c << ")  planted\n";
                    done++;
                }
            }
            std::cout << "\n  Done -- " << done << " plot(s) planted.\n";
            pauseForEnter();
        } else { std::cout << "  Invalid.\n"; pauseForEnter(); }
    }

    // =================================================================
    //  3.  WATER
    // =================================================================
    void doWater() {
        int ch = showSubMenu("WATER CROP");
        if (ch==0) return;

        if (ch==1) {
            auto [pRow, pCol] = selectPlot("Water");
            if (pRow<0) return;
            const Cell& cell = plotCell(pRow,pCol);
            if (!cell.isPlanted) {
                std::cout << "  Plot (" << pRow << "," << pCol << ") is empty.\n";
                pauseForEnter(); return;
            }
            if (cell.isWithered) {
                std::cout << "  Plot (" << pRow << "," << pCol
                          << ") has withered -- clear it first.\n";
                pauseForEnter(); return;
            }
            int prev = cell.waterLevel;
            applyToPlot(pRow, pCol, 'w');
            int now = plotCell(pRow,pCol).waterLevel;
            std::cout << "\n  Watered Plot (" << pRow << "," << pCol
                      << ")  |  Water: " << prev << "% -> " << now << "%\n";
            pauseForEnter();

        } else if (ch==2) {
            std::cout << "\n  Watering all planted plots...\n\n";
            int done=0;
            for (int r=1;r<=3;r++) for (int c=1;c<=3;c++) {
                const Cell& cell = plotCell(r,c);
                if (!cell.isPlanted||cell.isWithered) {
                    std::cout << "  Plot (" << r << "," << c << ")  skipped\n";
                } else {
                    int prev = cell.waterLevel;
                    applyToPlot(r, c, 'w');
                    int now = plotCell(r,c).waterLevel;
                    std::cout << "  Plot (" << r << "," << c << ")  watered"
                              << "  |  " << prev << "% -> " << now << "%\n";
                    done++;
                }
            }
            std::cout << "\n  Done -- " << done << " plot(s) watered.\n";
            pauseForEnter();
        } else { std::cout << "  Invalid.\n"; pauseForEnter(); }
    }

    // =================================================================
    //  4.  HARVEST
    // =================================================================
    void doHarvest() {
        int ch = showSubMenu("HARVEST CROP");
        if (ch==0) return;

        if (ch==1) {
            auto [pRow, pCol] = selectPlot("Harvest");
            if (pRow<0) return;
            const Cell& cell = plotCell(pRow,pCol);
            if (!cell.isPlanted) {
                std::cout << "  Plot (" << pRow << "," << pCol << ") is empty.\n";
                pauseForEnter(); return;
            }
            if (cell.isWithered) {
                std::cout << "  Plot (" << pRow << "," << pCol
                          << ") has withered -- clear it first.\n";
                pauseForEnter(); return;
            }
            if (!cell.isMature) {
                std::cout << "  Plot (" << pRow << "," << pCol
                          << ") is not mature yet.\n";
                pauseForEnter(); return;
            }
            std::string cropName = cell.cropName;
            int total = 0;
            for (int dr=0;dr<3;dr++) for (int dc=0;dc<3;dc++) {
                int y = plot_.harvestCrop(pg(pRow)+dr, pg(pCol)+dc);
                if (y>0) total+=y;
            }
            std::cout << "\n  Harvested " << cropName
                      << " from Plot (" << pRow << "," << pCol
                      << ")  |  Total yield: " << total << " units\n";
            pauseForEnter();

        } else if (ch==2) {
            std::cout << "\n  Harvesting all mature plots...\n\n";
            int done=0, grandTotal=0;
            for (int r=1;r<=3;r++) for (int c=1;c<=3;c++) {
                const Cell& cell = plotCell(r,c);
                if (!cell.isPlanted||!cell.isMature||cell.isWithered) {
                    std::cout << "  Plot (" << r << "," << c << ")  skipped\n";
                } else {
                    std::string cropName = cell.cropName;
                    int total=0;
                    for (int dr=0;dr<3;dr++) for (int dc=0;dc<3;dc++) {
                        int y = plot_.harvestCrop(pg(r)+dr, pg(c)+dc);
                        if (y>0) total+=y;
                    }
                    std::cout << "  Plot (" << r << "," << c << ")  harvested  "
                              << cropName << "  |  " << total << " units\n";
                    grandTotal += total;
                    done++;
                }
            }
            std::cout << "\n  Done -- " << done << " plot(s) harvested"
                      << "  |  Grand total: " << grandTotal << " units\n";
            pauseForEnter();
        } else { std::cout << "  Invalid.\n"; pauseForEnter(); }
    }

    // =================================================================
    //  5.  CLEAR WITHERED
    // =================================================================
    void doClear() {
        int ch = showSubMenu("CLEAR WITHERED CROPS");
        if (ch==0) return;

        if (ch==1) {
            auto [pRow, pCol] = selectPlot("Clear");
            if (pRow<0) return;
            if (!plotCell(pRow,pCol).isWithered) {
                std::cout << "  Plot (" << pRow << "," << pCol
                          << ") is not withered.\n";
                pauseForEnter(); return;
            }
            applyToPlot(pRow, pCol, 'c');
            std::cout << "\n  Plot (" << pRow << "," << pCol
                      << ") cleared. Ready to plant again.\n";
            pauseForEnter();

        } else if (ch==2) {
            std::cout << "\n  Clearing all withered plots...\n\n";
            int done=0;
            for (int r=1;r<=3;r++) for (int c=1;c<=3;c++) {
                if (!plotCell(r,c).isWithered) {
                    std::cout << "  Plot (" << r << "," << c << ")  skipped\n";
                } else {
                    applyToPlot(r, c, 'c');
                    std::cout << "  Plot (" << r << "," << c << ")  cleared\n";
                    done++;
                }
            }
            std::cout << "\n  Done -- " << done << " plot(s) cleared.\n";
            pauseForEnter();
        } else { std::cout << "  Invalid.\n"; pauseForEnter(); }
    }

    // =================================================================
    //  6.  TIME SKIP
    // =================================================================
    void doTimeSkip() {
        std::cout << "\n  Days to skip (1-70): ";
        int days = readInt();
        if (days<1||days>70) {
            std::cout << "  Please enter a value between 1 and 70.\n";
            pauseForEnter(); return;
        }
        int before = plot_.getCurrentDay();
        plot_.advanceDays(days);
        std::cout << "  Time advanced: Day " << before
                  << " -> Day " << plot_.getCurrentDay()
                  << "  (" << days << " day(s) passed)\n";
        std::cout << "  Note: unwatered crops wither after 3 dry days.\n";
        pauseForEnter();
    }

    // =================================================================
    //  7.  VIEW HISTORY
    // =================================================================
    void doViewHistory() {
        std::cout << "\n";
        sep('=', 68);
        std::cout << "  |                       ACTION  HISTORY                         |\n";
        sep('=', 68);
        history_.display();
        pauseForEnter();
    }
};
