#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/hal/types.hpp>

#include "CanDataStruct.hpp"

class ModelListener;



class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    struct canData* CanData_model = nullptr;

    void handleTickEvent();


//struct canData* getData(); // modell returnerer en struct


protected:
    ModelListener* modelListener;
    int16_t value;

};

#endif // MODEL_HPP
