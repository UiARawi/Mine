#include <gui/historicalstats_screen/HistoricalStatsView.hpp>

HistoricalStatsView::HistoricalStatsView()
{
	this-> bodometer = 0;  // Battery Odometer
	this -> nfp = 0;  // Nominal Full Pack Remaining
	this -> ner = 0; // Nominal Energy Remaining
	this -> tkc = 0; // Total KWH Charged
	this -> tkd = 0; // Total KWH Discharged
	this -> frameSkippedCounter = 0;
	this -> frames = 0;
}

void HistoricalStatsView::setupScreen()
{
    HistoricalStatsViewBase::setupScreen();

    fps = 0;
    updateFPS();
}

void HistoricalStatsView::tearDownScreen()
{
    HistoricalStatsViewBase::tearDownScreen();
}

void HistoricalStatsView::handleTickEvent()
{

	if (HAL::getInstance()->getLCDRefreshCount() > 1)
	{
		frameSkippedCounter++;
	}
	else
	{
		frames++;
	}

	if (frames + frameSkippedCounter >= 60)
	{
		fps = frames;
		updateFPS();
		frameSkippedCounter = 0;
		frames = 0;
	}

}

void HistoricalStatsView::updateFPS()
{
    Unicode::snprintf(FPSScreen2Buffer, FPSSCREEN2_SIZE, "%d", fps);
    FPSScreen2.invalidate();
}


void HistoricalStatsView::setData(struct canData* CANDATA_view)
{
	bodometer = CANDATA_view->Model_Battery_Odometer; // Battery Odometer
	nfp = CANDATA_view->Model_Nominal_Full_Pack; // Nominal Full Pack Remaining
	ner = CANDATA_view->Model_Nom_Energy_Remaining; // Nominal Energy Remaining
	tkc = CANDATA_view->Model_KWH_Charge_Total; // Total KWH Charged
	tkd = CANDATA_view->Model_KWH_Discharge_Total; // Total KWH Discharged

	//if((bodometer != 0) && (nfp != 0) && (ner != 0) && (tkc != 0) && (tkd != 0)){
	Unicode::snprintf(Battery_odometer_textareaBuffer, BATTERY_ODOMETER_TEXTAREA_SIZE, "%02d", bodometer);
	Unicode::snprintf(nominal_full_pack_textareaBuffer, NOMINAL_FULL_PACK_TEXTAREA_SIZE, "%02d", nfp);
	Unicode::snprintf(Nominal_energy_remaining_textareaBuffer, NOMINAL_ENERGY_REMAINING_TEXTAREA_SIZE, "%02d", ner);
	Unicode::snprintf(KWH_charge_total_areaboxBuffer, KWH_CHARGE_TOTAL_AREABOX_SIZE, "%02d", tkc);
	Unicode::snprintf(Total_kwh_discharge_textareaBuffer, TOTAL_KWH_DISCHARGE_TEXTAREA_SIZE, "%02d", tkd);

	Battery_odometer_textarea.invalidate();
	nominal_full_pack_textarea.invalidate();
	Nominal_energy_remaining_textarea.invalidate();
	KWH_charge_total_areabox.invalidate();
	Total_kwh_discharge_textarea.invalidate();
	//}
}

