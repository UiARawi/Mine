#ifndef POWERSCREENVIEW_HPP
#define POWERSCREENVIEW_HPP

#include <gui_generated/powerscreen_screen/PowerScreenViewBase.hpp>
#include <gui/powerscreen_screen/PowerScreenPresenter.hpp>

class PowerScreenView : public PowerScreenViewBase
{
public:
    PowerScreenView();
    virtual ~PowerScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    struct canData* CANDATA_view = NULL;

   void handleTickEvent();

   void updateFPS();

   void setData(struct canData* CANDATA_view);


protected:

   uint16_t pp; // Pedal Position
   uint16_t dp; // Drive Power
   int16_t mp; // Mech power
   uint16_t rt; // Rear torque
   int32_t pc; // Pack Current

   int frameSkippedCounter;
   int frames;
   int fps;
};

#endif // POWERSCREENVIEW_HPP
