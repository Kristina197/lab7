#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    float x, y;
    Point(float x = 0, float y = 0) : x(x), y(y) {}
};

// функция для кривой Коха
void invertedKochCurve(Point p1, Point p2, int depth, std::vector<Point>& points) {
    if (depth == 0) {
        points.push_back(p1);
        return;
    }

    // Вычисляем промежуточные точки
    Point delta = Point((p2.x - p1.x) / 3, (p2.y - p1.y) / 3);
    Point pA = Point(p1.x + delta.x, p1.y + delta.y);
    Point pC = Point(p2.x - delta.x, p2.y - delta.y);
    
    // Вычисляем вершину треугольника 
    float angle = -M_PI / 3; // -60 градусов
    Point pB = Point(
        pA.x + delta.x * cos(angle) - delta.y * sin(angle),
        pA.y + delta.x * sin(angle) + delta.y * cos(angle)
    );

    // Рекурсивное построение кривой
    invertedKochCurve(p1, pA, depth - 1, points);
    invertedKochCurve(pA, pB, depth - 1, points);
    invertedKochCurve(pB, pC, depth - 1, points);
    invertedKochCurve(pC, p2, depth - 1, points);
}

int main() {
    const int width = 800;
    const int height = 600;
    const int max_depth = 4;

    sf::RenderWindow window(sf::VideoMode(width, height), "Кривая Коха");
    window.setFramerateLimit(60);

    std::vector<Point> points;
    Point start(100, height / 2);
    Point end(width - 100, height / 2);

    // Генерирация (.) кривой Коха
    invertedKochCurve(start, end, max_depth, points);
    points.push_back(end);

    sf::VertexArray lines(sf::LineStrip, points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        lines[i].position = sf::Vector2f(points[i].x, points[i].y);
        lines[i].color = sf::Color::Black;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(lines);
        window.display();
    }

    return 0;
}