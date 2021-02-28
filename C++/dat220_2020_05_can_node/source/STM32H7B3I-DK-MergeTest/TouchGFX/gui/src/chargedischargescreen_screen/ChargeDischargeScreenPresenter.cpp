#include <gui/chargedischargescreen_screen/ChargeDischargeScreenView.hpp>
#include <gui/chargedischargescreen_screen/ChargeDischargeScreenPresenter.hpp>

ChargeDischargeScreenPresenter::ChargeDischargeScreenPresenter(ChargeDischargeScreenView& v)
    : view(v)
{

}

void ChargeDischargeScreenPresenter::activate()
{

}

void ChargeDischargeScreenPresenter::deactivate()
{

}

void ChargeDischargeScreenPresenter::notifyNewCANDataChanged(struct canData* CANDATA_view) {
  view.setData(CANDATA_view);
}
