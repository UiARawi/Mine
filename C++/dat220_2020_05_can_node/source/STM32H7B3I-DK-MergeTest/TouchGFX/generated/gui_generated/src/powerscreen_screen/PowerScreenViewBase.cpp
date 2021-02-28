/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/powerscreen_screen/PowerScreenViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

PowerScreenViewBase::PowerScreenViewBase() :
    buttonCallback(this, &PowerScreenViewBase::buttonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_DARK_BACKGROUNDS_MAIN_BG_TEXTURE_480X272PX_ID));

    button1.setXY(0, 112);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_ICONS_BACK_ARROW_48_ID), touchgfx::Bitmap(BITMAP_DARK_ICONS_BACK_ARROW_48_ID));
    button1.setAction(buttonCallback);

    FpsScreen4.setPosition(0, 0, 80, 21);
    FpsScreen4.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 0, 0));
    FpsScreen4.setLinespacing(0);
    Unicode::snprintf(FpsScreen4Buffer, FPSSCREEN4_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID46).getText());
    FpsScreen4.setWildcard(FpsScreen4Buffer);
    FpsScreen4.setTypedText(touchgfx::TypedText(T_SINGLEUSEID35));

    PedalPositionCircleProgress.setXY(56, 3);
    PedalPositionCircleProgress.setProgressIndicatorPosition(0, 0, 184, 94);
    PedalPositionCircleProgress.setRange(0, 100);
    PedalPositionCircleProgress.setCenter(92, 92);
    PedalPositionCircleProgress.setRadius(82);
    PedalPositionCircleProgress.setLineWidth(16);
    PedalPositionCircleProgress.setStartEndAngle(-90, 90);
    PedalPositionCircleProgress.setCapPrecision(180);
    PedalPositionCircleProgress.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_LARGE_CIRCLE_INDICATOR_BG_LINE_HALF_ID));
    PedalPositionCircleProgressPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(32, 159, 78));
    PedalPositionCircleProgress.setPainter(PedalPositionCircleProgressPainter);
    PedalPositionCircleProgress.setValue(0);

    Pedal_Position_Textarea.setPosition(53, 97, 190, 21);
    Pedal_Position_Textarea.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    Pedal_Position_Textarea.setLinespacing(0);
    Unicode::snprintf(Pedal_Position_TextareaBuffer, PEDAL_POSITION_TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID37).getText());
    Pedal_Position_Textarea.setWildcard(Pedal_Position_TextareaBuffer);
    Pedal_Position_Textarea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID36));

    DrivePowerCircleProgress.setXY(262, 3);
    DrivePowerCircleProgress.setProgressIndicatorPosition(0, 0, 184, 94);
    DrivePowerCircleProgress.setRange(0, 400);
    DrivePowerCircleProgress.setCenter(92, 92);
    DrivePowerCircleProgress.setRadius(82);
    DrivePowerCircleProgress.setLineWidth(16);
    DrivePowerCircleProgress.setStartEndAngle(-90, 90);
    DrivePowerCircleProgress.setCapPrecision(180);
    DrivePowerCircleProgress.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_LARGE_CIRCLE_INDICATOR_BG_LINE_HALF_ID));
    DrivePowerCircleProgressPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(32, 159, 78));
    DrivePowerCircleProgress.setPainter(DrivePowerCircleProgressPainter);
    DrivePowerCircleProgress.setValue(0);

    Drive_Power_Max_Textarea.setPosition(259, 99, 187, 19);
    Drive_Power_Max_Textarea.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    Drive_Power_Max_Textarea.setLinespacing(0);
    Unicode::snprintf(Drive_Power_Max_TextareaBuffer, DRIVE_POWER_MAX_TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID39).getText());
    Drive_Power_Max_Textarea.setWildcard(Drive_Power_Max_TextareaBuffer);
    Drive_Power_Max_Textarea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID38));

    MechPowerCircleProgress.setXY(56, 122);
    MechPowerCircleProgress.setProgressIndicatorPosition(0, 0, 184, 94);
    MechPowerCircleProgress.setRange(0, 400);
    MechPowerCircleProgress.setCenter(92, 92);
    MechPowerCircleProgress.setRadius(82);
    MechPowerCircleProgress.setLineWidth(16);
    MechPowerCircleProgress.setStartEndAngle(-90, 90);
    MechPowerCircleProgress.setCapPrecision(180);
    MechPowerCircleProgress.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_LARGE_CIRCLE_INDICATOR_BG_LINE_HALF_ID));
    MechPowerCircleProgressPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(32, 159, 78));
    MechPowerCircleProgress.setPainter(MechPowerCircleProgressPainter);
    MechPowerCircleProgress.setValue(0);

    Mech_Power_Textarea.setPosition(53, 216, 190, 20);
    Mech_Power_Textarea.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    Mech_Power_Textarea.setLinespacing(0);
    Unicode::snprintf(Mech_Power_TextareaBuffer, MECH_POWER_TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID41).getText());
    Mech_Power_Textarea.setWildcard(Mech_Power_TextareaBuffer);
    Mech_Power_Textarea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID40));

    RearTorqueCircleProgress.setXY(262, 122);
    RearTorqueCircleProgress.setProgressIndicatorPosition(0, 0, 184, 94);
    RearTorqueCircleProgress.setRange(0, 700);
    RearTorqueCircleProgress.setCenter(92, 92);
    RearTorqueCircleProgress.setRadius(82);
    RearTorqueCircleProgress.setLineWidth(16);
    RearTorqueCircleProgress.setStartEndAngle(-90, 90);
    RearTorqueCircleProgress.setCapPrecision(180);
    RearTorqueCircleProgress.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_LARGE_CIRCLE_INDICATOR_BG_LINE_HALF_ID));
    RearTorqueCircleProgressPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(32, 159, 78));
    RearTorqueCircleProgress.setPainter(RearTorqueCircleProgressPainter);
    RearTorqueCircleProgress.setValue(0);

    Rear_Torque_Textarea.setPosition(259, 216, 187, 20);
    Rear_Torque_Textarea.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    Rear_Torque_Textarea.setLinespacing(0);
    Unicode::snprintf(Rear_Torque_TextareaBuffer, REAR_TORQUE_TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID45).getText());
    Rear_Torque_Textarea.setWildcard(Rear_Torque_TextareaBuffer);
    Rear_Torque_Textarea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID42));

    Pack_Current_Textarea.setPosition(90, 244, 300, 21);
    Pack_Current_Textarea.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    Pack_Current_Textarea.setLinespacing(0);
    Unicode::snprintf(Pack_Current_TextareaBuffer, PACK_CURRENT_TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID44).getText());
    Pack_Current_Textarea.setWildcard(Pack_Current_TextareaBuffer);
    Pack_Current_Textarea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID43));

    add(image1);
    add(button1);
    add(FpsScreen4);
    add(PedalPositionCircleProgress);
    add(Pedal_Position_Textarea);
    add(DrivePowerCircleProgress);
    add(Drive_Power_Max_Textarea);
    add(MechPowerCircleProgress);
    add(Mech_Power_Textarea);
    add(RearTorqueCircleProgress);
    add(Rear_Torque_Textarea);
    add(Pack_Current_Textarea);
}

void PowerScreenViewBase::setupScreen()
{

}

void PowerScreenViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Interaction1
        //When button1 clicked change screen to ChargeDischargeScreen
        //Go to ChargeDischargeScreen with screen transition towards East
        application().gotoChargeDischargeScreenScreenSlideTransitionEast();
    }
}
