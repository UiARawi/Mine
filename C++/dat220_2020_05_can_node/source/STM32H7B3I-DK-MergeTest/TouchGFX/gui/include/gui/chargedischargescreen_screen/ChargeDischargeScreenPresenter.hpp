#ifndef CHARGEDISCHARGESCREENPRESENTER_HPP
#define CHARGEDISCHARGESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ChargeDischargeScreenView;

class ChargeDischargeScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ChargeDischargeScreenPresenter(ChargeDischargeScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ChargeDischargeScreenPresenter() {};

    void notifyNewCANDataChanged(struct canData* CANDATA_view);

private:
    ChargeDischargeScreenPresenter();

    ChargeDischargeScreenView& view;
};

#endif // CHARGEDISCHARGESCREENPRESENTER_HPP
