#include <gui/batteryscreen_screen/BatteryScreenView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

#include "CanDataStruct.hpp"
#include "cmsis_os.h"
extern osMessageQId setBrightnessQId;

//static int16_t counter = 0;

BatteryScreenView::BatteryScreenView()
{
	this->bpv = 0;
	this->temp = 0;
	this->ucr = 0;
	this->ufc = 0;
	this->frameSkippedCounter = 0;
	this->frames = 0;
	this->fps = 0;
}

void BatteryScreenView::setupScreen()
{
    BatteryScreenViewBase::setupScreen();
    fps = 0;
    updateFPS();
}

void BatteryScreenView::tearDownScreen()
{
    BatteryScreenViewBase::tearDownScreen();
}


void BatteryScreenView::handleTickEvent()
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

void BatteryScreenView::setBrightnessScreen1(int value)
{
	osMessagePut(setBrightnessQId, value, 0);
}

void BatteryScreenView::updateFPS()
{
    Unicode::snprintf(fpsValueTestBuffer, FPSVALUETEST_SIZE, "%d", fps);
    fpsValueTest.invalidate();
}


void BatteryScreenView::setData(struct canData* CANDATA_view){

	bpv = CANDATA_view->Model_B_Pack_Voltage; // Battery pack voltage
	temp = CANDATA_view->Model_Neg_Termi_Temp; // Negative terminal temperature
	ucr = CANDATA_view->Model_Usable_Remaining; // Usable Capacity Remaining
	ufc = CANDATA_view->Model_Usable_Full_Pack; // Usable Full Capacity

	CircleProgressBPV.setValue(bpv);
	circleProgressTemp.setValue(temp);
	UsableCapacityBoxProgress.setValue(ucr);
	UsableCapacityFullBoxProgress.setValue(ufc);

	Unicode::snprintf(batterypackvoltage_textboxBuffer, BATTERYPACKVOLTAGE_TEXTBOX_SIZE, "%02d", bpv);
	Unicode::snprintf(Temperature_textboxBuffer, TEMPERATURE_TEXTBOX_SIZE, "%02d", temp);
	Unicode::snprintf(Usable_remaining_textboxBuffer, USABLE_REMAINING_TEXTBOX_SIZE, "%02d", ucr);
	Unicode::snprintf(Usable_full_textboxBuffer, USABLE_FULL_TEXTBOX_SIZE, "%02d", ufc);

	batterypackvoltage_textbox.invalidate();
	Temperature_textbox.invalidate();
	Usable_remaining_textbox.invalidate();
	Usable_full_textbox.invalidate();

}

