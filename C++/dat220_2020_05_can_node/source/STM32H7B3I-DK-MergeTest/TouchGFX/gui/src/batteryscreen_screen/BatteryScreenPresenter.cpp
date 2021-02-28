#include <gui/batteryscreen_screen/BatteryScreenView.hpp>
#include <gui/batteryscreen_screen/BatteryScreenPresenter.hpp>

#include "CanDataStruct.hpp"

BatteryScreenPresenter::BatteryScreenPresenter(BatteryScreenView& v)
    : view(v)
{

}

void BatteryScreenPresenter::activate(){}

void BatteryScreenPresenter::deactivate(){}

//struct canData* BatteryScreenPresenter::getData()
//{
//	return model->getData();
//}


void BatteryScreenPresenter::notifyNewCANDataChanged(struct canData* CANDATA_view) {
  view.setData(CANDATA_view);
}
