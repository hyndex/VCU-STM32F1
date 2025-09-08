Generic Profiles Mapping

This codebase exposes generic, de-branded names in the parameter UI while retaining the underlying, proven drivers. The table below documents the mapping so existing setups remain understandable.

- VEHMODES
  - Vehicle_A → BMW_E46 profile (src/BMW_E39.cpp with SetE46(true))
  - Vehicle_B → BMW_E6x+ profile (src/BMW_E65.cpp)
  - Vehicle_C → BMW_E39 profile (src/BMW_E39.cpp with SetE46(false))
  - Vehicle_D → Mid-2000s VAG profile (src/Can_VAG.cpp)
  - Vehicle_E → Subaru profile (src/subaruvehicle.cpp)
  - Vehicle_F → BMW_E31 profile (src/BMW_E31.cpp)
  - Classic → Classic analog/IO profile (src/V_Classic.cpp)
  - None → No vehicle integration

- SHIFTERS
  - Shifter_A → BMW_F30 (src/F30_Lever.cpp)
  - Shifter_B → JLR_G1 (src/JLR_G1.cpp)
  - Shifter_C → JLR_G2 (src/JLR_G2.cpp)
  - Shifter_D → BMW_E65 (src/E65_Lever.cpp)

- INVMODES
  - Inverter_A → Leaf_Gen1 (src/leafinv.cpp)
  - Inverter_B → GS450H (src/GS450H.cpp)
  - Inverter_C → Prius_Gen3 (src/GS450H.cpp with SetPrius())
  - Inverter_D → Outlander front (src/outlanderinverter.cpp)
  - Inverter_E → GS300H (src/GS450H.cpp with SetGS300H())
  - Inverter_F → RearOutlander (src/rearoutlanderinverter.cpp)
  - UserCAN → OpenInverter CAN (src/Can_OI.cpp)
  - OpenI → OpenInverter protocol (src/Can_OI.cpp)

- CHGMODS (On-board AC chargers)
  - External_Digital → extCharger (src/extCharger.cpp)
  - Charger_A → Volt/Ampera (src/amperacharger.cpp)
  - Charger_B → Leaf_PDM (src/NissanPDM.cpp)
  - Charger_C → Tesla OI charger (src/teslaCharger.cpp)
  - Charger_D → Outlander OBC (src/outlanderCharger.cpp)
  - Charger_E → Elcon (src/ElconCharger.cpp)

- CHGINT (DC fast charge interfaces)
  - DCFC_A → i3 LIM CCS (src/i3LIM.cpp)
  - DCFC_B → CHAdeMO (src/chademo.cpp)
  - DCFC_C → CPC CCS (src/CPC.cpp)
  - DCFC_D → FOCCCI CCS (src/Foccci.cpp)

- HTTYPE (Cabin heaters)
  - Heater_A → Ampera heater (src/amperaheater.cpp)
  - Heater_B → VW LIN heater (src/VWheater.cpp)
  - Heater_C → Outlander CAN heater (src/OutlanderCanHeater.cpp)

- SHNTYPE (Current/voltage measurement)
  - Shunt_A → ISA shunt (src/isa_shunt.cpp)
  - Shunt_B → BMW SBOX (src/bmw_sbox.cpp)
  - Shunt_C → VAG measurement box (src/Can_VAG.cpp)

- PINFUNCS update
  - TransPump label replaces GS450pump. Functionality unchanged; see utils::GS450hOilPump.

Notes
- Only parameter UI labels changed. No behavior or enumerations were altered.
- Existing configurations continue to work; only the display names differ.
- If you want source-level renames (classes/files), we can phase that next.

