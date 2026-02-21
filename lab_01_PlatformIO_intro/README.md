# Lab 1


## 1. Information about EDA

### 8. PlatformIO version



```bash
pio system info
```

```log
--------------------------  -------------------------------------------
PlatformIO Core             6.1.18
Python                      3.15.0-alpha.5
System Type                 windows_amd64
Platform                    Windows-11
File System Encoding        utf-8
Locale Encoding             utf-8
PlatformIO Core Directory   C:\PioVScPort\platformio
PlatformIO Core Executable  C:\PioVScPort\python\Scripts\platformio.exe
Python Executable           C:\PioVScPort\python\python.exe
Global Libraries            1
Development Platforms       2
Tools & Toolchains          16
--------------------------  -------------------------------------------

*************************************************************************************************************************************************************************
There is a new version 6.1.19 of PlatformIO available.
Please upgrade it via `platformio upgrade` or `python -m pip install -U platformio` command.
Changes: https://docs.platformio.org/en/latest/history.html
*************************************************************************************************************************************************************************
```

### 9. Installed packages

```bash
pio pkg list -g
```

```log
Platforms
├── native @ 1.2.1 (required: platformio/native)
└── ststm32 @ 19.4.0 (required: platformio/ststm32)

Tools
├── contrib-piohome @ 3.4.4 (required: platformio/contrib-piohome)
├── framework-cmsis @ 2.50501.200527 (required: platformio/framework-cmsis)
├── framework-cmsis-stm32f4 @ 2.6.11 (required: platformio/framework-cmsis-stm32f4)
├── framework-cmsis-stm32h7 @ 1.10.6 (required: platformio/framework-cmsis-stm32h7)
├── framework-stm32cubef4 @ 1.28.1 (required: platformio/framework-stm32cubef4)
├── framework-stm32cubeh7 @ 1.12.1 (required: platformio/framework-stm32cubeh7)
├── tool-cppcheck @ 1.21100.230717 (required: platformio/tool-cppcheck)
├── tool-dfuutil @ 1.11.0 (required: platformio/tool-dfuutil)
├── tool-dfuutil-arduino @ 1.11.0 (required: platformio/tool-dfuutil-arduino)
├── tool-ldscripts-ststm32 @ 0.2.0 (required: platformio/tool-ldscripts-ststm32)
├── tool-openocd @ 3.1200.0 (required: platformio/tool-openocd)
├── tool-pvs-studio @ 7.18.59865 (required: platformio/tool-pvs-studio)
├── tool-scons @ 4.40801.0 (required: platformio/tool-scons)
├── tool-stm32duino @ 1.0.2 (required: platformio/tool-stm32duino)
├── tool-stm32flash @ 0.7.0 (required: platformio/tool-stm32flash)
└── toolchain-gccarmnoneeabi @ 1.70201.0 (required: platformio/toolchain-gccarmnoneeabi)

Libraries
└── Unity @ 2.6.0 (required: throwtheswitch/Unity)
```

### 10. Supported devices

```bash
pio boards --installed
```

```log
Platform: ststm32
=========================================================================================================================================================================
ID                           MCU             Frequency    Flash     RAM       Name
---------------------------  --------------  -----------  --------  --------  -------------------------------------------------------
1bitsy_stm32f415rgt          STM32F415RGT    168MHz       1MB       128KB     1Bitsy
acsip_s76s                   STM32L073RZ     32MHz        192KB     20KB      ACSIP S76S
adafruit_feather_f405        STM32F405RGT6   168MHz       1MB       128KB     Adafruit Feather STM32F405
afroflight_f103cb            STM32F103CBT6   72MHz        128KB     20KB      AfroFlight Rev5 (8MHz)
agafia_sg0                   STM32G071RBT6   64MHz        128KB     36KB      Sigma IC AGAFIA SG0
armed_v1                     STM32F407VET6   168MHz       512KB     128KB     3D Printer Controller
armstrap_eagle1024           STM32F417VGT6   168MHz       1MB       192KB     Armstrap Eagle 1024
armstrap_eagle2048           STM32F427VIT6   168MHz       1.99MB    256KB     Armstrap Eagle 2048
armstrap_eagle512            STM32F407VET6   168MHz       512KB     192KB     Armstrap Eagle 512
b96b_aerocore2               STM32F427VIT6   168MHz       1.99MB    256KB     96Boards Neonkey
b96b_argonkey                STM32F412CG     100MHz       1MB       256KB     96Boards Argonkey (STEVAL-MKI187V1)
b96b_f446ve                  STM32F446VET6   168MHz       512KB     128KB     96Boards B96B-F446VE
b96b_neonkey                 STM32F411CE     100MHz       512KB     128KB     96Boards Neonkey
black_f407ve                 STM32F407VET6   168MHz       512KB     128KB     Black STM32F407VE
black_f407vg                 STM32F407VGT6   168MHz       512KB     128KB     Black STM32F407VG
black_f407ze                 STM32F407ZET6   168MHz       512KB     128KB     Black STM32F407ZE
black_f407zg                 STM32F407ZGT6   168MHz       1MB       128KB     Black STM32F407ZG
blackpill_f103c8             STM32F103C8T6   72MHz        64KB      20KB      BlackPill F103C8
blackpill_f103c8_128         STM32F103C8T6   72MHz        128KB     20KB      BlackPill F103C8 (128k)
blackpill_f401cc             STM32F401CCU6   84MHz        256KB     64KB      WeAct Studio BlackPill V2.0 (STM32F401CC)
blackpill_f401ce             STM32F401CEU6   84MHz        512KB     96KB      WeAct Studio BlackPill V3.0 (STM32F401CE)
blackpill_f411ce             STM32F411CEU6   100MHz       512KB     128KB     WeAct Studio BlackPill V2.0 (STM32F411CE)
blue_f407ve_mini             STM32F407VET6   168MHz       512KB     128KB     Blue STM32F407VE Mini
bluepill_f103c6              STM32F103C6T6   72MHz        32KB      10KB      BluePill F103C6
bluepill_f103c8              STM32F103C8T6   72MHz        64KB      20KB      BluePill F103C8
bluepill_f103c8_128k         STM32F103C8T6   72MHz        128KB     20KB      BluePill F103C8 (128k)
blues_cygnet                 STM32L433CCT6   80MHz        256KB     64KB      Blues Cygnet
blues_swan_r5                STM32L4R5ZIY6   120MHz       2MB       640KB     Blues Swan R5
btt_ebb42_v1_1               STM32G0B1RET6   64MHz        128KB     144KB     Big Tree Tech EBB42 V1.1
bw_swan_r5                   STM32L4R5ZIY6   120MHz       2MB       640KB     BluesWireless Swan R5
cicada_l082cz                STM32L082CZY6   32MHz        192KB     20KB      Cicada-L082CZ
cloud_jam                    STM32F401RET6   84MHz        512KB     96KB      RushUp Cloud-JAM
cloud_jam_l4                 STM32L476RGT6   80MHz        1MB       128KB     RushUp Cloud-JAM L4
coreboard_f401rc             STM32F401RCT6   84MHz        256KB     64KB      Core board F401RCT6
cricket_l082cz               STM32L082CZY6   32MHz        192KB     20KB      Cricket-L082CZ
demo_f030f4                  STM32F030F4P6   48MHz        16KB      4KB       Demo F030F4
devebox_h743vitx             STM32H743VIT6   480MHz       2MB       512KB     DevEBox H743VITX
devebox_h750vbtx             STM32H750VBT6   480MHz       512KB     128KB     DevEBox H750VBTX
disco_b_g431b_esc1           STM32G431CBU6   170MHz       128KB     32KB      ST B-G431B-ESC1 Discovery
disco_b_u585i_iot02a         STM32U585AII6Q  160MHz       2MB       256KB     ST B-U585I-IOT02A Discovery
disco_f030r8                 STM32F030R8T6   48MHz        64KB      8KB       ST STM32F0308DISCOVERY
disco_f051r8                 STM32F051R8T6   48MHz        64KB      8KB       ST STM32F0DISCOVERY
disco_f072rb                 STM32F072RBT6   48MHz        128KB     16KB      ST Discovery F072RB
disco_f100rb                 STM32F100RBT6   24MHz        128KB     8KB       ST STM32VLDISCOVERY
disco_f303vc                 STM32F303VCT6   72MHz        256KB     40KB      ST STM32F3DISCOVERY
disco_f334c8                 STM32F334C8T6   72MHz        64KB      12KB      ST 32F3348DISCOVERY
disco_f401vc                 STM32F401VCT6   84MHz        256KB     64KB      ST 32F401CDISCOVERY
disco_f407vg                 STM32F407VGT6   168MHz       1MB       128KB     ST STM32F4DISCOVERY
disco_f411ve                 STM32F411VET6   100MHz       512KB     128KB     ST 32F411EDISCOVERY
disco_f412zg                 STM32F412ZGT6   100MHz       1MB       256KB     32F412GDISCOVERY
disco_f413zh                 STM32F413ZHT6   100MHz       1.50MB    320KB     ST 32F413HDISCOVERY
disco_f429zi                 STM32F429ZIT6   180MHz       2MB       256KB     ST 32F429IDISCOVERY
disco_f469ni                 STM32F469NIH6   180MHz       2MB       384KB     ST 32F469IDISCOVERY
disco_f723ie                 STM32F723IEK6   216MHz       512KB     192KB     32F723EDISCOVERY
disco_f746ng                 STM32F746NGH6   216MHz       1MB       320KB     ST 32F746GDISCOVERY
disco_f750n8                 STM32F750N8H6   216MHz       64KB      340KB     STM32F7508-DK
disco_f769ni                 STM32F769NIH6   216MHz       2MB       512KB     ST 32F769IDISCOVERY
disco_g031j6                 STM32G031J6     64MHz        32KB      8KB       ST STM32G0316-DISCO
disco_g071rb                 STM32G071RBT6   64MHz        128KB     36KB      ST STM32G071B Discovery
disco_h735ig                 STM32H735IGK6   550MHz       1MB       432KB     STM32H735G-DK Discovery kit
disco_h747xi                 STM32H747XIH6   400MHz       2MB       512KB     STM32H747I-DISCO
disco_l053c8                 STM32L053C8T6   32MHz        64KB      8KB       ST 32L0538DISCOVERY
disco_l072cz_lrwan1          STM32L072CZ     32MHz        192KB     20KB      ST DISCO-L072CZ-LRWAN1
disco_l100rc                 STM32L100RCT6   32MHz        256KB     16KB      ST 32L100DISCOVERY
disco_l152rb                 STM32L152RBT6   32MHz        128KB     16KB      ST STM32LDISCOVERY
disco_l475vg_iot01a          STM32L475VGT6   80MHz        1MB       96KB      ST B-L475E-IOT01A Discovery kit
disco_l476vg                 STM32L476VGT6   80MHz        1MB       128KB     ST 32L476GDISCOVERY
disco_l496ag                 STM32L496AGI6   80MHz        1MB       320KB     ST 32L496GDISCOVERY
disco_l4s5i_iot01a           STM32L4S5VIT6   80MHz        2MB       640KB     ST STM32L4+ Discovery kit IoT node
diymore_f407vgt              STM32F407VGT6   168MHz       1MB       128KB     F407VG
ebyte_e77_dev                STM32WLE5CC     48MHz        256KB     64KB      Ebyte E77 Dev Board
econode_l082cz               STM32L082CZY6   32MHz        192KB     20KB      Econode-L082CZ
electrosmith_daisy           STM32H750IBK6   400MHz       128KB     512KB     Electrosmith Daisy
electrosmith_daisy_patch_sm  STM32H750IBK6   400MHz       128KB     512KB     Electrosmith Daisy Patch SM
electrosmith_daisy_petal_sm  STM32H750IBK6   400MHz       128KB     512KB     Electrosmith Daisy Petal SM
elektor_f072c8               STM32F072C8T6   48MHz        64KB      16KB      Elektor LoRa Node Core F072C8 (64 kB)
elektor_f072cb               STM32F072C8T6   48MHz        128KB     16KB      Elektor LoRa Node Core F072C8 (128 kB)
elmo_f411re                  STM32F411RET6   100MHz       512KB     128KB     Espotel LoRa Module
eval_f072vb                  STM32F072VBT6   48MHz        128KB     16KB      STM32F072-EVAL
eval_f107vc                  STM32F107VCT6   72MHz        256KB     64KB      STM3210C-EVAL
eval_f373vc                  STM32F373VCT6   72MHz        256KB     32KB      STM32373C-EVAL
eval_l073z                   STM32L073VZT6   32MHz        192KB     20KB      ST STM32L073Z-EVAL
fk407m1                      STM32F407VET6   168MHz       512KB     128KB     FK407M1
fysetc_s6                    STM32F446VET6   168MHz       512KB     128KB     FYSETC S6
genericSTM32F103C4           STM32F103C4T6   72MHz        16KB      6KB       STM32F103C4 (6k RAM. 16k Flash)
genericSTM32F103C6           STM32F103C6T6   72MHz        32KB      10KB      STM32F103C6 (10k RAM. 32k Flash)
genericSTM32F103C8           STM32F103C8T6   72MHz        64KB      20KB      STM32F103C8 (20k RAM. 64k Flash)
genericSTM32F103CB           STM32F103CBT6   72MHz        128KB     20KB      STM32F103CB (20k RAM. 128k Flash)
genericSTM32F103R4           STM32F103R4T6   72MHz        16KB      6KB       STM32F103R4 (6k RAM. 16k Flash)
genericSTM32F103R6           STM32F103R6T6   72MHz        32KB      10KB      STM32F103R6 (10k RAM. 32k Flash)
genericSTM32F103R8           STM32F103R8T6   72MHz        64KB      20KB      STM32F103R8 (20k RAM. 64 Flash)
genericSTM32F103RB           STM32F103RBT6   72MHz        128KB     20KB      STM32F103RB (20k RAM. 128k Flash)
genericSTM32F103RC           STM32F103RCT6   72MHz        256KB     48KB      STM32F103RC (48k RAM. 256k Flash)
genericSTM32F103RD           STM32F103RDT6   72MHz        384KB     64KB      STM32F103RD (64k RAM. 384k Flash)
genericSTM32F103RE           STM32F103RET6   72MHz        512KB     64KB      STM32F103RE (64k RAM. 512k Flash)
genericSTM32F103RF           STM32F103RFT6   72MHz        768KB     96KB      STM32F103RF (96k RAM. 768k Flash)
genericSTM32F103RG           STM32F103RGT6   72MHz        1MB       96KB      STM32F103RG (96k RAM. 1024k Flash)
genericSTM32F103T4           STM32F103T4U6   72MHz        16KB      6KB       STM32F103T4 (6k RAM. 16k Flash)
genericSTM32F103T6           STM32F103T6U6   72MHz        32KB      10KB      STM32F103T6 (10k RAM. 32k Flash)
genericSTM32F103T8           STM32F103T8U6   72MHz        64KB      20KB      STM32F103T8 (20k RAM. 64k Flash)
genericSTM32F103TB           STM32F103TBU6   72MHz        128KB     20KB      STM32F103TB (20k RAM. 128k Flash)
genericSTM32F103V8           STM32F103V8T6   72MHz        64KB      20KB      STM32F103V8 (20k RAM. 64k Flash)
genericSTM32F103VB           STM32F103VBT6   72MHz        128KB     20KB      STM32F103VB (20k RAM. 128k Flash)
genericSTM32F103VC           STM32F103VCT6   72MHz        256KB     48KB      STM32F103VC (48k RAM. 256k Flash)
genericSTM32F103VD           STM32F103VDT6   72MHz        384KB     64KB      STM32F103VD (64k RAM. 384k Flash)
genericSTM32F103VE           STM32F103VET6   72MHz        512KB     64KB      STM32F103VE (64k RAM. 512k Flash)
genericSTM32F103VF           STM32F103VFT6   72MHz        768KB     96KB      STM32F103VF (96k RAM. 768k Flash)
genericSTM32F103VG           STM32F103VGT6   72MHz        1MB       96KB      STM32F103VG (96k RAM. 1024k Flash)
genericSTM32F103ZC           STM32F103ZCT6   72MHz        256KB     48KB      STM32F103ZC (48k RAM. 256k Flash)
genericSTM32F103ZD           STM32F103ZDT6   72MHz        384KB     64KB      STM32F103ZD (64k RAM. 384k Flash)
genericSTM32F103ZE           STM32F103ZET6   72MHz        512KB     64KB      STM32F103ZE (64k RAM. 512k Flash)
genericSTM32F103ZF           STM32F103ZFT6   72MHz        768KB     96KB      STM32F103ZF (96k RAM. 768k Flash)
genericSTM32F103ZG           STM32F103ZGT6   72MHz        1MB       96KB      STM32F103ZG (96k RAM. 1024k Flash)
genericSTM32F303CB           STM32F303CBT6   72MHz        128KB     32KB      STM32F303CB (32k RAM. 128k Flash)
genericSTM32F373RC           STM32F373RCT6   72MHz        256KB     32KB      STM32F373RC (32k RAM. 256k Flash)
genericSTM32F401CB           STM32F401CBU6   84MHz        128KB     64KB      STM32F401CB (64k RAM. 128k Flash)
genericSTM32F401CC           STM32F401CCU6   84MHz        256KB     64KB      STM32F401CC (64k RAM. 256k Flash)
genericSTM32F401CD           STM32F401CDU6   84MHz        384KB     96KB      STM32F401CD (96k RAM. 384k Flash)
genericSTM32F401CE           STM32F401CEU6   84MHz        512KB     96KB      STM32F401CE (96k RAM. 512k Flash)
genericSTM32F401RB           STM32F401RBT6   84MHz        128KB     64KB      STM32F401RB (64k RAM. 128k Flash)
genericSTM32F401RC           STM32F401RCT6   84MHz        256KB     64KB      STM32F401RC (64k RAM. 256k Flash)
genericSTM32F401RD           STM32F401RDT6   84MHz        384KB     96KB      STM32F401RD (96k RAM. 384k Flash)
genericSTM32F401RE           STM32F401RET6   84MHz        512KB     96KB      STM32F401RE (96k RAM. 512k Flash)
genericSTM32F405RG           STM32F405RGT6   168MHz       1MB       128KB     STM32F405RG (128k RAM. 1024k Flash)
genericSTM32F407IGT6         STM32F407IGT6   168MHz       1MB       128KB     STM32F407IG (192k RAM. 1024k Flash)
genericSTM32F407VET6         STM32F407VET6   168MHz       502.23KB  128KB     STM32F407VE (192k RAM. 512k Flash)
genericSTM32F407VGT6         STM32F407VGT6   168MHz       1MB       128KB     STM32F407VG (128k RAM. 1024k Flash)
genericSTM32F410C8           STM32F410C8T6   100MHz       64KB      32KB      STM32F410C8 (32k RAM. 64k Flash)
genericSTM32F410CB           STM32F410CBT6   100MHz       128KB     32KB      STM32F410CB (32k RAM. 128k Flash)
genericSTM32F410R8           STM32F410R8T6   100MHz       64KB      32KB      STM32F410R8 (32k RAM. 64k Flash)
genericSTM32F410RB           STM32F410RBT6   100MHz       128KB     32KB      STM32F410RB (32k RAM. 128k Flash)
genericSTM32F411CC           STM32F411CCU6   100MHz       256KB     128KB     STM32F411CC (128k RAM. 256k Flash)
genericSTM32F411CE           STM32F411CEU6   100MHz       512KB     128KB     STM32F411CE (128k RAM. 512k Flash)
genericSTM32F411RC           STM32F411RCT6   100MHz       256KB     128KB     STM32F411RC (128k RAM. 256k Flash)
genericSTM32F411RE           STM32F411RET6   100MHz       512KB     128KB     STM32F411RE (128k RAM. 512k Flash)
genericSTM32F412CE           STM32F412CEU6   100MHz       512KB     256KB     STM32F412CE (256k RAM. 512k Flash)
genericSTM32F412CG           STM32F412CGU6   100MHz       1MB       256KB     STM32F412CG (256k RAM. 1024k Flash)
genericSTM32F412RE           STM32F412RET6   100MHz       512KB     256KB     STM32F412RE (256k RAM. 512k Flash)
genericSTM32F412RG           STM32F412RGT6   100MHz       1MB       256KB     STM32F412RG (256k RAM. 1024k Flash)
genericSTM32F413CG           STM32F413CGU6   100MHz       1MB       320KB     STM32F413CG (320k RAM. 1024k Flash)
genericSTM32F413CH           STM32F413CHU6   100MHz       1.50MB    320KB     STM32F413CH (320k RAM. 1536k Flash)
genericSTM32F413RG           STM32F413RGT6   100MHz       1MB       320KB     STM32F413RG (320k RAM. 1024k Flash)
genericSTM32F413RH           STM32F413RHT6   100MHz       1.50MB    320KB     STM32F413RH (320k RAM. 1536k Flash)
genericSTM32F415RG           STM32F415RGT6   168MHz       1MB       128KB     STM32F415RG (128k RAM. 1024k Flash)
genericSTM32F417VE           STM32F417VET6   168MHz       512KB     128KB     STM32F417VE (128k RAM. 512k Flash)
genericSTM32F417VG           STM32F417VGT6   168MHz       1MB       128KB     STM32F417VG (128k RAM. 1024k Flash)
genericSTM32F423CH           STM32F423CHU6   100MHz       1.50MB    320KB     STM32F423CH (320k RAM. 1536k Flash)
genericSTM32F423RH           STM32F423RHT6   100MHz       1.50MB    320KB     STM32F423RH (320k RAM. 1536k Flash)
genericSTM32F446RC           STM32F446RCT6   180MHz       256KB     128KB     STM32F446RC (128k RAM. 256k Flash)
genericSTM32F446RE           STM32F446RET6   180MHz       512KB     128KB     STM32F446RE (128k RAM. 512k Flash)
genericSTM32G431CB           STM32G431CBU6   170MHz       128KB     32KB      STM32G431CB (32k RAM. 128k Flash)
genericSTM32H750VB           STM32H750VBT6   480MHz       128KB     512KB     STM32H750VBT6 (1024k RAM. 128k Flash)
giga_r1_m4                   STM32H747XIH6   480MHz       1MB       287.35KB  Arduino Giga R1 (M4 core)
giga_r1_m7                   STM32H747XIH6   480MHz       768KB     511.35KB  Arduino Giga R1 (M7 core)
gnat_l082cz                  STM32L082CZY6   32MHz        192KB     20KB      Gnat-L082CZ
grasshopper_l082cz           STM32L082CZY6   32MHz        192KB     20KB      Grasshopper-L082CZ
hy_tinystm103tb              STM32F103TBU6   72MHz        128KB     20KB      Tiny STM103T
leafony_ap03                 STM32L452RET6   80MHz        512KB     160KB     Leafony Systems AP03
lora_e5_dev_board            STM32WLE5JC     48MHz        256KB     64KB      SeeedStudio LoRa E5 Dev Board
lora_e5_mini                 STM32WLE5JC     48MHz        256KB     64KB      SeeedStudio LoRa-E5 mini
malyanm200_f070cb            STM32F070CBT6   48MHz        120KB     14.81KB   M200 V2
malyanm200_f103cb            STM32F103CBT6   72MHz        120KB     20KB      Malyan M200 V1
malyanm300_f070cb            STM32F070CBT6   48MHz        120KB     14.81KB   M300
maple                        STM32F103RBT6   72MHz        108KB     17KB      Maple
maple_mini_b20               STM32F103CBT6   72MHz        120KB     20KB      Maple Mini Bootloader 2.0
maple_mini_origin            STM32F103CBT6   72MHz        108KB     20KB      Maple Mini Original
maple_ret6                   STM32F103RET6   72MHz        256KB     48KB      Maple (RET6)
mbed_connect_odin            STM32F439ZIY6   168MHz       2MB       256KB     Mbed Connect Cloud
microduino32_flash           STM32F103CBT6   72MHz        105.47KB  20KB      Microduino Core STM32 to Flash
mkr_sharky                   STM32WB55CG     64MHz        512KB     192KB     MKR Sharky
mote_l152rc                  STM32L152RC     32MHz        256KB     32KB      NAMote72
mtb_ublox_odin_w2            STM32F439ZIY6   168MHz       2MB       256KB     u-blox ODIN-W2
mts_dragonfly_f411re         STM32F411RET6   100MHz       512KB     128KB     MTS Dragonfly
mts_mdot_f405rg              STM32F411RET6   100MHz       512KB     128KB     MultiTech mDot
mts_mdot_f411re              STM32F411RET6   100MHz       512KB     128KB     MultiTech mDot F411
mxchip_az3166                STM32F412ZGT6   100MHz       1MB       256KB     Microsoft Azure IoT Development Kit (MXChip AZ3166)
netduino2plus                STM32F405RGT6   168MHz       1MB       128KB     N2+
nicla_vision                 STM32H747XIH6   480MHz       768KB     511.35KB  Arduino Nicla Vision
nicla_vision_m4              STM32H747XIH6   480MHz       1MB       287.35KB  Arduino Nicla Vision (M4 core)
nucleo_f030r8                STM32F030R8T6   48MHz        64KB      8KB       ST Nucleo F030R8
nucleo_f031k6                STM32F031K6T6   48MHz        32KB      4KB       ST Nucleo F031K6
nucleo_f042k6                STM32F042K6T6   48MHz        32KB      6KB       ST Nucleo F042K6
nucleo_f070rb                STM32F070RBT6   48MHz        128KB     16KB      ST Nucleo F070RB
nucleo_f072rb                STM32F072RBT6   48MHz        128KB     16KB      ST Nucleo F072RB
nucleo_f091rc                STM32F091RCT6   48MHz        256KB     32KB      ST Nucleo F091RC
nucleo_f103rb                STM32F103RBT6   72MHz        128KB     20KB      ST Nucleo F103RB
nucleo_f207zg                STM32F207ZGT6   120MHz       1MB       128KB     ST Nucleo F207ZG
nucleo_f302r8                STM32F302R8T6   72MHz        64KB      16KB      ST Nucleo F302R8
nucleo_f303k8                STM32F303K8T6   72MHz        64KB      12KB      ST Nucleo F303K8
nucleo_f303re                STM32F303RET6   72MHz        512KB     64KB      ST Nucleo F303RE
nucleo_f303ze                STM32F303ZET6   72MHz        512KB     64KB      ST Nucleo F303ZE
nucleo_f334r8                STM32F334R8T6   72MHz        64KB      16KB      ST Nucleo F334R8
nucleo_f401re                STM32F401RET6   84MHz        512KB     96KB      ST Nucleo F401RE
nucleo_f410rb                STM32F410RBT6   100MHz       128KB     32KB      ST Nucleo F410RB
nucleo_f411re                STM32F411RET6   100MHz       512KB     128KB     ST Nucleo F411RE
nucleo_f412zg                STM32F412ZGT6   100MHz       1MB       256KB     ST Nucleo F412ZG
nucleo_f413zh                STM32F413ZHT6   100MHz       1.50MB    320KB     ST Nucleo F413ZH
nucleo_f429zi                STM32F429ZIT6   180MHz       2MB       192KB     ST Nucleo F429ZI
nucleo_f439zi                STM32F439ZIT6   180MHz       2MB       192KB     ST Nucleo F439ZI
nucleo_f446re                STM32F446RET6   180MHz       512KB     128KB     ST Nucleo F446RE
nucleo_f446ze                STM32F446ZET6   180MHz       512KB     128KB     ST Nucleo F446ZE
nucleo_f722ze                STM32F722ZET6   216MHz       512KB     256KB     ST Nucleo F722ZE
nucleo_f746zg                STM32F746ZGT6   216MHz       1MB       320KB     ST Nucleo F746ZG
nucleo_f756zg                STM32F756ZG     216MHz       1MB       320KB     ST Nucleo F756ZG
nucleo_f767zi                STM32F767ZIT6   216MHz       2MB       512KB     ST Nucleo F767ZI
nucleo_g031k8                STM32G031K8     64MHz        64KB      8KB       ST NUCLEO-G031K8
nucleo_g070rb                STM32G070RBT6   64MHz        128KB     36KB      Nucleo G070RB
nucleo_g071rb                STM32G071RBT6   64MHz        128KB     36KB      Nucleo G071RB
nucleo_g0b1re                STM32G0B1RET6   64MHz        512KB     144KB     ST Nucleo G0B1RE
nucleo_g431kb                STM32G431KBT6   170MHz       128KB     32KB      Nucleo G431KB
nucleo_g431rb                STM32G431RBT6   170MHz       128KB     32KB      Nucleo G431RB
nucleo_g474re                STM32G474RET6   170MHz       512KB     128KB     Nucleo G474RE
nucleo_g491re                STM32G491RET6   170MHz       512KB     112KB     Nucleo G491RE
nucleo_h563zi                STM32H563ZIT6U  250MHz       2MB       640KB     ST Nucleo H563ZI
nucleo_h723zg                STM32H723ZGT6   550MHz       1MB       320KB     ST Nucleo H723ZG
nucleo_h743zi                STM32H743ZIT6   400MHz       2MB       512KB     ST Nucleo H743ZI
nucleo_h745zi_q              STM32H745ZIT6   480MHz       1MB       512KB     ST Nucleo H745ZI-Q
nucleo_h753zi                STM32H753ZIT6   400MHz       2MB       512KB     ST Nucleo H753ZI
nucleo_l010rb                STM32L010RBT6   32MHz        128KB     20KB      ST Nucleo L010RB
nucleo_l011k4                STM32L011K4T6   32MHz        16KB      2KB       ST Nucleo L011K4
nucleo_l031k6                STM32L031K6T6   32MHz        32KB      8KB       ST Nucleo L031K6
nucleo_l053r8                STM32L053R8T6   32MHz        64KB      8KB       ST Nucleo L053R8
nucleo_l073rz                STM32L073RZ     32MHz        192KB     20KB      ST Nucleo L073RZ
nucleo_l152re                STM32L152RET6   32MHz        512KB     80KB      ST Nucleo L152RE
nucleo_l412kb                STM32L412KBU6   80MHz        128KB     40KB      ST Nucleo L412KB
nucleo_l412rb_p              STM32L412RBT6P  80MHz        128KB     40KB      ST Nucleo L412RB-P
nucleo_l432kc                STM32L432KCU6   80MHz        256KB     64KB      ST Nucleo L432KC
nucleo_l433rc_p              STM32L433RC     80MHz        256KB     64KB      ST Nucleo L433RC-P
nucleo_l452re                STM32L452RET6   80MHz        512KB     160KB     ST Nucleo L452RE
nucleo_l476rg                STM32L476RGT6   80MHz        1MB       96KB      ST Nucleo L476RG
nucleo_l486rg                STM32L486RGT6   80MHz        1MB       128KB     ST Nucleo L486RG
nucleo_l496zg                STM32L496ZGT6   80MHz        1MB       320KB     ST Nucleo L496ZG
nucleo_l496zg_p              STM32L496ZGT6P  80MHz        1MB       320KB     ST Nucleo L496ZG-P
nucleo_l4r5zi                STM32L4R5ZIT6   120MHz       2MB       640KB     ST Nucleo L4R5ZI
nucleo_l552ze_q              STM32L552ZET6   80MHz        512KB     192KB     ST Nucleo L552ZE-Q
nucleo_u575zi_q              STM32U575ZIT6Q  160MHz       2MB       256KB     ST Nucleo U575ZI-Q
nucleo_wb55rg_p              STM32WB55RG     64MHz        512KB     192KB     P-Nucleo WB55RG
nucleo_wl55jc                STM32WL55JC     48MHz        256KB     64KB      ST Nucleo WL55JC
olimex_e407                  STM32F407ZGT6   168MHz       1MB       128KB     STM32-E407
olimex_f103                  STM32F103RBT6   72MHz        128KB     20KB      Olimex STM32-H103
olimex_h407                  STM32F407ZGT6   168MHz       1MB       128KB     STM32-H407
olimex_p405                  STM32F405RGT6   168MHz       1MB       128KB     Olimex STM32-P405
olimexino                    STM32F103RBT6   72MHz        128KB     20KB      OLIMEXINO-STM32
olimexino_stm32f3            STM32F303RCT6   72MHz        256KB     40KB      Olimex OLIMEXINO-STM32F3
opta                         STM32H747XIH6   480MHz       768KB     511.35KB  Arduino Opta
opta_m4                      STM32H747XIH6   480MHz       1MB       287.35KB  Arduino Opta (M4 core)
piconomix_px_her0            STM32L072RB     32MHz        128KB     20KB      Piconomix PX-HER0
portenta_h7_m4               STM32H747XIH6   480MHz       1MB       287.35KB  Arduino Portenta H7 (M4 core)
portenta_h7_m7               STM32H747XIH6   480MHz       768KB     511.35KB  Arduino Portenta H7 (M7 core)
prntr_v2                     STM32F407VET6   168MHz       512KB     128KB     PrntrBoard V2
pybstick26_duino             STM32F072RB     48MHz        128KB     16KB      PYBSTICK26 Duino
pybstick26_lite              STM32F401CEU6   84MHz        512KB     96KB      PYBStick Lite 26
pybstick26_pro               STM32F412RE     100MHz       512KB     256KB     PYBStick 26 Pro
pybstick26_std               STM32F411CEU6   100MHz       512KB     128KB     PYBStick Standard 26
rak811_tracker               STM32L151RBT6   32MHz        128KB     16KB      RAK811 LoRa Tracker
rak811_tracker_32            STM32L151RBT6   32MHz        128KB     32KB      RAK811 LoRa Tracker
remram_v1                    STM32F765VIT6   216MHz       2MB       512KB     3D printer controller
rhf76_052                    STM32L051C8T6   32MHz        64KB      8KB       RHF76 052
rhombio_l476dmw1k            STM32L476VGT6   80MHz        1MB       128KB     L476DMW1K
robotdyn_blackpill_f303cc    STM32F303CCT6   72MHz        256KB     40KB      BlackPill F303CC
rumba32_f446ve               STM32F446RET6   180MHz       512KB     128KB     3D Printer control board
rymcu_f407ve                 STM32F407VET6   168MHz       502.23KB  128KB     RYMCU STM32F407VE (192k RAM. 512k Flash)
rymcu_nebulapi_f103ve        STM32F103VET6   72MHz        512KB     64KB      RYMCU Nebula Pi F103VE (64k RAM. 512k Flash)
sakuraio_evb_01              STM32F411RET6   100MHz       1MB       128KB     sakura.io Evaluation Board
seeedArchMax                 STM32F407VET6   168MHz       512KB     192KB     Seeed Arch Max
silica_sensor_node           STM32L476JG     80MHz        1MB       128KB     ST Sensor Node
sparkfun_micromod_f405       STM32F405RGT6   168MHz       1MB       128KB     SparkFun MicroMod STM32F405
sparky_v1                    STM32F303CCT6   72MHz        256KB     40KB      Sparky V1 F303
st3dp001_eval                STM32F401VET6   84MHz        512KB     96KB      3DP001V1 Evaluation board for 3D printer
steval_fcu001v1              STM32F401CCU6   84MHz        256KB     64KB      STEVAL-FCU001V1 Flight controller unit evaluation board
steval_mksboxv1              STM32L4R9ZI     120MHz       2MB       640KB     SensorTile.box
stm32f4stamp                 STM32F405RGT6   168MHz       1MB       128KB     STM32F4Stamp F405
storm32_v1_31_rc             STM32F103RCT6   72MHz        256KB     48KB      STorM32 BGC v1.31 RC
thunder_pack                 STM32L072KZ     32MHz        192KB     20KB      ThunderPack v1.0
thunder_pack_f411            STM32F411CEU6   100MHz       512KB     128KB     ThunderPack v1.1+
ublox_c030_n211              STM32F437VG     180MHz       1MB       256KB     u-blox C030-N211 IoT Starter Kit
ublox_c030_r410m             STM32F437VG     180MHz       1MB       256KB     u-blox C030-R410M IoT
ublox_c030_u201              STM32F437VG     180MHz       1MB       256KB     u-blox C030-U201 IoT Starter Kit
ublox_evk_odin_w2            STM32F439ZIY6   168MHz       2MB       256KB     u-blox EVK-ODIN-W2
vake_v1                      STM32F446RET6   180MHz       512KB     128KB     VAkE v1.0
vccgnd_f103zet6              STM32F103ZET6   72MHz        512KB     64KB      VCCGND F103ZET6 Mini
vccgnd_f407zg_mini           STM32F407ZGT6   168MHz       1MB       128KB     VCCGND F407ZGT6 Mini
waveshare_open103z           STM32F103ZET6   72MHz        512KB     64KB      Waveshare Open103Z
we_oceanus1                  STM32WLE5CCU6   48MHz        256KB     64KB      WE Oceanus-I Module
we_oceanus1_ev               STM32WLE5CCU6   48MHz        256KB     64KB      WE Oceanus-I EV
weact_mini_h743vitx          STM32H743VIT6   480MHz       2MB       512KB     WeAct Studio MiniSTM32H743VITX
weact_mini_h750vbtx          STM32H750VBT6   480MHz       512KB     128KB     WeAct Studio MiniSTM32H750VBTX
wio_3g                       STM32F439VI     180MHz       2MB       256KB     Seeed Wio 3G
wraith32_v1                  STM32F051K6     48MHz        32KB      7.75KB    Wraith V1 ESC
xdot_l151cc                  STM32L151CCU6   32MHz        256KB     32KB      MultiTech xDot
```

## 2. Project creation

Initialize project

```bash
pio project init
```


## 5. Run project for a native platform

### Building a project (with verbose flag)

```bash
pio run -e helloworld -v
```

```bash         
Processing helloworld (build_type: debug; build_src_filter: +<helloworld/*.c>; platform: native; build_flags: -O0, -std=c11, -Wall; lib_extra_dirs: C:\PioVScPort\platformio\lib)
----------------------------------------------------------------------------------------------------------------------------------------------
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 4 compatible libraries
Scanning dependencies...
No dependencies
Building in debug mode
gcc -o .pio\build\helloworld\src\helloworld\helloworld.o -c -std=c11 -Wall -Og -g2 -ggdb2 -DPLATFORMIO=60118 -D__PLATFORMIO_BUILD_DEBUG__ -Iinclude -Isrc src\helloworld\helloworld.c
gcc -o .pio\build\helloworld\program.exe -Og -g2 -ggdb2 .pio\build\helloworld\src\helloworld\helloworld.o -L.pio\build\helloworld
======================================================== [SUCCESS] Took 2.17 seconds ========================================================
```

#### Compilation

```bash
gcc -o .pio\build\helloworld\src\helloworld\helloworld.o -c -std=c11 -Wall -Og -g2 -ggdb2 -DPLATFORMIO=60118 -D__PLATFORMIO_BUILD_DEBUG__ -Iinclude -Isrc src\helloworld\helloworld.c;
```

* `-o .pio\build\helloworld\src\helloworld\helloworld.o` - output object file;

* `-c` - use compiler and assembler only (create object file);

* `-std=c11` - use C11 language standart;

* `-Wall` - Turn on almost all warnings;

* `-Og` - optimization level;

* `-g2` - save debug information;

* `-ggdb2` - extended debug info special for gdb;

* `-DPLATFORMIO=60118` - PIO version macro definition;

* `-D__PLATFORMIO_BUILD_DEBUG__` - debug macro definition;

* `-Iinclude`, `-Isrc` - including directiories `include` and `src`;

* `src\helloworld\helloworld.c` - target file to be compiled;

#### Linking

```bash
gcc -o .pio\build\helloworld\program.exe -Og -g2 -ggdb2 .pio\build\helloworld\src\helloworld\helloworld.o -L.pio\build\helloworld
```

* `-o .pio\build\helloworld\program.exe` - Output executable file (result of linker);

* `-L.pio\build\helloworld` - path to libraries for linking

### Run a project (with verbose flag)

```bash
pio run -e helloworld -t exec -v
```

```bash
Processing helloworld (build_type: debug; build_src_filter: +<helloworld/*.c>; platform: native; build_flags: -O0, -std=c11, -Wall; lib_extra_dirs: C:\PioVScPort\platformio\lib)
----------------------------------------------------------------------------------------------------------------------------------------------
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 4 compatible libraries
Scanning dependencies...
No dependencies
Building in debug mode
.pio\build\helloworld\program.exe

Hello, world!
======================================================== [SUCCESS] Took 0.54 seconds ========================================================
```

## Libraries creating and including

```bash
pio run -e helloworld -t exec -v
```

```bash
Processing helloworld (build_type: debug; build_src_filter: +<helloworld/*.c>; platform: native; build_flags: -O0, -std=c11, -Wall; lib_extra_dirs: C:\PioVScPort\platformio\lib)
--------------------------------------------------------------------------------------------------------------------------------------
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 5 compatible libraries
Scanning dependencies...
Dependency Graph
|-- dynlist (License: Unknown, Path: D:\Study\mcu-and-embedded-systems\lab_01_PlatformIO_intro\lib\dynlist)
Building in debug mode
gcc -o .pio\build\helloworld\src\helloworld\helloworld.o -c -std=c11 -Wall -Og -g2 -ggdb2 -DPLATFORMIO=60118 -D__PLATFORMIO_BUILD_DEBUG__ -Iinclude -Isrc -Ilib\dynlist src\helloworld\helloworld.c
ar rc .pio\build\helloworld\lib0ed\libdynlist.a .pio\build\helloworld\lib0ed\dynlist\dynlist.o
ranlib .pio\build\helloworld\lib0ed\libdynlist.a
gcc -o .pio\build\helloworld\program.exe -Og -g2 -ggdb2 .pio\build\helloworld\src\helloworld\helloworld.o -L.pio\build\helloworld -Wl,--start-group .pio\build\helloworld\lib0ed\libdynlist.a -Wl,--end-group
.pio\build\helloworld\program.exe
Student said: 
Hello, World!
==================================================== [SUCCESS] Took 2.04 seconds ====================================================
```

### Compilation

* Added path `-Ilib\dynlist` for finding header files for `dynlist` lib;

### Static lib creation

`ar rc .pio\build\helloworld\lib0ed\libdynlist.a .pio\build\helloworld\lib0ed\dynlist\dynlist.o`

* `ar` - GNU Archiver;

* `rc` - replace, create;

* `.pio\build\helloworld\lib0ed\libdynlist.a` - name of archive;

* `.pio\build\helloworld\lib0ed\dynlist\dynlist.o` - object file which used in archive;

`ranlib .pio\build\helloworld\lib0ed\libdynlist.a`

* `ranlib` - this tool generates index (symbol table) to archive for better perfomance of linking;

### Linking

* `-Wl,--start-group`, `-Wl,--end-group` - options that sent to linker;

* `.pio\build\helloworld\lib0ed\libdynlist.a` - resulting file of static lib;

## 8-9. Unit tests

* Add unit tests

* Add custom test runner

* Run test

```bash
pio test -e helloworld -v
```

```bash
Collected 1 tests (native/test_dynlist)

Processing native/test_dynlist in helloworld environment
------------------------------------------------------------------------------------------------------------------------------------------
Building...


Testing...
test\native\test_dynlist\test_dynlist.c:78:test_dynlist_new_created_empty:PASS
test\native\test_dynlist\test_dynlist.c:79:test_dynlist_free_called_clean_callback:PASS
test\native\test_dynlist\test_dynlist.c:80:test_dynlist_append_data_in_place:PASS
test\native\test_dynlist\test_dynlist.c:81:test_dynlist_foreach_called:PASS

-----------------------
4 Tests 0 Failures 0 Ignored
OK

--------------------------------------- helloworld:native/test_dynlist [PASSED] Took 1.43 seconds --------------------------------------- 

================================================================ SUMMARY ================================================================ 
Environment    Test                 Status    Duration
-------------  -------------------  --------  ------------
helloworld     native/test_dynlist  PASSED    00:00:01.433
=============================================== 4 test cases: 4 succeeded in 00:00:01.433 ===============================================
```

### Byte order 

Little-endian

## 10. Debugging

## 11. Static Code Analysis

```ini
[env:helloworld] ; Working environment for 'hello world' programm
build_type = debug ; Enable debug symbols
build_src_filter = +<helloworld/*.c> ; Source files directory ./src/helloworld
debug_test = native/test_dynlist
check_tool = cppcheck
check_flags = cppcheck:--enable=all
    --suppress=unusedFunction
    --suppress=unmatchedSuppression
check_src_filters =
    +<src/helloworld/*.c>
    +<lib/dynlist/src/*.c>
```

```bash
pio check -e helloworld
```

```bash
Checking helloworld > cppcheck (platform: native)
------------------------------------------------------------------------------------------------------------------------------------------
src\helloworld\helloworld.c:2: [low:information] Include file: <stdio.h> not found. Please note: Cppcheck does not need standard library headers to get proper results. [missingIncludeSystem]
======================================================= [PASSED] Took 0.05 seconds =======================================================

Component        HIGH    MEDIUM    LOW
--------------  ------  --------  -----
src\helloworld    0        0        1

Total             0        0        1

Environment    Tool      Status    Duration
-------------  --------  --------  ------------
helloworld     cppcheck  PASSED    00:00:00.048
====================================================== 1 succeeded in 00:00:00.048 ====================================================== 
```

## Practical task 

Доработать библиотеку dynlist, добавив в неё функцию для удаления узла из списка и вставки
нового узла в список. Проверьте решение тестами и код программы статическим анализатором.
```c
/**
* @brief Удалить узел из списка
* @param list список
* @param node узел, который необходимо удалить
*/
void dynlist_remove(Dynlist list, DynlistNode* node);
/* Вставить узел со значением *value после узал pos*/
void dynlist_insert(Dynlist list, DynlistNode* pos, void* value);
```
Написать тесты для проверки работы созданной функции. Проверить решение тестами и
статическим анализатором.


### UB examples

#### Dereferencing a pointer that has not yet been definitely initialized

```c
int* ptr;
*ptr = 100;
```

#### Dereferencing a NULL pointer

```c
int* ptr = 0;
*ptr = 100;
```

### MISRA rules example
|Check Id| Check Name|Supported|  Category|
|-| -| -| -|
| MISRA23_9.3 | 9.3 Arrays shall not be partially initialized | Yes | Required |
| MISRA23_13.6 | 13.6 The operand of the sizeof operator shall not contain any expression which has potential side effects | Yes | Mandatory |
| MISRA23_2.3 | 2.3 A project should not contain unused type declarations | Yes | Advisory |
| MISRA23_4.2 | 4.2 Trigraphs should not be used | Yes | Advisory |