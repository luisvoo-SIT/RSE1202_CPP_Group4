#include "Header_Files/FileWriter.h"
#include "Header_Files/plotv2.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void writeLogsToFile(const SeedingBot&    seeder,
                     const SprayerBot&    sprayer,
                     const HarvestingBot& harvester) {

    // ── Ask user for file name ────────────────────────────────
    string fileName;
    cout << "\nEnter output file name: ";
    cin  >> fileName;

    // ── Check what extension the user entered ─────────────────
    bool hasTxt = fileName.find(".txt") != string::npos;
    bool hasCsv = fileName.find(".csv") != string::npos;

    // ── Check if user entered an unsupported extension ────────
    bool hasOtherExtension = false;
    if (!hasTxt && !hasCsv) {
        size_t dotPos = fileName.find_last_of(".");
        if (dotPos != string::npos) {
            // ── dot found but not .txt or .csv ────────────────
            hasOtherExtension = true;
            string enteredExt = fileName.substr(dotPos);
            cout << "Unsupported file format: " << enteredExt << "\n"
                 << "Supported formats are .txt and .csv only.\n";

            // ── remove the unsupported extension ──────────────
            fileName = fileName.substr(0, dotPos);
            cout << "File name changed to: " << fileName << "\n";
        }
    }

    int formatChoice;

    if (hasTxt) {
        // ── user already typed .txt ───────────────────────────
        cout << "Text file format detected.\n";
        formatChoice = 1;

    } else if (hasCsv) {
        // ── user already typed .csv ───────────────────────────
        cout << "CSV file format detected.\n";
        formatChoice = 2;

    } else {
        // ── no valid extension — ask user to choose ───────────
        cout << "\n=== Select File Format ===\n"
             << "1. Text file (.txt)\n"
             << "2. CSV file  (.csv)\n"
             << "Select format: ";

        cin >> formatChoice;

        // ── validate choice ───────────────────────────────────
        while (formatChoice != 1 && formatChoice != 2) {
            cout << "Invalid choice. Please enter 1 or 2: ";
            cin  >> formatChoice;
        }

        // ── add extension ─────────────────────────────────────
        if (formatChoice == 1)
            fileName += ".txt";
        else
            fileName += ".csv";
    }

    // ── Open file ─────────────────────────────────────────────
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: could not create file " << fileName << "\n";
        return;
    }

    file << fixed << setprecision(2);

    // ── Write based on format ─────────────────────────────────
    if (formatChoice == 2) {
        // ══════════════════════════════════════════════════════
        //  CSV FORMAT
        // ══════════════════════════════════════════════════════
        file << "SEEDINGBOT LOG\n"
             << "Session,CropName,TimeToGrow,WaterPerDay,"
             << "MinHumidity,MaxHumidity,MinTemperature,"
             << "MaxTemperature,MinUV,MaxUV\n";

        const auto& seedLog = seeder.getSeedLog();
        if (seedLog.empty()) {
            file << "none\n";
        } else {
            for (size_t i = 0; i < seedLog.size(); ++i) {
                file << i + 1                        << ","
                     << seedLog[i].getName()         << ","
                     << seedLog[i].getTimeToGrow()   << ","
                     << seedLog[i].getWaterReq()     << ","
                     << seedLog[i].getMinHum()       << ","
                     << seedLog[i].getMaxHum()       << ","
                     << seedLog[i].getMinTemp()      << ","
                     << seedLog[i].getMaxTemp()      << ","
                     << seedLog[i].getMinUV()        << ","
                     << seedLog[i].getMaxUV()        << "\n";
            }
        }

        file << "\nSPRAYERBOT LOG\n"
             << "Session,Mode,Chemical,AreaSprayed,ChemicalUsed\n";

        const auto& sprayLog = sprayer.getSprayLog();
        if (sprayLog.empty()) {
            file << "none\n";
        } else {
            for (size_t i = 0; i < sprayLog.size(); ++i) {
                file << i + 1                        << ","
                     << sprayLog[i].mode             << ","
                     << sprayLog[i].chemicalName     << ","
                     << sprayLog[i].areaSprayed      << ","
                     << sprayLog[i].chemicalUsed     << "\n";
            }
        }

        file << "\nHARVESTINGBOT LOG\n"
             << "Session,CropName,Status,YieldKg\n";

        const auto& harvestLog = harvester.getLog();
        if (harvestLog.empty()) {
            file << "none\n";
        } else {
            for (size_t i = 0; i < harvestLog.size(); ++i) {
                file << i + 1                        << ","
                     << harvestLog[i].cropName       << ","
                     << (harvestLog[i].status == Plot::Status::PLANT
                            ? "Plant" : "Dead")      << ","
                     << harvestLog[i].yieldKg        << "\n";
            }
        }

    } else {
        // ══════════════════════════════════════════════════════
        //  TXT FORMAT
        // ══════════════════════════════════════════════════════
        file << "========================================\n"
             << "           SeedingBot Log\n"
             << "========================================\n"
             << "  Seeds Planted: " << seeder.getSeedsPlanted() << "\n"
             << "  Seed Log:\n";

        const auto& seedLog = seeder.getSeedLog();
        if (seedLog.empty()) {
            file << "    (none)\n";
        } else {
            for (size_t i = 0; i < seedLog.size(); ++i) {
                file << "    Session " << i + 1
                     << " | " << seedLog[i].getName()
                     << " | Time to Grow  : " << seedLog[i].getTimeToGrow()  << " days"
                     << " | Water/day     : " << seedLog[i].getWaterReq()    << " mL"
                     << " | Humidity      : " << seedLog[i].getMinHum()
                                              << " - " << seedLog[i].getMaxHum()  << " %"
                     << " | Temperature   : " << seedLog[i].getMinTemp()
                                              << " - " << seedLog[i].getMaxTemp() << " C"
                     << " | UV Intensity  : " << seedLog[i].getMinUV()
                                              << " - " << seedLog[i].getMaxUV()   << "\n";
            }
        }

        file << "\n========================================\n"
             << "           SprayerBot Log\n"
             << "========================================\n"
             << "  Sessions Done: " << sprayer.getSpraySessions() << "\n"
             << "  Spray Log:\n";

        const auto& sprayLog = sprayer.getSprayLog();
        if (sprayLog.empty()) {
            file << "    (none)\n";
        } else {
            for (size_t i = 0; i < sprayLog.size(); ++i) {
                file << "    Session " << i + 1
                     << " | " << sprayLog[i].mode
                     << " | " << sprayLog[i].chemicalName
                     << " | " << sprayLog[i].areaSprayed  << " m²"
                     << " | " << sprayLog[i].chemicalUsed << " L\n";
            }
        }

        file << "\n========================================\n"
             << "          HarvestingBot Log\n"
             << "========================================\n"
             << "  Harvests Done  : " << harvester.getHarvests()       << "\n"
             << "  Total Harvested: " << harvester.getTotalHarvested() << " kg\n"
             << "    Plant        : " << harvester.getTotalPlant()     << " kg\n"
             << "    Dead         : " << harvester.getTotalDead()      << " kg\n"
             << "  Harvest Log:\n";

        const auto& harvestLog = harvester.getLog();
        if (harvestLog.empty()) {
            file << "    (none)\n";
        } else {
            file << "    [Plant Harvests]\n";
            bool anyPlant = false;
            for (const auto& r : harvestLog) {
                if (r.status == Plot::Status::PLANT) {
                    file << "      " << r.cropName
                         << " | "   << r.yieldKg << " kg\n";
                    anyPlant = true;
                }
            }
            if (!anyPlant) file << "      (none)\n";

            file << "    [Dead Harvests]\n";
            bool anyDead = false;
            for (const auto& r : harvestLog) {
                if (r.status == Plot::Status::DEAD) {
                    file << "      " << r.cropName
                         << " | "   << r.yieldKg << " kg\n";
                    anyDead = true;
                }
            }
            if (!anyDead) file << "      (none)\n";
        }

        file << "\n========================================\n"
             << "            End of Report\n"
             << "========================================\n";
    }

    file.close();
    cout << "Report written to " << fileName << "\n";
}
