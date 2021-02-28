#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    // Call this function to notify that NewCANDataChanged.
    // Per default, use an empty implementation so that only those
    // Presenters interested in this specific event need to
    // override this function.
    virtual void notifyNewCANDataChanged(struct canData* CANDATA_view) {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
