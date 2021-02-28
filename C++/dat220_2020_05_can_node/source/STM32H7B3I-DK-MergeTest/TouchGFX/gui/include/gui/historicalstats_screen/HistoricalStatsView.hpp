#ifndef HISTORICALSTATSVIEW_HPP
#define HISTORICALSTATSVIEW_HPP

#include <gui_generated/historicalstats_screen/HistoricalStatsViewBase.hpp>
#include <gui/historicalstats_screen/HistoricalStatsPresenter.hpp>

class HistoricalStatsView : public HistoricalStatsViewBase
{
public:
    HistoricalStatsView();
    virtual ~HistoricalStatsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    struct canData* CANDATA_view = NULL;

    void handleTickEvent();

    void updateFPS();

    void setData(struct canData* CANDATA_view);


protected:

    uint32_t bodometer; // Battery Odometer
    uint16_t nfp; // Nominal Full Pack Remaining
    uint16_t ner; // Nominal Energy Remaining
    uint16_t tkc; // Total KWH Charged
    uint16_t tkd; // Total KWH Discharged

    int frameSkippedCounter;
    int frames;
    int fps;

};

#endif // HISTORICALSTATSVIEW_HPP
