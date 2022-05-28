#include <SFML/Graphics.hpp>
#include <vector>

void fill_vector(std::vector<sf::RectangleShape>& shapes, const sf::Vector2u& wsize, int number_of_items)
{
    float width = wsize.x / number_of_items;
    sf::Vector2f pos = { width, (float)wsize.y };

    for (size_t i = 0; i < number_of_items; i++)
    {    
        shapes.push_back(sf::RectangleShape({ width, (float)(std::rand() % wsize.y) }));
        shapes.at(i).setFillColor(sf::Color(255, 0, 0));
        shapes.at(i).setPosition(pos);
        shapes.at(i).setRotation(sf::degrees(180));
        pos.x += width;
    }
}

void swap(sf::RectangleShape& shape1, sf::RectangleShape& shape2)
{
    sf::Vector2f templ = shape1.getSize();
    shape1.setSize(shape2.getSize());
    shape2.setSize(templ);
}

bool bubbesort(std::vector<sf::RectangleShape>& shapes)
{
    static size_t i = 0;
    static size_t j = 0;

    if (i < shapes.size() - 1)
    {
        if (j < shapes.size() - i - 1)
        {
            if (shapes.at(j).getSize().y > shapes.at(j + 1).getSize().y)
                swap(shapes.at(j), shapes.at(j + 1));
            j++;
        }

        else
        {
            i++;
            j = 0;
        }
    }

    else
        return true;
    
    return false;
}

int main()
{
    std::srand(std::time(0));
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Bubble Sort Visualizer");
    //window.setFramerateLimit(60);

    std::vector<sf::RectangleShape> shapes;
    size_t i = 0;
    size_t j = 0;
    bool start = false;

    fill_vector(shapes, window.getSize(), 50);

    while (window.isOpen())
    {   
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        if (!start)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                start = true;

        if (start)
            bubbesort(shapes) ? start = !start : 0;

        window.clear(sf::Color::Black);

        for (const auto& item : shapes)
            window.draw(item);

        window.display();
    }

    return 0;
}