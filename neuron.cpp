/**
 * This code simulates a single Artificial Neuron, the fundamental building block
 * of a neural network.
 * * How it works:
 * 1. It takes a list of inputs and assigns each one a "weight" (importance).
 * 2. It calculates a weighted sum of those inputs and adds a "bias" (a baseline offset).
 * 3. It passes that final sum through a filter called an "Activation Function" (ReLU).
 * - In this case, the ReLU filter acts like a dimmer switch: if the result is
 * positive, it passes through; if it's negative, it gets turned into a zero.
 * * The main function demonstrates this by feeding three specific data points into
 * the neuron and printing the final decision/output.
 */

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <functional>

// Rectified Linear Unit: Returns x if x > 0, otherwise returns 0
double ReLU(double x) {
    return std::max(0.0, x);
}

class Neuron {
private:
    std::vector<double> weights; // Internal coefficients for each input
    double bias;                 // Offset value added to the weighted sum

public:
    // Constructor to initialize the neuron with specific weights and a bias
    Neuron(const std::vector<double>& initialWeights, double initialBias)
        : weights(initialWeights), bias(initialBias) {}

    // Processes inputs through the neuron and applies an activation function
    double forward(const std::vector<double>& inputs,
                   std::function<double(double)> activationFunc) const {

        // Safety check: Every input must have a corresponding weight
        if (inputs.size() != weights.size()) {
            throw std::invalid_argument("Inputs size must match weights size.");
        }

        double weightedSum = 0.0;

        // Calculate the Dot Product: (x1 * w1) + (x2 * w2) ...
        for (size_t i = 0; i < inputs.size(); ++i) {
            weightedSum += inputs[i] * weights[i];
        }

        // Add the bias to the sum
        weightedSum += bias;

        // Pass the final result through the activation function (e.g., ReLU)
        return activationFunc(weightedSum);
    }
};

int main() {
    // Define initial parameters for the neuron
    std::vector<double> weights = {0.5, -1.2, 0.3};
    double bias = 0.7;

    // Instantiate the neuron
    Neuron neuron(weights, bias);

    // Provide sample input data
    std::vector<double> inputs = {1.0, 0.5, -1.0};

    // Execute the forward pass and print result
    double output = neuron.forward(inputs, ReLU);
    std::cout << "Output with ReLU: " << output << '\n';
    // Output with ReLU: 0.3

    std::cout << "\n--- TEST 1 ---\n";
    std::cout << Neuron({0.5, 0.5, 0.5}, 0).forward({1,1,1}, ReLU)
              << " (expected 1.5)\n";

    std::cout << "\n--- TEST 2 ---\n";
    std::cout << Neuron({-1,-1,-1}, 0).forward({1,1,1}, ReLU)
              << " (expected 0)\n";

    std::cout << "\n--- TEST 3 ---\n";
    std::cout << Neuron({0.5,-1.2,0.3}, 0.7).forward({1.0,0.5,-1.0}, ReLU)
              << " (expected 0.3)\n";

    std::cout << "\n--- TEST 4 ---\n";
    std::cout << Neuron({1,2,3}, 0.5).forward({0,0,0}, ReLU)
              << " (expected 0.5)\n";

    std::cout << "\n--- TEST 5 ---\n";
    std::cout << Neuron({1,-1}, 0).forward({2,3}, ReLU)
              << " (expected 0)\n";

    std::cout << "\n--- TEST 6 ---\n";
    std::cout << Neuron({2,3}, 5).forward({10,10}, ReLU)
              << " (expected 55)\n";

    std::cout << "\n--- TEST 7 ---\n";
    std::cout << Neuron({1,1}, 0).forward({5,-5}, ReLU)
              << " (expected 0)\n";

    std::cout << "\n--- TEST 8 ---\n";
    std::cout << Neuron({0.5,0.5,0.5}, 0).forward({0.1,0.2,0.3}, ReLU)
              << " (expected 0.3)\n";

    std::cout << "\n--- TEST 9 ---\n";
    std::cout << Neuron({1,1,1}, -10).forward({2,2,2}, ReLU)
              << " (expected 0)\n";

    std::cout << "\n--- TEST 10 ---\n";
    std::cout << Neuron({0.2,-0.5,1.0}, 1).forward({3,1,2}, ReLU)
              << " (expected 3.1)\n";

    return 0;
}
