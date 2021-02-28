#ifndef BATTERYSCREENVIEW_HPP
#define BATTERYSCREENVIEW_HPP

#include <gui_generated/batteryscreen_screen/BatteryScreenViewBase.hpp>
#include <gui/batteryscreen_screen/BatteryScreenPresenter.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class BatteryScreenView : public BatteryScreenViewBase
{
public:
    BatteryScreenView();
    virtual ~BatteryScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    struct canData* CANDATA_view = NULL;
    void handleTickEvent();
    void setBrightnessScreen1(int value);
    void updateFPS();
    void setData(struct canData* CANDATA_view);

protected:
    uint16_t bpv; // Battery pack voltage
    uint16_t temp; // Negative terminal temperature
    uint16_t ucr; // Usable capacity remaining
    uint16_t ufc; // Usable full capacity

    bool BPV_increase = true;

    int frameSkippedCounter;
    int frames;
    int fps;

};

#endif // BATTERYSCREENVIEW_HPP
