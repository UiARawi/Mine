#include <gui/historicalstats_screen/HistoricalStatsView.hpp>
#include <gui/historicalstats_screen/HistoricalStatsPresenter.hpp>

HistoricalStatsPresenter::HistoricalStatsPresenter(HistoricalStatsView& v)
    : view(v)
{

}

void HistoricalStatsPresenter::activate()
{

}

void HistoricalStatsPresenter::deactivate()
{

}

void HistoricalStatsPresenter::notifyNewCANDataChanged(struct canData* CANDATA_view) {
  view.setData(CANDATA_view);
}
