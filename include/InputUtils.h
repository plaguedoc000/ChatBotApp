#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

// Читает int из std::getline, проверяет диапазон [minVal..maxVal].
// Бросает runtime_error при EOF.
inline int safeIntInput(const std::string& prompt, int minVal, int maxVal) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line))
            throw std::runtime_error("Неожиданный конец ввода");

        try {
            int x = std::stoi(line);
            if (x < minVal || x > maxVal) {
                std::cout << "Число должно быть в диапазоне [" 
                          << minVal << ".." << maxVal << "].\n";
                continue;
            }
            return x;
        } catch (const std::invalid_argument&) {
            std::cout << "Неверный формат числа, попробуйте ещё раз.\n";
        } catch (const std::out_of_range&) {
            std::cout << "Число слишком большое, попробуйте ещё раз.\n";
        }
    }
}

#endif // INPUT_UTILS_H
