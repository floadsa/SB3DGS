#pragma once

#include <functional>
#include "image.h"
#include "text.h"

class Button
{
protected:
    std::function<void()> function;
    Image body;
    Image ActiveBody;
    Text text;

    float nx, ny, nwidth, nheight, size;
public:
    Button(float _nx, float _ny, float _nwidth, float _nheight);

    void Check(float nMosPosX, float nMosPosY, const glm::mat4& projview);
    void Update();
    void Call();

    void SetText(const std::string& str);

    void SetCall(std::function<void()> f);
    void SetText(Text _text);
    void SetBody(Image _body);
    void SetActiveBody(Image _activeBody);

    void Render(float mosPosX, float mosPosY, const glm::mat4& projview);
};
