#include "button.hpp"

class QuitButton : public Button {
    private:
        sf::RenderWindow& window;
    public:
        QuitButton(std::string identifier, sf::Font& font, std::string buttonText, 
                sf::Vector2f size, sf::Color color, sf::RenderWindow& window);
        ~QuitButton();

        void onClick() override;
};

