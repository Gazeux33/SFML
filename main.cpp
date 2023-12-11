#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

bool caseEstDansPlateau(int i, int j, int matrixSize) {
    return i >= 0 && i < matrixSize && j >= 0 && j < matrixSize;
}

int checkNeightBoor(const Matrix& mat, int row, int column) {
    int number = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Exclure la cellule elle-même
            if (caseEstDansPlateau(row + i, column + j, mat.size()) && mat[row + i][column + j] == 1) {
                number++;
            }
        }
    }
    return number;
}

void displayMatrix(sf::RenderWindow& window, const Matrix& mat, float size) {
    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[i].size(); j++) {
            sf::RectangleShape rectangle(sf::Vector2f(size, size));
            rectangle.setPosition(j * size, i * size);
            rectangle.setFillColor(mat[i][j] == 0 ? sf::Color::Black : sf::Color::Blue);
            window.draw(rectangle);
        }
    }
}

void initializeMatrix(Matrix& mat, std::mt19937& generator, std::uniform_int_distribution<int>& distribution) {
    for (auto& row : mat) {
        std::generate(row.begin(), row.end(), [&]() { return distribution(generator); });
    }
}

void updateMatrix(Matrix& mat, Matrix& temp) {
    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat[i].size(); j++) {
            int voisins = checkNeightBoor(mat, i, j);
            if (mat[i][j] == 1 && (voisins < 2 || voisins > 3)) {
                temp[i][j] = 0;
            } else if (mat[i][j] == 0 && voisins == 3) {
                temp[i][j] = 1;
            } else {
                temp[i][j] = mat[i][j];
            }
        }
    }
    mat.swap(temp); // Échanger les matrices
}

int main() {
    const int matrixSize = 1000;
    float size = 1.0f;

    Matrix mat(matrixSize, std::vector<int>(matrixSize));
    Matrix temp(matrixSize, std::vector<int>(matrixSize));

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, 1);

    initializeMatrix(mat, generator, distribution);
    sf::RenderWindow window(sf::VideoMode(matrixSize*size, matrixSize*size), "GameLife");
    window.setFramerateLimit(100); // Ajustez le FPS selon les besoins

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                initializeMatrix(mat, generator, distribution);
            }
        }

        updateMatrix(mat, temp);

        window.clear();
        displayMatrix(window, mat, size); // Afficher la matrice
        window.display(); // Mettre à jour l'affichage de la fenêtre
    }

    return 0;
}


