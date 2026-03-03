#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// ============================================================
//  Base Class: Robot
// ============================================================
class Robot {
protected:
    std::string id;
    std::string name;
    double batteryLevel;   // 0.0 – 100.0 %
    bool   isOperational;

public:
    Robot(const std::string& id, const std::string& name)
        : id(id), name(name), batteryLevel(100.0), isOperational(true) {}

    virtual ~Robot() = default;

    // Pure virtual – every subclass must implement its primary task
    virtual void performTask() = 0;

    // Shared utilities
    virtual void recharge()   { batteryLevel = 100.0; std::cout << name << " fully recharged.\n"; }
    virtual void shutdown()   { isOperational = false; std::cout << name << " shut down.\n"; }
    virtual void statusReport() const {
        std::cout << "=== " << name << " [" << id << "] ===\n"
                  << "  Battery    : " << batteryLevel << "%\n"
                  << "  Operational: " << (isOperational ? "Yes" : "No") << "\n";
    }

    bool   getIsOperational() const { return isOperational; }
    double getBatteryLevel()  const { return batteryLevel;  }
    const  std::string& getName() const { return name; }

protected:
    void consumeBattery(double amount) {
        batteryLevel -= amount;
        if (batteryLevel <= 0.0) {
            batteryLevel   = 0.0;
            isOperational  = false;
            std::cout << name << " battery depleted – shutting down.\n";
        }
    }
};


// ============================================================
//  Subclass 1: SeedingBot
//  Plants seeds according to crop type and row spacing.
// ============================================================
class SeedingBot : public Robot {
public:
    enum class SeedPattern { ROW, GRID, BROADCAST };

private:
    std::string  cropType;
    double       rowSpacingCm;    // spacing between rows (cm)
    double       seedDepthCm;     // planting depth (cm)
    SeedPattern  pattern;
    int          seedsPlanted;

    static std::string patternToString(SeedPattern p) {
        switch (p) {
            case SeedPattern::ROW:       return "Row";
            case SeedPattern::GRID:      return "Grid";
            case SeedPattern::BROADCAST: return "Broadcast";
        }
        return "Unknown";
    }

public:
    SeedingBot(const std::string& id,
               const std::string& cropType,
               double rowSpacingCm  = 30.0,
               double seedDepthCm   =  5.0,
               SeedPattern pattern  = SeedPattern::ROW)
        : Robot(id, "SeedingBot-" + id),
          cropType(cropType),
          rowSpacingCm(rowSpacingCm),
          seedDepthCm(seedDepthCm),
          pattern(pattern),
          seedsPlanted(0) {}

    // Configure before deployment
    void setCropType(const std::string& crop)  { cropType      = crop; }
    void setRowSpacing(double spacing)          { rowSpacingCm  = spacing; }
    void setSeedDepth(double depth)             { seedDepthCm   = depth; }
    void setSeedPattern(SeedPattern p)          { pattern       = p; }

    // Plant a given number of seeds in one run
    void plantSeeds(int count) {
        if (!isOperational) { std::cout << name << " is not operational.\n"; return; }
        std::cout << name << ": Planting " << count << " " << cropType
                  << " seeds [" << patternToString(pattern) << " pattern, "
                  << rowSpacingCm << " cm spacing, " << seedDepthCm << " cm depth]...\n";
        seedsPlanted += count;
        consumeBattery(count * 0.05);   // 0.05% per seed
        std::cout << "  Done. Total seeds planted: " << seedsPlanted << "\n";
    }

    // Required override – plants a standard 100-seed pass
    void performTask() override {
        plantSeeds(100);
    }

    void statusReport() const override {
        Robot::statusReport();
        std::cout << "  Crop Type  : " << cropType         << "\n"
                  << "  Row Spacing: " << rowSpacingCm     << " cm\n"
                  << "  Seed Depth : " << seedDepthCm      << " cm\n"
                  << "  Pattern    : " << patternToString(pattern) << "\n"
                  << "  Seeds Planted: " << seedsPlanted   << "\n";
    }

    int getSeedsPlanted() const { return seedsPlanted; }
};


// ============================================================
//  Subclass 2: SprayerBot
//  Applies fertilizer or pesticide based on crop needs /
//  a fixed schedule.
// ============================================================
class SprayerBot : public Robot {
public:
    enum class SprayMode { FERTILIZER, PESTICIDE, HERBICIDE, CUSTOM };

private:
    SprayMode   mode;
    double      tankCapacityL;     // total tank (litres)
    double      tankLevelL;        // current level
    double      sprayRateL_per_m2; // litres per square metre
    std::string chemicalName;
    int         spraySessionsDone;

    // Simple schedule: days on which spraying is due (1 = Monday … 7 = Sunday)
    std::vector<int> scheduleDays;

    static std::string modeToString(SprayMode m) {
        switch (m) {
            case SprayMode::FERTILIZER: return "Fertilizer";
            case SprayMode::PESTICIDE:  return "Pesticide";
            case SprayMode::HERBICIDE:  return "Herbicide";
            case SprayMode::CUSTOM:     return "Custom";
        }
        return "Unknown";
    }

public:
    SprayerBot(const std::string& id,
               SprayMode   mode           = SprayMode::FERTILIZER,
               double      tankCapacityL  = 50.0,
               double      sprayRate      =  0.3,
               std::string chemical       = "NPK-20-20-20")
        : Robot(id, "SprayerBot-" + id),
          mode(mode),
          tankCapacityL(tankCapacityL),
          tankLevelL(tankCapacityL),
          sprayRateL_per_m2(sprayRate),
          chemicalName(std::move(chemical)),
          spraySessionsDone(0) {}

    void setMode(SprayMode m)                   { mode = m; }
    void setChemical(const std::string& chem)   { chemicalName = chem; }
    void setSchedule(const std::vector<int>& days) { scheduleDays = days; }
    void refillTank()  { tankLevelL = tankCapacityL;
                         std::cout << name << " tank refilled to " << tankCapacityL << " L.\n"; }

    // Spray an area (m²); returns false if tank or battery insufficient
    bool sprayArea(double areaSqM) {
        if (!isOperational) { std::cout << name << " is not operational.\n"; return false; }
        double required = areaSqM * sprayRateL_per_m2;
        if (required > tankLevelL) {
            std::cout << name << ": Insufficient chemical – need " << required
                      << " L, have " << tankLevelL << " L. Refill required.\n";
            return false;
        }
        std::cout << name << ": Spraying " << areaSqM << " m² with "
                  << chemicalName << " [" << modeToString(mode) << "]...\n";
        tankLevelL -= required;
        consumeBattery(areaSqM * 0.02);
        ++spraySessionsDone;
        std::cout << "  Used " << required << " L | Tank remaining: " << tankLevelL << " L\n";
        return true;
    }

    // Check whether today (1-7) is a scheduled spray day
    bool isScheduledToday(int dayOfWeek) const {
        for (int d : scheduleDays)
            if (d == dayOfWeek) return true;
        return false;
    }

    // Required override – sprays a default 200 m² pass
    void performTask() override {
        sprayArea(200.0);
    }

    void statusReport() const override {
        Robot::statusReport();
        std::cout << "  Mode       : " << modeToString(mode)  << "\n"
                  << "  Chemical   : " << chemicalName         << "\n"
                  << "  Tank       : " << tankLevelL << " / " << tankCapacityL << " L\n"
                  << "  Spray Rate : " << sprayRateL_per_m2   << " L/m²\n"
                  << "  Sessions   : " << spraySessionsDone    << "\n";
    }

    double getTankLevel() const { return tankLevelL; }
};


// ============================================================
//  Subclass 3: HarvestingBot
//  Harvests crops after assessing ripeness.
// ============================================================
class HarvestingBot : public Robot {
public:
    // Ripeness scale 0–100; threshold above which the bot harvests
    static constexpr double DEFAULT_RIPENESS_THRESHOLD = 75.0;

private:
    std::string cropType;
    double      ripenessThreshold;
    double      binCapacityKg;
    double      binCurrentKg;
    int         harvests;

    struct HarvestRecord {
        std::string cropType;
        double      ripenessScore;
        double      yieldKg;
    };
    std::vector<HarvestRecord> log;

    // Simulate a ripeness sensor reading (in production replace with real sensor)
    double senseRipeness(const std::string& zone) const {
        // Deterministic pseudo-value based on zone string length for demo
        return 60.0 + (zone.size() % 4) * 10.0;
    }

public:
    HarvestingBot(const std::string& id,
                  const std::string& cropType,
                  double binCapacityKg     = 200.0,
                  double ripenessThreshold = DEFAULT_RIPENESS_THRESHOLD)
        : Robot(id, "HarvestingBot-" + id),
          cropType(cropType),
          ripenessThreshold(ripenessThreshold),
          binCapacityKg(binCapacityKg),
          binCurrentKg(0.0),
          harvests(0) {}

    void setCropType(const std::string& crop)  { cropType = crop; }
    void setRipenessThreshold(double t)        { ripenessThreshold = t; }

    // Evaluate a named zone and harvest if ripe
    bool evaluateAndHarvest(const std::string& zone, double expectedYieldKg) {
        if (!isOperational) { std::cout << name << " is not operational.\n"; return false; }

        double ripeness = senseRipeness(zone);
        std::cout << name << ": Scanning zone [" << zone << "] – ripeness score: "
                  << ripeness << "/100 (threshold " << ripenessThreshold << ")\n";

        if (ripeness < ripenessThreshold) {
            std::cout << "  Crop not yet ripe. Skipping.\n";
            return false;
        }

        if (binCurrentKg + expectedYieldKg > binCapacityKg) {
            std::cout << "  Bin full! Empty bin before continuing.\n";
            return false;
        }

        std::cout << "  Harvesting " << expectedYieldKg << " kg of " << cropType << "...\n";
        binCurrentKg += expectedYieldKg;
        consumeBattery(expectedYieldKg * 0.08);
        log.push_back({cropType, ripeness, expectedYieldKg});
        ++harvests;
        std::cout << "  Bin: " << binCurrentKg << " / " << binCapacityKg << " kg\n";
        return true;
    }

    // Unload collected harvest
    double emptyBin() {
        double collected = binCurrentKg;
        binCurrentKg = 0.0;
        std::cout << name << ": Bin emptied – " << collected << " kg transferred.\n";
        return collected;
    }

    // Required override – evaluates a default zone
    void performTask() override {
        evaluateAndHarvest("Field-A1", 50.0);
    }

    void statusReport() const override {
        Robot::statusReport();
        std::cout << "  Crop Type  : " << cropType                          << "\n"
                  << "  Ripeness ≥ : " << ripenessThreshold                 << "/100\n"
                  << "  Bin        : " << binCurrentKg << " / " << binCapacityKg << " kg\n"
                  << "  Harvests   : " << harvests                           << "\n";
        if (!log.empty()) {
            std::cout << "  Harvest Log:\n";
            for (const auto& r : log)
                std::cout << "    " << r.cropType << " | ripeness " << r.ripenessScore
                          << " | " << r.yieldKg << " kg\n";
        }
    }

    double getBinLevel()  const { return binCurrentKg; }
    int    getHarvests()  const { return harvests; }
};


// ============================================================
//  Demo main()
// ============================================================
int main() {
    std::cout << "========================================\n"
              << "   Agricultural Robot Fleet – Demo\n"
              << "========================================\n\n";

    // --- SeedingBot ---
    SeedingBot seeder("S01", "Corn", 45.0, 6.0, SeedingBot::SeedPattern::ROW);
    seeder.statusReport();
    seeder.performTask();           // standard 100-seed pass
    seeder.plantSeeds(250);         // custom pass
    std::cout << "\n";

    // --- SprayerBot ---
    SprayerBot sprayer("SP01", SprayerBot::SprayMode::FERTILIZER, 100.0, 0.25, "Urea-46%");
    sprayer.setSchedule({2, 5});    // spray on Tuesday & Friday
    sprayer.statusReport();
    sprayer.performTask();          // 200 m² pass
    sprayer.sprayArea(150.0);
    std::cout << "  Scheduled today (day 2)? "
              << (sprayer.isScheduledToday(2) ? "Yes" : "No") << "\n\n";

    // --- HarvestingBot ---
    HarvestingBot harvester("H01", "Wheat", 300.0, 70.0);
    harvester.statusReport();
    harvester.evaluateAndHarvest("Field-B3", 80.0);
    harvester.evaluateAndHarvest("Field-C1", 60.0);
    harvester.evaluateAndHarvest("Field-A2", 90.0);
    harvester.emptyBin();
    std::cout << "\n";

    // --- Polymorphic dispatch ---
    std::cout << "--- Polymorphic task dispatch ---\n";
    std::vector<Robot*> fleet = { &seeder, &sprayer, &harvester };
    for (Robot* r : fleet) {
        r->performTask();
    }

    std::cout << "\n=== Final Status Reports ===\n\n";
    seeder.statusReport();   std::cout << "\n";
    sprayer.statusReport();  std::cout << "\n";
    harvester.statusReport();

    return 0;
}
