#include <gui/powerscreen_screen/PowerScreenView.hpp>

PowerScreenView::PowerScreenView()
{
	 this -> pp = 0; // Pedal Position
	 this -> dp = 0; // Drive Power
	 this -> mp = 0; // Mech power
	 this -> rt = 0; // Rear torque
	 this -> pc = 0; // Pack Current

     this -> frameSkippedCounter = 0;
     this -> frames = 0;
     this->fps = 0;
}

void PowerScreenView::setupScreen()
{
    PowerScreenViewBase::setupScreen();
    fps = 0;
    updateFPS();
}

void PowerScreenView::tearDownScreen()
{
    PowerScreenViewBase::tearDownScreen();
}

void PowerScreenView::handleTickEvent()
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

void PowerScreenView::updateFPS()
{
    Unicode::snprintf(FpsScreen4Buffer, FPSSCREEN4_SIZE, "%d", fps);
    FpsScreen4.invalidate();
}

void PowerScreenView::setData(struct canData* CANDATA_view)
{
	pp = CANDATA_view->Model_Pedal_Position_A; // Pedal Position
	dp = CANDATA_view->Model_Drive_Power_Max; // Drive Power
	mp = CANDATA_view->Model_Mech_Power; // Mech Power
	rt = CANDATA_view->Model_Rear_Torque_Measured; // Rear Torque
	pc = CANDATA_view->Model_Pack_current; // Pack Current


	//if((pp != 0) && (dp != 0) && (mp != 0) && (rt != 0) && (pc != 0)){
	PedalPositionCircleProgress.setValue(pp); // Set the value of the progress circle of Pedal Position
	DrivePowerCircleProgress.setValue(dp); // Set the value of the progress circle of Drive Power
	MechPowerCircleProgress.setValue(mp); // Set the value of the progress circle of Mech Power
	RearTorqueCircleProgress.setValue(rt); // Set the value of the progress circle of Rear Torque

	Unicode::snprintf(Pedal_Position_TextareaBuffer, PEDAL_POSITION_TEXTAREA_SIZE, "%02d", pp); // Regen Power Max
	Unicode::snprintf(Drive_Power_Max_TextareaBuffer, DRIVE_POWER_MAX_TEXTAREA_SIZE, "%02d", dp); // Stator Current
	Unicode::snprintf(Mech_Power_TextareaBuffer, MECH_POWER_TEXTAREA_SIZE, "%02d", mp); // Dissipation
	Unicode::snprintf(Rear_Torque_TextareaBuffer, REAR_TORQUE_TEXTAREA_SIZE, "%02d", rt); // BMS Max Charge
	Unicode::snprintf(Pack_Current_TextareaBuffer, PACK_CURRENT_TEXTAREA_SIZE, "%02d", pc); // BMS Max Discharge

	Pedal_Position_Textarea.invalidate();
	Drive_Power_Max_Textarea.invalidate();
	Mech_Power_Textarea.invalidate();
	Rear_Torque_Textarea.invalidate();
	Pack_Current_Textarea.invalidate();
	//}

}
