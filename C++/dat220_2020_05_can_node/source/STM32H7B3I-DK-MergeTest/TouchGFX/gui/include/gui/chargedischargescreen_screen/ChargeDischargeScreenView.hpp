#ifndef CHARGEDISCHARGESCREENVIEW_HPP
#define CHARGEDISCHARGESCREENVIEW_HPP

#include <gui_generated/chargedischargescreen_screen/ChargeDischargeScreenViewBase.hpp>
#include <gui/chargedischargescreen_screen/ChargeDischargeScreenPresenter.hpp>

class ChargeDischargeScreenView : public ChargeDischargeScreenViewBase
{
public:
    ChargeDischargeScreenView();
    virtual ~ChargeDischargeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    struct canData* CANDATA_view = NULL;

    void handleTickEvent();

    void updateFPS();

    void setData(struct canData* CANDATA_view);

protected:
    uint16_t rpm; // Regen Power Max
    uint16_t sc; // Stator current
    uint16_t dissipation; // Dissipation
    uint32_t bmc; // BMS Max Charge
    uint32_t bmd; // BMS Max Discharge

    int frameSkippedCounter;
	int frames;
	int fps;

};

#endif // CHARGEDISCHARGESCREENVIEW_HPP
