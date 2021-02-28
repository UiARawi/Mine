/*
 * CanDataStruct.hpp
 *
 *  Created on: 16. nov. 2020
 *      Author: panse
 */

#ifndef CANDATASTRUCT_HPP_
#define CANDATASTRUCT_HPP_

struct canData{

       	 /* Screen 1 (STATUS) */
       		uint16_t Model_B_Pack_Voltage;  // Battery pack Voltage
       		uint16_t Model_Neg_Termi_Temp; // Temperature at negative terminal
       		uint16_t Model_Usable_Remaining;  // Usable Remaining capacity
       		uint16_t Model_Usable_Full_Pack;  // Usable full capacity

       		/* Screen 2 (HISTORICAL STATS)*/
       		uint32_t Model_Battery_Odometer;
       		uint16_t Model_Nominal_Full_Pack;
       		uint16_t Model_Nom_Energy_Remaining;
       		uint16_t Model_KWH_Charge_Total;
       		uint16_t Model_KWH_Discharge_Total;

       		/* Screen 3 (CHARGE/DISCHARGE) */
       		uint32_t Model_BMS_Max_Charge;
       		uint32_t Model_BMS_MAX_Discharge;
       		uint16_t Model_Dissipation;
       		uint16_t Model_Regen_Power_Max;
       		uint16_t Model_Stator_Current;

       		/* Screen 4 (POWER) */
       		uint16_t Model_Pedal_Position_A;
       		uint16_t Model_Drive_Power_Max;
       		int16_t Model_Mech_Power;
       		uint16_t Model_Rear_Torque_Measured;
       		int32_t Model_Pack_current;

       };




#endif /* CANDATASTRUCT_HPP_ */
