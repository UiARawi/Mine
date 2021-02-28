#include <gui/chargedischargescreen_screen/ChargeDischargeScreenView.hpp>

ChargeDischargeScreenView::ChargeDischargeScreenView()
{
	this -> rpm = 0; // Regen Power Max
	this -> sc = 0; // Stator current
	this -> dissipation = 0; // Dissipation
	this -> bmc = 0; // BMS Max Charge
	this -> bmd = 0; // BMS Max Discharge
	this -> frameSkippedCounter = 0;
	this -> frames = 0;
}

void ChargeDischargeScreenView::setupScreen()
{
    ChargeDischargeScreenViewBase::setupScreen();

    fps = 0;
    updateFPS();
}

void ChargeDischargeScreenView::tearDownScreen()
{
    ChargeDischargeScreenViewBase::tearDownScreen();
}

void ChargeDischargeScreenView::handleTickEvent()
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

void ChargeDischargeScreenView::updateFPS()
{
    Unicode::snprintf(fpsScreen3Buffer, FPSSCREEN3_SIZE, "%d", fps);
    fpsScreen3.invalidate();
}

void ChargeDischargeScreenView::setData(struct canData* CANDATA_view)
{
	rpm = CANDATA_view->Model_Regen_Power_Max; // Regen Power Max
	sc = CANDATA_view->Model_Stator_Current; // Stator Current
	dissipation = CANDATA_view->Model_Dissipation; // Dissipation
	bmc = CANDATA_view->Model_BMS_Max_Charge; // BMS Max Charge
	bmd = CANDATA_view->Model_BMS_MAX_Discharge; // BMS Max Discharge




	//if((rpm != 0) && (sc != 0) && (dissipation != 0) && (bmc != 0) && (bmd != 0)){
		DissipationProgress.setValue(dissipation); // Put Stator Current values into Stator Current Progress Bar

			RegenPowerCircle.setValue(rpm); // Put RegenPowerMax values into RegenPower Progress Circle
			StatorCurrentCircle.setValue(sc); // Put StatorCurrent values into StaturCurrent Progress Circle
	Unicode::snprintf(Regen_Power_Max_TextareaBuffer, REGEN_POWER_MAX_TEXTAREA_SIZE, "%02d", rpm); // Regen Power Max
	Unicode::snprintf(Stator_Current_TextareaBuffer, STATOR_CURRENT_TEXTAREA_SIZE, "%02d", sc); // Stator Current
	Unicode::snprintf(Dissipation_TextareaBuffer, DISSIPATION_TEXTAREA_SIZE, "%02d", dissipation); // Dissipation
	Unicode::snprintf(BMS_Max_Charge_TextareaBuffer, BMS_MAX_CHARGE_TEXTAREA_SIZE, "%02d", bmc); // BMS Max Charge
	Unicode::snprintf(BMS_Max_Discharge_TextareaBuffer, BMS_MAX_DISCHARGE_TEXTAREA_SIZE, "%02d", bmd); // BMS Max Discharge

	Regen_Power_Max_Textarea.invalidate();
	Stator_Current_Textarea.invalidate();
	Dissipation_Textarea.invalidate();
	BMS_Max_Charge_Textarea.invalidate();
	BMS_Max_Discharge_Textarea.invalidate();
	//}

}
