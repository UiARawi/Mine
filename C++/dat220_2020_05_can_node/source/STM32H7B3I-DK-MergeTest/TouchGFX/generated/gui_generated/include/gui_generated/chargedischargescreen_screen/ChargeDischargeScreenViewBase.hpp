/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef CHARGEDISCHARGESCREENVIEWBASE_HPP
#define CHARGEDISCHARGESCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/chargedischargescreen_screen/ChargeDischargeScreenPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/progress_indicators/BoxProgress.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>

class ChargeDischargeScreenViewBase : public touchgfx::View<ChargeDischargeScreenPresenter>
{
public:
    ChargeDischargeScreenViewBase();
    virtual ~ChargeDischargeScreenViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Image image1;
    touchgfx::TextAreaWithOneWildcard fpsScreen3;
    touchgfx::TextAreaWithOneWildcard BMS_Max_Charge_Textarea;
    touchgfx::TextAreaWithOneWildcard BMS_Max_Discharge_Textarea;
    touchgfx::BoxProgress DissipationProgress;
    touchgfx::TextAreaWithOneWildcard Dissipation_Textarea;
    touchgfx::TextAreaWithOneWildcard Regen_Power_Max_Textarea;
    touchgfx::TextAreaWithOneWildcard Stator_Current_Textarea;
    touchgfx::Button ButtonBack;
    touchgfx::Button ButtonNext;
    touchgfx::CircleProgress RegenPowerCircle;
    touchgfx::PainterRGB888 RegenPowerCirclePainter;
    touchgfx::CircleProgress StatorCurrentCircle;
    touchgfx::PainterRGB888 StatorCurrentCirclePainter;

    /*
     * Wildcard Buffers
     */
    static const uint16_t FPSSCREEN3_SIZE = 10;
    touchgfx::Unicode::UnicodeChar fpsScreen3Buffer[FPSSCREEN3_SIZE];
    static const uint16_t BMS_MAX_CHARGE_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar BMS_Max_Charge_TextareaBuffer[BMS_MAX_CHARGE_TEXTAREA_SIZE];
    static const uint16_t BMS_MAX_DISCHARGE_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar BMS_Max_Discharge_TextareaBuffer[BMS_MAX_DISCHARGE_TEXTAREA_SIZE];
    static const uint16_t DISSIPATION_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Dissipation_TextareaBuffer[DISSIPATION_TEXTAREA_SIZE];
    static const uint16_t REGEN_POWER_MAX_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Regen_Power_Max_TextareaBuffer[REGEN_POWER_MAX_TEXTAREA_SIZE];
    static const uint16_t STATOR_CURRENT_TEXTAREA_SIZE = 10;
    touchgfx::Unicode::UnicodeChar Stator_Current_TextareaBuffer[STATOR_CURRENT_TEXTAREA_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<ChargeDischargeScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

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

#endif // CHARGEDISCHARGESCREENVIEWBASE_HPP