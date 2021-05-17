#include"UI/Hero_UIElement.hpp"

namespace Hero
{

void UIElement::SetRelativePosition(const int2& relativePosition)
{
    int2 diffrence = relativePosition - this->_relativePosition;
    this->_relativePosition = relativePosition;
    this->_absolutPosition += relativePosition;
}

void UIElement::SetAbsolutePosition(const int2& absolutePosition)
{
    this->_absolutPosition = absolutePosition + this->_relativePosition;
}

}