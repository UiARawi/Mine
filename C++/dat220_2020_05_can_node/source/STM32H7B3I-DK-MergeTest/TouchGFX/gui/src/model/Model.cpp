#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_fdcan.h"
#include "stm32h7b3xxq.h"

#include <CANClass.hpp>



extern "C" void HAL_NVIC_EnableIRQ(IRQn_Type);
extern "C" void HAL_NVIC_DisableIRQ(IRQn_Type);

/*
   FDCAN1_IT1_IRQn             = 21,     < FDCAN1 Interrupt line 1
   FDCAN1_IT0_IRQn             = 19,     < FDCAN1 Interrupt line 0
 */


extern CAN can;

static int16_t counter = 0;
uint32_t odoc_current = 0;
uint32_t odoc_previous = 0;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	counter++;
	if(counter == 60) // 300 = 5s
	{
		HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
		HAL_NVIC_DisableIRQ(FDCAN1_IT1_IRQn);
		can.switch_decode();

		// Screen 1 (STATUS): {Battery Pack Voltage, Average Cell Voltage, Average Cell Temp, Usable full pack}
		CanData_model ->Model_B_Pack_Voltage = can.B_Pack_Voltage; // Battery pack Voltage
		CanData_model->Model_Neg_Termi_Temp = can.Neg_Termi_Temp; // Temperature at negative terminal
		CanData_model->Model_Usable_Remaining = can.usableRemaining; // Usable Remaining capacity
		CanData_model->Model_Usable_Full_Pack = can.usableFullPack; // Usable Full Capacity

		// Screen 2(HISTORICAL STATS): {Battery Odometer, Nominal Full Pack, Nominal remaining, KWH charge total, KWH discharge total}

		// odometer never decreases, check for less or equal
		if(odoc_current < odoc_previous)
		{
			CanData_model->Model_Battery_Odometer = odoc_previous;
			// Do nothing
		}
		else
		{
			CanData_model->Model_Battery_Odometer = can.Battery_odometer;
			odoc_previous = odoc_current;
			odoc_current = can.Battery_odometer;
		}

		CanData_model->Model_Nominal_Full_Pack = can.Nominal_full_pack; // Nominal Full Pack
		CanData_model->Model_Nom_Energy_Remaining = can.nominalEnergyRemaining; // Norminal Energy Remaining
		CanData_model->Model_KWH_Charge_Total = can.kwhChargeTotal; // Total KWH Charge
		CanData_model->Model_KWH_Discharge_Total = can.kwhDischargeTotal; // Total KWH Discharge

		// Screen 3 (CHARGE/DISCHARGE): {BMS Max Charge, BMS Max Discharge, Dissipation, Regen Power, Energy to charge complete, Ene}
		CanData_model->Model_BMS_Max_Charge = can.BMS_max_charge; // BMS Max charge
		CanData_model->Model_BMS_MAX_Discharge = can.BMS_max_discharge; // BMS Max discharge
		CanData_model->Model_Dissipation = can.Dissipation; // Dissipation / loss
		CanData_model->Model_Regen_Power_Max = can.regenPowerMax; // Regen Power Max
		CanData_model->Model_Stator_Current = can.statorCurrent; // Stator Current

		// Screen 4 (POWER): {PedalPositionA, Drive Power Max, Mech Power, Rear Torque, Battery Pack Current}
		CanData_model->Model_Pedal_Position_A = can.Pedal_position_A; // Pedal Position (0-102%)
		CanData_model->Model_Drive_Power_Max = can.drivePowerMax; // Drive Power
		CanData_model->Model_Mech_Power =can.mechPower; // Mech Power
		CanData_model->Model_Rear_Torque_Measured = can.rear_torque_Measured; // Rear Torque
		CanData_model->Model_Pack_current = can.B_Pack_Current; // Battery Pack Current


		HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
		HAL_NVIC_EnableIRQ(FDCAN1_IT1_IRQn);
		counter = 0;

	      // Second, notify the currently active Presenter that NewCANDataChanged.
	      // The modelListener pointer points to the currently active Presenter.
	      if (modelListener != 0)
	      {
	        modelListener->notifyNewCANDataChanged(CanData_model);
	      }
	}


}

// Returnerer en struct av type canData
//struct canData* Model::getData(){

	//return CanData_model;
//}
