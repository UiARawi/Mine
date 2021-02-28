#ifndef HISTORICALSTATSPRESENTER_HPP
#define HISTORICALSTATSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HistoricalStatsView;

class HistoricalStatsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HistoricalStatsPresenter(HistoricalStatsView& v);

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

    virtual ~HistoricalStatsPresenter() {};

    void notifyNewCANDataChanged(struct canData* CANDATA_view);

private:
    HistoricalStatsPresenter();

    HistoricalStatsView& view;
};

#endif // HISTORICALSTATSPRESENTER_HPP
