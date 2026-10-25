# NUCLEO-C542RC 四实验 Demo

基于 ST **NUCLEO-C542RC**（STM32C542RCT6，Arm Cortex-M33，144 MHz）的四个入门实验，使用 **STM32CubeMX2 + CMake + GCC** 开发。

> 详细图文教程：[Markdown](docs/STM32C5_NUCLEO-C542RC_4Labs.md) · [PDF](docs/STM32C5_NUCLEO-C542RC_4Labs.pdf)

## 实验列表

| 实验 | 目录 | 内容 |
|---|---|---|
| 1. GPIO | `Lab1_GPIO_Board` | PA5 驱动 LD1 闪烁；PC13 读取 B1，20 ms 消抖，按键暂停/恢复闪烁 |
| 2. UART | `Lab2_UART` | USART2 115200 8N1；开机信息打印、字符回显、发送 `1`/`0` 控制 LD1 |
| 3. TIM | `Lab3_TIM` | TIM6 更新中断每 500 ms 翻转 PA5，LED 周期 1 秒 |
| 4. 低功耗 | `Lab4_LowPower` | PC13 EXTI13 上升沿唤醒；Sleep 模式，按键唤醒后 LED 快闪 |

每个实验目录包含：

- `*.ioc2`：STM32CubeMX2 工程
- `*_cmake/`：生成的 CMake 工程（`main.c`、`generated/`、驱动、CMake 配置）
- `*_cmake/build/`：已编译的产物（含 `.elf`、`.map`、`.o` 等，便于直接查看/复现）

## 板载资源

| 功能 | 引脚 / 接口 | 说明 |
|---|---|---|
| 用户 LED LD1 | PA5 | 高电平点亮 |
| 用户按键 B1 | PC13 | 按下为高电平，板载 10 kΩ 下拉 |
| 虚拟串口 VCP | USART2：PA2=TX，PA3=RX | 115200 8N1，STLINK-V3EC 提供 |
| 下载 / 调试 / 供电 | CN1（USB Type-C） | STLINK-V3EC |

## 开发环境

- STM32CubeMX2 1.1.2
- VS Code + STM32CubeIDE for Visual Studio Code
- GNU Tools for STM32 14.3.1、CMake、Ninja
- STLINK-V3EC 驱动与调试服务

## 编译与烧录

进入任意 `*_cmake` 目录后：

```powershell
# 配置
cube cmake --preset debug_GCC_NUCLEO-C542RC

# 编译（也可以在 VS Code 里按 F7）
cube cmake --build --preset debug_GCC_NUCLEO-C542RC

# 烧录（以 Lab2 为例）
cube programmer -c port=SWD -w .\build\debug_GCC_NUCLEO-C542RC\Lab2_UART.elf -v -rst
```

也可以在 VS Code 中打开 `*_cmake` 目录，选择 `debug_GCC_NUCLEO-C542RC` 预设，按 `F7` 编译、`F5` 调试。

### 烧录常见问题

如果 `cube programmer` 报 `DEV_CONNECT_ERR`，通常是 VS Code 的 ST-LINK 调试服务占用了探针。先结束调试（`Shift+F5`），或在任务管理器结束：

- `ST-LINK_gdbserver.exe`
- `stlinkserver.exe`

然后重新执行烧录命令。

## 说明

- Lab3 的 TIM6 参数（PSC=14399、ARR=4999）在 `main.c` 中显式设置，因为 CubeMX2 生成的是默认值 PSC=0、ARR=0xFFFF。
- PC13 只能配置为输入或 EXTI，不能配置为输出低电平，否则按下 B1 会短路。
- `build/` 中包含本机编译产物和部分本地路径信息，仅用于演示和复现参考；重新编译会覆盖。

## 作者

Yangyuheng1021
