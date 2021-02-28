/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef POWERSCREENVIEWBASE_HPP
#define POWERSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/powerscreen_screen/PowerScreenPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>

class PowerScreenViewBase : public touchgfx::View<PowerScreenPresenter>
{
public:
    PowerScreenViewBase();
    virtual ~PowerScreenViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Image image1;
    touchgfx::Button button1;
    touchgfx::TextAreaWithOneWildcard FpsScreen4;
    touchgfx::CircleProgress PedalPositionCircleProgress;
    touchgfx::PainterRGB888 PedalPositionCircleProgressPainter;
    touchgfx::TextAreaWithOneWildcard Pedal_Position_Textarea;
    touchgfx::CircleProgress DrivePowerCircleProgress;
    touchgfx::PainterRGB888 DrivePowerCircleProgressPainter;
    touchgfx::TextAreaWithOneWildcard Drive_Power_Max_Textarea;
    touchgfx::CircleProgress MechPowerCircleProgress;
    touchgfx::PainterRGB888 MechPowerCircleProgressPainter;
    touchgfx::TextAreaWithOneWildcard Mech_Power_Textarea;
    touchgfx::CircleProgress RearTorqueCircleProgress;
    touchgfx::PainterRGB888 RearTorqueCircleProgressPainter;
    touchgfx::TextAreaWithOneWildcard Rear_Torque_Textarea;
    touchgfx::TextAreaWithOneWildcard Pack_Current_Textarea;

    /*
     * Wildcard Buffers
     */
    static const uint16_t FPSSCREEN4_SIZE = 10;
    touchgfx::Unicode::UnicodeChar FpsScreen4Buffer[FPSSCREEN4_SIZE];
    static const uint16_t PEDAL_POSITION_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Pedal_Position_TextareaBuffer[PEDAL_POSITION_TEXTAREA_SIZE];
    static const uint16_t DRIVE_POWER_MAX_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Drive_Power_Max_TextareaBuffer[DRIVE_POWER_MAX_TEXTAREA_SIZE];
    static const uint16_t MECH_POWER_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Mech_Power_TextareaBuffer[MECH_POWER_TEXTAREA_SIZE];
    static const uint16_t REAR_TORQUE_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Rear_Torque_TextareaBuffer[REAR_TORQUE_TEXTAREA_SIZE];
    static const uint16_t PACK_CURRENT_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Pack_Current_TextareaBuffer[PACK_CURRENT_TEXTAREA_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<PowerScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // POWERSCREENVIEWBASE_HPP
