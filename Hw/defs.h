#ifndef DEFS_H
#define DEFS_H

#include "Hw/addr.h"
#include "Hw/scb.h"
#include "Hw/systick.h"
#include "Hw/gpio.h"
#include "Hw/uart.h"
#include "Hw/systemtimer.h"
#include "Hw/Device/flash.h"
#include "Hw/Device/ram.h"

namespace Hw {
constexpr std::uint32_t HCLK = UINT32_C(16'000'000);
using SystemControlBlockRegBase = SCBRegisters<SCB_BASE>;
using uCSystemControlBlock = SystemControlBlock<SystemControlBlockRegBase>;
using uCSysTickRegisters = SysTickRegisters<SysTick_BASE>;
using uCSysTickTimer = SysTickTimer<uCSysTickRegisters,
                                    HCLK,
                                    UINT32_C(1000)>;
using uCSystemTimer = SystemTimer<uCSysTickTimer>;

using GpioBankA = Hw::GpioConfig::Bank<GPIOA_BASE, Hw::uCRcc::gpioBankIndex::A>;
using GpioBankB = Hw::GpioConfig::Bank<GPIOB_BASE, Hw::uCRcc::gpioBankIndex::B>;
using GpioBankC = Hw::GpioConfig::Bank<GPIOC_BASE, Hw::uCRcc::gpioBankIndex::C>;
using GpioBankI = Hw::GpioConfig::Bank<GPIOI_BASE, Hw::uCRcc::gpioBankIndex::I>;

using gpioA9  = Hw::Gpio<GpioBankA, Hw::GpioConfig::bit9>;
using gpioB7  = Hw::Gpio<GpioBankB, Hw::GpioConfig::bit7>;
using gpioI1  = Hw::Gpio<GpioBankI, Hw::GpioConfig::bit1>;
using gpioC6  = Hw::Gpio<GpioBankC, Hw::GpioConfig::bit6>;
using gpioC7  = Hw::Gpio<GpioBankC, Hw::GpioConfig::bit7>;
using gpioI11 = Hw::Gpio<GpioBankI, Hw::GpioConfig::bit11>;

using Uart1RegBase = Hw::UartRegisters<USART1_BASE, Hw::uCRcc::uartIndex::Uart1>;
using Uart6RegBase = Hw::UartRegisters<USART6_BASE, Hw::uCRcc::uartIndex::Uart6>;

using Uart1 = Hw::Uart<Uart1RegBase,
                       HCLK,
                       gpioB7,
                       gpioA9,
                       GpioConfig::AF7,
                       GpioConfig::AF7>;

using Uart6 = Hw::Uart<Uart6RegBase,
                       HCLK,
                       gpioC7,
                       gpioC6,
                       GpioConfig::AF8,
                       GpioConfig::AF8>;

// Sector 0 is reserved for the bootloader. By not including it on the available sectors
//   we make sure it is never erased nor written.
// You should also enable write protection on the option bytes to make sure that the target
//   application doesn't erase the bootloader.
constexpr auto availableSectors = static_cast<Hw::Device::FlashSector>(
            Hw::Device::FlashSector1 |
            Hw::Device::FlashSector2 |
            Hw::Device::FlashSector3 |
            Hw::Device::FlashSector4 |
            Hw::Device::FlashSector5 |
            Hw::Device::FlashSector6 |
            Hw::Device::FlashSector7);
using uCFlash = Hw::Device::Flash<FLASH_R_BASE, FLASH_BASE, availableSectors>;

// The last 120 K of SRAM are reserved for the bootloader
using uCRam = Hw::Device::Ram<RAMDTCM_BASE, 200 * 1024>;
}

#endif // DEFS_H
