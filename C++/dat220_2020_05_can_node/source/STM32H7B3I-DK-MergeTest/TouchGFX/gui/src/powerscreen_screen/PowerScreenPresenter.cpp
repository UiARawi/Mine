#include <gui/powerscreen_screen/PowerScreenView.hpp>
#include <gui/powerscreen_screen/PowerScreenPresenter.hpp>

PowerScreenPresenter::PowerScreenPresenter(PowerScreenView& v)
    : view(v)
{

}

void PowerScreenPresenter::activate()
{

}

void PowerScreenPresenter::deactivate()
{

}

void PowerScreenPresenter::notifyNewCANDataChanged(struct canData* CANDATA_view) {
  view.setData(CANDATA_view);
}
