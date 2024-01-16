/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.8.0
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "isr_config.h"
#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// *************************** 例程硬件连接说明 ***************************
// 使用逐飞科技 英飞凌TriCore 调试下载器连接
//      直接将下载器正确连接在核心板的调试下载接口即可
// 使用 USB-TTL 模块连接
//      模块管脚            单片机管脚
//      USB-TTL-RX          查看 zf_common_debug.h 文件中 DEBUG_UART_TX_PIN 宏定义的引脚 默认 P14_0
//      USB-TTL-TX          查看 zf_common_debug.h 文件中 DEBUG_UART_RX_PIN 宏定义的引脚 默认 P14_1
//      USB-TTL-GND         核心板电源地 GND
//      USB-TTL-3V3         核心板 3V3 电源
// 接入正交编码器连接
//      模块管脚            单片机管脚
//      A                   ENCODER_QUADDEC_A 宏定义的引脚 默认 B4
//      B                   ENCODER_QUADDEC_B 宏定义的引脚 默认 B5
//      GND                 核心板电源地 GND
//      3V3                 核心板 3V3 电源
// 接入方向编码器连接
//      模块管脚            单片机管脚
//      LSB                 ENCODER_DIR_PULSE 宏定义的引脚 默认 B6
//      DIR                 ENCODER_DIR_DIR 宏定义的引脚 默认 B7
//      GND                 核心板电源地 GND
//      3V3                 核心板 3V3 电源



// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，单独使用核心板与调试下载器或者 USB-TTL 模块，并连接好编码器，在断电情况下完成连接
// 2.将调试下载器或者 USB-TTL 模块连接电脑，完成上电
// 3.电脑上使用串口助手打开对应的串口，串口波特率为 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义 默认 115200，核心板按下复位按键
// 4.可以在串口助手上看到如下串口信息：
//      ENCODER_QUADDEC counter     x .
//      ENCODER_DIR counter         x .
// 5.转动编码器就会看到数值变化
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查


// **************************** 代码区域 ****************************




#define PWM_CH1                 P02_4                               //电机的两个引脚
#define PWM_CH2                 (ATOM0_CH7_P20_8)

#define PIT0                            (CCU60_CH0 )                            // 使用的周期中断编号
#define ENCODER_DIR                     (TIM6_ENCODER)                         // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE               (TIM6_ENCODER_CH1_P20_3)               // PULSE 对应的引脚
#define ENCODER_DIR_DIR                 (TIM6_ENCODER_CH2_P20_0)               // DIR 对应的引脚

#define UART_INDEX              (DEBUG_UART_INDEX   )                           // 默认 UART_0
#define UART_BAUDRATE           (DEBUG_UART_BAUDRATE)                           // 默认 115200
#define UART_TX_PIN             (DEBUG_UART_TX_PIN  )                           // 默认 UART0_TX_P14_0
#define UART_RX_PIN             (DEBUG_UART_RX_PIN  )                           // 默认 UART0_RX_P14_1
#define TARGET_Velocity 5                       //设置后轮预定速度（单位：cm/s）
#define PERIOD 20                               //设置中断周期 （单位：ms）
int16 encoder_data_dir = 0;                     //编码器数值
int16 motor_speed = 0;                          //后轮当前时刻速度
int16 error_k=0;                                //当前时刻速度误差
int16 error_k_1 = 0;                            //上一时刻速度误差
int16 error_k_2 = 0;                            //上上时刻速度误差
int16 PWM_Output = 0;                           //后轮PWM输出
int16 SERVO_Pwm_Output=0;                       //舵机pwm输出
int16 Motor_direction = 0;                         //后轮方向控制，‘0’代表后轮反转，‘1’代表后轮正转
uint8 uart_get_data[64];                                                        // 串口接收数据缓冲区
uint8 fifo_get_data[64];                                                        // fifo 输出读出缓冲区



/********                        PID三个参数的调节                    ***********/

int16 Kp=1,Ki=0,Kd=0;                           //PID三个参数

/********                        PID三个参数的调节                    ***********/


void Motor_PID_Control(void)          //后轮增量式PID控制PWM输出
{

    error_k = TARGET_Velocity-motor_speed;
    PWM_Output += Kp*(error_k -error_k_1) + Ki*error_k + Kd*(error_k - 2*error_k_1 + error_k_2);
    error_k_2 = error_k_1;
    error_k_1 = error_k;
    if(PWM_Output>=10000)             //防止超出PWM输出限定最大值
        PWM_Output=10000;
    if(PWM_Output<=-10000)
        PWM_Output=-10000;
    if(PWM_Output>=0)                 //PWM输出
    {
        gpio_set_level(PWM_CH1,GPIO_HIGH);
        pwm_set_duty(PWM_CH2, PWM_Output);
    }
    if(PWM_Output<0)
       {
           gpio_set_level(PWM_CH1,GPIO_LOW);
           pwm_set_duty(PWM_CH2, -PWM_Output);
       }
}

void Serial_reactionfun(void)
{
  if(fifo_get_data[9]!='b')
      return;
  if(fifo_get_data[0]==1&&fifo_get_data[1]==1)//速度大于0
      Motor_direction=1;
  else if(fifo_get_data[0]==1&&fifo_get_data[1]==0)//速度小于0
      Motor_direction=0;
  motor_speed = 100*fifo_get_data[2]+10*fifo_get_data[3]+fifo_get_data[4];
  if(Motor_direction==0)
      motor_speed=-motor_speed;
  SERVO_Pwm_Output = 1000*fifo_get_data[5]+100*fifo_get_data[6]+10*fifo_get_data[7]+fifo_get_data[8];
  Motor_PID_Control();                          //电机PWM输出
  pwm_set_duty(ATOM1_CH1_P33_9,SERVO_Pwm_Output);           //舵机PWM输出
}


uint8  get_data = 0;                                                            // 接收数据变量
uint32 fifo_data_count = 0;                                                     // fifo 数据个数

fifo_struct uart_data_fifo;

int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等
    fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);                  // 初始化 fifo 挂载缓冲区
    uart_rx_interrupt(UART_INDEX, 1);                                           // 开启 UART_INDEX 的接收中断
    gpio_init(PWM_CH1,GPO,GPIO_HIGH,GPO_OPEN_DTAIN);                                    // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(ATOM1_CH1_P33_9,50,500);                                           //舵机接口初始化
    pwm_init(PWM_CH2, 17000, 0);
    encoder_dir_init(ENCODER_DIR, ENCODER_DIR_PULSE, ENCODER_DIR_DIR);          // 初始化编码器模块与引脚 带方向增量编码器模式

    pit_ms_init(PIT0, 20);                                                     // 初始化 PIT0 为周期中断 20ms

        uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);             // 初始化串口

    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    uart_rx_interrupt(UART_INDEX, 1);
    while (TRUE)
    {
        // 此处编写需要循环执行的代码
        fifo_data_count = fifo_used(&uart_data_fifo);
        if(fifo_data_count != 0)                                                // 读取到数据了
                {
                    fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // 将 fifo 中数据读出并清空 fifo 挂载的缓冲
                    uart_write_buffer(UART_INDEX, fifo_get_data, fifo_data_count);      // 将读取到的数据发送出去
                    Serial_reactionfun();

                }
                system_delay_ms(10);
        /*printf(" \t\t%d .\r\n", motor_speed);           // 输出后轮当前时刻速度（单位：cm/s）*/


        // 此处编写需要循环执行的代码
    }
}

void uart_rx_interrupt_handler (void)
{
//    get_data = uart_read_byte(UART_INDEX);                                      // 接收数据 while 等待式 不建议在中断使用
    uart_query_byte(UART_INDEX, &get_data);                                     // 接收数据 查询式 有数据会返回 TRUE 没有数据会返回 FALSE
    fifo_write_buffer(&uart_data_fifo, &get_data, 1);                           // 将数据写入 fifo 中
}
IFX_INTERRUPT(uart0_rx_isr, 0, UART0_RX_INT_PRIO)
{
    interrupt_global_enable(0);                     // 开启中断嵌套

    uart_rx_interrupt_handler();                    // 串口接收处理
}
#pragma section all restore
// **************************** 代码区域 ****************************
// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：串口没有数据
//      查看串口助手打开的是否是正确的串口，检查打开的 COM 口是否对应的是调试下载器或者 USB-TTL 模块的 COM 口
//      如果是使用逐飞科技 英飞凌TriCore 调试下载器连接，那么检查下载器线是否松动，检查核心板串口跳线是否已经焊接，串口跳线查看核心板原理图即可找到
//      如果是使用 USB-TTL 模块连接，那么检查连线是否正常是否松动，模块 TX 是否连接的核心板的 RX，模块 RX 是否连接的核心板的 TX
// 问题2：串口数据乱码
//      查看串口助手设置的波特率是否与程序设置一致，程序中 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义为 debug uart 使用的串口波特率
// 问题3：数值一直在正负一跳转
//      不要把方向编码器接在正交编码器模式的接口下
// 问题4：数值不随编码转动变化
//      如果使用主板测试，主板必须要用电池供电
//      检查编码器是否是正常的，线是否松动，编码器是否发热烧了，是否接错线
