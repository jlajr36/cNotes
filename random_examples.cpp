#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <stdexcept>

class Random {
public:
    Random() = delete;
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static float getFloat(float min, float max) {
        if (min > max) std::swap(min, max);
        std::uniform_real_distribution<float> dist(min, max);
        return dist(getGenerator());
    }

    static int getInt(int min, int max) {
        if (min > max) std::swap(min, max);
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getGenerator());
    }

    static bool getBool(double probability = 0.5) {
        std::bernoulli_distribution dist(std::clamp(probability, 0.0, 1.0));
        return dist(getGenerator());
    }

    template <typename Container>
    static void shuffle(Container& container) {
        std::shuffle(std::begin(container), std::end(container), getGenerator());
    }

    template <typename Container>
    static const typename Container::value_type& getElement(const Container& container) {
        if (container.empty()) {
            throw std::runtime_error("Random::getElement() called on empty container");
        }

        auto it = std::begin(container);
        std::advance(it, getInt(0, static_cast<int>(container.size()) - 1));
        return *it;
    }

    static void seed(uint32_t value) {
        getGenerator().seed(value);
    }

private:
    static std::mt19937& getGenerator() {
        thread_local static std::mt19937 gen(std::random_device{}());
        return gen;
    }
};

int main() {
    float f = Random::getFloat(0.0f, 1.0f);
    int i   = Random::getInt(1, 100);
    bool b  = Random::getBool(0.75);

    std::cout << "Float: " << f << "\nInt: " << i << "\nBool: " << std::boolalpha << b << "\n\n";

    std::vector<std::string> items = {"Health", "Mana", "Gold", "Key"};

    std::cout << "Random Pick: " << Random::getElement(items) << "\n";

    Random::shuffle(items);
    std::cout << "Shuffled: ";
    for (const auto& item : items) std::cout << item << " ";
    std::cout << "\n";
}
