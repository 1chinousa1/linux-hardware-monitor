#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

// Function to read CPU thermal zones directly from the Linux filesystem
double get_cpu_temperature() {
    std::string line;
    std::ifstream tempFile("/sys/class/thermal/thermal_zone0/temp");
    
    if (tempFile.is_open()) {
        std::getline(tempFile, line);
        tempFile.close();
        // Convert millidegrees Celsius string to double and divide by 1000
        return std::stod(line) / 1000.0;
    }
    return -1.0; 
}

// Function to parse the virtual memory file /proc/meminfo
void print_memory_usage() {
    std::string line;
    unsigned long memTotal = 0;
    unsigned long memFree = 0;

    std::ifstream memFile("/proc/meminfo");
    if (memFile.is_open()) {
        while (std::getline(memFile, line)) {
            if (line.compare(0, 8, "MemTotal") == 0) {
                size_t first_digit = line.find_first_of("0123456789");
                size_t last_digit = line.find_last_of("0123456789");
                memTotal = std::stoul(line.substr(first_digit, last_digit - first_digit + 1));
            }
            if (line.compare(0, 7, "MemFree") == 0) {
                size_t first_digit = line.find_first_of("0123456789");
                size_t last_digit = line.find_last_of("0123456789");
                memFree = std::stoul(line.substr(first_digit, last_digit - first_digit + 1));
                break; 
            }
        }
        memFile.close();

        unsigned long memUsed = memTotal - memFree;
        std::cout << "RAM Allocation: " << memUsed / 1024 << " MB / " << memTotal / 1024 << " MB" << std::endl;
    } else {
        std::cout << "Error: Unable to access system memory metrics." << std::endl;
    }
}

int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "   AI Infrastructure Hardware Performance Monitor   " << std::endl;
    std::cout << "==================================================" << std::endl;
    
    while (true) {
        double current_temp = get_cpu_temperature();
        std::cout << "\n[System Status Update]" << std::endl;
        
        if (current_temp >= 0) {
            std::cout << "CPU Core Temperature: " << current_temp << " °C" << std::endl;
            if (current_temp > 75.0) {
                std::cout << "⚠️  CRITICAL ALARM: High thermal load!" << std::endl;
            }
        } else {
            std::cout << "CPU Temperature: [Data Unreadable]" << std::endl;
        }
        
        print_memory_usage();
        std::cout << "--------------------------------------------------" << std::endl;
        
        // Pause execution for 3 seconds to keep resource footprint near zero
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return 0;
}